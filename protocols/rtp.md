# RTP
RFC 3550
```
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |V=2|P|X|  CC   |M|     PT      |       sequence number         |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                           timestamp                           |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |           synchronization source (SSRC) identifier            |
   +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
   |            contributing source (CSRC) identifiers             |
   |                             ....                              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
CSRC 以後為 option
* V (version)：RTP 版本，目前為 2。
* P (padding)：表示結尾含有 padding octets 不是 payload 的一部分。padding 的長度由 padding 最後 octet 決定。有些固定區塊大小的加密演算法或下層 protocol data unit 可放多個 RTP 封包時需要 padding。
* X (extension)：表示 header 有加 extension
* CC (CSRC count)：CSRC 數目，表示固定 header 之後有幾個 CSRC。
* M (marker bit)：由 profile 定義用途，用來標記封包串流中的重大事件，例如 frame boundaries。profile 可以改變 PT 位元數目來定義更多 marker 位元或不用 marker 位元。在 voice activity detector 啟用時使用，只有當封包包含 silence 期間後第一個語音封包時設為 1，幫助 decoder 分辨是有 silence 還是有掉封包。
* [PT](http://lirobo.blogspot.com/2017/11/rtp-payload-type.html)：代碼對應到 payload 使用的影音編碼格式，在 [RFC 3551](https://tools.ietf.org/html/rfc3551) 有[對應表](https://tools.ietf.org/html/rfc3551#page-32)，包括靜態及動態的對應方式。如果是動態方式，使用非 RTP 得知代碼。
* sequence number：每個 RTP 封包加一，讓接收端偵測封包遺失或順序錯誤。
* timestamp：
* SSRC (Synchronization Source) Identifier：來源的亂數編號。

extension 格式
```
    0                   1                   2                   3
    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |      defined by profile       |           length              |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |                        header extension                       |
   |                             ....                              |
```

https://tools.ietf.org/html/rfc3550
http://albert-oma.blogspot.tw/2012/05/rtp.html
