# BRI U Reference Point

ISDN 交換機 (Line Termination, LT) 跟 Network Termination 1 (NT1) 之間的界面，定義在 ANSI T1.601，使用 RJ-11 中間一對雙絞線作雙向各 160 kbps 傳輸，距離可達 18,000 feets，通常是指 Digital Subscriber Line
* 80 kbaud 2B1Q 編碼速率 160 kbps，每 1.5ms 240 bits 的 frame，包含 18-bit synchronization word (SW)、216-bit 2B+D、及 6-bit M-channel (Maintenance channel)。
* NT1 同步 ISDN 交換機的時間
* 8 frames 形成 superframe，由 SW 傳送 Inver SW (ISW) 來辨別 superframe 開始，定義 M-channel 6 * 8 = 48-bit 的欄位。

Frame#|1-18|19 - 234| 235 | 236 | 237 | 238   | 239 | 240
------|----|--------|-----|-----|-----|-------|-----|----
1     |ISW |12x 2B+D|a1   |a2   |a3   |act    |1    |1
2     | SW |12x 2B+D|dm   |i1   |i2   |dea/ps1|1    |febe
3     | SW |12x 2B+D|i3   |i4   |i5   |sco/ps2|crc1 |crc2
4     | SW |12x 2B+D|i6   |i7   |i8   |1/ntm  |crc3 |crc4
5     | SW |12x 2B+D|a1   |a2   |a3   |1/cso  |crc5 |crc6
6     | SW |12x 2B+D|dm   |i1   |i2   |1      |crc7 |crc8
7     | SW |12x 2B+D|i3   |i4   |i5   |uoa/sai|crc9 |crc10
8     | SW |12x 2B+D|i6   |i7   |i8   |aib/nib|crc11|crc12

M-channel 包括：
* act: start up bit, set 0 during start up
* aib: alarm indication bit
* eoc (embedded operation channel): a1 a2 a3 dm i1 i2 i3 i4 i5 i6 i7 i8
* dea
* sco
* uoa (U–only–activation)
* ps1, ps2
* ntm
* cso
* sai
* nib
* febe (far–end block error)
* crc
