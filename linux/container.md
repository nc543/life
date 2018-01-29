## 虛擬化的技術

虛擬化技術將應用程式所需的執行環境獨立打包起來，方便在不同的硬體中移動。
有兩種打包方式，一種包含作業系統，另一種不含作業系統。

傳統虛擬化技術 (如 vSphere 或 Hyper-V 等) 建立一個可以用來執行整套作業系統的獨立執行環境，所以習慣稱為虛擬機器 (Virtual Machine, VM)。打包應用程式所需的執行環境需要包含作業系統 (Guest OS)。

Container 則是以應用程式為中心，共用同一個作業系統，將一個應用程式所需的相關程式碼、函式庫、環境配置檔都打包起來建立沙箱執行環境。相對於 VM，Container 是輕量級的虛擬化技術。


Docker 是唯讀的 Image (映像檔)，執行後產生 Container (容器)，是每個獨立分離的 instance，會在 Image 上面建立可以寫入的層級。Container 可以 run、start、stop、rm。

## Container 相關技術

* 1982 Unix 的 chroot
* 1998 FreeBSD 的 jails
* 2004 Windows 的Sandboxie
* 2005 Solaris Zones 和 OpenVZ
* LXC
* 2013 Container 標準化的平臺 Docker

## Container OS
專為大量部署 Container 的專用型作業系統，移除不必要的 Linux 系統程式和元件，只保留 OS 核心和 Container 所需執行環境，以及管理工具。

## Container 的應用

傳統慣用的應用程式 (Monolithic Application) 會將所有功能都放入這隻程式中執行，當要擴充效能時，需要把同一隻程式複製到多個機器上執行。。

而微服務則是藉由許多小型獨立執行的服務組合成一套應用程式，可以各自擴充效能，而不用複製一整套的應用程式。

微服務架構需要管理大量 Process，Docker 可將這些小程式打包放到 Docker 平臺執行並可用 Docker 工具管理。

## 延伸閱讀
* [Docker 初學筆記 - 基本指令操作教學](https://blog.longwin.com.tw/2017/01/docker-learn-initial-command-cheat-sheet-2017/)
* Registry 倉庫 (Public / Private) https://hub.docker.com/
