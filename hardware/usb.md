# USB

USB 接頭
* Type
	* Type-A：長方形接口，目前市面上大多隨身碟使用
	* Type-B：大多手機連接埠使用
	* Type-C：對稱的扁形接口，最高 100 瓦的供電輸出以及支援 HDMI、VGA、DisplayPort 影片輸出。
* Standard A 插頭與插座 (有 USB 3.1 版本向前支援)、Standard B 插頭與插座、USB 3.1 Standard B 插座可插 USB 3.1 或之前的 Std-B 插頭
* Mini-A 插頭與插座、Mini-B 插頭與插座、Mini-AB 插座
* Micro-A 插頭、Micro-B 插頭與插座、Micro-AB 插座 (USB OTG)、USB 3.1 Micro-B 插座可插 USB 3.1 或之前的 Micro-B 插頭
* Lightning
* MHL (Mobile High-Definition Link)

傳輸介面
* 無論是哪種 USB 接頭 (USB Type-A / Type-B / Type-C)，都可以搭載不同的傳輸介面 (USB 1.0 / USB2.0 / USB3.0)。

用 USB 充電

充電標準
* Battery Charging (BC) 1.2 Standard
	* 標準下行埠 (Standard Downstream Port, SDP) 最多 500 mA
	* 充電下行埠 (Charging Downstream Port, CDP)，在 low-/full-speed 時可達 1.5 A，但在 Hi-speed 大約只能 900 mA
	* 專用充電埠 (Dedicated Charging Port, DCP)，可加大充電電流例如到 2.0 A，不需要完整的 USB Controller
* Charging Protocols：透過溝通決定充電電流，USB Battery Charging 1.0 specification > 1.1 > 1.2, China's YDT-1591 spec.
* Apple
	* D+ = D- = 2.0V：0.5A (電腦)
	* D+ = 2.0V, D- = 2.7V：1.0A (iPhone 充電器)
	* D+ = 2.7V, D- = 2.0V：1.5A (iPad 充電器)
	* D+ = D- = 2.7V：2.4A (2.4 充電器)
* 三星
* 中國 YD/T1591 - 2009
* 過電流保護

訊號|USB|micro/mini-USB|Lightning|說明
----|---|--------------|---------|----
VBUS| 1 | 1            | 4       |Red 5V±5% 電源
D-  | 2 | 2            | 6       |White
D+  | 3 | 3            | 7       |Green
ID  | - | 4            |         |OTG 作為 Host 時接地，slave 時空接。
GND | 4 | 5            | 8       |Black
Type A 插頭接點向上時，接腳由右到左分別為 1、2、3、4。

5V 電源

一個單位 100mA，最多 500mA

有兩種充電模式，一般俗稱為「USB 模式」和「AC 模式」。USB 模式屬於標準充電模式，裝置會將輸入電流限制在 500mA 以下。AC 模式輸入電流可達500mA以上。

其它大多就 USB 所規範定義的 D+、D- 腳位短路，裝置就會判定得以 AC 模式進行快速充電

D+、D-：使用 NRZI 的 differential data signals。連續六個 1 時，bit stuffing 一個 0 來避免太久沒準位變動。電壓準位low: 0.0~0.3V, high: 2.8~3.6V

USB 周邊 pullup D+ 表示 full-speed、pullup D- 表示 low-speed。

一個USB插座最多提供500mA，也就是約2.5W。如果併兩個USB插座則可達5W。連接的設備一開始使用 low-power mode (最多100 mA)，然後要求它所需的電流大小再切到 high-power mode。Host controller可以關掉一些設備來避免過載。

OTG 線兩端分別是 mini-A 插頭跟 mini-B 插頭。插入 mini-A 插頭端的設備預設為主機角色，另一端則預設為周邊角色，但可經由 Host Negotiation Protocol 協調交換彼此的角色。OTG 的主機功能是有限制的，因為手持裝置不像電腦那麼容易加入各種周邊的驅動程式，只能各自列表說明它支援哪些週邊。

插 入 mini-A 插頭的設備必須提供電源至少 8mA ，但資料停止傳送後可以關掉以達到省電的目的；另一端 OTG 設備 (除了用mini-AB插座外，也可能採用 mini-B 插座或 mini-A 插頭) ，最多消耗 8mA，並且能夠使用 Session Request Protocol 叫醒主機送電。

mini-AB 插座，可以接受 mini-A 或 mini-B 插頭，並且多一個 ID pin。 mini-A 插頭的ID是接地，而 mini-B的是空接。插入 mini-A 接頭的設備必須提供至少8mA電流，資料停止傳送後可以關掉電源省電。並預設為主機角色， 。Adapters allow connection to standard USB sockets.

[USB On-The-Go Basics](https://www.maximintegrated.com/en/app-notes/index.mvp/id/1822)
[Tutorial: USB On-The-Go (OTG)](http://www.nxp.com/acrobat/literature/9397/75009316.pdf)

延伸閱讀
    http://www.chipworks.com/en/technical-competitive-analysis/resources/blog/systems-analysis-of-the-apple-lightning-to-usb-cable/：有 IC NXP SP3D2、STMicroelectronics USB2A、TI BQ2025、及 Unknown manufacturer with markings identified as 4S (functionality is known)

速度一開始時 D+ 跟 D- 亦用來決定 slave 速度，D+ pull high 表示是 high speed 或 full speed，D- pull high 表示是 low speed。


USB UART bridge
* FTDI FT232R
* CP21xx USB bridge from Silicon Laboratories : UART or I²C，不需要外部 crystal oscillator.

USB scope
* [The cheapest dual trace scope in the galaxy](http://yveslebrac.blogspot.tw/2008/10/cheapest-dual-trace-scope-in-galaxy.html)

USB Wifi Analyzer
USB Classes
* 相同 class 的裝置或界面有一些共同的屬性或服務，通常會有類似的資料通訊格式，由 Class Specification 定義 class 的相關需求，可共用驅動程式。
* 參考：[USB Common Class Specification 1.0](http://www.usb.org/developers/docs/devclass_docs/usbccs10.pdf)

====================
USB 是樹狀架構，透過 USB hubs 分支出去，所有 USB 連接線都是點對點的，一端是往上游主機，另一端往下游週邊。

一般的週邊使用 USB 5V 的電小於 100 mA，經過週邊要求，最多可用到 500 mA。

USB 的資料訊號 D+ 及 D- 是阻抗 90Ω ±15% 的雙絞線，約 3、4 伏特左右。在主機端，兩者有 15 kΩ pull-down，在沒驅動的時候，訊號停在所謂的 single-ended zero (SE0) 狀態，表示 reset 或 disconnected。10~20 ms SE0 表示 reset。當 D+ 及 D- 一個為 high，一個為 low 為 J 或 K 狀態。

USB 速率有三種 (名稱|速率|認定方式|說明)
* Low Speed (LS): 1.5 Mbit/s ±15000 ppm。週邊端 1.5 kΩ 拉高 D- 表示 LS。
* Full Speed (FS): 12 Mbit/s ±2500 ppm。週邊端 1.5 kΩ 拉高 D+ 表示 FS。所有 USB hubs 都支援 FS。
* High Speed (HS): 480 Mbit/s ±500 ppm。週邊端 90 Ω terminate D+ 及 D-，需經過 chirping 步驟來 negotiate。USB 2.0 才有，往前相容，如果需要的話可回到 FS 運作。

chirping 步驟：週邊端先當作自己是 FS，拉高 D+，然後當收到 USB RESET 後改拉高 D− (K) 告訴主機端要用 HS。如果主機端支援 HS，會回 JK 告訴週邊端。週邊端至少要收到 3 sets of KJ chirps 才能切換到 HS。

USB 採用 NRZI 編碼，toggle (J 及 K 切換) 表示 0，不變 (維持 J 或 K) 表示 1，六個連續 1 要作 bit-stuffing，多加一個 0。

A USB device pulls one of the data lines high with a 1.5 kΩ resistor. This overpowers one of the pull-down resistors in the host and leaves the data lines in an idle state called "J".

A USB packet begins with an 8-bit synchronization sequence '00000001'. That is, after the initial idle state J, the data lines toggle KJKJKJKK. The final 1 bit (repeated K state) marks the end of the sync pattern and the beginning of the USB frame. For high bandwidth USB, the packet begins with a 32-bit synchronization sequence.

A USB packet's end, called EOP (end-of-packet), is indicated by the transmitter driving 2 bit times of SE0 (D+ and D− both below max) and 1 bit time of J state. After this, the transmitter ceases to drive the D+/D− lines and the aforementioned pull up resistors hold it in the J (idle) state. Sometimes skew due to hubs can add as much as one bit time before the SE0 of the end of packet. This extra bit can also result in a "bit stuff violation" if the six bits before it in the CRC are '1's. This bit should be ignored by receiver.

===============
```
    USB 系統是 tree 架構，一個 Master (Host) 及許多 Slaves (Devices)，資料傳送統一由 Host 指揮 (device request)，除了 wakeup。
    USB 的 transaction 由不同 Packet ID (PID) 的資料封包達成。 PID 有四類：Token, Data, Handshake, Special.
        Token:
            OUT：表示 host 要送資料給 device
            IN：表示 host 要收 device 的資料
            SETUP: preface eight bytes of data from which the peripheral decodes host Device Requests.
            SOF (Start Of Frame)：每 1 ms 送一次，每次 11-bit 的 frame count 加一。
        Data: DATA0 及 DATA1 交錯使用，用來偵測 ACK 遺失。
        Handshake: ACK, NAK, STALL
            ACK：success
            NAK：busy, try again。不是 error，A USB device indicates an error by not responding.
            STALL： means that something unforeseen went wrong (probably as a result of miscommunication or lack of cooperation between the software and firmware writers). A device sends the STALL handshake to indicate that it doesn’t understand a device request, that something went wrong on the peripheral end, or that the host tried to access a resource that isn’t there. It’s like “halt,” but better, because USB provides a way to recover from a stall.
        Special: PRE (Preamble): precedes a low-speed (1.5 Mbps) USB transmission.
    Send data to a USB peripheral：the host issues an OUT token followed by the data. If the peripheral accepts it without error, it returns an ACK. If it is busy, it instead sends a NAK. If it finds an error, it sends nothing back. For the latter two cases, the host re-sends the data at a later time.
    Sending Data to the Host
    A USB device never spontaneously sends data to the host. Nevertheless, in the EZ-USB chip, there’s nothing to stop the 8051 from loading data for the host into an endpoint buffer and arming it for transfer. But the data will sit in the buffer until the host sends an IN token to that particular endpoint. If the host never sends the IN token, the data sits there indefinitely.

PID TYPE D7-D4
SETUP 1101 (D Hex)
IN 1001 (9 Hex)
OUT 0001 (1 Hex)
SOF 0101 (5 Hex)
PREAMBLE 1100 (C Hex)
NAK 1010 (A Hex)
STALL 1110 (E Hex)
DATA0 0011 (3 Hex)
DATA1 1011 (B Hex)

Transfer Types: Bulk, Interrupt, Isochronous

Bulk: Bulk data is bursty, traveling in packets of 8, 16, 32, or 64 bytes. Bulk data has guaranteed accuracy, due to an automatic re-try mechanism for erroneous data. The host schedules bulk packets when there is available bus time. Bulk transfers are typically used for printer, scanner, or modem data. Bulk data has built-in flow control provided by handshake packets.
IN/OUT+ADDR+ENDP+CRC5
DATA1/DATA0+Payload+CRC16
ACK

Interrupt: 類似 bulk，但只有 IN。packet sizes of 1-64 bytes. Interrupt endpoints have
an associated polling interval that ensures that they will be pinged (will receive an IN token) by the host on a regular basis.

Isochronous data is time-critical and used for streaming data like audio and video. Time of delivery is the most important requirement for isochronous data. In every USB frame, a certain amount of USB bandwidth is allocated to isochronous transfers. To lighten the overhead, isochronous transfers have no handshake (ACK/NAK/STALL), and no retries. Error detection is limited to a 16-bit CRC. Isochronous transfers do not use the data toggle mechanism; isochronous data uses only the DATA0 PID.

Control transfers are used to configure and send commands to a device. Being mission critical, they employ the most extensive error checking USB offers. Control transfers are delivered on a best effort basis by the host. Control transfers consist of two or three stages.

    SETUP:
        SETUP+ADDR+ENDP+CRC5
        DATA0+8-byte SETUP data+CRC16
        ACK
    DATA (optional):
        IN+ADDR+ENDP+CRC5
        DATA1+Payload data + CRC16
        ACK
    STATUS (handshake): allows the device to indicate successful completion of a control operation
        OUT+ADDR+ENDP+CRC5
        DATA1+CRC16
        ACK

Enumeration

    The host sends a “Get_Descriptor/Device” request to address zero (devices must respond to address zero when first attached).
    The device dutifully responds to this request by sending ID data back to the host telling what it is.
    The host sends the device a “Set_Address” request, which gives it a unique address to distinguish it from the other devices connected to the bus.
    The host sends more “Get_Descriptor” requests, asking more device information. from this, it learns everything else about the device, like how many endpoints the device has, its power requirements, what bus bandwidth it requires, and what driver to load.
```
==========
```
The information in the /proc/bus/usb/devices output is arranged in groups:

    T (topology):
        Bus indicates which bus the device is on.
        Lev (level): 00 = root hub, 01 = any device attached to the root hub, 02 = devices attached to hubs at level 01, and so on.
        Prnt is the parent device for this device (always 00 for the root hub, and 01 for the devices attached to the root hub).
        Port is the port on the parent device, starting at 00 for the first port on each device. Prnt/Port is unique per bus.
        Cnt indicates what number device this is, at this level, based on the enumeration order within that level of the topology, starting at 01 for the first device.
        Dev# indicates what number device this is, irrespective of level, based on the bus enumeration order. This is unique per bus.
        Spd (speed in Mbps): either 1.5 or 12 with the current version of USB.
        MxCh indicates how many devices can be connected to this device, and is 00 for anything except a hub.
        Driver indicates which device driver is being used for this device - an entry of (none) indicates that no driver is being used.
    B
    D (device descriptor):
        Ver: claims to meet which USB specification version
        Cls (device class in both hexadecimal and as a string). A Cls entry of 00(>ifc) indicates that the device class specification compliance is interface dependent, and the interface descriptor should be read for device class information.
        Sub indicates which sub-class (within the Cls entry), the device meets.
        Prot indicates which protocol within a class or sub-class the device claims to meet.
        MxPS indicates how big the packets from Endpoint 0 are.
        #Cfgs indicates how many configurations this device has.
    Much like D:, the line that starts with P: is information from the device descriptor, and is seperated mainly because it wouldn't all fit on one line. Vendor indicates the Vendor Identification code for the device, and ProdID indicates the Product Identification code for the device. Rev indicates the product revision number.
    S:, if any, are the vendor and product strings that the device returned.
    C (configuration descriptor): the number of C:lines per device is given by #Cfgs, and the entry followed by an asterisk is the current configuration. #If indicates how many interfaces the device has. Cfg# indicates which configuration is being described. Atr is a hexadecimal indication of the device attributes (0x80 for bus-powered, 0x40 for self-powered, 0x20 for remote wake-up capable). MxPwr is the maximum power draw for this device configuration, in milliamps.
    I (interface descriptor): the number of I: lines per C: line is given by the #Ifs entry.
        If# indicates which interface is being described within a given device configuration.
        Alt indicates which alternate setting of this interface is being described.
        #EPs indicates how many endpoints there are within the alternate setting for this endpoint.
        Cls indicates which class the alternate setting of the interface corresponds to, in both hexadecimal and as a character string.
        Sub indicates which sub-class the alternate setting of the interface belongs to.
        Prot indicates which interface protocol (within a class and sub-class tuple) the alternate setting of the interface conforms to.
        Driver indicates which of the various USB drivers has claimed this interface.
    E (endpoint descriptor): the number of E: lines per I: line is given by the #EPs entry. Endpoint 0 is not displayed.
        Ad: endpoint address and an In or Out endpoint.
        Atr indicate the attribute (transfer type) associated with the endpoint, followed by a string translating the transfer type.
        MxPS indicates the maximum packet size this endpoint is capable of sending or receiving, as appropriate.
        Ivl: polling interval in milliseconds of interrupt endpoints. Ivl is ignored for bulk and control transfers, and is set to 1 for isochronous transfers.

Refer to linux/Documentation/usb/proc_usb_info.txt for more information on using the USB device filesystem information. 
```
