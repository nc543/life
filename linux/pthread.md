
http://lirobo.blogspot.tw/2014/05/pthread.html

PTHREAD_MUTEX_RECURSIVE_NP

* 每個 thread 可以 scheduled independently by the kernel so that one may sleep while another remains runnable.
* 大部分用 pthread (POSIX thread) libraries 來寫，created, handled, and scheduled entirely in User Mode。

參考：http://man7.org/linux/man-pages/man3/pthread_create.3.html

one-time initialization: pthread_once()

#include <pthread.h>
pthread_once_t once_var = PTHREAD_ONCE_INIT;
void init(void)
{
	/* Function body */
}
pthread_once(once_var, init);

依據 once_var 透過 pthread_once() 呼叫的函數只會執行一次。

use thread-specific data or thread-local storage to make an existing function thread-safe without changing the function’s interface.

Thread-specific data is a technique for making an existing function thread-safe
without changing its interface. 可能比 reentrant 的效率只稍微差一點點。

讓函數在不同 thread 呼叫時有不同 copy of a variable
Thread-specific
data is persistent; each thread’s variable continues to exist between the thread’s
invocations of the function. This allows the function to maintain per-thread information
between calls to the function, and allows the function to pass distinct result
buffers (if required) to each calling thread.

首先 pthread_key_create()
pthread_getspecific
pthread_setspecific
