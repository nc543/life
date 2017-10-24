## 4-20mA Current Loop
4-20mA 電流迴圈在工業監控應用上常用來傳送感應器資訊，例如溫度、壓力、速度、流速等，特別是 300 米以上的長距離資料傳送。

感應器的輸出電壓轉換成 a proportional 電流，通常 4mA 代表最小值，20mA 代表最大值。遠端的接收器再轉成電壓。

長距離傳送電壓，除非使用非常高的輸入阻抗，不然經過接線的電阻會有壓降。高輸入阻抗
對雜訊較敏感，用有遮蔽的線可以減少干擾，但也增加了成本。

長距離傳送電流產生的壓降跟傳輸線的距離成正比 (loop drop)，然而這壓降並不會減小
4-20mA 電流，只要傳輸器跟 loop supply 可以補償 loop drop。

電路迴圈由三個部份串接起來：
1. 迴圈電源：提供整個系統運作電源，常用 +24V，+12V 等
2. 感應器及傳送器
	* 傳送器能驅動 20mA 輸出的最大迴圈電阻。
	* 最小運作電壓，最大容忍電壓
	* 從迴圈取得電源，運作消耗需小於 4 mA
	* sensor/transducer：提供輸出電壓，其值代表量測值。
	* 電壓到電流轉換器 (transmitter and/or signal conditioner)：轉換成proportional 4-20mA 直流電流。
3. receiver/monitor：電流轉換成電壓。大部份是純電阻輸入，結合 zener 二極體來限制最大電壓。

LTC3105

## 4–20 mA Current Loop with HART

## 參考
* [4-20mA Current Loop Primer](http://www.murata-ps.com/data/meters/dms-an20.pdf)
* [Power & Signal Over A Single Wire Do More With Less](http://www.eetimes.com/author.asp?section_id=36&doc_id=1326167&)

Combining power and data wires [Part 1](http://www.embedded.com/electronics-blogs/without-a-paddle/4439353/Combining-power-and-data-wires--Part-1) [Part 2](http://www.embedded.com/electronics-blogs/without-a-paddle/4439429/Combining-power-and-data-wires--Part-2)



It is possible to configure some three-wire sensors for a current output and then use them as two wire devices. For instance the LM35 temperature sensor is a three-wire device — supply, ground, and signal. By connecting the output to the ground pin via a 200 Ω resistor, the device regulates the current flowing in proportion to its temperature. This allows the device to be remotely connected using two wires as you can see in Figures 16, 17, and 19 of the data sheet (linked above).

http://www.ti.com/lit/ds/symlink/lm35.pdf
