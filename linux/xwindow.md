# X Window 系統

英文字母 X 順序排在 W(indow) 後面，意思是下一版新視窗

歷史
...

X 圖形使用者介面軟體採用網路主從式架構，包括 X 伺服器、X 用戶端、及 X 協定三個部份。X 伺服器提供 X 視窗系統中的輸出及輸入服務，也就是管理顯示卡、螢幕、鍵盤、滑鼠等這些硬體，通常位在使用者操作的電腦。X 用戶端就是各種 X 應用程式，例如 xterm、xeyes 等，透過 X 協定接收 X 伺服器的輸入，並將所要呈現的畫面傳給 X 伺服器繪製出來。

X 伺服器跟 X 客戶端可以執行在相同或不同的機器上。要注意的是，一般認知的伺服器在遠端，用戶端在近端。就 X 客戶端而言，X 伺服器是在遠端沒錯。但就使用者而言，X 視窗系統剛好相反。X 伺服器通常是使用者操作的電腦，是在近端；而 X 客戶端未必在使用者電腦，可能在其它電腦而在遠端，稱 X 應用程式或 X 應用較不會搞混。

視窗管理員 (Window Manager)：
一個基本 X 視窗系統只需要一個 X 應用程式連結到一個 X 伺服器，當 X 應用程式增多，需要一個特殊 X 應用程式來控制視窗位置、外觀與行為，這就是視窗管理員。

顯示管理員 (Display Manager)，又稱登入管理員 (Login Manager)：提供 GUI 登入環境，登入後載入使用者選擇的視窗管理員、語系等，可視為 getty 或 login 程式的圖形版。有 XFree86 的 xdm (X Display Manager)、GNOME 的 gdm、KDE 的 kdm、LigitDM、LXDM 等。

桌面環境 (Desktop Environments) 可以說是一套有一致外觀界面的 GUI 軟體元件，包括視窗管理員、面板、系統功能表、啟動程式，及一些預設的 X 應用，例如檔案管理員、終端程式、瀏覽器、編輯器等。常見的桌面環境有 Gnome、KDE、Xfce 等，依開發的工具套件 (toolkit) 可分成 GTK 跟 Qt 兩大陣營。

啟動 X 要先執行 X Server，然後執行 X Client

一台電腦可以有多個 X 系統同時啟動，對應到各自的顯示界面

在文字介面底下啟動 X 時，直接使用 startx 來找到 X server 與 X client 的參數或設定檔， 然後再呼叫 xinit 來啟動 X 視窗系統。xinit 先載入 X server 到預設的 :0 這個顯示介面，然後再載入 X client 到這個 X 顯示介面上。而 X client 通常就是 GNOME 或 KDE ，這兩個設定也能夠在 /etc/sysconfig/desktop 裡面作好設定。


有兩種啟動的方式，一是透過 Display Manager 啟動，然後使用者在一個 GUI 畫面登入。另一是使用者在文字界面登入後，一般是執行 startx 來啟動 X。startx 是 xinit 的 shell script wrapper。

## Lubuntu
使用 [LightDM](https://wiki.ubuntu.com/LightDM)，讀取 /etc/lightdm/lightdm.conf.d/20-lubuntu.conf 內容是
```
[SeatDefaults]
user-session=Lubuntu
```
對應到 /usr/share/xsessions/Lubuntu.desktop，其內容是
```
[Desktop Entry]
Name=Lubuntu
Comment=Lubuntu - Lightweight X11 desktop environment based on LXDE
Exec=/usr/bin/lxsession -s Lubuntu -e LXDE
Type=Application
```

參考資料與延伸閱讀
1. 傲笑紅塵路：[簡介X Window 系統(An Introduction to the X Window System)](http://www.lijyyh.com/2015/12/x-window-introduction-to-x-window-system_17.html)
1. http://linux.vbird.org/linux_basic/0590xwindow.php
1. http://www.tldp.org/HOWTO/XWindow-User-HOWTO/runningx.html
1. XDMCP
1. Windows 上的 X 伺服器
	1. xming：最新版本需要捐贈才能下載，舊版則與新版顯示管理程式和桌面環境有相容性問題。
	1. VcXsrv
1. OS X 上的 X 伺服器：XQuartz
1. 跟 tty 的關係
1. 新的顯示協定：Wayland、Mir
