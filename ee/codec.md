* speech (語音): 人類發聲器官產生帶有語言訊息的聲音。
* language (語言): 不只是聲音問題，還關聯到如何分辨與解讀其中含意。
語音處理可以跟語言無關，如語音編碼 (speech coding)、語音增強 (speech enhancement，去除噪音)；也可以跟語言有關，如語音辨認 (speech recognition)、語音合成 (speech synthesis)。

## Voice Compression
* Waveform coding
* Parameter coding
* Hybrid coding

## PCM -- Pulse-Code Modulation
* sampled at fixed period
* each sample is linear quantized

## A-law and µ-law
* 64 kbit/s = 8 bit/sample x 8k sample/s
* logarithmic compression: a 13 or 14 bit linear PCM sample is mapped into an 8 bit value.
* international standard G.711

## ADPCM -- Adaptive Differential PCM
* the prediction error of the signal
* speech compression
* also for all waveform, high-quality audio, image, modem data

## Standard ADPCM
* 8k sample/s
* bit/sample
	* 2: 16 kbit/s (G.726) digital circuit multiplication equipment (DCME)
	* 3: 24 kbit/s (G.726, G.723) DCME
	* 4: 32 kbit/s (G.726, G.721) international phone trunk, DECT
	* 5: 40 kbit/s (G.726, G.723) modem signals > 4800 bit/s in DCME

## ADPCM algorithm
dialogic adpcm.pdf
