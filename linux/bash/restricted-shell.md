# restricted shell
使用名稱 rbash 或選項 -r 來執行 bash，建立比較受限的執行環境，不允許或不進行下列行為：

* 改變目錄 (cd)
* setting or unsetting the values of SHELL, PATH, ENV, or BASH_ENV
* 執行或用內建指令 . 執行包含 / 的檔名
* specifying  a  filename containing a slash as an argument to the -p option to the hash builtin command 見 [hash](http://lirobo.blogspot.com/2017/11/bash-hash.html)
* 匯入 function 定義 from  the  shell  environment  at startup
* parsing  the  value  of  SHELLOPTS from the shell environment at startup
* [輸出導向](bash-redirection.md) 使用 >, >|, <>, >&, &>, and >> redirection operators
* 用內建指令 exec 將 shell 取代為其它指令
* 用內建指令 enable 來啟用、停用、載入、或移除內建指令
* specifying the -p option to the command builtin command
* 關閉 restricted 模式 (set +r 或 set +o restricted)

這些限制 enforced after any startup files are read.

When a command that is found to be a shell script is executed (see COM‐
MAND  EXECUTION  above),  rbash turns off any restrictions in the shell
spawned to execute the script.
