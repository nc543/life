# assert()
善用 assert()：只是開發過程中暫時的判定，還是作為最終的 error handling？

http://lirobo.blogspot.tw/2015/04/assert.html

是 macro ？

assert() 的目的是在程式中幫忙找出 bugs。

assert - abort the program if assertion is false
```c
#include <assert.h>

void assert(scalar expression);
```

當 expression 是假 (也就是等於 0)，assert() 印類似錯誤訊息「assertion  failed  in  file  foo.c,  function do_bar(), line 1287」到 stderr 並呼叫 abort() 結束程式
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

http://www.edn.com/electronics-blogs/embedded-basics/4440193/8-tips-for-squashing-bugs-using-ASSERT-in-C
