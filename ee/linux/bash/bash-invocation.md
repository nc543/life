# INVOCATION

定義什麼是 login shell，什麼是 interactive shell？

bash 執行時會執行存在的 startup 檔案，如果這些檔案存在，但無法讀，bash 會回報錯誤

## login shell
執行 bash 引數 0 的第一個字元是 - 或使用選項 --login

執行時執行 /etc/profile 及 ~/.bash_profile、~/.bash_login、~/.profile 三個第一個存在且可讀的，選項 --noprofile 關閉執行這些。
結束時執行 ~/.bash_logout。

## interactive shell
沒有非選項的引數 (除非有 -s 選項) 且沒有選項 -c，其標準輸入及錯誤輸出都連接到終端機 (由 isatty() 決定)，
或者開始時設 -i 選項。

選項 -s 可用來設定位置參數

在非 login shell 或標準輸入連結到網路 (例如 rshd 或 sshd) 時，開始時執行 /etc/bash.bashrc 及 ~/.bashrc，選項 --norc 關閉執行這些，選項 --rcfile file 則改執行 file。

### 判定是否在互動模式
方式一：看 $- 是否有 i
```sh
case "$-" in
*i*)	echo This shell is interactive ;;
*)	echo This shell is not interactive ;;
esac
```
方式二：PS1 有設
```sh
if [ -z "$PS1" ]; then
	echo This shell is not interactive
else
	echo This shell is interactive
fi
```

### 互動式 shell 的行為
https://www.gnu.org/software/bash/manual/html_node/Interactive-Shell-Behavior.html#Interactive-Shell-Behavior

##

當 bash 以非互動的方式執行，例如執行一個 shell script，
會 expand 環境變數 BASH_ENV 作為執行的檔名，相當於執行
```
if [ -n "$BASH_ENV" ]; then . "$BASH_ENV"; fi
```
但是環境變數 PATH 並不作為尋找檔名用。

當 bash 用名字 sh 執行，會盡量模仿傳統 sh 的起始行為，維持相容 POSIX。
互動式 sh 會擴展變數 ENV 作為開始執行的檔名。由於不執行其他 startup 檔，所以 --rcfile 沒作用。
非互動式 sh 不執行任何 startup 檔。

如果 shell 開始時 effective user (group) id 跟 real user (group) id 不同，且 [-p](builtin-set.md#-p) 沒設，startup 檔不執行，且 shell function 不繼承自環境，忽略變數 SHELLOPTS、BASHOPTS、CDPATH、及 GLOBIGNORE  variables，effective user id 設為 real user id。如果 -p 有設時一樣，但 effective user id 不重設。

## 延伸閱讀
* 每個使用者帳戶在 /etc/passwd 會有一行，包含用「:」分隔的 7 個欄位，其中最後一欄是使用者的 command interpreter，作為使用者第一個程式，很可能就是 /bin/bash。
