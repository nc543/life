# GPS
* waypoint (路點、方位點)：獨立的標記點，如照相的地點或使用者手動標記的休息站或路口等等；
* 軌跡點 (trackpoint)：GPS 裝置自動定時記錄的路點。
* track (軌跡、航跡紀錄)：走過的路徑座標記錄起來成一串有順序的軌跡點，可能包含走錯的路，通常含有時間訊息。(Oruxmaps 軌跡預設為紅色) 記錄點的採樣根據衛星接收器(或是 App)上的設定有關
* route (航線、路程)：一串有順序的軌跡點作為預設的路徑，可由軌跡整理而來。
	* routepoint：
* 座標系統：GPS 使用 WGS84。台灣常用的大地基準座標有三種：WGS84、TWD97 與 TWD67，其中 TWD97 跟 WGS84 幾乎相同並適用於全球。而 TWD67 僅限用於臺灣地區，跟 TWD97 的差異在東西向約 828 公尺，南北向約 200公尺。目前國防部空軍救護隊及內政部空勤總隊直升機都依據 WGS84 執行救援任務。

軌跡檔、航線檔
* GPX (<u>GP</u>S e<u>X</u>change Format)： XML 的通用標準格式，內含緯經度、高度、及時間的軌跡點串接而成的軌跡，以及路點的紀錄。
	* gpx
		* metadata
		* trk
			* name
			* trkseg
				* trkpt lat lon
					* ele
					* time
* KML (Keyhole Markup Language)：XML 格式用在前主是 Keyhole 公司的 Google 地球，可包含影像記錄的方位點。KMZ 是 ZIP 2.0 壓縮的 KML。
* GDB (Garmin GPS database)：Garmin 導航裝置使用的檔案，格式未公開。
	* 線上轉成 GPX 或 KML：http://www.gpsvisualizer.com/convert_input
	* Garmin MapSource
	* Garmin BaseCamp
	* gpsbabel

編輯可用 viking

圖資
* OpenStreetMap 地圖合併等高線圖資，例如 www.viewfinderpanoramas.org、[ASTER](https://asterweb.jpl.nasa.gov/gdem.asp) 及[內政部20公尺網格數值地形模型資料](http://data.gov.tw/node/35430)。
* [MOI.OSM](https://dl.dropboxusercontent.com/u/899714/maps/taiwan_topo.html)
	* 每週四發行，使用當日 [OSM](http://openstreetmap.tw) 的圖資。
	* MOI 來自 [Rex](http://blog.nutsfactory.net) 轉換 “[內政部 20 公尺網格數值地形模型資料](http://tgos.nat.gov.tw)” 而成的等高線，可用來做一般登山參考。探勘式登山建議仍搭配經建三版地形圖 (地圖產生器)。
	* Style 由綬草北三兄與 Rudy 共同設定，作為合適登山與尋寶（hiking/geocaching）風格樣式。
	* [臉書社團](facebook.groups/taiwan.topo)。
* [ASTER.OSM - Taiwan TOPO](https://sites.google.com/site/asterosmtaiwantopo/)：OpenStreetMap 跟 ASTER GDEM v2 合而為一製成
* 下載位址:http://goo.gl/I6Xxka 包含:
	1. 台灣等高線地圖(JING 製作,地圖切分 16 檔案,等高線 10M)
	2. 台灣等高線地圖(單一檔案,等高線 20M,資料來源:OpenStreet Map)
	3. 台灣百岳路徑(行走軌跡),由登山前輩收集
	4. 台灣小百岳 GPX
	5. 台灣各大郊山路徑(山岳前輩阿銘與阿容在 Google 硬碟分享)
	6. 等高線風格樣式設定
	7. 國內外各大線上地圖圖資設定

軌跡下載
* 登山補給站
* [地圖產生器](http://map.happyman.idv.tw/twmap/login.php)
* [地圖瀏覽器](http://map.happyman.idv.tw/~happyman/twmap3/)
* 健行筆記
* 馬克褚工作室 -- 自行車與登山
* Google
* [航跡分享](https://www.facebook.com/groups/1631034120482669)[檔案](https://www.facebook.com/groups/1631034120482669/files/)

## APP
* https://drive.google.com/file/d/0B4Lt5N7jhnjzMkZ5QUFlMFdEU2M/view
	* OruxMaps：「tracklogs」「mapfiles」「mapstyles」

[Locus MAP](http://www.locusmap.eu/)
* [使用手冊](http://docs.locusmap.eu)
* [Locus 經驗](https://sites.google.com/site/asterosmtaiwantopo/locus)
* [使用台灣百年歷史地圖](http://gis.rchss.sinica.edu.tw/gps/?p=1814)
* https://www.mobile01.com/topicdetail.php?f=628&t=4385125

綠野遊蹤及[離線圖資](http://sea.tokyo.idv.tw/?p=3004)

登山客 (iPhone)

OsmAnd Maps (iPhone)

## 上傳 OSM
http://docs.locusmap.eu/doku.php?id=manual:advanced:map_tools:osm

## 參考及延伸閱讀
* 加速定位：GPS 依距上次使用定位的時間與距離，可分為冷開機、暖開機、熱開機。冷開機時，GPS 需透過衛星重新下載定位所需資料，可能需要15分鐘。可透過網路下載 aGPS 資料，可加速初次定位的速度 (例如用「GPS狀態」APP)。暖開機的前提是年曆資料未超過一星期、已有目前時間、距離上次定位未超過 100 公里，可以在 60 秒內定位。
* [手機GPS登山](https://sites.google.com/view/mobilegpshiking)
* [OSM 相關登山用手機軟體使用常見問題](https://osmtw.hackpad.com/OSM--kauuIuQ27tR)
* http://lirobo.blogspot.tw/2016/09/gps.html
* https://bluebottle.idv.tw/?p=3910
* http://bluebottle.idv.tw/?p=3909
