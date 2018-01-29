# Record-Route & Route

呼叫端和受話端建立 dialog 時，SIP 請求是逐 proxy 傳送，但建立之後的 SIP 請求是呼叫端和受話端之間直送，不經過這些 proxy。
proxy 如果想要維持在訊息路徑中，在 dialog 建立經手 SIP 請求時，就要插入一筆最頂端的 Record-Route: 紀錄自己的位址。請求到達受話端後，會有全部需要的 Record-Route: 及順序，全部複製到回應訊息並紀錄成 Route 列表。
發話端收到回應訊息，也會有全部需要的 Record-Route:，同樣紀錄成 Route 列表，但順序相反。
dialog 中 (如 ACK、BYE、re-INVITE)，任一端的請求依 Route 列表產生 Route: 標頭，並先依 Route: 順序傳送。

比較：Via: 標頭

在 dialog 建立請求時，發話端也可以事先設定 Route: 標頭，例如 outbound proxy。

參數
* lr (loose router)：dialog 中的請求會先不理會請求 URI，直接依照 Route: 傳送。proxy 收到後，最頂端的 Route: 中的第一個位址應該就是自己，會把它移除。和 loose router 相對的，就是以前 [RFC 2543](https://tools.ietf.org/html/rfc2543) 的 strict routing，需要把一開始的請求 URI 插到最後的 Route: 標頭，過程中需要一直把最頂的 Route: 移到請求 URI。lr 只需要做移除最頂的 Route:。
* r2=
* ftag=
* nat=

應用：
* [作 NAT 的 proxy](http://lirobo.blogspot.tw/2015/02/siprtp-nat-traversal.html) 需要持續作位址轉換
* 作 accounting 的 proxy 需要知道何時 BYE 通話結束。

[SIP REGISTER](http://lirobo.blogspot.tw/2016/07/sip-register.html) 可以有 Route，忽略 Record-Route。

## 參考及延伸閱讀
1. http://lirobo.blogspot.tw/2010/10/sip-invite.html
1. http://kamailio.org/docs/modules/stable/modules/rr.html
1. http://tools.ietf.org/html/rfc3261

##
移除 http://lirobo.blogspot.tw/2015/01/sip.html 對應的部份
