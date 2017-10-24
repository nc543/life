# Protothreads

[Protothreads](http://dunkels.com/adam/pt/) 用 C 語言巨集實作的無堆疊的輕量執行緒，用較容易理解的線性方式來撰寫事件驅動程式。

protothread 是一個需要多次或一直呼叫的 C 函數，每次呼叫會從上次離開的地方一直執行到需要 block 的地方暫時離開，下次呼叫再繼續直到工作完成。

protothread 能夠回到上次離開的地方是利用程式行號作為 C 語言的 switch-case 使用，並用 C 語言巨集實作。內部分別由 PT_BEGIN(pt) 跟 PT_END(pt) 作為開始跟結束來形成 switch 區塊，之間「判斷是否要 block」的地方用 PT_WAIT_UNTIL(pt, cond) 或 PT_WAIT_WHILE(pt, cond)，會先紀錄程式行號，並且以行號作為 case，然後判斷如果要 block 就 return。這樣每次呼叫 protothread 就可以透過 switch 行號紀錄跳到「判斷是否要 block」的地方。

```
#include "pt.h"

struct pt pt;
struct timer timer;

PT_THREAD(example(struct pt *pt))
{
  PT_BEGIN(pt);

  while(1) {
    if(initiate_io()) {
      timer_start(&timer);
      PT_WAIT_UNTIL(pt,
         io_completed() ||
         timer_expired(&timer));
      read_data();
    }
  }
  PT_END(pt);
}
```

疑問：__LINE__ 只有 2-byte？

protothread 也提供 yield 機制，需要一個區域布林變數，每次呼叫 protothread 會先設起來，在 yield 前清掉，再來就是一個「判斷是否要 block」，這裡的判斷是 yield 為清掉則 block。下次呼叫 protothread 時布林變數會先設起來，然後跳到「判斷是 yield 為清掉則 block」的結果是不 block 而繼續。(或許有方式可以省下布林變數，也不用判斷)

另外，protothread 還可以有階層式，protothread 裡可以還有 protothread。

優點：

限制：

應用範例：

比較：
Simon Tatham's coroutines http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
