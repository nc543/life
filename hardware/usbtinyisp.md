# USBtinyISP

* 用三根 IO (PD2/PD3/PD6) 模擬低速 USB 介面，透過 SPI 燒錄 AVR
* 核心處理器是 ATtiny2313-20P
	* 2KB Flash, 128B SRAM, 128B EEPROM
	* PWM, Analog Comparator
	* 20MHz, 工作在 12MHz 需要 5V 取自 USB
* 韌體 USBtiny
* 軟體
	* AVRDUDE
	* 其它
* RS-232 介面沒用到，或許可改為 TTL RS-232 轉 USB

* PB0: LED
* PB1: NC
* PB2: NC
* PB3: NC
* PB4: RST out
* PB5: MOSI out
* PB6: MISO in
* PB7: SCK out
* PD0: NC (RxD)
* PD1: NC (TxD)
* PD2: USB
* PD3: USB
* PD4: buffer enable
* PD5: LED2
* PD6: USB

http://lirobo.blogspot.tw/2010/06/usbtinyisp.html
https://learn.adafruit.com/usbtinyisp
