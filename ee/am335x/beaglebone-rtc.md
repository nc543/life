RTC 在無外部電源時仍要維持時間計數，當外部電源恢復且無法線上取得時間時，還有一定的時間準確度。無外部電源時，依賴電池維持 RTC 運作，需要把其它電路電源都關閉，才能減少電池的消耗、延長 RTC 的生命。

從文件或網路都找不到 BeagleBone Green 使用 AM335x 內建 RTC 的資訊，甚至有[文件](http://www.ti.com/lit/ug/slvu551i/slvu551i.pdf "Powering the AM335x with the TPS65217x")提到 BeagleBone Grenn 使用的電源管理晶片 [TPS65217C](http://www.ti.com/product/TPS65217) 不支援 RTC 單獨運作，但為什麼呢？

要用 BeagleBone Green AM335x 內建的 RTC 需要了解各種電源怎麼供應的，才能在只有電池

 提供 BeageBone Black/Green 電源管理及轉換 (接 I<sup>2</sup>C0，CONFIG_MFD_TPS65217 及 CONFIG_REGULATOR_TPS65217)、TL5209 3.3V 電源轉換

TPS65217C power-on sequence

1. 選擇電源 5V 來源，依優先序可來自 AC (P9-5:6, VDD_5V)、USB (P4 &micro;USB, USB_DC) 或 BAT (電池接點 TP5, TP6, TP7, TP8)，提供 SYS (5V) 給其它所有電源。
	* 作為 LDO 電源，立即輸出基本待機電源 LDO1 (1.8V 250mA)
		* (R7) 提供 LDO_PGOOD、PGOOD、SYS_RESETn 電源
		* (R5) 提供 WAKEUPn pull high, AM335x RTC 電源。
		* (R8, R9 切換成 LDO3) AM335x VDDS
	* 20ms 後輸出 LDO_PGOOD 來釋放 AM335x RTC 的重置，AM335x 再決定要不要 PWR_EN
	* P9-7:8
	* 其它電源包括 LED 都有開關
	* USB 亦接到 AM3358，用途待查
2. WAKEUPn until PWR_EN 啟動 DCDC1 (1.5V 1.2A)。
	*  DDR3L SDRAM 電源，可設為 1.35V 來省電
3. LDO3 (1.8V 285mA)：提供 AM335x 其它需要 1.8V 電源的地方
4. LDO2 (3.3V)：點 POWER LED
5. LDO4 (3.3V 400mA)：(VDD_3V3A) 提供 .. 以及啟用 TL5209A 提供 VDD_3V3B
6. DCDC2 & DCDC3：分別是 CPU MPU 及 CPU Core 電源，皆為 1.1V 1.2A。可設定提高 CPU MPU 電壓來超頻 CPU。
7. 20ms 後輸出 PGOOD 釋放 AM335x 重置

可以使用內建 RTC 嗎？

* TPS65217A 給 AM335x ZCE 包裝用，VDD_MPU 跟 VDD_CORE 是接在一起的。剩下是給 ZCZ 包裝用，VDD_MPU 跟 VDD_CORE 可以是獨立的。
* TPS65217B DDR2 電源 DCDC1 = 1.8V
* TPS65217C DDR3 電源 DCDC1 = 1.5V，不支援 AM335x RTC-only operation (why???)
* TPS65217D 跟 TPS65217C 只差在 DDR3L 電源 DCDC1 = 1.35V

SYS

* LDO、LDO3、LDO4、DCDC1, DCDC2, DCDC3 電源
* TL5209 電源，提供 3.3V max. 500mA，但 .. 才會啟用
* LED 電源
* USB 電源，... 才會啟用

