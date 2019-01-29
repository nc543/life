[RFC3960: Early Media and Ringing Tone Generation in the Session Initiation Protocol (SIP)](https://tools.ietf.org/html/rfc3960)

early media：受話端收到初始 INVITE 後，在送出的最後回應前使用的 media，media 可以是任一單向或雙向。

可能用途
* 受話端產生的 ringing tone and announcements (e.g., queuing status)
* 發話端產生的語音指令或 DTMF，用來驅動 interactive voice response (IVR)。

基本 SIP 規範 RFC3261 只支援很簡易的 early media 機制，在 forking 和 security 有一些問題，不能滿足大多數應用。
RFC3960 描述兩種 SIP early media 實作模式：gateway 模式及 application server 模式。
gateway 模式在 forking 仍有問題，但一些 SIP entities (特別是一些 gateways) 無法實作 application server 模式，所以還是需要。

application server 模式使用 the early-session disposition type, which is specified in "The Early Session Disposition Type for the Session Initiation Protocol (SIP)", RFC 3959.

## Session Establishment in SIP
沒有 early media 情況下的 offer/answer model

SIP 使用 two-way 交握的 offer/answer 模式來協調 session 參數。
發話端或受話端有一端先準備一個 session 描述，稱為 offer。
另一端回應另一個 session 描述稱為 answer。(如果不同意，則...)

例如：
offer 在 INVITE 請求，answer 在回覆的 200 OK：
* 發話端 INVITE 時就可以準備好接收封包，不會 media clipping。
* media 封包可能直送而比 200 OK 早到發話端，發話端如果因收到的 media 訊息內容而馬上講話，此時不曉得要送到哪裡，而有可能出現 media clipping。
有些情況發話端需要收到 200 OK 才能處理接收的語音封包，例如需要 QoS, media authorization, or media encryption，使用 preconditions 來避免 media clipping。

offer 在 200 OK 回覆，answer 在 ACK：會有 media clipping，受話端送 200 OK 時使用者就可能開始「喂」，但此時還不知道 media 封包要送到哪裡，直到收到 ACK。

當使用 [reliable provisional responses](https://tools.ietf.org/html/rfc3262) 和 [UPDATE](https://tools.ietf.org/html/rfc3311) 請求，會有很多可能的方式來交換 offers 和 answers.

media clipping：使用者認為 media session 已經建立而開始講話，但實際上建立程序
尚未完成，忽略了一開始一些資料。

## gateway model

   在 INVITE 的最後回應前就透過 offer/answer 建立 early
   media，最後回應如果是 200 OK，就轉成一般的 media 繼續使用。

   The gateway model consists of managing
   early media sessions using offer/answer exchanges in reliable
   provisional responses, PRACKs, and UPDATEs.

gateway model 在 forking 時會有問題，因此, its use is only acceptable when
   the User Agent (UA) cannot distinguish between early and regular
   media, as described in Section 3.4.  In any other situation (the
   majority of UAs), use of the application server model described in
   Section 4 is strongly recommended instead.

### forking

如果 INVITE 出現 fork，發話端可能會收到不同受話端 provisional response 的 answer。

大多時候發話端需要選擇一個 early media，並且送 UPDATE 來 mute 其它。但如何選呢？隨機？

   If one of the early media sessions that was muted transitions to a
   正常使用的 media session (i.e., the UAS sends a 2xx response), media
   clipping is likely.  發話端 typically sends an UPDATE with a new
   offer (upon reception of the 200 (OK) for the INVITE) 來 unmute the
   media session.  The UAS cannot send any media until it receives the
   offer from the UAC.  Therefore, if the caller starts speaking before
   the offer from the UAC is received, his words will get lost.

      Having the UAS send the UPDATE to unmute the media session
      (instead of the UAC) does not avoid media clipping in the backward
      direction and it causes possible race conditions.

### Ringing Tone Generation

在 PSTN，當受話端正在振鈴時，電話交換機有送回鈴音給發話端的標準。

但在 SIP UA 可就多元了，可能在螢幕顯示訊息，或者顯示一張電話正在響的圖片。
而使得
   SIP user agents
   have different capabilities, different user interfaces, and may be
   used to establish sessions that do not involve audio at all.  Because
   of this, the way a SIP UA provides the user with information about
   the progress of session establishment is a matter of local policy.

大部分 SIP UA 選擇 to imitate the user interface of the
   PSTN phones.  They provide a ringing tone to the caller when the
   callee is being alerted.  Such a UAC is supposed to generate ringing
   tones locally for its user as long as no early media is received from
   the UAS.  If the UAS generates early media (e.g., an announcement or
   a special ringing tone), the UAC is supposed to play it rather than
   generate the ringing tone locally.

問題在於有時候發話端不好判別其是否會收到 early media 而決定是否要產生回鈴音。
   A UAS can send early media without using reliable
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

      1. 除非收到 180 Ringing，不然不產生回鈴音。

      2. 如果收到 180 Ringing，但沒有 incoming media 封包, 產生回鈴音。

      3. 如果收到 180 Ringing 並且有 incoming
         media 封包, play them and do not generate local ringing.

         Note that 180 Ringing 表示受話端正在響鈴
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
### 3.3.  Absence of an Early Media Indicator
   SIP, as opposed to other signalling protocols, does not provide an
   early media indicator.  That is, there is no information about the
   presence or absence of early media in SIP.  Such an indicator could
   be potentially used to avoid the generation of local ringing tone by
   the UAC when UAS intends to provide an in-band ringing tone or some
   type of announcement.  However, in the majority of the cases, such an
   indicator would be of little use due to the way SIP works.

   One important reason limiting the benefit of a potential early media
   indicator is the loose coupling between SIP signalling and the media
   path.  SIP signalling traverses a different path than the media.  The
   media path is typically optimized to reduce the end-to-end delay
   (e.g., minimum number of intermediaries), while the SIP signalling
   path typically traverses a number of proxies providing different
   services for the session.  Hence, it is very likely that the media
   packets with early media reach the UAC before any SIP message that
   could contain an early media indicator.

   Nevertheless, sometimes SIP responses arrive at the UAC before any
   media packet.  There are situations in which the UAS intends to send
   early media but cannot do it straight away.  For example, UAs using
   Interactive Connectivity Establishment (ICE) [6] may need to exchange
   several Simple Traversals of the UDP Protocol through NAT (STUN)
   messages before being able to exchange media.  In this situation, an
   early media indicator would keep the UAC from generating a local
   ringing tone during this time.  However, while the early media is not
   arriving at the UAC, the user would not be aware that the remote user
   is being alerted, even though a 180 (Ringing) had been received.
   Therefore, a better solution would be to apply a local ringing tone
   until the early media packets could be sent from the UAS to the UAC.
   This solution does not require any early media indicator.

      Note that migrations from local ringing tone to early media at the
      UAC happen in the presence of forking as well; one UAS sends a 180
      (Ringing) response, and later, another UAS starts sending early
      media.

### 3.4.  Applicability of the Gateway Model

gateway model 的限制是在 forking 時會產生 media clipping，而需要偵測 media
來適當產生 local ringingi。
These issues are
   addressed by the application server model, described in Section 4,
   which is the recommended way of generating early media that is not
   continuous with the regular media generated during the session.

   The gateway model is, therefore, acceptable in situations where the
   UA cannot distinguish between early media and regular media.  A PSTN
   gateway is an example of this type of situation.  The PSTN gateway
   receives media from the PSTN over a circuit, and sends it to the IP
   network.  The gateway is not aware of the contents of the media, and
   it does not exactly know when the transition from early to regular
   media takes place.  From the PSTN perspective, the circuit is a
   continuous source of media.

## 4. Application Server Model
解決 gateway 模式的一些 issues

受話端作為 application server 跟發話端建立 early media。
發話端使用 early-session option tag 表示支援 early-session disposition type
(定義在 [RFC 3959](https://tools.ietf.org/html/rfc3959]))，然後受話端知道
   that they can keep offer/answer exchanges for early media
   (early-session disposition type) 跟 regular media (session
   disposition type) 分開。

   Sending early media using a different offer/answer exchange than the
   one used for sending regular media helps avoid media clipping in
   cases of forking.  The UAC can reject or mute new offers for early
   media without muting the sessions that will carry media when the
   original INVITE is accepted.  The UAC can give priority to media
   received over the latter sessions.  This way, the application server
   model transitions from early to regular media at the right moment.

   Having a separate offer/answer exchange for early media also helps
   UACs decide whether or not local ringing should be generated.  If a
   new early session is established and that early session contains at
   least an audio stream, the UAC can assume that there will be incoming
   early media and it can then avoid generating local ringing.

      An alternative model would include the addition of a new stream,
      with an "early media" label, to the original session between the
      UAC and the UAS using an UPDATE instead of establishing a new
      early session.  We have chosen to establish a new early session to
      be coherent with the mechanism used by application servers that
      are NOT
      co-located with the UAS.  This way, the UAS uses the same
      mechanism as any application server in the network to interact
      with the UAC.

### 4.1.  In-Band Versus Out-of-Band Session Progress Information

   Note that, even when the application server model is used, a UA will
   have to choose which early media sessions are muted and which ones
   are rendered to the user.  In order to make this choice easier for
   UAs, it is strongly recommended that information that is not
   essential for the session not be transmitted using early media.  For
   instance, UAs should not use early media to send special ringing
   tones.  The status code and the reason phrase in SIP can already
   inform the remote user about the progress of session establishment,
   without incurring the problems associated with early media.

## Section 5 discusses the
   interactions between the Alert-Info header field in both early media
   models.

## 5.  Alert-Info Header Field

   The Alert-Info header field allows specifying an alternative ringing
   content, such as ringing tone, to the UAC.  This header field tells
   the UAC which tone should be played in case local ringing is
   generated, but it does not tell the UAC when to generate local
   ringing.  A UAC should follow the rules described above for ringing
   tone generation in both models.  If, after following those rules, the
   UAC decides to play local ringing, it can then use the Alert-Info
   header field to generate it.

## 6.  Security Considerations

   SIP uses the offer/answer model [3] to establish early sessions in
   both the gateway and the application server models.  User Agents
   (UAs) generate a session description, which contains the transport
   address (i.e., IP address plus port) where they want to receive
   media, and send it to their peer in a SIP message.  When media
   packets arrive at this transport address, the UA assumes that they
   come from the receiver of the SIP message carrying the session
   description.  Nevertheless, attackers may attempt to gain access to
   the contents of the SIP message and send packets to the transport
   address contained in the session description.  To prevent this
   situation, UAs SHOULD encrypt their session descriptions (e.g., using
   S/MIME).

   Still, even if a UA encrypts its session descriptions, an attacker
   may try to guess the transport address used by the UA and send media
   packets to that address.  Guessing such a transport address is
   sometimes easier than it may seem because many UAs always pick up the
   same initial media port.  To prevent this situation, UAs SHOULD use
   media-level authentication mechanisms such as the Secure Realtime
   Transport Protocol (SRTP)[7].  In addition, UAs that wish to keep
   their communications confidential SHOULD use media-level encryption
   mechanisms (e.g, SRTP [7]).

   Attackers may attempt to make a UA send media to a victim as part of
   a DoS attack.  This can be done by sending a session description with
   the victim's transport address to the UA.  To prevent this attack,
   the UA SHOULD engage in a handshake with the owner of the transport
   address received in a session description (just verifying willingness
   to receive media) before sending a large amount of data to the
   transport address.  This check can be performed by using a connection
   oriented transport protocol, by using STUN [8] in an end-to-end
   fashion, or by the key exchange in SRTP [7].

   In any event, note that the previous security considerations are not
   early media specific, but apply to the usage of the offer/answer
   model in SIP to establish sessions in general.

   Additionally, an early media-specific risk (roughly speaking,
   equivalent to forms of "toll fraud" in the PSTN) attempts to exploit
   the different charging policies some operators apply to early and
   regular media.  When UAs are allowed to exchange early media for
   free, but are required to pay for regular media sessions, rogue UAs
   may try to establish a bidirectional early media session and never
   send a 200 (OK) response for the INVITE.

   On the other hand, some application servers (e.g., Interactive Voice
   Response systems) use bidirectional early media to obtain information
   from the callers (e.g., the PIN code of a calling card).  So, we do
   not recommend that operators disallow bidirectional early media.
   Instead, operators should consider a remedy of charging early media
   exchanges that last too long, or stopping them at the media level
   (according to the operator's policy).
