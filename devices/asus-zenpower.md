# ZenPower
使用說明
* http://www.asus.com/zentalk/tw/forum.php?mod=viewthread&tid=66396 或 http://www.mobile01.com/topicdetail.php?f=588&t=4257231 有使用說明書照片
* 電池容量9600mAh、額定電容量(6510mAh/32.55Wh)
* 215g
* LED 顯示
	* 按電源開關或插入裝置時啟動，依剩餘電量顯示，5 秒後會自動關閉
	* 放電時會依剩餘電量慢閃
	* 四顆快閃時為錯誤，重新拔插 USB 線可排除
* 負載過小時會自動關閉
* 可同時放電跟充電嗎？
* 11 重安全保護機制：溫度保護、短路保護、Rest 保護、輸入過壓保護、輸出過壓保護、輸入防反保護、輸出過流保護、電芯 PTC 保護、充電器保護、Jetia 保護。

主要元件
* 三顆鋰電池 LGABE 11865 並聯 3.75V
* [MPS MP2636](http://www.monolithicpower.com/DesktopModules/DocumentManage/API/Document/getDocument?id=3331) 充電電池充放電 IC
	* 充電模式及升壓放電 (boost) 模式
	* 建議充電電壓 4.5V~6V
* 賽微電子 CW3002 USB 充電辨識 IC
* HOLTEK HT68F30-1 MCU，用於電量顯示及行動電源功能控制

參考來源
* [ASUS初心作品ZenPower 9600mAh行動電源簡介及測試](http://wolflsi.pixnet.net/blog/post/60000268)

* V-Mount鋰電池:單顆PAGlink電池的電力為96瓦-小時、14.8V、6.5Ah
