# assert()
assert(expression) 是程式開發過程中作為除錯用的判斷，當 expression 判斷為「假」則印出程式檔名、行數、函數名稱、判斷式等資訊到 strerr 後呼叫 abort() 結束程式。

```c
#include <assert.h>

void assert(scalar expression);
```

如果在 <assert.h> 之前定義了NDEBUG，assert() 不會產生任何程式碼。
```c
#define NDEBUG
#include <assert.h>

main()
{
	assert(xxx);
}
```

是 macro ？

assert() 的目的是除錯，就程式本身功能的運作是不需要的，所以並不適合作為程式功能的 error handling。

http://lirobo.blogspot.tw/2015/04/assert.html

http://www.edn.com/electronics-blogs/embedded-basics/4440193/8-tips-for-squashing-bugs-using-ASSERT-in-C
