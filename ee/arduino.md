## digispark
http://lirobo.blogspot.tw/2013/07/digispark.html

## ATtiny
http://lirobo.blogspot.tw/2013/11/attiny.html

## uDuino 3V

ATmega168 最低操作電壓是 2.7V，可跑到 10MHz。超過 6 HMHz，耗電會高於 2mA。
ATmega168AP 跟 ATmega328P 最低操作電壓是 1.8V，在 2.4V 可跑到 8MHz，耗電低於 2mA，可用兩顆充電電池當電源

## Arduino GSM/GPRS plus GPS daughter card by Futura Elettronica
based on SIM900 or SIM908 to make voice and data connections via GSM/GPRS.
two 3.5-mm connectors for a microphone and headset

## AVR picoPower
* 只需 650 nA (100 nA in power down)
* 可操作在 1.6V，但須降頻
* 其它

ATmega328P
* 20MHz: 4.5V+
* 16MHz: 4.0V+
* 12MHz: 3.3V+
* 10MHz: 2.7V+
* 4MHz: 1.8V+

## 記憶體
http://playground.arduino.cc/Learning/Memory
http://pizgchen.blogspot.tw/2017/03/arduino-1.html

##
http://lirobo.blogspot.tw/2010/06/arduino.html<br>
<br>
AVR IDE 開發：<a href="http://elabz.com/arduino-shrunk-how-to-use-attiny13-with-arduino-ide/">Arduino shrunk – how to use ATtiny13 with Arduino IDE</a>
<ul><li>在 Linux Arduino IDE 環境增加 ATtiny13 支援</li>
<li>Linux Arduino IDE 已含有 C/C++ 編譯器E – <i>AVR-GCC</i>，及 AVR in-system programming 軟體 –  <i>avrdude</i></li>
<li>IDE 目錄或使用者的 sketchboot 目錄 -- ~/sketchbook/</li>
<ul><li>hardware/<b>xxxx</b>/boards.txt：設定檔包含一些硬體資訊 -- programming (upload) 資訊、fuse 設定 (處理器的固定設定)、處理器速度,&nbsp; 函式庫等。 </li>
<li>hardware/<b>xxxx</b>/cores/：hardware-specific C libraries，例如 hardware/arduino/cores/ 放 arduino 的硬體函式庫</li></ul>
<li>Tools→Board 選擇</li>
<li>Tools→Programmer 選擇</li>
<li>接 Programmer </li>
<li>Tools→Burn Bootloader (只需做一次)</li>
<li>寫程式</li>
<li>File Upload Using Programmer</li></ul>
<br>
Multimeter<br>
<a href="http://members.shaw.ca/Botgoodies2/MegaMeter/MegaMeter.htm">Mega Meter</a><br>
<a href="http://arduino.cc/forum/index.php/topic,16174.0.html">http://arduino.cc/forum/index.php/topic,16174.0.html</a><br>
<br>
Current Monitor<br>
<a href="http://www.ti.com/product/ina219">TI INA219 Current/Power Monitor</a><br>
TI INA210/INA211/INA212/INA213/INA214 Current-Shunt Monitor<br>
ZXCT1009<br>
ZXCT1021<br>
<br>
ArduGate：<a href="http://www.arduinodev.com/software/ardugate/">http://www.arduinodev.com/software/ardugate/</a><br>
<br>
紅外線遙控器：http://coopermaa2nd.blogspot.tw/2011/04/22-keypad.html<br>
<br>
Arduino Spectrum Analyzer：<a href="https://www.google.com/url?q=https%3A%2F%2Fgithub.com%2Ffrack%2FArduino-SpectrumAnalyzer&amp;sa=D&amp;sntz=1&amp;usg=AFrqEzdvXc4wzQZESFFR2vWHty6XlpvQ_A">https://github.com/frack/Arduino-SpectrumAnalyzer</a><br>
<br>
Arduino + CYWM6935<br>
<br>
Convert Optical Mouse into Arduino Web Camera：Optical mouse -&gt; Arduino -&gt; Ethernet Shield -&gt; PC /w node.js + socket.io as webserver <a href="http://frenki.net/2013/12/convert-optical-mouse-into-arduino-web-camera/">http://frenki.net/2013/12/convert-optical-mouse-into-arduino-web-camera/</a><br>
<br>
Wi-Fi router 安裝 OpenWrt 及 WebUI，透過 USB 轉 UART 控制 Arduino<br>
<a href="http://ediy.com.my/index.php/projects/item/42-wireless-router-home-automation">Wireless Router Home Automation</a><br>
<a href="http://ediy.com.my/index.php/blog/item/40-send-message-to-serial-port-or-router-using-lua">Sending Message to Serial Port of Router using Lua</a><br>

