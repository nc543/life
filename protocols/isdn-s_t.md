# BRI S/T Reference Point

NT 跟 TE 間的界面，可接一個 NT 及 8 個 TE，定義在 ITU-T I.430，至少兩對雙絞線分別作為傳跟收使用，使用 RJ-45 或 RJ-48 接頭。
* 速率 192 kbps，每 250µS 48 bits 的 frame，包含 36-bit 2B+D 等。
* pseudo-ternary 編碼：1 = 0V；0 = +750mV 跟 -750mV 交錯出現
	* DC balanced (no DC current) 使得電感電容耦合較容易，減少靜電及串音，接線可以長些。
	* 用 bipolar violation 表示 frame 開始
* TE 同步 NT 的傳送速度及 frame，並延後 2-bit 傳送，偵測到衝突就不再送
* 20 frames 形成 multi-frame，由 M-bit 辨別 multi-frame 開始，用來定義 Q-channel 20-bit 的欄位。

F|L|B1|E/L|D|A/L|F<sub>A</sub>|N/L|B2|E/L|D|M/L|B1|E/L|D|S/L|B2|E/L|D|L
-|-|--|---|-|---|-------------|---|--|---|-|---|--|---|-|---|--|---|-|-
1|1|8 |1  |1|1  |1            |1  |8 |1  |1|1  |8 |1  |1|1  |8 |1  |1|1

* F, L, N
	* F: + 的 bipolar violation 表示 frame 開始，之後還需要的 - 的 bipolar violation 來維持 DC balance
	* L: 維持 DC balance
	* N: F<sub>A</sub> 相反，確保 - 的 bipolar violation 至少在此之前發生
* B1, B2, D, E：包含兩組 2B+D，E 是 NT echo 收到的 D。
* A: activated
* F<sub>A</sub>: Q channel
* M：Multi-frame
* S：Spare-bit

連線初始化
* INFO 0：雙方不送訊號
* INFO 1：TE 送 192 kbps 的 +-111111 (類似 HDLC flag)
* INFO 2：NT 送 I.430 frame，其中 B-/D-/E-/A-bit 為 0
* INFO 3：TE 送 I.430 frame，其中 B-/D-bit 為 0
* INFO 4：NT 送 I.430 frame，其中 A-bit 為 1、B-/D-/E-bit 開始運作
