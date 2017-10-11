# RTP

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
CSRC 之後為 option
* V (version)：RTP 版本，目前為 2。
* P (padding)：結尾含有 padding octets 不是 payload 的一部分。padding 的最後 octet 是 padding 的 octets 數。有些 fixed block sizes 的加密演算法或 carrying several RTP packets in a lower-layer protocol data unit 需要 padding。
* X (extension)：header 包含有 extension
* CC (CSRC count)：CSRC 數目
* M (marker bit)：由 profile 定義用途，用來標記封包串流中 significant events such as frame boundaries。profile 可以定義更多 marker bits 或 specify that there is no marker bit by changing the number of bits in the payload type field。在 voice activity detector 啟用時使用，只有當封包包含 the first voice frame after a silence period 時設為 1，幫助 decoder 分辨 between silence periods and lost frames.。
* PT
* sequence number
* timestamp
* SSRC

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

https://tools.ietf.org/html/rfc1889
