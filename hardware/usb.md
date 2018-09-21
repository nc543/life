# USB

插入 mini-A 插頭的設備必須提供電源至少 8mA ，但資料停止傳送後可以關掉以達到省電的目的；另一端 OTG 設備 (除了用mini-AB插座外，也可能採用 mini-B 插座或 mini-A 插頭) ，最多消耗 8mA，並且能夠使用 Session Request Protocol 叫醒主機送電。

mini-AB 插座插入 mini-A 接頭的設備必須提供至少8mA電流，資料停止傳送後可以關掉電源省電。並預設為主機角色， 。Adapters allow connection to standard USB sockets.

[USB On-The-Go Basics](https://www.maximintegrated.com/en/app-notes/index.mvp/id/1822)
[Tutorial: USB On-The-Go (OTG)](http://www.nxp.com/acrobat/literature/9397/75009316.pdf)

延伸閱讀
    http://www.chipworks.com/en/technical-competitive-analysis/resources/blog/systems-analysis-of-the-apple-lightning-to-usb-cable/：有 IC NXP SP3D2、STMicroelectronics USB2A、TI BQ2025、及 Unknown manufacturer with markings identified as 4S (functionality is known)

USB scope
* [The cheapest dual trace scope in the galaxy](http://yveslebrac.blogspot.tw/2008/10/cheapest-dual-trace-scope-in-galaxy.html)

USB Wifi Analyzer
USB Classes
* 相同 class 的裝置或界面有一些共同的屬性或服務，通常會有類似的資料通訊格式，由 Class Specification 定義 class 的相關需求，可共用驅動程式。
* 參考：[USB Common Class Specification 1.0](http://www.usb.org/developers/docs/devclass_docs/usbccs10.pdf)

====================
USB 是樹狀架構，透過 USB hubs 分支出去，所有 USB 連接線都是點對點的，一端是往上游主機，另一端往下游週邊。

一般的週邊使用 USB 5V 的電小於 100 mA，經過週邊要求，最多可用到 500 mA。

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

The basic types of transactions are as follows:
■■ Control. Used to configure and enumerate a peripheral, allowing the host software to interrogate the
peripheral to find out what it is and how it can use it. Every peripheral needs to support this traffic type.
■■ Bulk. Reliable data transport that guarantees sequential reception of data. Retransmits are used to ensure
the data is received correctly. Depending on the current bus utilization, the throughput with bulk transfers
will vary. Typical uses of bulk transport are Disk-On-Keys and printers.
■■ Interrupt. Meant for low bandwidth transfers with periodic transport needs. The host pre-schedules an
interval at which the peripheral is queried. Unlike bulk, this transport type is guaranteed allocation on the bus
for transport. The typical use is keyboards, mice, track-balls, and game controllers.
■■ Isochronous. Guaranteed bandwidth, but not guaranteed reception. This method is typically associated
with video cameras and audio speakers. It is used to insure that the data always has a path. During
enumeration and configuration, the host determines if a configuration setting has enough bandwidth to talk
with a certain peripheral. If sufficient bandwidth is not available, it rejects the configuration selection in favor
of less bandwidth consumption.
All peripherals support a single control endpoint and any number of bulk, interrupt, and isochronous endpoints to
fit their application up to the maximum of 32 endpoints.
