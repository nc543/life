## Selectors
選擇器               |說明
---------------------|---
\#**id**             |
.**class**           |
*                    |
**tag**              |
**tag1**,**tag2**    |**tag1** 及 **tag2**
**tag1** **tag2**    |**tag1** 內的任何 **tag2**
**tag1**>**tag2**    |**tag1** 內一層的 **tag2** (**tag2** 的 parent 是 **tag1**)
**tag1**~**tag2**    |**tag1** 後的任何 **tag2**
**tag1**+**tag2**    |**tag1** 後緊接的 **tag2**
[**attr**]           |有 **attr** 屬性的元素
[**attr**=**value**] |**attr** 屬性值為 **value** 的元素
[**attr**~=**value**]|**attr** 屬性值含有字 **value** 的元素
[**attr***=**value**]|**attr** 屬性值含有子字串 **value** 的元素
[**attr**\|=**value**]|**attr** 屬性值以 **value** 開頭的元素
[**attr**^=**value**]|**attr** 屬性值以 **value** 開頭的元素
[**attr**$=**value**]|**attr** 屬性值以 **value** 結束的元素
:active              |active 的元素
::after              |在元素的後面加一些東西
::before             |在元素的前面加一些東西
:checked             |
:disabled            |
:empty               |
:enabled             |
:first-child         |
::first-letter       |
::first-line         |
:first-of-type       |
:focus               |

http://www.w3schools.com/cssref/css_selectors.asp

## Box Model
所有 HTML element 可視為方塊，由內而外有 4 層，包括 Content、Padding、Border、及 Margin。

element box|CSS 屬性|說明
-----------|--------|----
Content    |width   |內容本身
Padding    |padding |內容旁邊的淨空
Border     |border  |圍牆
Margin     |margin  |圍牆外的淨空

* 這些都可以分別設寬 (高) 度，整個 element 的寬度或高度需要把這些加起來。
* Padding、Border、Margin 有四個方位，可分別設定上右下左。
* border 可設 width (預設 medium)、style (預設 none, border-style)、color。

註：IE8 或之前的版本，其 width 包含了 padding 及 border，網頁可加 \<!DOCTYPE html> 排除這個問題 

參考：
http://www.w3schools.com/css/css_boxmodel.asp
