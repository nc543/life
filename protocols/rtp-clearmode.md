## [RFC 4040](https://tools.ietf.org/html/rfc4040)
使用 pseudo-codec "Clearmode"、MIME type "audio/clearmode"，沒有必要參數，選擇性參數有：ptime、maxtime。使用 MIME media type audio 是因為主要讓它 telephony and voice-gateway-related，共用 the port in the
             SDP "m=" line with codecs such as audio/g711 [6], [7], for
             one example.  This sharing is an important application and
             would not be possible otherwise.
```
m=audio 12345 RTP/AVP 97
a=rtpmap:97 CLEARMODE/8000
a=ptime:10
```

   Clearmode does not use any encoding or decoding.  It just provides
   packetization.

   Clearmode assumes that the data to be handled is sample oriented with
   one octet (8bits) per sample.  There is no restriction on the number
   of samples per packet other than the 64 kbyte limit imposed by the IP
   protocol.  The number of samples SHOULD be less than the path maximum
   transmission unit (MTU) minus combined packet header length.  If the
   environment is expected to have tunnels or security encapsulation as
   part of operation, the number of samples SHOULD be reduced to allow
   for the extra header space.


   The payload packetization/depacketization for Clearmode is similar to
   the Pulse Code Modulation (PCMU or PCMA) handling described in RFC
   3551 [5].  Each Clearmode octet SHALL be octet-aligned in an RTP
   packet.  The sign bit of each octet SHALL correspond to the most
   significant bit of the octet in the RTP packet.

   A sample rate of 8000 Hz MUST be used.
   This calculates to a 64 kbit/s transmission rate per channel.

   The Timestamp SHALL be set as described in RFC 3550 [4].

   The marker bit is always zero.  Silence suppression is not applicable
   for Clearmode data streams.

   The payload type is dynamically assigned and is not presented in this
   document.

   RTP header fields not mentioned here SHALL be used as specified in
   RFC 3550 [4] and any applicable profile.

   This document specifies the use of RTP over unicast and multicast UDP
   as well as TCP.  (This does not preclude the use of this definition
   when RTP is carried by other lower-layer protocols.)
