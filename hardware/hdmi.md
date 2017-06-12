# High-Definition Multimedia Interface

## 類比界面
舊的電視或螢幕使用類比界面接收顯示資料：
* Composite Video (黃色 RCA，CVBS, Composite Video, Blanking, and Sync.)：一個訊號由 Y (亮度，黑白) 及 UV (色彩) 合成。
* S-Video (Separate Video, Y/C)： 兩個訊號 Y (亮度) C (彩色)
* D-SUB (VGA, CRT)：五個訊號分別是 RGBHV (紅、綠、藍、水平、垂直)，另外有 I²C 訊號讀取 DDC (Display Data Channel) 資訊
* Component Video (色差)： 三個訊號 YPbPr
* SCART：整合影像跟聲音訊號，可送 Composite, RGB, YC。

## DVI
再來出現 DVI (Digital Visual Interface) 開始使用數位訊號，但也可以包含傳統 VGA 類比訊號來維持通用性，因此分成三種類型：
* DVI-D (Digital)：只有數位 RGB 訊號
* DVI-A (Analog)：只有相容 VGA 的類比 RGBHV 訊號
* DVI-I (Integrated)：混合式，數位及類比訊號皆可

DVI 只有單一組數位 RGB 訊號稱為 Single Link，包含 RGB 三對雙較線，另外還需要一對雙較線傳 clock 訊號。速度最快 165 MHz，每個 clock 送 8-bit RGB 資料共 24 bits，所以最大頻寬為 165 x 24 = 3.96Gbps。如果在影像更新頻率 60 Hz 時，每張影像最大畫素是 165MHz ÷ 60 Hz = 2.75 megapixels (含 blanking 間隔)，允許的最大解析度是 1,915 × 1,436 (4:3 ratio)、1,854 × 1,483 (5:4 ratio)、或 2,098 × 1,311 (寬螢幕 16:10 ratio)。

有兩組數位訊號 (Dual Link) 的 DVI，用來支援更高的解析度或影像更新率。

數位訊號採用 TMDS (Transition-minimized differential signaling)，是含有一種 8b/10b 編碼的差動訊號。減少電磁干擾。

The 10-bit TMDS symbol can represent either an 8-bit data value during normal data transmission, or 2 bits of control signals during screen blanking. Of the 1,024 possible combinations of the 10 transmitted bits:
TMDS 8b/10b 編碼後的 10-bit 可表示 8-bit 資料或 2-bit 控制訊號。8-bit 資料轉換方式如下：
* 第 1 bit 不變
* 剩下 7-bit 跟 bit-0 XOR 或 XNOR，看哪種產生的 transition 較少。看是用 XOR 或 XNOR 成為第 9 bit
* 前面 8 bits 再依 1 跟 0 數目平衡需要決定要不要再 invert，第 10 bit 填是否 invert

控制訊號可表示 HSync 及 VSync，採用較多 transition 的碼來增進接收器同步時脈。

C0 	C1 	codeword
--------------------------
0 	0 	0010101011
0 	1 	0010101010
1 	0 	1101010100
1 	1 	1101010101

## HDMI
HDMI 可看成 DVI-D 但採用不同的接頭，此外 HDMI 有更豐富的影像格式並整合聲音資料，以及採用 SCART 的 AV.link。

HDMI 使用數位訊號傳送封包形式的資料，含有影像區塊及聲音區塊，equivalent information 需要的頻寬比類比訊號少(?)，可支援非常 large 的解析度，可達 4096x2160 at 24 bits per pixel color depth) 及 8 通道的 24-bit @ 192 KHz的聲音。

2002 HDMI 規範 v1.0，隨著技術發展，HDMI 規範經歷許多修改及新增，支援更高的解析度及例如 3D 等新功能。

    DVI-D (只有數位 RGB)：相容 HDMI，但無聲音

v1.4a
2013.9 v2.0

一般 19 條訊號
* clock, data0, data1, data2: TMDS differential 訊號，每組包括 +、-、及 shield
* CEC (Consumer Electronics Control)：單線雙向傳送工業標準 AV.link 協定，讓設備彼此間可以溝通，使用一個遙控器就可以控制多個設備。不同製造商可能使用不同的名稱，例如 BRAVIA Sync。
* Reserved
* SCL, SDA：100kHz 的 I²C 訊號作為 DDC (Display Data Channel) 獲知顯示器的能力，傳送資料結構為 VESA Enhanced EDID（V1.3）
* Ground
* +5V
* Hot Plug Detect

TMDS

* 數位，影音交錯
* 最多 8 頻道的壓縮或未壓縮音訊
* 未壓縮視訊: 跟 DVI 相容
* Ethernet
* 距離? 

接頭
HDMI
mini HDMI
µHDMI

MHL (Mobile High-definition Link)

### ARC 及 HEC
ARC (Audio Return Channel)：使用原本沒用的接腳及 hot plug detect 接腳作為喇叭輸出用，省去另一條聲音的線
HEC (HDMI Ethernet Channel)

DisplayPort

[HDMI的前世今生－HDMI線探秘（一）](http://feature.u-audio.com.tw/featuredetail.asp?featureid=583)
[視訊介面](http://lirobo.blogspot.tw/2010/12/blog-post.html)
