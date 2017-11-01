# nameref
參考變數名稱

`declare -n` 或 `local -n` 建立名稱參考的變數，來間接使用另一個變數。
除了 `-n` 選項外，改變 nameref 變數實際作用在參考的變數。常用在函數 call-by-reference 的參數。

例如：變數名稱作為引數傳進函數，函數裡建立了 nameref 變數 ref，其值指定傳入的參數，也就是作為引數的變數名稱。改變 ref 相當於改變變數名稱為引數的變數。
```
#!/bin/bash

A=1

f1() {
	local -n ref=$1
	ref=2
}

f1 A
echo $A
```

如果 for 迴圈的 control variable 是
       nameref, the list of words 可以是 a list of shell  variables,
       and  a name reference will be established for each word in the list, in
       turn, when the loop is executed.

陣列不能設 `-n` 屬性。
然而 nameref 可以 reference 陣列或 subscripted 的陣列變數。
`unset -n` 可以取消 nameref，此外 `unset` 是作用在參考的變數。

相關：參數擴展 (parameter expansion)，內建指令 declare、local、typeset、unset

http://tldp.org/LDP/abs/html/ivr.html
