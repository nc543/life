# Protothreads

[Protothreads](http://dunkels.com/adam/pt/) 用 C 語言巨集實作的無堆疊的輕量執行緒，用好理解的線性方式撰寫事件驅動程式。

protothread 是一個 C function，需要一直呼叫直到完成工作。每次呼叫會一直執行到需要 block 的地方暫時離開，下次呼叫再跳回來。下次能跳回來是靠 C 語言的 switch-case，在每個「判斷是否要 block」前會紀錄程式行號，同時以這個行號作為 case，這樣每次呼叫 protothread 就可以透過 switch 紀錄的行號跳到「判斷是否要 block」的地方。

protothread 用 C macro 實作，function 內部分別由 PT_BEGIN(pt) 跟 PT_END(pt) 作為開始跟結束來形成 switch，判斷是否要 block 用 PT_WAIT_UNTIL(pt, cond) 或 PT_WAIT_WHILE(pt, cond)，如果要 block 就 return。 
疑問：__LINE__ 只有 2-byte？

protothread 也提供 yield 機制，需要一個區域布林變數，每次呼叫 protothread 會先設起來，在 yield 前清掉，再來就是一個「判斷是否要 block」，這裡的判斷是 yield 為清掉則 block。下次呼叫 protothread 時布林變數會先設起來，然後跳到「判斷是 yield 為清掉則 block」的結果是不 block 而繼續。(或許有方式可以省下布林變數，也不用判斷)

另外，protothread 還可以有階層式，protothread 裡可以還有 protothread。

優點：

限制：

應用範例：

比較：
Simon Tatham's coroutines http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
