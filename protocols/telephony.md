Hookflash 或 Flash：按一下話機的 hook

PBX 功能
* DID：在於會送 Callee ID 給用戶，用戶 PBX 可依此讓特定分機響鈴
* DOD (Direct Outward Dialing)：直接用自己的號碼外撥，不用透過
* Hunting Group
* Wait Queue
* Call pickup (代接)
	* Group pickup (群組代接)：代接群組中的分機
	* Direct pickup (指定代接)：代接指定分機
* Call forwarding (指定轉接)：依狀況自動轉接到指定號碼
	* Unconditional forwarding：設定的分機發話時會有不同的 dial tone
	* No answer
	* Busy
* Call hold (保留)：通話中，通常是 hookflash 後保留，暫時停止談話，可以送保留音樂 (music on hold) 給對方。再 hookflash 回復通話。進階功能是保留時 (可能有 dial tone)，可以再撥一通電話出去，然後可以掛斷接回、不掛斷接回、轉接、三方通話、或掛斷保留的通話。
* Call Waiting (話中插接、插撥)：通話中有另一通電話進來，這時候可以聽到 call waiting tone，通常是 hookflash 來 call hold 目前的通話，切換到新來電。再 hookflash 切換回去。
* Wake up (鬧鐘)
* DnD
* Hot line (直通預設用戶號碼)
* Timed hot line (在時間內可作一般發話，超過則直通預設用戶號碼)
* 簡撥
* Call lock (特定碼能撥或不能撥)
* Call back (兩端空閒時自動建立連線)
* 3 way calling (三方通話)
* Call transfer (轉接電話)
	* blind transfer：轉接後斷線
	* attended transfer：轉接確認後，再看要不要斷線
	* http://www.osslab.org.tw/index.php?title=VoIP/IP_PBX/軟體式_IP_PBX/Asterisk/Basic/Call_Transfer-電話轉接
* Call parking (駐留) ：雙方打同樣的 parking 號碼來接通。
* Broker call
* Inquiry call
* Attendant Station
* Attendant Console
* 自動總機

## 延伸閱讀
http://en.wikipedia.org/wiki/Telephony
