[RFC 6086](https://tools.ietf.org/html/rfc6086 "Session Initiation Protocol (SIP) INFO Method and Package Framework")

定義 SIP INFO 及 Info Package mechanism

[RFC 2976](https://tools.ietf.org/html/rfc2976)： "legacy INFO usage"

用建立的 SIP dialog 在兩端應用間傳送訊息。
* 不用來更新 characteristics of a SIP dialog or session
	* 比較：SIP re-INVITE、SIP UPDATE
* 使用 an invite dialog [RFC5057](https://tools.ietf.org/html/rfc5057).

## Info Package mechanism

An Info
   Package specification defines 內容及語意 of the
   information carried in an INFO message associated with the Info
   Package.  The Info Package mechanism 也提供一個方式給 UA
 to indicate for which Info Packages they are willing to
   receive INFO requests, and which Info Package a specific INFO request
   is associated with.

   A UA uses the Recv-Info header field, on a per-dialog basis, to
   indicate for which Info Packages it is willing to receive INFO
   requests.  A UA can indicate an initial set of Info Packages during
   dialog establishment and can indicate a new set during the lifetime
   of the invite dialog usage.

      NOTE: A UA can use an empty Recv-Info header field (a header field
      without a value) to indicate that it is not willing to receive
      INFO requests for any Info Package, while still informing other
      UAs that it supports the Info Package mechanism.

   When a UA sends an INFO request, it uses the Info-Package header
   field to indicate which Info Package is associated with the request.
   One particular INFO request can only be associated with a single Info
   Package.

## 應用

* [RFC 3372] specifies the encapsulation of ISDN User Part
      (ISUP) in SIP message bodies.  ITU-T and the Third Generation
      Partnership Project (3GPP) have specified similar procedures.
* [ECMA-355] specifies the encapsulation of "QSIG" in SIP message bodies.
* [RFC 5022] specifies how INFO is used as a transport mechanism by the Media Server Control Markup Language (MSCML) protocol.  MSCML uses an option-tag in the Require header field to ensure that the receiver understands the INFO content.
* [RFC 5707] specifies how INFO is used as a transport mechanism by the Media Server Markup Language (MSML) protocol.
* Companies have been using INFO messages in order to request fast video update.  Currently, a standardized mechanism, based on the Real-time Transport Control Protocol (RTCP), has been specified in [RFC 5168].
* Companies have been using INFO messages in order to transport Dual-Tone Multi-Frequency (DTMF) tones.  All mechanisms are proprietary and have not been standardized.

   Furthermore, RFC 2976 did not define mechanisms that would enable a
   SIP UA to indicate (1) the types of applications and contexts in
   which the UA supports the INFO method or (2) the types of
   applications and contexts with which a specific INFO message is
   associated.

   Because legacy INFO usages do not have associated Info Packages, it
   is not possible to use the Recv-Info and Info-Package header fields
   with legacy INFO usages.  That is, a UA cannot use the Recv-Info
   header field to indicate for which legacy INFO usages it is willing
   to receive INFO requests, and a UA cannot use the Info-Package header
   field to indicate with which legacy INFO usage an INFO request is
   associated.

   Due to the problems described above, legacy INFO usages often require
   static configuration to indicate the types of applications and
   contexts for which the UAs support the INFO method, and the way they
   handle application information transported in INFO messages.  This
   has caused interoperability problems in the industry.

   To overcome these problems, the SIP Working Group has spent
   significant discussion time over many years coming to agreement on
   whether it was more appropriate to fix INFO (by defining a
   registration mechanism for the ways in which it was used) or to
   deprecate it altogether (with the usage described in RFC 3398
   [RFC3398] being grandfathered as the sole legitimate usage).
   Although it required substantial consensus building and concessions
   by those more inclined to completely deprecate INFO, the eventual
   direction of the working group was to publish a framework for
   registration of Info Packages as defined in this specification.

## backward compatibility (legacy INFO usages)
1. A UA MUST NOT insert an Info-Package header field in a legacy INFO request (as described in Section 4.2.1, an INFO request associated with an Info Package always contains an Info-Package header field).
2. Any new usage MUST use the Info Package mechanism defined in this specification, since it does not share the issues associated with legacy INFO usage, and since Info Packages can be registered with IANA.
3. UAs are allowed to enable both legacy INFO usages and Info Package usages as part of the same invite dialog usage, but UAs SHALL NOT mix legacy INFO usages and Info Package usages in order to transport the same application level information. If possible, UAs SHALL prefer the usage of an Info Package.

##
INFO 請求可以 associated 一個 Info Package 或一個傳統 INFO 的使用方式

associated 一個 Info Package 有 Info-Package header 表示用哪個 Info Package，傳統 INFO 使用沒有 Info-Package header

INFO 請求不能有 Recv-Info header， A UA can
   only indicate a set of Info Packages for which it is willing to
   receive INFO requests by using the SIP methods (and their responses)
   listed in Section 5.

某個 Info Package 相關的 INFO 請求只有對方表示願意接收才能送。
Message bodies associated with Info Packages MUST only be sent in INFO requests.

UPDATE 回應 469 (Bad Info Package) 不影響 dialog

469

415

The application information data is
   carried in the payload of the message body of the INFO request.

If an INFO request associated with an Info Package contains a message
   body part, the body part is identified by a Content-Disposition
   header field "Info-Package" value.  The body part can contain a
   single MIME type, or it can be a multipart [RFC5621] that contains
   other body parts associated with the Info Package.


--------
INFO – now an extensible framework
現在是一個可擴充的框架，跟 IANA 註冊

新的 Recv-Info header 讓 UA 用來聲明只接受哪些 INFO Package
* 一個 Recv-Info 可列多個 INFO Package，或用多個 Recv-Info
* 支援哪些 INFO Package 可事後再更改，也可以清空。
* initial INVITE 及其 reliable 18x/2xx response 要有 Recv-Info
* 如果請求沒有 Recv-Info，其 response 也不能有
新的 Info-Package header 讓 sender 表明 INFO 請求是用哪個 framework
新的 SIP response code 469

The RFC declare all the old INFO usages as “legacy” and indicates that the lack of these headers and framework definitions has created interoperability issues. In short, it has been an ugly mess. The new RFC obsoletes the old INFO RFC. It doesn’t declare all the old usage models for INFO as deprecated, but clearly states that new implementations should avoid using them.

兩個 UA 間其它可能的訊息交換方式：HTTP, MSRP, SIP Message and SUBSCRIBE/NOTIFY

SUBSCRIBE/NOTIFY

   An alternative for application level interaction is to use
   subscription-based events [RFC3265] that use the SIP SUBSCRIBE and
   NOTIFY methods.  Using that mechanism, a UA requests state
   information, such as keypad presses from a device to an application
   server, or key-map images from an application server to a device.
   Event Packages [RFC3265] perform the role of disambiguating the
   context of a message for subscription-based events.  The Info Package
   mechanism provides similar functionality for application information
   exchange using invite dialog usages [RFC5057].

   While an INFO request is always part of, and shares the fate of, an
   existing invite dialog usage, a SUBSCRIBE request creates a separate
   dialog usage [RFC5057], and is normally sent outside an existing
   dialog usage.

   The subscription-based mechanism can be used by SIP entities to
   receive state information about SIP dialogs and sessions, without
   requiring the entities to be part of the route set of those dialogs
   and sessions.

   As SUBSCRIBE/NOTIFY messages traverse through stateful SIP proxies
   and back-to-back user agents (B2BUAs), the resource impact caused by
   the subscription dialogs needs to be considered.  The number of
   subscription dialogs per user also needs to be considered.

   As for any other SIP-signaling-plane-based mechanism for transporting
   application information, the SUBSCRIBE/NOTIFY messages can put a
   significant burden on intermediate SIP entities that are part of the
   dialog route set, but do not have any interest in the application
   information transported between the end users.

8.4.1.3.  MESSAGE

   The MESSAGE method [RFC3428] defines one-time instant message
   exchange, typically for sending MIME contents for rendering to the
   user.

大量資料適合用 media 機制傳，延遲也可能較小


8.4.2.2.  MRCP

   One mechanism for media plane exchange of application data is the
   Media Resource Control Protocol (MRCP) [SPEECHSC-MRCPv2], where a
   media plane connection-oriented channel, such as a Transmission
   Control Protocol (TCP) [RFC0793] or Stream Control Transmission
   Protocol (SCTP) [RFC4960] stream is established.

8.4.2.3.  MSRP

   MSRP [RFC4975] defines session-based instant messaging as well as
   bulk file transfer and other such large-volume uses.

8.4.3.  Non-SIP-Related Mechanisms

   Another alternative is to use a SIP-independent mechanism, such as
   HTTP [RFC2616].  In this model, the UA knows about a rendezvous point
   to which it can direct HTTP requests for the transfer of information.
   Examples include encoding of a prompt to retrieve in the SIP Request
   URI [RFC4240] or the encoding of a SUBMIT target in a VoiceXML
   [W3C.REC-voicexml21-20070619] script.
