Unity 是 Canonical 公司替 Ubuntu 作業系統所開發，是執行在 GNOME 之上的桌面 shell，使用大部分 GNOME 應用程式，從 Ubuntu 11.04 開始作為預設的桌面環境。

autostart
http://askubuntu.com/questions/48321/how-do-i-start-applications-automatically-on-login

## start YouTube in full screen automatically on login
1. 設為自動登入
1. `sudo apt install xdotool` #安裝 xdotool
1. 新增檔案 ~/bin/auto_youtube.sh
```
#! /bin/sh
DISPLAY=:0
firefox https://www.youtube.com/watch?v=t7D4bUk7lq4 &
sleep 6
xdotool key f
sleep 3
xdotool key f
```
1. chmod +x ~/bin/auto_youtube.sh
1. 左上角尋找「初始啟動程式」或... 點開「已安裝」找「初始應用程式」
1. 關閉恢復上一次的瀏覽狀況
	1. Firefox 網址列輸入 about:config (會出現 "隨便亂搞會讓保固失效！" 的警告文字。選「我發誓，我一定會小心的！」。
	1. 搜尋「browser.sessionstore.resume_from_crash」雙擊設成 false。

參考：https://support.mozilla.org/zh-TW/kb/restore-previous-session#w_ogdaiaau

## 延伸閱讀
* 什麼是 GNOME 之上的桌面 shell？
