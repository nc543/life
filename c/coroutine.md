# coroutine
透過程式語言的特定技巧或機制，讓原本循序執行的陳述指令，得以做出交錯執行的結果。

可以暫時中斷，之後再繼續執行的程序

coroutine 間切換成本很低、速度很快，自己排程

範例：網路連線處理
* 阻塞式單一行程：單一行程、單一迴圈，一個請求處理完之後才能繼續處理下一個。
* 阻塞式多行程：每個請求開一個行程去處理，需要 context-switch 切換處理的連線，連線非常多時，context-switch 可能佔了大部份 CPU 時間。
* 阻塞式多執行緒：如果不同執行緒有共同的東西要處理，會有 dead lock、race condition 等問題
* 非阻塞式事件驅動：單一主迴圈檢查各種事件是否發生，再決定要怎樣處理，但程式寫法不是線性的，當事件觸發時需記下目前未完成的狀態，下次觸發時再依先前的狀態來決定接下來要做什麼
* 非阻塞式 Coroutine

http://blog.linux.org.tw/~jserv/archives/001848.html

http://blog.ez2learn.com/2010/07/17/talk-about-coroutine-and-gevent/
