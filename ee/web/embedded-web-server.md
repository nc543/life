一些名詞
* server side scripting
* server side includes

簡易的 server side scripting，在 server 端將其它資料加到 html 網頁中，例如另一個檔案內容、執行指令的結果，甚至有條件判斷。

## eServ
嵌入式系統，如 AP，通常需要提供網頁的 GUI，需要在資源有限的環境下跑網頁伺服器，反而位於使用者端的瀏覽器有很好的效能。eServ 用最少的資源實做基本的 Web framework 功能，產生相對少量的資料，讓瀏覽器端盡情去描繪多采多姿的內容，也對使用者互動方面有了更多的需求。

期許可兼顧效能、彈性，以及建立原生 (native) 函式庫與系統程式的有效互動。可從 Webserver + CGI/Servlet + Database 都用同一隻 C 語言程式處理，僅佔用極少的系統資源。

Ajax 是一種使用 XMLHttpRequest 的非同步資料取得技術，可以減少網頁在瀏覽器跟伺服器之間的資料傳送量。

[eServ : Embedded Native C/C++ Web Framework (OSDC.TW)](http://osdc.tw/2010/04/schedule_eserv_embedded_native.html)
http://code.google.com/p/eserv/

## 延伸閱讀
* [lwkhttpd : Lightweight kHTTPd for Linux Kernel](http://orzlab.blogspot.com/2007/03/lwkhttpd-lightweight-khttpd-for-linux.html)
* [Ajax/Embedded](http://orzlab.blogspot.com/2007/03/ajaxembedded.html) (an lightweight and efficient web server, an Ajax engine written in C/C++, and rich Web UI widgets.)
* 愛做夢的蘆薈：[Embedded AJAX+CGI web UI solution](http://daydreamer.idv.tw/rewrite.php/read-4.html)
* [Embedded Ajax](http://www.access-company.com/PDF/NetFront/Ajax%20white%20paper.pdf) (見 Figure 1)
* [Wt C++ Web toolkit](http://www.webtoolkit.eu/wt)
* [Boa](http://www.boa.org/)：缺存取認證及 SSL 等功能 ([wikipedia](http://en.wikipedia.org/wiki/Boa_%28web_server%29)) 
* fnord
* [Mongoose](http://code.google.com/p/mongoose/) (40kB)
* thttpd
* uip
* kHTTPd
