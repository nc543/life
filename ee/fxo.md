* [LED 顯示響鈴 ](http://lirobo.blogspot.tw/2014/02/led.html)
* 電壓偵測

## FXO power

on-hook 時可用多少電？off-hook 時呢？

話機狀態：on-hook, ringing, off-hook

降壓穩壓限流

https://www.maximintegrated.com/en/app-notes/index.mvp/id/1923 Draw 150mW of Isolated Power from Off-Hook Phone Line

http://www.edn.com/design/power-management/4315670/Get-power-from-a-telephone-line-without-disturbing-it Get power from a telephone line without disturbing it

http://rtony56789.pixnet.net/blog/post/27467768

## Line status 偵測
光耦合器 in a voltage divider resistor network in tandem
* 0 V：電話線沒接
* ~0.45 V：off-hook
* 5V 或 digital 1：on-hook

seize the line：可在 protection fuse 及 varistor 之後使用 reed relay 及電阻。

## 其它
1. ring detection
1. caller ID detection (on-hook DTMF/FSK detection)
1. off-hook
1. DTMF detection (http://lirobo.blogspot.tw/2015/11/dtmf-decoder-hm9270d.html)
1. tone generation
1. on-hook
* IN4001, IN4148S

1. 十秒內 ring + CID 符合三次接起 (設定：時間、次數、CID)
1. 偵測 DTMF 碼作為指令
	* 設定回應：成功 -> 一短聲，失敗 -> 三短聲
	* 查詢會應：yes ->兩短聲，no-> 一長聲
1. 掛斷 (timeout, 指令)

[Si3050 + Si3011/18/19](https://www.silabs.com/Support%20Documents/TechnicalDocs/Si3050-11-18-19.pdf) Voice DAA
	* Si3050 可以透過 SPI 或 GCI，SPI 可以 daisy chain 多顆 Si3050
	* 不處理 Caller ID
Si32919
	* 搭配 Si32178，同時有 FXS

http://lirobo.blogspot.tw/2015/09/fxodaa.html
http://lirobo.blogspot.tw/2012/09/fxs-uart.html

AVR FXS/FXO：ATmega406 有 12-bit ADC

##
在一對雙絞線<br>
<ul><li>Disconnected</li>
<li>DC loop current</li>
<ul><li>DC</li>
<li>hook</li>
<ul><li>dial pulse</li>
<li>flash: 20ms ~ 2sec</li></ul>
<li>ringing: 20 Hz</li></ul>
<li>AC audio signal</li>
<ul><li>transmit and receive</li>
<ul><li>DTMF, FSK, Voice, Fax, Modem, ...</li></ul>
<li>xDSL<br>
</li></ul></ul>
<br>
FXS<br>
<a href="http://lirobo.blogspot.tw/2012/09/fxs-uart.html">http://lirobo.blogspot.tw/2012/09/fxs-uart.html</a><br>
<br>
Si3217x + Si32911/19 Single-Chip ProSLIC® <br>
<br>
Si32178/9<br>
<h2>Si3210</h2>
<code>The registers about ringing generation list in Si3210 Datasheet Table 30 (p. 43)</code><br>
<br>
<br>
<code>Currently, the sinusoidal ringing is used, and RCO=0x7EF0, RNGX = 0x0160</code><br>
<code>coeff = RCO/(2^15) = 32496/32768</code><br>
<code>VPK = 64V (i.e., ring voltage)</code><br>
<br>
<br>
<code>The REN or current depends on how much power VBAT can provide.</code><br>
<code>Current VBAT setting should be -75V (DR74=0x32)</code><br>
<br>
<br>
<code>Ring current for 1 REN is VPK / 6900 ohm = 9.3 mA</code>
<h2>USB</h2>
<a href="https://openusbfxs.wordpress.com/">Open USB FXS</a>: PIC18F2550 + Si3210 + Si3201<br>
<ul><li>oufxs DAHDI driver：<a href="http://code.google.com/p/openusbfxs/">http://code.google.com/p/openusbfxs/</a>sangoma <a href="http://www.sangoma.com/telecom-interface-boards/analog-voice-boards/usb_fxo.html">u100</a> (wanpipe)</li></ul>
digium s100u (wcusb): Tiger560B <br>
<ul><li><a href="http://www.earth.li/~noodles/hardware-usbfxs.html">http://www.earth.li/~noodles/hardware-usbfxs.html</a></li></ul>
xorcom (xpp_usb)<br>

## Si3210
constant voltage zone
* 由 TIP-to-RING Open-circuit voltage (V<sub>OC</sub>) 定義
* 0 V to 94.5 V in 1.5 V  steps
constant current zone
* 由 loop current limit (I<sub>LIM</sub>) 定義
* 20 mA to 41 mA in 3 mA steps

inherent dc output resistance (R<sub>O</sub>) of 160Ω

## 電話線網路

## 電話線供電系統
電話線是厝內現成的 48V 電源供電系統，由電信公司提供給所有並接的話機

可供電瓦數，損耗
mΩ/m
AWG 越小越粗

電話線線徑 2C 一般為 0.65mm，多P線為 0.5mm。
電信機房到家用的是 0.4mm 多P 銅纜線...(600P)

網路線強調高頻信號傳輸，對絞的目的就是要減少雜音(Noise)，串音(Crosstalk)等干擾，橙/白橙，綠/白綠絞線次數每英吋約4次，藍/白藍,棕/白棕絞線次數每英吋約3次。

有廠牌的 CAT6 網路線 23 AWG

### 並聯供電
跟隨電壓供應電流
電話可能摘機，所以供應電流只能緩慢增加

### 沒用的線路獨立供電

##
[利用電話線供電的雙音門鈴電路圖](http://cocdig.com/docs/show-post-33268.html)
