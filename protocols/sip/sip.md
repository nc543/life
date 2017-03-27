 [VoIP Basics](https://telconotes.wordpress.com/2013/02/11/voice-over-ip-voip-basics/)
 [Introduction to SIP](https://telconotes.wordpress.com/2013/02/17/introduction-to-sip/)
http://www.kamailio.org/docs/tutorials/sip-introduction/
 [A Basic SIP Call Flow](https://telconotes.wordpress.com/2013/02/27/a-basic-sip-call-flow/)
 [SIP INVITE Request-line & R-URI](https://telconotes.wordpress.com/2013/03/01/sip-invite-request-line-r-uri/)

SIP INVITE
* Request URI 跟 To URI 的用途 (轉接 R-URI 但 To-URI 會變？)
* From URI 跟 Contact URI 的用途


SIP 類似 HTTP，是一個 request-response 協定，不同請求有不同 method，各有標準使用方式。call setup 用 INVITE、call tear-down (hangup) 用BYE。此外 REFER for call transfers and MESSAGE for SMS-like text messages. The SIP INFO method for 兩端 UA 交換訊息
