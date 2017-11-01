# NFC (Near-field communication)
近場通訊、近距離無線通訊

RFID 演變而來，運行在 13.56 MHz 的短距無線電技術，傳輸速度 106 ~ 424 Kbit/秒，在相距 4 公分之內時開始進行通訊的協定。

NFC 標籤通常包含 96 ~ 8192 byte 資料，本身不需要電源，可透過無線電電力被動讀取，在特定情況可寫入。

完整的 NFC 裝置可以用三種模式運作：
1. 卡模擬模式 (Card emulation mode)：模擬成 NFC 標籤，可以替代大量的 IC 卡。
2. 讀卡機模式 (NFC reader/writer)：讀取 NFC 標籤。
3. 對等模式 (P2P mode)：用於資料交換，如下載音樂、交換圖片或者同步電話薄。

應用
* 非接觸支付系統，像過去信用卡與電子票券卡刷卡一樣。
* 車票、門票
* 電子身分證和鑰匙卡。
* 從海報上讀取相關資訊
* 在社群網路，分享聯絡方式、相片、影片或檔案。
* 提供設定簡便的低速連接，也可用於引導能力更強的無線連接，如藍芽、Wi-Fi。

參考
* wikipedia
* RFID 標籤或 NFC 標籤可以想成是光線的反射
* [NFC 動手玩！DIY 做 NFC 標籤，讓生活更有智慧](https://cjay.cc/2012/08/nfc)：台北大眾交通工具的 IC 代幣有 48 bytes 的資料儲存空間，清除後可寫入 4 種手機動作

NDEF (NFC Data Exchange Format)：標準的 NFC 資料格式，包括寫到 NFC 標籤的「NDEF Records」及作為對等通訊用的「NDEF Messages」。
* NDEF Records
* NDEF Messages：basic "transportation" mechanism for NDEF records, with each message containing one or more NDEF Records.
https://learn.adafruit.com/adafruit-pn532-rfid-nfc/ndef
http://www.nfc-forum.org/specs/spec_list/ for 《NFC Data Exchange Format (NDEF) Technical Specification》和《NFC Record Type Definition (RTD) Specification》

NXP White Paper - NFC Forum Type Tags


保密方式

