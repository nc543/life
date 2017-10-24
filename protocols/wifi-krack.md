KRACK 攻擊針對四手交握協議而來，攻擊的目標在客戶端，不在 AP，所以應該優先更新客戶端。也許 AP 不需要安全更新，但可以透過下列方式降低攻擊路由器的可能：關閉客戶端功能、將 802.11r 功能 disabling 掉。

目前四手交握協議無法確保金鑰只安裝一次，只能確保金鑰維持隱密性，以及交握過程傳遞的訊息並不會被偽造。

KRACK 並沒有破解四路握手協議的安全性。事實上，過程中傳遞的加密金鑰依然是安全的，以及握手協議過程中，用來確認 AP 端及客戶端的身分驗證性也是安全的。KRACK 並沒有破解加密金鑰，因此四路握手協議依然很安全。


Mathy Vanhoef (KU Leuven, imec-DistriNet), Frank Piessens (KU Leuven, imec-DistriNet). Key Reinstallation Attacks: Forcing Nonce Reuse in WPA2
https://papers.mathyvanhoef.com/ccs2017.pdf
https://acmccs.github.io/session-F3/
https://technews.tw/2017/10/19/krack-authors-in-person-13-qa-quick-responses-to-your-questions/
