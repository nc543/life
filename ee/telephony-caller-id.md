Caller ID (caller identification, CID) 有多種翻譯或別名：來電顯示、來電號碼顯示、CLID (Caller Line Identity Display), CLI (calling line identification)、calling number identification (CNID)、CLIP (Calling Line Identification Presentation)、CND (Caller Number Display)、Caller Display, CND (Calling Number Delivery)、CPN (Calling Party Number)

一般講的 Caller ID 是指來電時傳送的，另外還有話中插撥時傳送 (Call Waiting)、及 ADSI (Analogue Display Services Interface)。

以前的 Bellcore 定義了三種等級的 caller ID 服務：

* Type I：在 on-hook 來電時傳送來電顯示
* Type II：除了 Type I 功能外，還有話中插撥傳送來電顯示 (Call Waiting)
* Type III：除了 Type II 功能外，還有 ADSI (Analogue Display Services Interface) 對談式應用 (Telephone Management、E-bank、E-mail)

相關功能還有在掛機時傳送有留言的訊息 (Visual Message Waiting Indication, VMWI)

## Type I
有兩種傳送方式，DTMF 跟 FSK，FSK 又分成 V.23 跟 Bell 202。DTMF 的訊息只能送號碼，[FSK 的訊息](http://lirobo.blogspot.tw/2009/11/fsk-cid-format.html)有時間日期 (SDMF)，或者加上名子 (MDMF)。

DTMF 跟 V.23 都是在振鈴之前送，而 Bell 202 是在第一段振鈴之後的長停歇送。

FSK 使用 audio frequency-shift keying 傳送，baud rate 是 1200±1%，用高低兩種頻率分別表示 space (0) 及 mark (1)，訊號規格有 Bell 202 及 V.23 兩種：

1. [Bell 202](http://en.wikipedia.org/wiki/Bell_202)：通常在振鈴第一聲跟第二聲之間的長停歇 (long silence period，第一聲結束 500ms 後，第二聲開始 200ms 前，短停歇的前後振鈴視為一個振鈴)，受話端未接起時
	* Space: 2,200±22 Hz, Mark: 1,200±12 Hz。Transmit signal level: -13.5±1.5 dBm into 900 ohm. 
2. V.23：在響鈴前的極性反轉後
	* Space: 2100±1.5%, Mark: 1300±1.5%
	* Received signal level for mark : -8 dBV to –40 dBV
	* Received signal level for space : The received signal levels may differ by up to 6 dB for mark and space.
	* Unwanted signals : Total power of extraneous signals in the voice band 300~3400Hz are at least 20dB below the signal levels.

台灣的 FSK 用 V.23，但使用 Dual Tone Alerting Signal (DTAS) 通知 Caller ID 訊息開始，然後開始振鈴。

* DTAS (100±10 ms, 2130 + 2750 Hz) &rarr; 45 ~ 500 ms &rarr; FSK data &rarr; 200 ~ 500 ms &rarr; 振鈴

傳送時，將日期時間、號碼、或名子包裝成 SDMF 或 MDMF 格式，包括產生 checksum。再來是產生 sample 資料，FSK baud rate 1200，在取樣率 8000 時，每 3 symbols 20 samples (每個 symbol 有 6 個或 7 個取樣)。

每個 octet 10 symbols：start(0) LSB .... MSB stop(1)

Channel Seizure Signal &rarr; Mark &rarr; Message Type + Message Length + Presentation Layer Message + Checksum

* Channel Seize Signal：250ms 共 300-symbol 0101... (相當於 30 octets 10101010)
* Mark Signal：150ms 共 180-symbol 111...
* SDMF 或 MDMF 格式的資料，每個 byte 前面加 start bit 0，依序由 LSB 送到 MSB，然後加 stop bit 1，可以額外插入最多 10 個 mark 作為小暫停。

## Call Waiting
步驟：

1. 局端送 CAS tone
	* 一開始會有 0 ~ 300 ms OSI 訊號 (非必要)，再來交換機會暫時靜止遠端的聲音送入 0 ~ 60 ms，並送出一個插播聲音 SAS 250ms ~ 1 sec. 經過 0 ~ 50 ms 的間斷，交換機送出 CAS 2130 + 2750 Hz 約 80 ~ 85 ms 的複頻音
2. 話機 on-hook &rarr; off-hook &rarr; ACK
	* 話機偵測到 CAS Tone 後作一個並機測試，如果沒並聯的分機佔線才發出一個 "D" Tone 給局端即所謂的 ACK 回應訊號 (靜音避免送出刺耳的 FSK 聲音)。局端會等待 ACK 約 160±5 ms 的時間
3. 局端送 CID，用戶端顯示 Caller ID，最後用戶端結束靜音
	* 局端先送 50 ~ 500 ms 的間隔，然後送資料，緊接著 OSI 和 0 ~ 320 ms 間格，最後回到通話狀態

## ADSI
## VMWI
FSK 除了用在振鈴期間送 caller ID 外，也可在 on-hook 非振鈴時送，例如 Visual Message Waiting Indication (VMWI) 用 MDMF

Message Type 0x82: Message Waiting Notification &nbsp;Type=0x0B, Length=1, Indication on=0xff, Indication off=0x00

## 延伸閱讀
* https://sites.google.com/site/molexliao/Home/caller-id-sms
* [Format](http://www.melabs.com/resources/callerid.htm)
* [Caller ID FAQ](http://www.ainslie.org.uk/callerid/cli_faq.htm)
* Call Waiting Caller ID
* Voice Mail Waiting Indicator：話機上有個燈，表示有留言。
* http://matthieu.benoit.free.fr/cid_dsp.htm
* http://www.picbasic.co.uk/support/tml_callerid_cnt.pdf
* CLASS (custom local area signaling services)
