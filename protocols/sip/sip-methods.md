Call Setup 相關
* [INVITE](http://lirobo.blogspot.tw/2010/10/sip-invite.html) [RFC3261](http://tools.ietf.org/html/rfc3261 "SIP: Session Initiation Protocol)
	* 建立 SIP 通話，採用 INVITE → 200 OK → ACK 3-way handshake，其中 INVITE 跟 200 OK 用 SDP 溝通通話媒介的參數。
	* re-INVITE
* ACK [RFC3261](http://tools.ietf.org/html/rfc3261 "SIP: Session Initiation Protocol")
	* 搭配 <a href="http://lirobo.blogspot.tw/2010/10/sip-invite.html">INVITE</a> 使用，確認其最後的回應。
* BYE [RFC3261](http://tools.ietf.org/html/rfc3261 "SIP: Session Initiation Protocol)
	* 掛斷結束 Dialog。
in-dialog
out-of-dialog
* NOTIFY [<a href="http://tools.ietf.org/html/rfc3265">RFC3265</a>]
	* 事件通知。
* PUBLISH [RFC3903](http://tools.ietf.org/html/rfc3903)
	* 可用來設定自身的狀態，例如「線上」、「忙碌」等。
* SUBSCRIBE [<a href="http://tools.ietf.org/html/rfc3265">RFC3265</a>]
	* Event/Expires 說明要訂閱的事件及時間， 例如訂閱他人的狀態，訂閱成功與否會以 NOTIFY method 通知。

查 <a href="http://www.iana.org/assignments/sip-parameters">Session Initiation Protocol (SIP) Parameters</a> 有下列 Methods：<br />
<br>
<dl>
<dt>CANCEL [<a href="http://tools.ietf.org/html/rfc3261" title="SIP: Session Initiation Protocol">RFC3261</a>]</dt>
<dd>取消等候的請求。</dd>
<dt>INFO [<a href="http://tools.ietf.org/html/rfc6086" title="Session Initiation Protocol (SIP) INFO Method and Package Framework">RFC6086</a> ← <a href="http://tools.ietf.org/html/rfc2976" title="The SIP INFO Method">RFC2976</a>]</dt>
<dd>dialog 內兩端 UA交換</dd>
<dt>MESSAGE [<a href="http://tools.ietf.org/html/rfc3428">RFC3428</a>]</dt>
<dd>可用來傳送即時訊息</dd>
<dt>OPTIONS [<a href="http://tools.ietf.org/html/rfc3261" title="SIP: Session Initiation Protocol">RFC3261</a>]</dt>
<dd>詢問能力，例如看 UA 或 Server 還在不在。</dd>
<dt>PRACK [<a href="http://tools.ietf.org/html/rfc3262">RFC3262</a>]</dt>
<dt>REFER [<a href="http://tools.ietf.org/html/rfc3515">RFC3515</a>]</dt>
<dd><ul>
<li>使用專有的 Refer-To 告訴對方第三方資訊，正常會回 2xx 並隱含訂閱 (SIP SUBSCRIBE) 了相關事件，後續發展對方會用同樣 dialog 的 NOFITY 通知，內含「Event: refer」及 message/sipfrag 類型的 SIP Response Status-Line。</li>
<li>可用來進行轉接 (call transfer) 等應用。轉接流程可參考 <a href="http://www.vocal.com/sip-2/call-transferring/">http://www.vocal.com/sip-2/call-transferring/</a></li>
</ul>
</dd>
<dt><a href="http://lirobo.blogspot.tw/2016/07/sip-register.html">REGISTER</a> [<a href="http://tools.ietf.org/html/rfc3261" title="SIP: Session Initiation Protocol">RFC3261</a>]</dt>
<dd>跟 SIP registrar 註冊自己的位置及週期。這些資料彙整到 location server 供查詢。最終反應到受話端的 Contact: 欄位。   </dd>
<dt>UPDATE [<a href="http://tools.ietf.org/html/rfc3311">RFC3311</a>]</dt>
</dl>
<br />
延伸閱讀：<a href="http://lirobo.blogspot.tw/2015/01/sip.html">本站其它 SIP 文章</a>

-------
      INVITE [RFC3261]             REGISTER [RFC3261]
      OPTIONS [RFC3261]            BYE [RFC3261]
      UPDATE [RFC3311]             INFO [RFC6086]
      MESSAGE [RFC3428]            REFER [RFC3515]

