# procd -- OpenWrt 的 init 及 udev
[procd 原始碼](http://git.openwrt.org/project/procd.git)包括 OpenWrt 使用的套件 procd、procd-ujail、procd-seccomp、procd-nand、procd-nand-firstboot。

procd 取代傳統 Linux 使用的 init 及 udev

這裡只談 procd 套件，包括二進位程式 init、procd、askfirst、udevtrigger，shell 腳本 reload_config 跟 procd.sh，以及 hotplug json 檔 hotplug-preinit.json 及 hotplug.json。

Linux userspace 開機動作：init → preinit → procd

## init
在 OpenWrt 開機，Linux 最後會執行腳本 /etc/preinit [註1]，但現在一開始就先插隊執行 init，然後才執行原本的 preinit，最後交棒給 procd 繼續執行。 

一開始 PREINIT 沒設，執行 init  取代自己
```
[ -z "$PREINIT" ] && exec /sbin/init
```

1. `ulog_open(ULOG_KMSG, LOG_DAEMON, "init")`： 設定 log 方式
1. SIGTERM、SIGUSR1、SIGUSR2 的處置是 sa_shutdown
1. `early()`：掛載檔案系統及設定環境變數
1. `cmdline()`：讀取 Linux 指令行參數 init_debug 設定 debug 等級。
1. `watchdog_init(1)`：初始化 watchdog，使用 /dev/watchdog
1. fork() 執行 `/sbin/kmodloader /etc/modules-boot.d/` 載入一些 kernel 模組，並等候結束
1. fork() 執行 `/sbin/procd -h /etc/hotplug-preinit.json` 處理事件
	* 載入韌體：使用 /sbin/hotplug-call
	* failsafe 按鍵：執行 /etc/rc.button/failsafe 產生 /tmp/failsafe_button
1. fork() 執行 `PREINIT=1 /bin/sh /etc/preinit`，執行 [preinit](http://lirobo.blogspot.tw/2012/10/openwrt-preinit.html) 原本該跑的腳本，結束時執行
	1. 如果 hotplug-preinit.json 還在跑，殺了他。
	1. 如果檔案 /tmp/sysupgrade 存在，就一直睡吧不往下執行了 (等候 reboot 嗎?) 
	1. 清掉環境變數 INITRAMFS、PREINIT
	1. 設環境變數 WDTFD 交出 watchdog file descriptor
	1. 交接除錯等級
	1. 改為繼續執行 /sbin/procd

註1： 在 OpenWrt 開機，Linux 最後會執行腳本 /etc/preinit (`try_to_run_init_process("/etc/preinit")`@init/main.c → do_execve()@fs/exec.c)， 執行時會檢查檔案開頭決定何種執行檔，腳本需要以 #! 開頭 (load_script()@fs/binfmt_script.c)，/etc/preinit 使用的直譯器是 busybox sh

## procd
procd 其實可看成是兩個程式，有加 -h 參數是當作 hotplug daemon (hotplug_run())，否則

1. 繼承除錯等級或重設，並設定 log 方式
1. `setsid()`：建立新 session 並成為 process goup leader，且成為 process group 唯一的成員，使用 process ID 作為 session ID 及 process group ID，回傳 session ID。no controlling terminal。如果已經是 process group leader，則回傳 -1 且 errno 為 EPERM。
1. `procd_signal()`：signal 的處置
	* SIGTERM、SIGINT、SIGUSR1、SIGUSR2：sa_shutdown
	* SIGSEGV、SIGBUS：sa_crash
	* SIGHUP、SIGKILL、SIGSTOP：sa_dummy
1. 如果不是第 1 個 process，一秒後連結到 ubus，否則進入以下 state
1. STATE_EARLY
	1. 設定 watchdog timeout
	1. hotplug(/etc/hotplug.json) 事件處理
	1. fork() 執行 `udevtrigger`，結束 ... 進入下個 state
1. STATE_UBUS
	1. 重開 /dev/console stdin/stdout/stderr
	1. ubus timeout：ubus 連上後最後進入下個 state
	1. service_start_early()
1. STATE_INIT
	1. LOG("- init -\n");
	1. `procd_inittab()`：讀取 inittab 建立 actions 列表 (id:run-level:action:process)
		* process 切出 argv
		* 除了 sysinit 及 shutdown 外，可以有多個
	1. `procd_inittab_run("respawn")`：
	1. `procd_inittab_run("askconsole")`
	1. `procd_inittab_run("askfirst")`
	1. `procd_inittab_run("sysinit")`：依序執行 /etc/rc.d/ 下 S 開始的腳本中的 boot() 部份
	1. `ulog_open(ULOG_SYSLOG, LOG_DAEMON, "procd")`：切換到 syslog
1. STATE_RUNNING：沒做什麼事，只是 log 完成 init
1. STATE_SHUTDOWN：shutdown 時進入，依序執行 /etc/rc.d/ 下 K 開始的腳本中的 shutdown() 部份
1. STATE_HALT

sysinit 跟 shutdown 都是執行 /etc/rc.d/ 下的腳本，這些腳本通常是依所要執行的順序連結到 /etc/init.d/ 下的腳本，在 inittab 可能的內容如下：
```
::sysinit:/etc/init.d/rcS S boot
::shutdown:/etc/init.d/rcS K shutdown
```

在 procd 會用 glob() 取出所有 /etc/rc.d/S* 的檔案，全部加到 [libubox runqueue](http://lirobo.blogspot.tw/2014/07/libubox-runqueue.html) 去執行。

## askfirst
用在 inittab

## udevtrigger

## procd.sh
共用腳本函數，當 init 腳本使用 procd 方式時 (USE_PROCD=1) 使用。

OpenWrt 的 init 腳本通常透過 /etc/rc.common 執行，在開機時是執行 shell function  boot()，而 boot() 預設是執行 start()。在傳統方式，由 init 腳本提供 start() 功能，但當使用 procd 方式時則改提供 start_service()。


old     | procd
--------|-------
start() |start_service() 至少要提供 json command 的部份
stop()  |已採用 procd_kill 停止程式，stop_service()
reload()|如有 reload_service() 則執行，不然執行 start()
        |running()
        |trace()

使用 procd 方式的特別之處
* 所有引數會打包成 json 格式，透過 ubus 送給 procd
	* command
	* respawn
	* ...
* service_triggers() 可用 procd_add_reload_trigger() 登記哪些設定檔改變後執行 reload_config 需要重新執行。可用 procd_add_network_trigger() 登記網路改變作為重啟的 trigger

範例：package/network/services/dnsmasq

詳情見 OpenWrt package/base-files/files/etc/rc.common。
rc.common 會載入 /lib/functions.sh (一些共同的函數，包括 config_ 開頭的函數)、/lib/config/uci.sh (uci_ 開頭存取 uci 的函數)、及 /lib/functions/service.sh (使用 busybox start-stop-daemon 提供 service_ 開頭的函數)。

## reload_config
configd 完成前的臨時替代方案，
檢查設定有改變則呼叫 `ubus call service event { "type": "config.change", "data": { "package": "設定檔名" }}`

開機時會產生設定檔的 MD5 checksum 存在記憶體，更改設定後執行 reload_config 會自動重啟相關的程式。

## hotplug-preinit.json 及 hotplug.json。

## 延伸閱讀
* [Linux ELF 檔載入過程](http://wthung2.blogspot.tw/2010/03/linux-elf.html)
* ubox, ubus, mount_root
* list_add_tail()
