BeagleBone Black 內建有 HDMI 功能，由 HDMI Framer TDA19988 驅動 HDMI 訊號，透用 µHDMI 插座輸出。

[指出 AM3358、TDA19988、及 µHDMI 的 BeagleBone Black 照片]

## 支援的解析度

TDA19988 是 HDMI 1.4a 傳送器，向後相容 DVI 1.0

It allows mixing 3 x 8-bit RGB or YCbCr video stream at pixel rate up to 165 MHz together with S/PDIF or I2S-bus audio streams at audio sampling rate up to 192 kHz.
integrates a full programmable input formatter and color space 
conversion block.
The video input formats accepted are YCbCr 4 : 4 : 4 (up to 3 x 8-bit), YCbCr 4 : 2 : 2 semi-planar (up to 2 x 12-bit) and YCbCr 4 : 2 : 2 compliant with ITU656 (up to 1 x 12-bit). In case of ITU656-like format, the input pixel clock can be made active on one (SDR mode) or both edges (DDR mode).

TDA19988AHN and TDA19988AET only include a HDCP 1.4 compliant cipher block. The 
HDCP keys are stored interna
lly in a non-volatile OTP memory for maximum security.

150 MHz pixel rate HDMI 1.4a transmitter with 
3 x 8-bit video inputs, HDCP and CEC support


The HDMI hardware on the BeagleBone Black uses version 1.4a of the specification.
1280x1024 (MAX)
1024x768,1280x720,1440x900 ,1920x1080@24Hz

## TDA19988 需要的訊號

16b HDMI,
w/EDID Support

A single HDMI interface is connected to the 16 bit LCD interface on the processor. The 16b interface was used to preserve as many expansion pins as possible to allow for use by the user. The NXP TDA19988BHN is used to convert the LCD interface to HDMI and convert the audio as well. The signals are still connected to the expansion headers to enable the use of LCD expansion boards or access to other functions on the board as needed.
The HDMI device does not support HDCP copy protection. Support is provided via EDID to allow the SW to identify the compatible resolutions. Currently the following resolutions are supported via the software:
 1280 x 1024
 1440 x 900
 1024 x 768
 1280 x 720

The BeagleBone Black has an onboard HDMI framer that converts the LCD signals and audio signals to drive a HDMI monitor. The design uses an NXP TDA19988 HDMI Framer.

The BeagleBone Black has an onboard HDMI framer that converts the LCD signals and audio signals to drive a HDMI monitor. The design uses an NXP TDA19988 HDMI Framer.

The maximum resolution supported by the BeagleBone Black is 1280x1024 @ 60Hz. Table 9 below shows the supported resolutions. Not all resolutions may work on all monitors, but these have been tested and shown to work on at least one monitor. EDID is supported on the BeagleBone Black. Based on the EDID reading from the connected monitor, the highest compatible resolution is selected.

HDMI Supported Monitor Resolutions RESOLUTION AUDIO
800 x 600 @60Hz
800 x 600 @56Hz
640 x 480 @75Hz
640 x 480 @60Hz
YES
720 x 400 @70Hz
1280 x 1024 @75Hz
1024 x 768 @75Hz
1024 x 768 @70Hz
1024 x 768 @60Hz
800 x 600 @75Hz
800 x 600 @72Hz
720 x 480 @60Hz
YES
1280 x 720 @60Hz
YES
1920x1080@24Hz
YES
NOTE: The updated software image used on the Rev A5B board added support for 1920x1080@24HZ.

Audio is limited to CEA supported resolutions. LCD panels only activate the audio in CEA modes. This is a function of the specification and is not something that can be fixed on the board via a hardware change or a software change.

## HDMI Framer
TDA19988 是 HDMI 1.4a transmitter，並相容 DVI 1.0。
The HDCP mode is not used in the design. The non-HDCP version of the device is used in the BeagleBone Black design.

This device provides additional embedded features like CEC (Consumer Electronic Control). CEC is a single bidirectional bus that transmits CEC over the home appliance network connected through this bus. This eliminates the need of any additional device to handle this feature. While this feature is supported in this device, as of this point, the SW to support this feature has not been implemented and is not a feature that is considered critical. It can be switched to very low power Standby or Sleep modes to save power when HDMI is not used. TDA19988 embeds I2C-bus master interface for DDC-bus communication to read EDID. This device can be controlled or configured via I2C-bus interface.


HDMI Framer TDA19988 (LCD_DATA, McASP0, I2C0, 可關掉的 24.576 MHz 振盪器)
LCD
I<sup>2</sup>C
int
I2S
Clk
24.576
