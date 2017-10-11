# Bluetooth
Bluetooth 是固定或行動裝置短距離交換資料的無線技術標準，使用在 2.4~2.485 GHz ISM band 的 short-wavelength UHF radio waves 建立 personal area network (PAN)。

Bluetooth 規格由 Bluetooth Special Interest Group (SIG) 管理，IEEE 曾標準化為 IEEE 802.15.1，但後來沒繼續維護。

Bluetooth 是 master/slave 架構的封包協定，一個 master 可以跟 7 個 slave 通訊。除了少用的 broadcast 模式，資料是由一個 master 選擇跟一個 slave 間通。一個 slave 可能有多個 master。

官方 Class 3 radios 可傳 1 公尺、Class 2 10 公尺、Class 1 100 公尺。市面上 Class 2 大致 5~10 公尺、Class 1 大致 20~30 公尺。

## Bluetooth 版本
* 1.0, 1.0B：仍有許多問題
* 1.1：修正問題，IEEE 802.15.1-2002
* 1.2：改進干擾忍受度、速度可達 721 kbit/s 等，IEEE 802.15.1-2005
* 2.0 + EDR：增加 EDR 選項讓 bit rate 3 Mbit/s 使得最大資料傳送速率達 2.1 Mbit/s，可降低 duty cycle 來省電。其它小改善。
* 2.1 + EDR：新增 secure simple pairing (SSP) 改善配對及 security。其它改善包括 Extended inquiry response (EIR) 在 inquiry 提供更多資訊作為連結前更好的過濾; sniff subrating 在 low-power mode 減少 power 消耗
* 3.0 + HS：新增 HS 選項透過 Bluetooth 的 negotiation 在 colocated 802.11 建立 link 讓資料傳送速率達 24 Mbit/s，也就是 AMP (Alternative MAC/PHY) 功能，需要 L2CAP。
	* Enhanced Retransmission Mode (ERTM) 實作 reliable L2CAP 通道，然而 Streaming Mode (SM) 實作沒有重傳及流量控制的 unreliable channel
	* Unicast Connectionless Data：允許未建立 explicit L2CAP 通道送服務資料，作為使用者 action and reconnection/transmission of data 間低延遲應用的需要，只適合少量資料。
	* Enhanced Power Control
* 4.0 + LE：包含 Classic Bluetooth、Bluetooth high speed、及 Bluetooth low energy (Wibree、Bluetooth ULP (Ultra Low Power)、BLE、Bluetooth Smart)。Classic Bluetooth 是傳統 Bluetooth 協定，Bluetooth high speed 基於 Wi-Fi，而 Bluetooth low energy 是全新的協定作為 rapid build-up of simple links aimed at very low power applications。single-mode 只實作 Bluetooth low energy，而 dual-mode 則整合 Bluetooth low energy 到 Classic Bluetooth。此外改善 Generic Attribute Profile (GATT) 及 Security Manager (SM) services with AES Encryption，改善 audio Host Controller Interface
* 4.1：軟體更新增進可用性
* 4.2：新增一些 IoT 用的功能
* 5：主要新增一些 IoT 用的功能

## Bluetooth profiles
藍芽技術的使用方式是透過 profile 規範
It resides on top of the Bluetooth Core Specification and (optionally) additional protocols.

### A2DP (Advanced Audio Distribution Profile)
藍牙音訊協定 A2DP 頻寬約 328kbps

可提供多個 A2DP 服務，每個 A2DP 可傳單向立體聲音訊
* 基於 AVDTP 協定及 GAVDP profile
	* The Audio/Video Distribution Transport Protocol (AVDTP) is used by A2DP to stream music to stereo headsets over an L2CAP channel intended for video distribution profile in the Bluetooth transmission.
基本支援是 low-complexity SBC codec (非 CVSDM)，可額外支援 MPEG-1 Part 3/MPEG-2 Part 3 (MP2 and MP3), MPEG-2 Part 7/MPEG-4 Part 3 (AAC and HE-AAC), and ATRAC，可擴展支援 aptX 等。

在實際情境，標準藍牙技術容易受到干擾，暫時中斷不影響一般簡單的數據連接。
音樂傳輸需要穩定的持續頻寬，當受到干擾會產生遲滯、中斷的現象。

藍牙立體聲音訊規範 SBC 採用高壓縮比的方式傳輸音訊，雖在規格還是達到 20-20kHz 的頻響，不過由於採用心理聲學的壓縮模式，僅設定在有限的頻寬內進行傳輸，選擇大幅壓縮人耳不易聽見的高頻部分，導致聲音的品質也連帶受影響。

CD 音質：44.1 (kHz) x 16 ( Bit ) x 2 (聲道)
aptX: 16bit @48kHz
aptX HD：24bit LPCM @48kHz，平均的在四個音域的流量進行分配，將原本完整的音訊壓縮到 1/4
蘋果 AAC：大幅削減中高頻資訊
Sony LDAC：24 bit
、aptX Low Latency

Sony LDAC 可提供高達 990kbps 的頻寬 (傳統藍芽音訊三倍資料量)，目前 24bit 96kHz 格式約需要 4.5Mbps，透過壓縮與解壓縮後 LDAC 仍能維持 24bit 96kHz PCM 格式音訊所需的 4.5Mbps 頻寬。

### AVRCP (Audio/Video Remote Control Profile)
遙控器

### Headset (HSP) or Hands-Free (HFP) profiles

## aptX on Linux NB/PC
* https://askubuntu.com/questions/425333/how-to-make-aptx-capable-bluetooth-equipment-work-with-ubuntu
* https://bbs.archlinux.org/viewtopic.php?id=189706
