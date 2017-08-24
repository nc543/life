pthread-incr.c

Dynamic mutex creation
is somewhat more complex, and we delay discussion of it until Section 30.1.5.


According to SUSv3, applying the operations that we describe in the remainder
of this section to a copy of a mutex yields results that are undefined. Mutex
operations should always be performed only on the original mutex that has
been statically initialized using PTHREAD_MUTEX_INITIALIZER or dynamically initialized
using pthread_mutex_init() (described in Section 30.1.5).


## Locking and Unlocking a Mutex



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
1. http://lirobo.blogspot.tw/2014/11/pthread-mutex.html
