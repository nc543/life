# Quoting
Quoting 用來跳脫特殊字元 (metacharacters, ...) 、保留字的解釋，或避免 parameter expansion。

有三種 quoting 方式
* \\<字元>：跳脫緊接著字元的特殊意義。除了 \\<換行> 是連結到下一行。
* 單引號包起來：跳脫裡面所有字元及字的特殊意義。包括 \\，所以單引號無法巢狀使用。
* 雙引號包起來：跳脫裡面所有字元及字的特殊意義，除了
	* 「$」及「`」的擴展仍進行
	* 「\」跳脫 $、`、"、\、\<換行>
	* 「!」歷史擴展仍進行，但「\\!」不進行歷史擴展。在 POSIX 模式「!」沒特殊意義。
	* 「*」及「@」.... (見 PARAMETERS).

雙引號可以藉由前置「\」來巢狀使用

$'string'：「$」後的單引號字串會轉換裡面的下列 \\<字元> 成 ANSI C 標準字元，轉換後依照上述單引號方式解釋。

\\<字元>|轉換後字元
--------|------------
\a      |alert (bell)
\b	|backspace
\e 或 \E|escape
\f      |form feed
\n      |new line
\r      |carriage return
\t      |horizontal tab
\v      |vertical tab
\\\     |backslash
\\'     |single quote
\\"     |double quote
\nnn    |用 1 到 3 位十進位數字表示 8-bit 字元
\xHH    |用 1 到 2 位十六進位數字表 示8-bit 字元
\uHHHH  |用 1 到 4 位十六進位數字表示 Unicode (ISO/IEC 10646) 字元
\UHHHHHHHH|用 1 到 8 位十六進位數字表示 Unicode (ISO/IEC 10646) 字元
\cx     |control-x 字元

[Shell 工作完成自動發聲通知](https://blog.longwin.com.tw/2011/10/shell-done-sound-alert-2011/)

$"string"：「$」後的雙引號字串依據 locale 轉換，轉換後依照上述雙引號方式解釋。
