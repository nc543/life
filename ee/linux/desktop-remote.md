# 遠端桌面

## AnyDesk
有免安裝版本

## TeamViewer
使用遠端的 ID 及密碼連線，輕易穿越防火牆

遠端
* Linux TeamViewer QuickSupport
* Linux TeamViewer
* Android TeamViewer Host

近端
* Linux TeamViewer
* Android TeamViewer

## Chrom Remote Desktop
開啟的 Linux 遠端是一個 Virtual Desktop，不是原本的桌面

## NX
[NoMachine](http://www.nomachine.com) 的遠端桌面技術使用高效率的壓縮和 buffer，處理低頻寬高延遲的網路連接。

可選擇哪個 Desktop Session

### FreeNX
[FreeNX](http://freenx.berlios.de/)： NX 伺服器的免費實作。NX 可使用很慢的連線，例如 Modem 或 ISDN，連 X-connections。聽說比 VNC, remotedesktop 好，讓你感覺不到延遲。
* [Ubuntu Server 與 Windows 系統的遠端桌面遙控 by FreeNX](http://www.kenming.idv.tw/ubuntu-server_windows-os_remote-desktop-control_by-freenx)：機器是 ION HTPC，螢幕是 40" Sony (40Z5500) 液晶螢幕，平常只有 XMBC 超傻瓜級的多媒體控制介面，方便只需要 MCE (Microsoft Media Center Edition) 遙控器就可以控制。
* ssh

安裝參考 [Ubuntu help 的 FreeNX](https://help.ubuntu.com/community/FreeNX)

遠端：server，套件是 freenx
近端：client，套件是 nxclient
要先安裝 ssh

### X2go
基於 NX 的遠程桌面伺服器和客戶端。

## ssh -X
ssh 登入後執行 GUI 程式，視窗會傳回近端 X-Server

## 延伸閱讀
* [How is TeamViewer so fast?](http://stackoverflow.com/questions/9498877) -- 2012 的文章
* [7 of the best Linux remote desktop clients](http://www.techradar.com/news/software/applications/7-of-the-best-linux-remote-desktop-clients-716346) -- 2016.2 的文章
* [[Linux] 使用 NoMachine 連上 CentOS 7 現有的 X-Window session](http://ephrain.pixnet.net/blog/post/59627479)
* 協議？ (比如 RDP、RFB、NX)
