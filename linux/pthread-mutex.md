thread 有個好處是可以透過全域變數來共用資訊，但需要避免存取變數時，有其它 thread 正在更新它。

pthread-incr.c

如果變數只是一個 int 且只有一個 thread 會改變它，其它都只是讀 => 沒有同步問題

mutex (mutual exclusion) 讓 thread 同步
 a shared resource 使用，so that, for example, one thread doesn’t try to access
a shared variable at the same time as another thread is modifying it.



critical section: a section of code that accesses a shared resource and whose execution should be atomic; that is, its execution should not be interrupted by another thread that simultaneously accesses the same shared resource.



To avoid the problems that can occur when threads try to update a shared variable,
we must use a mutex  to ensure that only one thread
at a time can access the variable. More generally, mutexes can be used to ensure
atomic access to any shared resource, but protecting shared variables is the most
common use.



mutex 只有兩種狀態：locked 及 unlocked。同一時間，只有一個 thread 可以取得 lock，然後只有它可以 unlock。嘗試 lock 一個已經 locked 的 mutex，
depending on the method used to place the lock 可能 block 或 fails with an error.

the terms acquire and release are sometimes used synonymously for lock and unlock.

## Statically Allocated Mutexes
mutex 可以 allocated as a static variable 或 created dynamically at run
time.
A mutex is a variable of the type pthread_mutex_t. 使用前必須先初始化

For a statically allocated mutex
使用預設的屬性
```
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
```

Dynamic mutex creation
is somewhat more complex, and we delay discussion of it until Section 30.1.5.


According to SUSv3, applying the operations that we describe in the remainder
of this section to a copy of a mutex yields results that are undefined. Mutex
operations should always be performed only on the original mutex that has
been statically initialized using PTHREAD_MUTEX_INITIALIZER or dynamically initialized
using pthread_mutex_init() (described in Section 30.1.5).


如果 mutex 是在 heap 的動態配置、在 stack 的自動變數、或要用不是預設的屬性

```
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```
Returns 0 on success, or a positive error number on error

如果 attr 是 NULL，使用預設的屬性。

當動態 allocated 的 mutex 不再使用，應該要回到 unlocked 狀態並 pthread_mutex_destroy().
```
#include <pthread.h>
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```
Returns 0 on success, or a positive error number on error

## Locking and Unlocking a Mutex
After initialization, a mutex is unlocked. To lock and unlock a mutex, we use the
pthread_mutex_lock() and pthread_mutex_unlock() functions.

```
#include <pthread.h>

int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
/* Both return 0 on success, or a positive error number on error */
```

`pthread_mutex_lock()` 等候到 unlock 後，lock mutex 並馬上 return。

If the calling thread itself has already locked the mutex given to
pthread_mutex_lock(), then, for the default type of mutex, one of two implementationdefined
possibilities may result: the thread deadlocks, blocked trying to lock a
mutex that it already owns, or the call fails, returning the error EDEADLK.
On Linux,
the thread deadlocks by default. (We describe some other possible behaviors when
we look at mutex types in Section 30.1.7.)
The pthread_mutex_unlock() function unlocks a mutex previously locked by the
calling thread. It is an error to unlock a mutex that is not currently locked, or to
unlock a mutex that is locked by another thread.
If more than one other thread is waiting to acquire the mutex unlocked by a
call to pthread_mutex_unlock(), it is indeterminate which thread will succeed in
acquiring it.


另外還有兩種 lock 的 variants：pthread_mutex_trylock() and pthread_mutex_timedlock().

pthread_mutex_trylock()：如果已經 lock，回 EBUSY.

pthread_mutex_timedlock()：等候 abstime 還未取得 lock，回 ETIMEDOUT.

In most well-designed applications, a
thread should hold a mutex for only a short time, so that other threads are not prevented
from executing in parallel. This guarantees that other threads that are
blocked on the mutex will soon be granted a lock on the mutex. A thread that uses
pthread_mutex_trylock() to periodically poll the mutex to see if it can be locked risks
being starved of access to the mutex while other queued threads are successively
granted access to the mutex via pthread_mutex_lock().

## Performance of Mutexes
What is the cost of using a mutex?

實際測試 pthread-inc.c 比 pthread-inc-mutex.c 可能快約十倍 (雖然結果是錯的)。但看程式主要內容只有「變數加一」，意思是 lock/unlock 只需要「變數加一」約十倍的工作量，實際程式內容會比「變數加一」多很多，而 lock/unlock 不會那麼頻繁。

mutexes are implemented using atomic machine-language
operations (performed on memory locations visible to all threads) and require system
calls only in case of lock contention.

在 Linux, mutexes 使用 futexes (fast user space mutexes) 實作，並且 lock contentions 用 futex() syscall 處理。

比較：
locking and unlocking a file region using fcntl()
incrementing and decrementing a System V semaphore

## Mutex Deadlocks
有時候，一個 thread 需要同時處理兩個以上的共用資源，每個資源用不同的 mutex。
當多個 thread 同時 locking 相同 set 的 mutexe 時，由於順序的關係而可能出現 deadlock.

## Mutex Attributes
pthread_mutexattr_t defines the attributes of a mutex

functions used to initialize and retrieve the attributes

one of the attributes that can be set for a mutex: its type.

## Mutex Types
一般 mutex 不能有下列行為：
1. 一個 thread lock 同一個 mutex 兩次。
2. 一個 thread unlock 不是它 lock 的 mutex
3. 一個 thread unlock 還沒 lock 的 mutex

mutex type
* PTHREAD_MUTEX_DEFAULT：出現上述行為的結果為 undefined
* PTHREAD_MUTEX_NORMAL：一個 thread lock 同一個 mutex 兩次會造成 deadlock，其它為 undefined (在 Linux，這兩種都會成功)
* PTHREAD_MUTEX_ERRORCHECK：皆進行錯誤檢查並回錯誤碼，執行會較慢，較適合作為除錯使用。
* PTHREAD_MUTEX_RECURSIVE：會計數一個 thread lock 同一個 mutex 的次數，每次 unlock 減 1。其它 thread 要在完全 unlock 時才能取得 lock。2. 跟 3. 都會失敗。

Linux 提供 nonstandard static (Non-Portable) initializers for
each of the above mutex types (e.g., PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP), so that
the use of pthread_mutex_init() is not required to initialize these mutex types for
statically allocated mutexes.

##
1. 《[The Linux Programming Interface](http://man7.org/tlpi/)》chap. 30
1. http://lirobo.blogspot.tw/2014/11/pthread-mutex.html
