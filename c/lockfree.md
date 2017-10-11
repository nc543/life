lock-free programming
lock-less

多個 thread 存取共享記憶體會有互相干擾的問題，其中一種方式是把其它 thread 鎖住 (lock 或擋住 block)，同一時間只允許一個 thread 可以存取。

例如兩個 thread 對同一個變數加一：讀->加->寫，讀和加、或加和寫中間可能插入別的 thread

要有兩個以上 thread (也包括中斷或 signal 服務程式) 且有共享記憶體，才會有干擾的問題。「lock」可能 mutex 的 lock，也可能是其它形式。

一個簡單變數，只有一個 thread 會寫，其它只有讀 => 沒有干擾問題

lock 或 block 可能造成一些問題
* deadlock
* lock 競爭太多造成效能低落
* 效率

lock-free 字面看起來是不用 lock，廣義可看成是不用任何擋住其它 thread 的方式
lock-free 是指不用擋住其它 thread 的方式解決。
* 通常不會期待整個程式 lock-free，而釐出一組 lock-free 操作，例如在一個 lock-free queue 的 push、pop，或許 isEmpty 等。
* 特別設計要 block 的操作屬於例外，例如 queue 空的時候的 pop 操作需要 block，仍視為 lock-free。

atomic operations：不可分割的動作 manipulate memory，thread 不會 observe 操作一半的情形。現代處理器，許多操作已經是 atomic，例如 aligned reads and writes of simple types

atomic read-modify-write
* 支援 lock-free 的 multiple writers 特別有用，當 multiple threads 嘗試 RMW 相同位址，會 effectively 排隊一個一個依序執行
* 可實作 lightweight mutex、recursive mutex、lightweight logging system
* 不同處理器家族用不同方式支援 RMW，PowerPC 及 ARM 使用 load-link/store-conditional 指令
* comare-and-swap
* sequential consistency and memory ordering

http://preshing.com/20111118/locks-arent-slow-lock-contention-is/
http://preshing.com/20120612/an-introduction-to-lock-free-programming/
https://www.codeproject.com/Articles/43510/Lock-Free-Single-Producer-Single-Consumer-Circular
https://pdfs.semanticscholar.org/1b0c/2563aecc2062298cd71850bdece32caeed6d.pdf

https://hackmd.io/s/ry7eqDEC

## Problems with Locking
This list is more or less contentious, not equally relevant to all locking situations:
* Deadlock
* Priority Inversion
* Convoying
* “Async-signal-safety”
* Kill-tolerant availability
* Pre-emption tolerance
* Overall performance

https://www.cs.cmu.edu/~410-s05/lectures/L31_LockFree.pdf

##
[Lockless Programming Considerations for Xbox 360 and Microsoft Windows](https://msdn.microsoft.com/en-us/library/windows/desktop/ee418650(v=vs.85).aspx)
