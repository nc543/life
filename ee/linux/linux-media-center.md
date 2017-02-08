# Linux 多媒體播放器

## 硬體
* Raspberry Pi：價格低、體積小、耗電少、無噪音，推得動 1080p 的影片，支援 CEC。
* ASUS VivoMini UN62
* ASUS VivoMini UN66：有 CEC 接頭

HTPC (Home Theater Personal Computer)

HTPC header

## Kodi
[Kodi](https://kodi.tv) 的前身是 XBMC (XBox Media Center)，原本是為了在 XBox 上播放影片、音樂、電視、照片 ... 等用途的程式，漸漸擴展到其它平台。

使用 Kodi 時的一個重要工具, 就是 scraper, 中文稱之為"刮削器"
外掛i「附加元件」 (Add-on) 中的一種, 自動從網路上取得多媒體內容的各種相關資訊, 例如影片海報、介紹等等, 以便建構內容豐富的家庭娛樂中心。

命名原則
[Kodi: 2 – 刮削器](http://www.homeoffice.idv.tw/2015/07/8330)
[Kodi: 3 – 影片檔案的命名](http://www.homeoffice.idv.tw/2015/07/8347)
[Kodi: 5 – 安裝電影資訊的刮削器](http://www.homeoffice.idv.tw/2015/08/8415)

### Linux 發行版
[OSMC (Open Source Media Center)](https://osmc.tv) 前身是「RaspBMC」，是整合 XBMC 的 Linux 發行版。

[OpenELEC] 同樣是整合了 XBMC 的 Linux 發行版，但作了不少的最佳化，運作速度比 OSMC 快了許多。

[Xbian]

## 透過 HDMI 控制電視
CEC 是傳輸，使用 DDC

USB to CEC Adapters exist that allow a computer to control CEC-enabled devices. 

一些 HDMI-CEC 指令
* One Touch Play: the device will become active source when playback starts
* System Standby: switches all connected devices to standby
* Preset Transfer: transfers the tuner channel setup to another TV set
* One Touch Record: start recording immediately
* Timer Programming: allow one device (e.g. a TV set or HTPC) to set the timer programming of another (e.g. a PVR/DVR or DVD-recorder)
* System Information: checks all components for bus addresses and configuration
* Deck Control: playback control
* Tuner Control: control the tuner of another device
* OSD Display: use the OSD of the TV set to display text
* Device Menu Control: use the menus of another device
* Routing Control: control the switching of signal sources
* Remote Control Pass Through: pass through remote control commands
* Device OSD Name Transfer: transfer the preferred device names to the TV set

顯示器使用 physical address 0.0.0.0 及 logical address 0
所有啟用 CEC 的設備會有 physical 及 logical 位址，而非 CEC 裝置只有 physical 位址。Physical addresses are taken up based on the position of the device with respect to the root. For example, if an A/V receiver's output is connected to HDMI1 of the TV, it gets the physical address 1.0.0.0. A device connected to the first HDMI input port of the A/V receiver would get the address 1.1.0.0, while one connected to the second HDMI port would get 1.2.0.0.

邏輯位址依據功能。
* 0：顯示器
* 15：廣播

When the HDMI device menu is brought up on the display (On a Sony KDL46EX720, this is achieved by pressing the Sync Menu button), the display sends a broadcast over the CEC wire to all the downstream devices. It then collects the responses arriving over the CEC wire and presents the user with a list of CEC enabled devices. Choosing one of them ensures that future remote key presses are transferred by the TV to that particular address. 

深入了解：QuantumData's excellent [CEC whitepaper](http://www.quantumdata.com/pdf/CEC_White_Paper.pdf) 及 CEC 規範

Media center systems XBMC and MythTV already support HDMI-CEC via libCEC[1][2]; libCEC gained support for the Raspberry Pi in version 1.8.0[3], allowing you to control them via your television remote control without having a dedicated HTPC / MCE remote for your Raspberry Pi

http://elinux.org/CEC_(Consumer_Electronics_Control)_over_HDMI
[HDMI CEC protocol](http://kezeodsnx.pixnet.net/blog/post/28219224)
[HDMI CEC 的一點補充](http://www.cash.idv.tw/wordpress/?p=8411)
[CEC Addressing - Quantum Data](www.quantumdata.com/pdf/CEC_HDMI_Conference_Final.pps)


BRAVIA Sync
