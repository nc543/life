E1 30B + D (timeslot 16, timeslot 0 for synchronization)
T1 23B + D (timeslot 24)

* [Digital subscriber signalling system No. 1 (DSS1)](https://en.wikipedia.org/wiki/Digital_Subscriber_System_No._1)：Digital subscriber 是指 E1、T1、BRI 這種數位的用戶界面，DSS1 就是指用在上面的信令系統，也就是在 D 通道使用的協定。後繼的 DSS2 是用在 B-ISDN。
* Signalling System No. 7 ISDN User Part (SS7 ISUP)：SS7 是一群電話信令協定的第七代，ISUP 是其中一個部份。SS7 前身 SS5 (R1、R2 是其變種) 是用 in-band 音，會受用戶干擾。自 SS6 改用獨立的信令通道，稱為 common-channel signaling (信令使用多個用戶共用的通道)。

## 增添服務
ISDN D 通道的協定規範中，除了基本呼叫程序外，尚有增添服務 (supplementary services)，包括 UUS 等。

## ISDN UUS
UUS, User User Service, User-to-User Service, User-to-User Signalling

用戶與用戶間訊息服務

傳送 UUS 資訊用 User-user IE。除了 UUS1 implicit 外，需要先透過 Facility IE 請求協調啟動，請求分 perferred 跟 required，required 請求失敗會連帶無法建立通話。
UUS 依存在某個通話下，依通話階段分成三種服務，

ISDN 基本呼叫過程中或通話時，藉由 D 通道順便傳送附加訊息至另一端用戶，不需要另外建立第二個呼叫即可傳送額外訊息。UUS 又可係分成三類：
* UUS1：建立或結束通話時，藉由  SETUP, ALERTING, CONNECT, DISCONNECT, RELEASE, RELEASE COMPLETE 來夾帶附加訊息。
	* 分成 implicit 跟 explicit，implicit 不需要啟用請求。
	* USS1 explicit 在 SETUP 啟用請求，此時可一併送 User-user IE。在 ALERTING or CONNECT or first clearing 接受。
	* 可直接在 SETUP、ALERTING、CONNECT、DISCONNECT 或 RELEASE COMPLETE 使用。
* UUS2：在響鈴期間 (ALERTING 及 CONNECT 間) 使用 USER INFORMATION 訊息傳送，可用 More data IE，每個方向最多送兩個 USER INFORMATION。
	* 啟用：在 SETUP 送 UUS2 請求，在 ALERTING 接受
* UUS3：在通話階段使用 USER INFORMATION 訊息傳送。More data IE
	* 啟用請求：
		* 通話建立階段：在 SETUP 送 UUS3 請求，在 CONNECT 接受。
			* 請求 preferred，但網路拒絕，在 SETUP ACKNOWLEDGE, CALL PROCEEDING, PROGRESS, ALERTING or CONNECT 表示 "rejected by network"
			* 請求 preferred，但對方用戶拒絕會沒回應接不接受，在 CONNECT 表示 "rejected by user"
			* 請求 required，但網路拒絕，連線無法建立會在 DISCONNECT 或 RELEASE COMPLETE 表示 "rejected by network" 及 cause #47 "resource unavailable, unspecified" 或 cause #69 "requested facility not implemented" 或 #50 "requested facility not
subscribed"
			* 請求 required，但對方用戶拒絕，連線無法建立會在 DISCONNECT 或 RELEASE COMPLETECONNECT 表示 "rejected by user" 及 #69, "requested facility not implemented"
			* 請求 required，但對方用戶沒回應接不接受，連線無法建立，網路送 DISCONNECT 給呼叫端表示 "rejected by user" 及 #69, "requested facility not implemented"，送 DISCONNECT 給受叫端 cause #31 "normal, unspecified"
		* 通話階段只能請求 UUS3 preferred，透過 FACILITY 訊息請求或拒絕
		* 當跟 non-ISDN 網路 interworking，在 PROGRESS or an ALERTING message with the progress indicator IE 表示 #1, "call is not end-to-end ISDN; further call progress information may be available in-band", is sent to the calling user to indicate that the service cannot be guaranteed.  In the case of interworking with a non-ISDN called user, the return of a PROGRESS or an ALERTING message with the progress indicator information element indicating #2 "destination address is non-ISDN" to the calling user shall serve as indication that the full service cannot be guaranteed.
		* 如果沒啟用出現 USER INFORMATION，網路 discarded 掉並送 STATUS 訊息 cause #43 "access information discarded"
	* 可進行 congestion control： N 代表可送 USER INFORMATION 數量，一開始為 X，每 T 週期加 Y 不超過 X，每送一個就減一。預設 X = 16，Y = 8。當網路在 T 週期內收到超過 N 個 USER INFORMATION 訊息，超過的部份會被 discarded 並回 CONGESTION CONTROL 訊息包含 Congestion level IE "receive not ready" 及 cause #43, "access information discarded"。等到限制解除 (T expires)，再送 CONGESTION CONTROL 訊息包含 Congestion level IE "receive ready"。
