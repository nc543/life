# assert()
善用 assert()：只是開發過程中暫時的判定，還是作為最終的 error handling？

http://lirobo.blogspot.tw/2015/04/assert.html

       The  purpose  of  this  macro is to help programmers find bugs in their
       programs.  The  message  "assertion  failed  in  file  foo.c,  function
       do_bar(), line 1287" is of no help at all to a user.

assert - abort the program if assertion is false
```c
#include <assert.h>

void assert(scalar expression);
```

當 expression 是假 (也就是等於 0)，assert() 印錯誤訊息到 stderr 並呼叫 abort() 結束程式
```c
#include <assert.h>

void assert(scalar expression);
```

If  the  macro  NDEBUG  was  defined  at the moment <assert.h> was last
       included, the macro assert() generates no code, and hence does  nothing
       at all. 
```c
#define NDEBUG
#include <assert.h>

main()
{
	assert(xxx);
}
```

http://www.edn.com/electronics-blogs/embedded-basics/4440193/8-tips-for-squashing-bugs-using-ASSERT-in-C
