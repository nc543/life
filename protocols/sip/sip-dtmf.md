* In-band Audio 內建音頻產生：是由SIP終端設備直接模擬出DTMF訊號，編碼後當做通話聲音的一部分來傳送，但有可能在傳送過程中因延遲、封包漏失而導致音頻訊號失真，或因為雙方音頻太大或太小聲，使接受端無法準確的判斷。通常不建議使用。
* RFC 2833 DTMF (Out of Band) RTP轉帶DTMF訊號：發送端將DTMF的音頻內容承載在RTP語音封包內，接受端再解碼復原播放DTMF音頻。(RFC 2833規範)
* SIP INFO 轉帶DTMF 訊號：在通話中將DTMF音頻訊號以數位方式模擬為SIP的控制訊息發送至Proxy Server，並視需要再轉送到接受端。(RFC 2976 規範)

http://lirobo.blogspot.tw/2009/12/dtmf-relay.html
