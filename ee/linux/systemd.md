# systemd
systemd 是 Linux  a system and service manager。
當作為第一個行程 (PID 1) 執行時，如同 init brings up 及維護 userspace services.

為了相容 SysV，如果用名子 init 來執行 systemd 且 PID 不為 1，會執行 telinit 來 Change SysV runlevel。

       When run as a system instance, systemd interprets the configuration
       file system.conf and the files in system.conf.d directories; when run
       as a user instance, systemd interprets the configuration file user.conf
       and the files in user.conf.d directories. See systemd-system.conf(5)
       for more information.

採用 systemd 代替原來的System V

將系統初始化要進行的每件事情抽象為一個設定單元 (unit)，提供對應的設定檔給系統管理員維護。單元有下列類型
* service (伺服器服務): mysql.service, auditd.service
* socket
* device
* mount
* automount
* swap
* target (目標，類似於執行等級)：multi-user.target
* timer
* snapshot
* path

與 System V 的 init 比較：
* 採用 Socket 啟用式與 D-Bus 啟用式服務，以提高相互依賴的各服務的並列執行效能；
* 用 cgroups 取代行程 ID 來追蹤行程，以此即使是兩次 fork 之後生成的守護行程也不會脫離systemd的控制。
* 內建檔案系統掛載功能
* 用 target 代替 System V 的執行級別 (Runlevel)，例如 graphical.target 相當於 System V 的 init 5，multi-user.target 相當於 System V的init 3。
* 內建新的 journald 日誌管理系統取代 syslog，使用 journalctl 查看。
* 引入localectl、timedatectl等新命令，系統配置更方便。

fanotify

## 服務啟用及停用
使用 `systemctl`
http://askubuntu.com/questions/19320/how-to-enable-or-disable-services

##
http://lirobo.blogspot.tw/2015/02/systemd.html
