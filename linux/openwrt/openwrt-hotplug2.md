hotplug2 是輕巧版的 udev，在 OpenWrt 已經由 procd 取代。

程式 /sbin/hotplug2 會常駐，連結到 netlink socket 讀取 uevent，變數拿來跟每個規則比對，符合的就執行對應的指令。


規則比對有 "==" 及 "!=" 檢查字串是否相等、"~~" 及 "!~" 執行正規表示式比對、"is set" 及 "is unset" 檢查有無此變數。每個規則可以有多項比對用「,」隔開，接著是以 { } 包起來的指令。指令也可以有多個，可執行的指令有：
* print <text>：印訊息
* print-event [rule label]：印出整個 event。If the rule label is provided, it is printed along with the rule.
* setenv <key> <value>：設定環境變數
* remove <file>：移除檔案
* chown <owner> <file>：改變檔案的擁有者
* chgrp <group> <file>：改變檔案的群組
* chmod <mode> <file>：改變檔案的存取模式
* run <command>：使用 system() 執行 shell 指令
* exec <command> [arg1 [arg2 [... [argn]]]]：直接執行指令
* mknod <filepath> <mode>：建立 device node (使用 MAJOR, MINOR 及 SUBSYSTEM 變數)
* load-firmware <firmware directory>：載入存在 <firmware directory> 的韌體，需要 FIRMWARE 變數
* serialize [socket:]：
* next-event：跳到下個 event，也就是不比對接下來的規則。
* branch-event [success]：如果上個指令執行失敗 (或成功)，跳到下個 event。
* branch-rule [success]：如果上個指令執行失敗 (或成功)，跳出此規則，繼續比對接下來的規則。

最後三個是流程控制。

在 [preinit](http://lirobo.blogspot.tw/2012/10/openwrt-preinit.html) 時，規則是 /etc/hotplug2-init.rules，如果是按鍵 (SUBSYSTEM == button) 就「kill -USR1 1」。

在 init 的 boot 時，規則會改設為 /etc/hotplug2-init.rules，會再包含 /etc/hotplug2-platform.rules 及 /etc/hotplug2-common.rules。這些規則有一部分會去執行 /sbin/hotplug-call，第一個參數是 SUBSYSTEM 變數值或 firmware，會去執行 /etc/hotplug.d/$1/ 下所有的程式

在 [preinit](http://lirobo.blogspot.tw/2012/10/openwrt-preinit.html) 時， 如果沒有 devfs，則執行
    /sbin/hotplug2 --set-worker /lib/hotplug2/worker_fork.so --set-rules-file /etc/hotplug2-init.rules --no-persistent --set-coldplug-cmd /sbin/udevtrigger
    /sbin/hotplug2 --set-worker /lib/hotplug2/worker_fork.so --set-rules-file /etc/hotplug2-init.rules --persistent &
在 init 的 boot
/sbin/hotplug2 --override --persistent --set-rules-file /etc/hotplug2.rules --set-coldplug-cmd /sbin/udevtrigger --max-children 1 >/dev/null 2>&1 &

疑問：
* hotplug 跟 hotplug2 的關係？

參考來源：
1. https://wiki.openwrt.org/doc/techref/hotplug
1. hotplug2 原始碼
1. OpenWrt 原始碼

延伸閱讀：
* devtmpfs
* devfs
* udev
* [mdev](http://lirobo.blogspot.tw/2010/04/mdev.html) (busybox 的簡化版 udev)
* [hotplug](http://lirobo.blogspot.tw/2010/04/linux-hotplug.html) ()

