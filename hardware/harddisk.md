
『磁區』(sector) 是使用硬碟的最小儲存單位，可存入 512 個位元組資料。硬碟的內部結構有數片磁盤 (platter) 用來儲存資料，每一面磁盤 (一般有正反兩面) 都同樣有許多由大到小的同心圓，稱為『磁軌』(track)。而每個磁軌不管大圈或小圈皆切成相同數量的小段弧形區域，稱為磁區。

資料在硬碟的哪個位置 (也就是磁區)，可以以磁柱 (cylinder)、磁頭 (head)、磁區 (sector) 三個向量參數來表示，稱為 CHS 定址。其中磁柱為所有相同半徑的磁軌形成的空心圓柱，從最大半徑編號為 0 開始。磁頭是每面磁盤都有一個負責讀寫，從 0 開始編號。磁區則是從 1 開始編號。

另一種定址則是跟硬碟結構細節無關，全部磁區從 0 開始的編號，不分磁柱、磁頭，直到最後磁區為止，稱為 LBA (Logical Block Addressing，邏輯磁區定址)，這裡的 block 指的就是磁區。

The original ATA specification used a 28-bit addressing mode, allowing for the addressing of 228 (268,435,456) sectors (with blocks of 512 bytes each;, resulting in a maximum capacity of 137 gigabytes (128 GiB). The standard PC BIOS system supported up to 7.88 GiB (8.46 GB), with a maximum of 1024 cylinders, 256 heads and 63 sectors. ATA-6 introduced 48 bit addressing, increasing the limit to 128 PiB (or 144 petabytes). Some OS environments, including Windows 2000, until Service Pack 3, did not enable 48-bit LBA by default, requiring the user to take extra steps to get full capacity on a 160 GB drive.

ATA (PATA) 使用排線，上有兩個或三個 40-pin 的連接頭，一個接到主機板上，其它接到 drives。

以前 ATA 的排線有 40 條線，但 UDMA 模式開始需要 80 條線，增加的線都是 ground 以減少訊號干擾，但連接頭仍然是 40-pin，改用 blue (主機板)、gray (cable select slave) 及 black (cable select master) 三種顏色。
UDMA -- 33
UDMA4 -- 66 MB/s

|  Pin  |  Signal  |  描述  |h
|  1 	|Reset  |
|  2, 19, 22, 24, 26, 30, 40  	|Ground  |
|  18, 16, 14, 12, 10, 8, 6, 4, 3, 5, 7, 9, 11, 13, 15, 17  |Data 15 ~ 0 |
|  20 	|Key or VCC_in  |在 ATA 標準定義為 key。部份記憶卡拿來作為 VCC 電源供應不用額外電源線|
|  21 	|DDRQ  |
|  23 	|I/O write  |
|  25 	|I/O read  |
|  27 	|IOC HRDY  |
|  28 	|Cable select  |在灰色連接頭沒接到排線，讓 cable select 時為 slave。|
|  29 	|DDACK  |
|  31 	|IRQ  |
|  32 	|No connect  |
|  33 	|Addr 1  |
|  34 	|GPIO_DMA66_Detect  |主機板讀到 low 則視為 80 條線排線，可用 UDMA3 以上。在藍色連接頭只接到 ground，沒接到排線。It is attached normally on the gray and black connectors.|
|  35 	|Addr 0  |
|  36 	|Addr 2  |
|  37 	|Chip select 1P  |
|  38 	|Chip select 3P  |
|  39 	|Activity  |




介面訊號
容量限制

!參考文獻
# 小木偶的組合語言教學之[[Ch 32 硬碟 (1) 分割區|http://home.educities.edu.tw/wanker742126/asm/ch32.html]]
# http://www.48bitlba.com/
# http://en.wikipedia.org/wiki/Advanced_Technology_Attachment
!延伸閱讀
# http://ata-atapi.com/
