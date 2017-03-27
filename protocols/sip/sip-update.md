# SIP UPDATE
RFC 3311 The Session Initiation Protocol (SIP) UPDATE Method

讓呼叫端或受話端在 dialog (early 或 confirmed) 內更新 media 參數而不影響 dialog 本身的狀態
* early dialog 或 early media：初始 INVITE 尚未完成，此時 media 已預先建立來傳 call progress tone
* 更新 early media 參數，例如要 put on hold
* early dial 時 re-INVITE 不能使用
* 可用在 confirmed dialog，但建議改用 re-INVITE，因為 UPDATE 必須馬上回答，排除了使用人 approval 的可能.  Such approval will frequently be needed, and is possible with a re-INVITE.

Content-Disposition

The caller begins
   with an INVITE transaction, which proceeds normally.  Once a dialog
   is established, either early or confirmed, the caller can generate an
   UPDATE method that contains an SDP offer [3] for the purposes of
   updating the session.  The response to the UPDATE method contains the
   answer.  Similarly, once a dialog is established, the callee can send
   an UPDATE with an offer, and the caller places its answer in the 2xx
   to the UPDATE.  The Allow header field is used to indicate support
   for the UPDATE method.  There are additional constraints on when
   UPDATE can be used, based on the restrictions of the offer/answer
   model.



# Determining Support for this Extension

UAC INVITE 時 Allow 列表加 UPDATE，表示接受 UPDATE

UAS 產生含有 SDP 的 reliable provisional response 時，Allow 列表加 UPDATE，表示接受 UPDATE。依據 [RFC 3265](https://tools.ietf.org/html/rfc3265 "Reliability of Provisional Responses in the Session Initiation Protocol (SIP)") 會在 UAC 建立 early dialog，以便接受 UPDATE。
   An unreliable provisional response MAY contain an Allow header field
   listing the UPDATE method, and a 2xx response SHOULD contain an Allow
   header field listing the UPDATE method.

5.1 第三段開始待讀
