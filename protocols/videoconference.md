H.320：ISDN

H.323 IP based videoconferencing
* UDP 1718：Gatekeeper Discovery (if a Gatekeeper is used)
* UDP 1719：Gatekeeper RAS (if a Gatekeeper is used)
* TCP 1720：Call Setup
* TCP 1731：Audio Call Control
* UDP 1024~65535：Audio/Video Data

SIP：缺乏 H.320 或 H.323 有的 structured call control 來維護及 delivering 呼叫，在 professional videoconferencing deployments 並未廣泛採用。

A Gatekeeper, one of the optional components to an H.323 network can be used to manage routes and control bandwidth between endpoints.

bonding：多個 BRA (128k per line) 可一起使用。先建立單一 BRA 的 call，然後再請求額外的 BRA。

http://proavschool.com/understanding-isdn-and-ip-videoconferencing-part-1/
