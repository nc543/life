## Lubuntu 16.10
### Fcitx 無法選字
安裝後預設的漢字輸入法是 Fctix 新酷音，會出現黑框無法選字。
解法
1. 「開始功能表」→「偏好設定」→「Fcitx設定」→ 左方「附加元件」→取消勾選「Kimpanel」→ 重新登入
	* Kimpanel 是 KDE 輸入法面板
1. 「開始功能表」→「偏好設定」→「LXSession的預設應用程式」→ 左方「自動啟動」→取消勾選「Fcitx Qt IMPanel」→ 重新登入
1. `sudo apt-get install qml-module-qtquick2`
1. 改用 hime
1. 改用 ibus-chewing

參考
1. https://www.ubuntu-tw.org/modules/newbb/viewtopic.php?post_id=353834
1. http://smpsfox.blogspot.tw/2016/06/ubuntufcitx.html
1. http://goodjack.blogspot.tw/2013/08/linux-phonetic-setting.html
1. http://lirobo.blogspot.tw/2014/07/lubuntu.html

## 家目錄漢文目錄名稱改為英文
`LANG=C xdg-user-dirs-gtk-update`勾選「Don't ask me this again」，然後按「Update Names」
