
行動電話的世代
* 1G：基本語音服務，類比系統。
* 2G：數位化。GSM 系統只支援電路交換的語音通道，主要透過語音通道打電話與傳送簡訊，GPRS 系統支援封包交換因此可以上網，但是由於利用語音通道傳送資料封包，因此上網的速度很慢。
* 3G：UMTS 系統支援封包交換，可以用更快的速度上網。
* 4G：IP 封包化，LTE / LTE-A 系統支援封包交換，可以用更快的速度上網。
* 5G：增加整體資料傳輸率，增加頻段

世代|系統名稱|調變方式|多工方式|通道頻寬|資料傳輸率|頻譜效率
----|--------|--------|--------|--------|----------|--------
2G  | GSM    |GMSK    |FDMA/TDMA|200KHz |9.6K/14.4K|0.05/0.07
2.5G| GPRS   |GMSK    |FDMA/TDMA|200KHz |9.6K/115K |0.05/0.58|在 2G 提供分封交換功能
2.75G|EDGE   |8PSK    |FDMA/TDMA|200KHz |384K/384K |1.92/1.92
3G  | W-CDMA |QPSK    |FDMA/CDMA|5MHz   |64K/2M    |0.01/0.40
3.5G| HSDPA  |16QAM   |FDMA/CDMA|5MHz   |384K/14.4M|0.08/2.88
3.75G|HSUPA  |QPSK    |FDMA/CDMA|5MHz   |5.76M/14.4M|1.15/2.88
4G  | LTE    |64QAM   |FDMA/OFMA|20MHz  |50M/100M  |2.5/5
4G  | LTE-A  |64QAM   |FDMA/OFMA|100MHz  |500M/1G  |5/10

調變技術 (Modulation)：2G 以後是採用數位調變，將類比電磁波變成不同的波形來代表 0 與 1 的數位訊號 (包括用振幅大小、頻率高低、相位不同等)，利用天線傳送到很遠的地方。數位調變的優點包括可以偵錯與除錯、壓縮與解壓縮、加密與解密、更好的抗雜訊能力等。

多工技術 (Multiplex)：將電磁波區分給不同的使用者使用，常見的多工技術包括下列 4 種：
* 分時多工接取 (TDMA)：依照「時間先後」區分。
* 分頻多工接取 (FDMA)：依照「頻率範圍不同」區分。
* 分碼多工接取 (CDMA)：用不同的碼加密資料後再傳送到資料通道，只有有特定碼的接收端以不同的密碼來分辨要接收的訊號。
* 正交分頻多工 (OFDM)：使用彼此頻率「正交」的 FDMA，目前 4G 的 LTE / LTE-A、無線區域網路（IEEE802.11a/g/n）、數位電視（DTV）、數位音訊廣播（DAB）有使用。

為了增加資料傳輸率，可能必須同時使用兩種以上的多工技術，才能滿足每個人都要使用的需求。

「頻譜效率」(Spectrum efficiency) 是單位頻寬 (Hz) 具有多少資料傳輸率 (bps)，越高就是把更多的 0 和 1 塞進相同頻寬的電磁波裡來傳送，取得更高的資料傳輸率，效率越好，例如：LTE 可以提供上傳 2.5bps/Hz，下載 5bps/Hz；LTE-A 可以提供上傳 5bps/Hz，下載 10bps/Hz，顯然 LTE-A 的頻譜效率比 LTE 高。

http://technews.tw/2015/10/12/3g、4g、5g-meaning-part-two

[2G退場 拔釘不易 NCC：3G到期絕不延期](https://cnews.com.tw/2g退場-拔釘不易-ncc：3g到期絕不延期)
[3G年底終止影響643萬人 NCC推保障方案](http://m.cna.com.tw/news/firstnews/201801030214.aspx)
https://cnews.com.tw/wp-content/uploads/Mobile-Evolution-1G-2G-3G-4G.jpg

## 3G
UMTS (Universal Mobile Telecommunications System, 通用行動通訊系統) 是一種 3G 系統，由 3GPP 發展，基於 GSM，使用 W-CDMA 無線介面，電路交換加上 GPRS 分封交換。也叫 3GSM 或 FOMA。

UMTS 是 ITU IMT-2000 的一部分，相對於基於 cdmaOne 的 CDMA200。

UMTS 需要新基地台及新頻譜，而 EDGE (IMT Single-Carrier, based on GSM) 及 CDMA2000 (IMT Multi-Carrier) 不需要。

UMTS 封包交換系統是由 GPRS 演進而來。

UMTS 與 GSM 的一個主要差別是，由無線介面等構成的通用無線接入網 (GRAN) 能夠連入不同的骨幹網路，如網際網路、ISDN、GSM 或者 UMTS網路。GRAN 包含 OSI 模型的低三層 (實體層、資料鏈路層、網路層)。

## LTE

4G LTE 的傳輸是使用 IP 封包交換 (Packet Switching)，不同於 2G / 3G 所使用的電路交換 (Circuit Switched) 傳輸方式。
語音通話服務可以透過 CSFB、SGLTE 或 VoLTE 等方法來達到 。

* CSFB (Circuit Switched Fallback)：上網用 4G，語音切回 3G
* SGLTE (Simultaneous GSM and LTE)：同時使用 4G 及 GSM (較耗電)
* SVLTE (Simultaneous Voice and LTE)：同時使用 4G 及 CDMA (較耗電)
* SRVCC (Single Radio Voice Call Continuity)：3GPP 標準，話音通話在 VoLTE 跟 2G/3G 之間切換時能維持通話連續性，在 LTE 覆蓋率不佳的環境可確保通話不中斷。

### VoLTE
IMS
[[教學]何謂VoLTE？認識新一代高品質語音通話服務](https://www.sogi.com.tw/articles/volte/6246425)

## 5G
光以影音規格來說，很快地，人們就不會滿足於 Full HD 的解析度，而會想要往 4K、甚至 8K 的解析度邁進，人們對於無線網路的速度需求只會越來越大，因此一旦 5G 逐漸普及，許多需要更快下載速度的服務與應用也會迅速流行。

* 低延遲：4G 在端對端的延遲約 50 毫秒，5G 的端對端延遲約為 1 毫秒。達到即時控制與命令，可應用在車聯網

http://technews.tw/2017/03/11/5g-value/
