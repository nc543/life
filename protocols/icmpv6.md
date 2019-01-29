# ICMPv6

ICMPv6 是給 IPv6 用的 ICMP (Internet Control Message Protocol)，修改自 [IPv4 的 ICMP](https://tools.ietf.org/html/rfc792)，規範在 [RFC 4443](https://tools.ietf.org/html/rfc4443)，使用 IPv6 Next Header 58。

IPv6 節點皆需要實作 ICMPv6，用來回報處理封包遭遇的錯誤、以及進行其它 IPv6 功能，例如 diagnostics (ICMPv6 "ping").

ICMPv6 訊息共通格式：
```
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |     Type      |     Code      |          Checksum             |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                                                               |
      +                         Message Body                          +
      |                                                               |
```
Checksum 用來偵測 ICMPv6 訊息及部份 IPv6 表頭資料錯誤。Type 決定剩下的資料格式。

ICMPv6 訊息有 2 種類型：
* 錯誤訊息 (Type 0~127)：目的或中間節點報告傳送封包時遇到的錯誤，包括
	* Type 1: Destination Unreachable
	* Type 2: Packet Too Big
	* Type 3: Time Exceed
	* Type 4: Parameter Problem
* 資訊訊息(Type 128~255)：
	* Echo 診斷
		* Type 128：Echo Request
		* Type 129：Echo Reply
	* MLD
		* Type 130：Multicast Listener Query
		* Type 131：Multicast Listener Report
		* Type 132：Multicast Listener Done
	* MLDv2
	* Type 133~137：Neighbor Discovery

http://hanteye01.blog.fc2blog.us/blog-entry-3.html

# IPv6 Neighbor Discovery
Neighbor Discovery (ND) 提供機制來解決鄰近節點的下列問題：
* Router Discovery：得知連接鄰近的 router。
* Prefix Discovery：得知哪些 prefix 是可直接傳送的位址，或者需要透過 router 傳送。
* Parameter Discovery：得知 link 的相關參數，例如：link MTU，Hop Limit 值。
* Address Autoconfiguration：自動配置網路界面參數，例如：IPv6位址，link MTU 等。
* Address resolution：解析鄰近節點的 link 層地址。
* Next-hop determination：將欲傳送的封包的目的地對應到 next-hop位址。Prefix Discovery？非鄰近的位址，Next-hop 位址是 router 的位址。鄰近的目的位址，next-hop 位址就是目的位址本身。
* Neighbor Unreachability Detection：偵測鄰近的節點是否可達。對於不可達的nodes，可嘗試用位址解析機制來確認是否還可達。此外，如果link上有2個以上的routers，還可以透過更換default router來解決鄰近router不可達問題。
* Duplicate Address Detection：偵測要使用的位址是否已經被鄰近的節點使用。
* Redirect (重新導向)：當link上有2個以上routers時，Router如何告知host使用更佳的next-hop （即別的router）將封包送達特定的目的位址。
