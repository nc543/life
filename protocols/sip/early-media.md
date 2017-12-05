[RFC3960: Early Media and Ringing Tone Generation in the Session Initiation Protocol (SIP)](https://tools.ietf.org/html/rfc3960)

Early media：受話端接受 session 前使用的 media (e.g., audio and video) exchanged. Within a dialog, early media occurs from the moment the initial INVITE 送出到
UAS 產生最後 response. 可以是單向或雙向，可以由發話端或受話端產生。
例如受話端產生的 ringing tone and announcements (e.g., queuing status)，發話端產生的 voice commands 或 dual tone multi-frequency (DTMF) tones to drive interactive voice response (IVR) systems.

基本 SIP 規範 RFC3261 只支援很簡易的 early media 機制，對於 forking 和 security 有一些問題，不能滿足大多數應用。
RFC3960 describes two models of SIP early media implementations: the gateway model and the application server model.

gateway model 在 forking 仍有問題，但一些 SIP entities (in particular, some gateways) 無法實作 application server model，所以還是需要。

application server model 使用 the early-session disposition type, which is specified in "The Early Session Disposition Type for the Session Initiation Protocol (SIP)", RFC 3959.

## Session Establishment in SIP
沒有 early media 情況下的 offer/answer model

SIP 使用 offer/answer model 來 negotiate session 參數。
一端 - the offerer - 準備 a session description that is called the offer.
另一端 - the answerer - responds with another session description called the answer.
This two-way handshake allows both user agents to agree upon the session parameters to be used to exchange media.

例如：
offer 在 INVITE 請求，answer 在回覆的 200 OK：發話端 INVITE 時就可以準備好接收封包，不會 media clipping。media 封包可能是直送，而可能比 200 OK 早到發話端，發話端馬上講話就有可能出現 media clipping。有些情況發話端需要收到 200 OK 才能處理接收的語音封包，例如需要 QoS, media authorization, or media encryption，使用 preconditions 來避免 media clipping。
offer 在空白 INVITE 的 200 OK 回覆，answer 在 ACK：會有 media clipping，受話端送 200 OK 時可能就開始講話「喂」，但還未收到 ACK 前無法送出 media 封包。
當使用 [reliable provisional responses](https://tools.ietf.org/html/rfc3262) and [UPDATE](https://tools.ietf.org/html/rfc3311) requests，會有很多可能的方式來 exchange offers and answers.

Media clipping occurs when the user
認為 media session 已經建立，但
establishment process 尚未完成，而開始講話，
造成一開始一些資料遺失。

## gateway model
the early media session is established using the early dialog established by the original INVITE.

Early media session 在 INVITE 的最後回覆送出時結束，200 OK 轉換成 regular media session。

The gateway model consists of managing
   early media sessions using offer/answer exchanges in reliable
   provisional responses, PRACKs, and UPDATEs.

### forking

On the other hand, if the INVITE forks, the gateway model may
   introduce media clipping.
如果 INVITE 出現 fork，發話端會收到多個不同受話端 provisional response 的 answer。

大多時候發話端需要選擇一個 early media，並且送 UPDATE 來 mute 其它。但如何選呢？隨機？

   If one of the early media sessions that was muted transitions to a
   regular media session (i.e., the UAS sends a 2xx response), media
   clipping is likely.  The UAC typically sends an UPDATE with a new
   offer (upon reception of the 200 (OK) for the INVITE) to unmute the
   media session.  The UAS cannot send any media until it receives the
   offer from the UAC.  Therefore, if the caller starts speaking before
   the offer from the UAC is received, his words will get lost.

      Having the UAS send the UPDATE to unmute the media session
      (instead of the UAC) does not avoid media clipping in the backward
      direction and it causes possible race conditions.

### Ringing Tone Generation

In the PSTN, telephone switches typically 送 ringback tones 給發話端
, 表示受話端 is being alerted.  When, where,
   and how these ringing tones are generated has been standardized
   (i.e., the local exchange of the callee generates a standardized
   ringing tone while the callee is being alerted).  It makes sense for
   a standardized approach to provide this type of feedback for the user
   in a homogeneous environment such as the PSTN, where all the
   terminals have a similar user interface.

   This homogeneity is not found among SIP user agents.  SIP user agents
   have different capabilities, different user interfaces, and may be
   used to establish sessions that do not involve audio at all.  Because
   of this, the way a SIP UA provides the user with information about
   the progress of session establishment is a matter of local policy.
   For example, a UA with a Graphical User Interface (GUI) may choose to
   display a message on the screen when the callee is being alerted,
   while another UA may choose to show a picture of a phone ringing
   instead.  Many SIP UAs choose to imitate the user interface of the
   PSTN phones.  They provide a ringing tone to the caller when the
   callee is being alerted.  Such a UAC is supposed to generate ringing
   tones locally for its user as long as no early media is received from
   the UAS.  If the UAS generates early media (e.g., an announcement or
   a special ringing tone), the UAC is supposed to play it rather than
   generate the ringing tone locally.

   The problem is that, sometimes, it is not an easy task for a UAC to
   know whether it will be receiving early media or it should generate
   local ringing.  A UAS can send early media without using reliable
   provisional responses (very simple UASs do that) or it can send an
   answer in a reliable provisional response without any intention of
   sending early media (this is the case when preconditions are used).
   Therefore, by only looking at the SIP signalling, a UAC cannot be
   sure whether or not there will be early media for a particular
   session.  The UAC needs to check if media packets are arriving at a
   given moment.

      An implementation could even choose to look at the contents of the
      media packets, since they could carry only silence or comfort
      noise.

   With this in mind, a UAC should develop its local policy regarding
   local ringing generation.  For example, a POTS ("Plain Old Telephone
   Service")-like SIP User Agent (UA) could implement the following
   local policy:

      1. Unless a 180 (Ringing) response is received, never generate
         local ringing.

      2. If a 180 (Ringing) has been received but there are no incoming
         media packets, generate local ringing.

      3. If a 180 (Ringing) has been received and there are incoming
         media packets, play them and do not generate local ringing.

         Note that a 180 (Ringing) response means that the callee is
         being alerted, and a UAS should send such a response if the
         callee is being alerted, regardless of the status of the early
         media session.

   At first sight, such a policy may look difficult to implement in
   decomposed UAs (i.e., media gateway controller and media gateway),
   but this policy is the same as the one described in Section 2, which
   must be implemented by any UA.  That is, any UA should play incoming
   media packets (and stop local ringing tone generation if it was being
   performed) in order to avoid media clipping, even if the 200 (OK)
   response has not arrived.  So, the tools to implement this early
   media policy are already available to any UA that uses SIP.

   Note that, while it is not desirable to standardize a common local
   policy to be followed by every SIP UA, a particular subset of more or
   less homogeneous SIP UAs could use the same local policy by
   convention.  Examples of such subsets of SIP UAs may be "all the
   PSTN/SIP gateways" or "every 3GPP IMS (Third Generation Partnership
   Project Internet Multimedia System) terminal".  However, defining the
   particular common policy that such groups of SIP devices may use is
   outside the scope of this document.

### 3.3 ~
   The gateway model is seriously limited in the presence of forking, as
   described in Section 3.1.  Therefore, its use is only acceptable when
   the User Agent (UA) cannot distinguish between early and regular
   media, as described in Section 3.4.  In any other situation (the
   majority of UAs), use of the application server model described in
   Section 4 is strongly recommended instead.

## Section 4 introduces the application
   server model, which, as stated previously, resolves some of the
   issues present in the gateway model.

## Section 5 discusses the
   interactions between the Alert-Info header field in both early media
   models.
