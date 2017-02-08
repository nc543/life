### Raspberry Pi 1
BCM2835 ARM11767JZF-S(ARMv6) @700 MHz 512MB DDR2
LAN9512 提供 Ethernet

### Raspberry Pi 2 Model B
BCM2836 quad-core Cortex-A7 (ARMv7) @900MHz
1GB RAM

LAN9514 提供 Ethernet

4 USB ports
40 GPIO pins
Full HDMI port
Ethernet port
Combined 3.5mm audio jack and composite video
Camera interface (CSI)
Display interface (DSI)
Micro SD card slot
VideoCore IV 3D graphics core

### Raspberry Pi 3
BCM2837 Quad core Cortex A53 (ARMv7) 512K L2, 64-bit 4x ARM Cortex-A53 @1.2 GHz
LAN9514 提供 Ethernet
http://www.jeffgeerling.com/blogs/jeff-geerling/getting-gigabit-networking


###
CM1 (基於 Raspberry Pi B+) 4G eMMC
CM3 (基於 Raspberry Pi 3) 1G DDR2, 4G eMMC
CM3L 同 CM3 無 eMMC
沒有內建 MII，Ethernet 需由 USB 或其它界面提供。

GPIO

Secondary Memory Interface (SMI)
* asynchronous NAND type bus supporting Intel mode80 type transfers at 8-/16-bit and available in the ALT1 positions on GPIO banks 0 and 1.
* 可作為 shared memory interface 嗎？

Display Parallel Interface (DPI)

SD/SDIO Interface
* SD0：a proprietary Broadcom controller, primary interface 用來開機及 talk to the eMMC or SDX_x signals.
* SD1：可接 SD, SDIO and eMMC devices，例如在 Raspberry Pi 3 用 SDIO 模式接到 BCM43438 WiFi
Both interfaces can support speeds up to 50MHz single ended (SD High Speed Mode).

CSI (MIPI Serial Camera)

DSI (MIPI Serial Display)

USB OTG

HDMI V1.3a

Composite (TV Out)
