* [LED 顯示響鈴 ](http://lirobo.blogspot.tw/2014/02/led.html)

## FXO power

話機狀態：on-hook, ringing, off-hook

降壓穩壓限流

https://www.maximintegrated.com/en/app-notes/index.mvp/id/1923 Draw 150mW of Isolated Power from Off-Hook Phone Line


http://www.edn.com/design/power-management/4315670/Get-power-from-a-telephone-line-without-disturbing-it Get power from a telephone line without disturbing it

## 其它
1. ring detection
1. caller ID detection (on-hook DTMF/FSK detection)
1. off-hook
1. DTMF detection (http://lirobo.blogspot.tw/2015/11/dtmf-decoder-hm9270d.html)
1. tone generation
1. on-hook

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
