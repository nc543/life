Dial() string
```
DAHDI/pseudo[/extension[/options]]
DAHDI/<channel#>[c|r<cadance#>|d][/extension[/options]]
DAHDI/<subdir>!<channel#>[c|r<cadance#>|d][/extension[/options]]
DAHDI/i<span>[/extension[/options]])
DAHDI/[i<span>-](g|G|r|R)<group#(0-63)>[c|r<cadance#>|d][/extension[/options]]
```
* 什麼是 pseudo
* 選項 c 或 `r<cadance#>` 或 d
* extension
* options
* `<channel#>`
* `<subdir>!<channel#>`
* `i<span>`：指定 ISDN span。ISDN span 怎麼來？
* g、G、r、R：指定群組 0 到 63
	* 小寫是使用 iflist 來 search forward ，大寫是使用 ifend 來 search backward
	* r 或 R 使用 round robin

每個 channel (也就是 interface 或 timeslot) 有一個 struct dahdi_pvt，使用頭跟尾分別是 iflist 跟 ifend 的 double link list 串起來，當有 call 進來方便一個一個 search forward 或 backward。搜尋時可指定 group、span、channel，看有沒有 alarm，...。

如果是 ISDN B channel，或有 pri
