atomic: 一個在共享記憶體的操作，對於其它 thread 是一步完成的。

atomic store：其它 thread 不能看到變更過程中的情況。

atomic load：讀取整個值如同在一瞬間發生。

lock-free programming 必須確保 atomic operation

rule:
    任何時間，兩個 threads 同時對一個共享變數操作，只要其中一個進行「寫」的動作，這兩個 threads 必須使用 atomic operations.

在 C++11 稱為 data race (跟 Java 的 data race 不同，而 race condition 是更 general 的東西)。造成讀或寫的撕裂。

不會 atomic 的原因：
* 需要多個處理器指令，中間可能會插入其它 thread 的指令，或者在多核處理器有多個有個指令同時執行。
* 有些單一處理器指令實際上需要多個動作，例如 ARMv7 的 strd、x86 的 32-bit mov 作用在 unaligned 記憶體或跨越 cache line boundary。
* C/C++ 沒說是 atomic 的操作，都應該假定是 non-atomic，即使是 int assignment。雖然知道在許多平台 integer assignment 是 atomic，只要變數的記憶體位址是 naturally aligned。

[](http://preshing.com/20130618/atomic-vs-non-atomic-operations/)
