https://tools.ietf.org/html/rfc4566

每個媒體描述有一行
```
m=<media> <port> <proto> <fmt> ...
```
作為開始，其中：
* **media** 可以是 "audio"、"video"、"text"、"application"、"message" 等
* **port** 使用的傳輸埠
* **proto** 使用的傳輸協定，例如 "udp"、"RTP/AVP"、"RTP/SAVP" 等
* **fmt** ... 依據 proto 解釋。如果是 "RTP/AVP" 或 "RTP/SAVP"，fmt 是使用的 RTP payload type 數字列表。

接下來可能有一些相關屬性行 a=

## rtpmap
動態 payload type 對應
```
a=rtpmap:<payload type> <encoding name>/<clock rate> [/<encoding parameters>]
```
對應 RTP payload type 數字到一個媒體編碼名稱

## gpmd
General-Purpose Media Descriptor Parameter
* VBD (Voiceband Data) 轉換，含即不含 redundancy 或 FEC (forward error correction)
* 也可以用來為特定 codec authorize 其它操作模式

[MGCP VBD Package and General-Purpose Media Descriptor Parameter Package](https://tools.ietf.org/html/rfc6498) -- 除了 gpmd，亦說明the use of the Media Format Parameter package and Fax package with VBD, redundancy, and FEC.

## fmtp

## silenceSupp
`a=silenceSupp: <silenceSuppEnable> <silenceTimer> <suppPref> <sidUse> <fxnslevel>`
https://tools.ietf.org/html/rfc3108
