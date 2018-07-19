# IPv6

## 沿革
* v1, v2, v3：IP 出現之前就有 TCP 了，TCP v1 在 1973 ([RFC 675](https://tools.ietf.org/html/rfc675))，TCP v2 在 1977。後來 Jon Postel 發現 TCP 同時作為 end to end 協定，以及封包 packaging 和路由的協定，違反網路階層原則的發展方向不對，TCP 跟 IP 才分家，並同時使用版本 3 (1978)。
* v4：第一個 IP 穩定版本。RFC 760 (1980) -> RFC 791 (1981)
* v5：[Internet Stream Protocol](https://en.wikipedia.org/wiki/Internet_Stream_Protocol) 用掉
* v6：RFC 1883 (1995) -> RFC 2460 (1998) -> [RFC 8200](https://tools.ietf.org/html/rfc8200) (2017)

## 改良
* 大位址空間
* 階層式位址配置
* Multicasting
* Stateless address autoconfiguration (SLAAC)
* Network-layer security
* 減輕路由器的負擔
* Mobility
* Options extensibility
* Jumbograms
* Privacy
* ...

IPv6 無法直接跟 IPv4 互通，但大多 transport 層及應用層協定不用改或小改就能用在 IPv6，不行的是內含 IP 位址的協定，例如 FTP、NTP 等。

##
辨別是使用 IPv6 或是 IPv4

 ?          |IPv4|IPv6|說明
------------|----|----|---
位址 bit 數 |  32| 128|
位址 byte 數|   4|  16|
data type|unsigned long|?|
位址字串表示|4 個十進位數字以 . 隔開|8 組 4 個十六進位數字每組以 : 隔開|IPv6 有簡寫規則
位址字串長度|  16|  40|含結尾 0
[EtherType](http://lirobo.blogspot.tw/2014/09/ether-type.html)|0x0800|0x86DD|
header 版本 |   4|   6|一開始 4-bit，剩下欄位都不同。
header 長度 |  20|  40|不含 options

IPv6 簡寫規則：
* 每組開頭的 0 可省略，若全為 0 ，則可簡寫為 0
* 若連續好幾組全為 0，可全省略，只留下「:」，但以一次為限。

```
struct ip_addr{
	unsigned int af; /* address family: AF_INET6 or AF_INET */
	unsigned int len;    /* address len, 16 or 4 */

	/* 64 bits aligned address */
	union {
		unsigned long  addrl[16/sizeof(long)]; /* long format*/
		unsigned int   addr32[4];
		unsigned short addr16[8];
		unsigned char  addr[16];
	}u;
};
```

128-bit IPv6 位址，原則上前面 64-bit 為 Network ID，後面 64-bit 為 Host ID。Network ID 又可分成 Routing prefix 跟 subnet

## address
* unicast: 單一網路界面
* anycast addressing: assigned to a group of interfaces, usually belonging to different nodes. A packet sent to an anycast address is delivered to just one of the member interfaces, typically the nearest host, according to the routing protocol's definition of distance. Anycast addresses 格式和 unicast 位址相同 cannot be identified easily, and differ only by their presence in the network at multiple points. Almost any unicast address can be employed as an anycast address.
* multicast: 到所有參與 multicast 群組的成員
	* broadcast by multicast addressing to the all-nodes link-local multicast group ff02::1. However, the use of the all-nodes group is not recommended, and most IPv6 protocols use a dedicated link-local multicast group to avoid disturbing every interface in the network.

unicast 位址和 anycast 位址一般包含 64-bit network prefix 作為 routing 及 64-bit interface identifier 用來 identify a host's network interface. 64-bit interface identifier 可能來自介面卡的 MAC address (使用 modified EUI-64 格式)、DHCPv6 伺服器、亂數產生、或手動指定。

* ::/128：位址未指定，相當於 IPv4 的 0.0.0.0/32。
* ::/96：IPv4-compatible address (deprecated)
* ::/0：default route，相當於 IPv4 的 0.0.0.0/0。
* ::1/128：localhost，相當於 IPv4 的 127.0.0.1/8。
* ::ffff:0:0/96：IPv4-mapped IPv6 address
* ::ffff:c000:0280 is written as ::ffff:192.0.2.128
* ::ffff:0:0:0/96：IPv4-translated address
* 64:ff9b::/96：IPv4-Embedded IPv6 Address
* 0100::/64：discarding
* 2001::/32：Teredo tunneling (IPv6 transition mechanism)
* 2001:2::/48：benchmarking IPv6，相當於 IPv4 的 192.18.0.0/15。
* 2001:20::/28：ORCHIDv2
* 2001:db8::/32：文件範例使用，相當於 IPv4 的 192.0.2.0/24、198.51.100.0/24、和 203.0.113.0/24。
* 2002::/16：6to4
* fc00::/7：Unique local address，相當於 IPv4 的 private 位址 10.0.0.0/8、172.16.0.0/12、和 192.168.0.0/16。
* fe80::/64：link-local address，LSB 64-bit 通常使用介面卡 MAC address 的 modified EUI-64 格式。相當於 IPv4 的 169.254.0.0/16。
* fec0::/10：Site-local address (deprecated)
* ffFS::/16: multicast address
	* F = rRPT: r (reserved), R (Rendezvous), P (Prefix), T (Traniet)
	* S (scope)
	* Solicited-Node multicast address
	* ff02::1： link-local all nodes multicast group

A link-local address is also based on the interface identifier, but uses a different format for the network prefix.

## IPv6 轉換
Dual IP stack
RFC 4213

## 其它參考及延伸閱讀
* [IPv6 簡介](http://hanteye01.blog.fc2blog.us/blog-entry-1.html)
