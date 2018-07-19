jQuery 是一個 JavaScript Library，所有屬性及函數都定義在「jQuery」這個物件下，別名是「$」。

包含下列功能：
* HTML/DOM manipulation
* CSS manipulation
* HTML event methods
* Effects and animations
* AJAX
* Utilities
此外，還有 plugins 增加其它功能。

下載後放在伺服器裡，在網頁加：
```
<head>
<script src="jquery-3.1.1.min.js"></script>
</head> 
```
註：JavaScript 在 HTML5 及所有現代瀏覽器是預設的腳本語言，所以 `<script>` 標籤裡不需要 `type="text/javascript"`。

可改自 CDN (Content Delivery Network) 下載

Google CDN:
```
<head>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
</head>
```
Microsoft CDN:
```
<head>
<script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.1.1.min.js"></script>
</head>
```
這樣使用者的瀏覽器如果已經自 Google 或 Microsoft 下載 jQuery，就不用再下載。

## 語法
基本語法：**$**(**selector**).**action**()
* **$** 存取 jQuery
* **$**(**selector**) 選取 HTML 元素，採用 CSS 選擇器的語法，如 tag, #id, .class, ...
* **action**() 進行動作

範例：

$(this).hide() - hides the current element.

$("p").hide() - hides all `<p>` elements.

$(".test").hide() - hides all elements with class="test".

$("#test").hide() - hides the element with id="test".

為避免在網頁完成載入前就執行 jQuery 程式碼，jQuery 程式碼會放在 document ready event 裡：
```js
$(document).ready(function(){
   // 放 jQuery 程式
});
```
或
```js
$(function(){
   // 放 jQuery 程式
});
```
可放在 body 之前的 head section。

有些動作在網頁完成載入前執行會失敗：
* 隱藏未建立的元素
* 取得未載入影像的大小

##
[Add a new option to a select with jQuery](https://www.electrictoolbox.com/jquery-add-option-select-jquery/)
[Arduino 筆記 - 製作一個溫溼度記錄器 (3)](http://coopermaa2nd.blogspot.tw/2011/01/arduino-3.html)：使用 .csv =jQuery => Google chart
[HTML 表格排序：使用 tablesorter](http://lirobo.blogspot.tw/2013/02/html-tablesorter.html)

jQuery alternatives
* http://zeptojs.com/
