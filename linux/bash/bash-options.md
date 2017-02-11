# Options 選項
選項有單字元跟多字元兩類，多字元選項必須放在單字元選項前面。

單字元選項可使用內建指令 [set](builtin-set.md) 支援的單字元選項外，還可以用下列選項：
* -c：選項後第一個引數作為指令執行。之後如有引數從 $0 開始指定。(注意：不是從 $1 開始指定) $0 作為 shell 名稱，用在 warning 及 error 訊息。
* -i：interactive
* -l 或 --login：invoke 為 login shell (見 INVOCATION)
* -r：見 [RESTRICTED SHELL](restricted-shell.md)
* -s 或選項後沒有引數：從標準輸入讀取指令，這個選項讓 interactive shell 可以設定位置參數。
* -D 或 --dump-strings：在標準輸出印出所有 preceded by $ 的雙引號字串，當 locale 不為 C 或 POSIX 時會做語言轉換。隱含 -n 選項，不執行指令。
* [-+]O [shopt_option]：shopt_option 是內建指令 shopt 接受的 shell 選項，-O 設定，+O unset。沒有 shopt_option 時，印出這些選項的名稱及值，如果用 +O，輸出可作為輸入的格式。
* -- 或 -：表示選項結束了，之後不再進行選項處理。任何在 -- 之後的引數視為檔名及其引數。

多字元選項：
* --debugger：在 shell 開始前安排執行 debugger profile，啟用 extended 除錯模式 (見內建指令 shopt 選項 extdebug 的說明)
* --dump-po-strings：相當於 -D，但輸出 GNU gettext po (portable object) 檔案格式
* --help：顯示使用說明後成功離開
* --init-file file 或 --rcfile file：在 interactive shell 執行 file 的指令取代 /etc/bash.bashrc 及 ~/.bashrc (見 INVOCATION).
* --noediting：在 interactive shell 不使用 GNU readline 函式庫來讀取指令行
* --noprofile：不執行 /etc/profile、~/.bash_profile、~/.bash_login、或 ~/.profile。login shell 預設執行這些檔案 (見 INVOCATION)
* --norc：在 interactive shell 不執行 /etc/bash.bashrc 及 ~/.bashrc。以 sh invoke 時預設啟用的選項。
* --posix：改變 bash 的行為符合 POSIX 標準 (posix 模式)
* --restricted：restricted shell (見 [RESTRICTED SHELL](restricted-shell.md)).
* --verbose：相當於 -v.
* --version：顯示版本訊息。
