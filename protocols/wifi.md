[IEEE 802.11](https://en.wikipedia.org/wiki/IEEE_802.11) 是實作 Wireless LAN (WLAN) 的標準，基於蜂巢式架構，每個巢室 (在 802.11 稱為 Basic Service Set, BSS) 由一個基地台 (稱為 Access Port, AP) 管理所屬的無線用戶端 (client)，並用 AP 的 MAC 位址作為唯一的 BSS 識別碼 (BSSID)。

BSS 或 ESS 有一串叫做 Service Set ID (SSID) 的識別文字，最多 32 字。AP 廣播 SSID，在訊號涵蓋範圍 (Basic Service Area, BSA) 內的用戶端看到可依據 SSID、訊號強度等選擇加入。
AP 也可以選擇不廣播 SSID，變成需要用戶端 Probe 特定 SSID 後加入。
AP 也是交通轉運中心，轉送用戶端們及 uplink 之間的封包。

多個巢室的 AP 可以共同運作，都使用同一個 SSID，讓用戶端可以在這些 AP 間漫遊。這些 AP 透過某種有線或無線網路 (稱為 Distribution System, DS)，例如 Ethernet，連在一起，整個視為一個 802 網路，稱為 Extended Service Set (ESS)。

另外還有一種 BSS 稱為 Independent BSS (IBSS)，運作在 Ad Hoc 或 Peer-to-peer 模式，沒有特定的 AP，BSSID 是亂數產生的區域 MAC 位址 (local bit 為 1，group bit 為 0)。互連的用戶端可用手動或用互相協調的方式決定管理者，條件包括是否連上網際網路、剩餘電源多寡、是否已經是管理者、接收到的無線訊號強弱等。

無線訊號是在開放空間傳送，AP 需要認證用戶端以及資料需要加密來維持隱私，主要有 WPA2、WPA、WEP 方式。

* WDS
* MESH

<table cellspacing="0" border="1">
<tbody>
<tr>
<th rowspan="2">Data Link Layer</th>
<td colspan="3">802.2 LLC</td>
</tr>
<tr>
<td colspan="3">802.11 MAC</td>
</tr>
<tr>
<th>Physical Layer</th>
<td>FH</td>
<td>DS</td>
<td>IR</td>
</tr>
</tbody>
</table>
* FH: Frequency Hopping Spread Spectrum in the 2.4 GHz Band 
* DS: Direct Sequence Spread Spectrum in the 2.4 GHz Band
* IR: InfraRed

802.11 MAC 除了一般 MAC 功能外，還多了一些跟上 (下？？？) 層協定有關的功能，例如 Fragmentation, Packet Retransmitions, and Acknowledges.

Wi-Fi 加密：WPA2 最佳，[WEP](http://lirobo.blogspot.tw/2011/01/wep.html) 容易遭破解，[WPA](http://lirobo.blogspot.tw/2011/01/wpa.html) 是好些，None 沒加密
