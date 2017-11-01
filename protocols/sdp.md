[SDP: Session Description Protocol](https://tools.ietf.org/html/rfc4566)

* `v=0`：protocol version，目前為 0
* `o=<username> <session-id> <session-version> <nettype> <addrtype> <unicast-address>`：originator
	* username：在來源端主機登入名稱或 -
	* session-id
	* `o=root 763858396 763858396 IN IP4 10.1.1.130`
* `s=<session name>`
* c=IN IP4 10.1.1.130
* t=0 0

## m=
每種媒體描述，例如 audio、video 等，有一行
```
m=<media> <port> <proto> <fmt> <fmt> ...
```
作為開始，其中：
* **media** 媒體種類可以是 "audio"、"video"、"text"、"application"、"message" 等
* **port** 使用的傳輸埠
* **proto** 使用的傳輸協定，例如 "udp"、"RTP/AVP"、"RTP/SAVP" 等
* **fmt** 可有多個，這些數字依據 proto 而有不同解釋。如果是 "RTP/AVP" 或 "RTP/SAVP"，是指使用的 RTP payload type。

接下來可能有一些相關屬性行 a=

## a=rtpmap
動態 payload type 對應
```
a=rtpmap:<payload type> <encoding name>/<clock rate> [/<encoding parameters>]
```
對應 RTP payload type 到一個編碼名稱和其參數。編碼名稱有 PCMA、PCMU、GSM、telephone-event 等。PCMU 的 payload type 固定使用 0，GSM 固定使用 3，PCMA 固定使用 8，telephone-event 通常用 110 或 96。

## a=gpmd
General-Purpose Media Descriptor Parameter
* VBD (Voiceband Data) 轉換，含即不含 redundancy 或 FEC (forward error correction)
* 也可以用來為特定 codec authorize 其它操作模式

[MGCP VBD Package and General-Purpose Media Descriptor Parameter Package](https://tools.ietf.org/html/rfc6498) -- 除了 gpmd，亦說明the use of the Media Format Parameter package and Fax package with VBD, redundancy, and FEC.

## a=fmtp
```
a=fmtp:101 0-15
```

## a=silenceSupp
`a=silenceSupp: <silenceSuppEnable> <silenceTimer> <suppPref> <sidUse> <fxnslevel>`
https://tools.ietf.org/html/rfc3108

## a=ptime

## a=sendrecv

## 其它
