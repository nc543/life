# Signal

Linux 支援 POSIX reliable signals (standard signals) 及 POSIX real-time signals。

## signal 動作
signal 的動作是 process 的屬性，每個 signal 都安排有處理方式 (disposition)，預設動作有：
* Term：結束 process。
* Ign：忽略。
* Core：結束 process 並 dump core (見 core(5))。
* Stop：暫停 process。
* Cont：繼續執行原本暫停的 process。

透過系統呼叫 sigaction() (或 signal() 但不 portable) 可改變 signal 的動作為
* default action
* ignore the signal
* 自訂的 signal handler。預設使用 process stack，可透過 sigaltstack() 改用其它 stack。

fork() 繼承 signal 動作，execve() 時回復預設值，但忽略的維持忽略。

### 系統呼叫 sigaction()
改變 process 收到特定 signal 的動作
```
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
* signum：任何 valid signal，除了 SIGKILL 及 SIGSTOP.
* act：非 NULL 時設定新動作。
* oldact：非 NULL 時取回舊動作。

```
struct sigaction {
    void     (*sa_handler)(int);
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer)(void);
};
```
有些處理器架構使用 union，要避免同時設定 sa_handler 及 sa_sigaction.

sa_handler：指定動作，可以是 SIG_DFL 設為預設動作、SIG_IGN 忽略、或者一個 signal 處理函數指標。此函數接收 signal 號碼作為唯一的引數。

sa_sigaction：使用時 sa_flags 設為 SA_SIGINFO，取代 sa_handler 作為 signal 處理函數，接收 signal 號碼作為第一個引數、siginfo_t 指標作為第二個引數、cast 為 void * 的 ucontext_t 指標作為第三個引數。
Commonly, 第三個引數不使用。ucontext_t 見 getcontext(3)。

sa_mask：signal 處理函數執行時新增的 signal block mask，除非使用 SA_NODEFER flag。

sa_restorer：並非打算給 application 使用，POSIX 沒有 sa_restorer 欄位，細節見 sigreturn(2)。

## 送 signal

## 等候 signal

## 同步接受 signal

## Signal mask and pending signals
可以 block 某些 signal，也就是 signal 產生後不會傳送，直到 unblock，這中間的階段稱為 pending。

每個 thread 有 signal mask 表明 block 哪些 signals (使用 pthread_sigmask()，單 thread process 可用 sigprocmask())。

fork() 繼承 signal mask，execve() 後仍舊維持。

signal 可以是給 process 的 (例如使用 kill()) 或給特定 thread 的 (例如產生 SIGSEGV 及 SIGFPE 是 a consequence of exe‐
       cuting a specific machine-language instruction are thread directed,  as
       are  signals  targeted  at a specific thread using pthread_kill(3)).
任何未 block 的 thread 都可能收到給 process 的 signal。

thread 透過 sigpending() 可以取得 pending 的 signals，包括給 process 的及給此 thread 的。

## Standard signals
有些 signal 號碼是跟處理器架構有關，如同 Value 欄位所示。
有三個值的，第一個通常用在 alpha 及 sparc，第二個用在 x86、arm、及其它大部分架構，第三個用在 mips。parisc 用的值沒標示，請見 Linux 核心原始碼。- 表示沒用到。

original POSIX.1-1990 standard.
       Next  the  signals  not  in  the POSIX.1-1990 standard but described in
       SUSv2 and POSIX.1-2001.
       Next various other signals.

Signal   |Value   |Action|Comment
---------|--------|------|--
SIGHUP   |    1   |Term  |Hangup detected on controlling terminal or death of controlling process
SIGINT   |    2   |Term  |Interrupt from keyboard
SIGQUIT  |    3   |Core  |Quit from keyboard
SIGILL   |    4   |Core  |Illegal Instruction
SIGABRT  |    6   |Core  |Abort signal from abort(3)
SIGFPE   |    8   |Core  |Floating point exception
SIGKILL  |    9   |Term  |Kill signal
SIGSEGV  |   11   |Core  |Invalid memory reference
SIGPIPE  |   13   |Term  |Broken pipe: write to pipe with no readers
SIGALRM  |   14   |Term  |Timer signal from alarm(2)
SIGTERM  |   15   |Term  |Termination signal
SIGUSR1  |30,10,16|Term  |User-defined signal 1
SIGUSR2  |31,12,17|Term  |User-defined signal 2
SIGCHLD  |20,17,18|Ign   |Child stopped or terminated
SIGCONT  |19,18,25|Cont  |Continue if stopped
SIGSTOP  |17,19,23|Stop  |Stop process
SIGTSTP  |18,20,24|Stop  |Stop typed at terminal
SIGTTIN  |21,21,26|Stop  |Terminal input for background process
SIGTTOU  |22,22,27|Stop  |Terminal output for background process
---------|--------|------|--
SIGBUS   |10,7,10 |Core  |Bus error (bad memory access)
SIGPOLL  |        |Term  |Pollable event (Sys V). Synonym for SIGIO
SIGPROF  |27,27,29|Term  |Profiling timer expired
SIGSYS   |12,31,12|Core  |Bad argument to routine (SVr4)
SIGTRAP  |   5    |Core  |Trace/breakpoint trap
SIGURG   |16,23,21|Ign   |Urgent condition on socket (4.2BSD)
SIGVTALRM|26,26,28|Term  |Virtual alarm clock (4.2BSD)
SIGXCPU  |24,24,30|Core  |CPU time limit exceeded (4.2BSD)
SIGXFSZ  |25,25,31|Core  |File size limit exceeded (4.2BSD)
---------|--------|------|--
SIGIOT   |   6    |Core  |IOT trap. A synonym for SIGABRT
SIGEMT   | 7,-,7  |Term  |
SIGSTKFLT| -,16,- |Term  |Stack fault on coprocessor (unused)
SIGIO    |23,29,22|Term  |I/O now possible (4.2BSD)
SIGCLD   | -,-,18 |Ign   |A synonym for SIGCHLD
SIGPWR   |29,30,19|Term  |Power failure (System V)
SIGINFO  | 29,-,- |      |A synonym for SIGPWR
SIGLOST  | -,-,-  |Term  |File lock lost (unused)
SIGWINCH |28,28,20|Ign   |Window resize signal (4.3BSD, Sun)
SIGUNUSED| -,31,- |Core  |Synonymous with SIGSYS

* SIGKILL 及 SIGSTOP 不能 caught, blocked, or ignored.
* Signal 29 is SIGINFO / SIGPWR on an alpha but SIGLOST on a sparc.
* SIGEMT is not specified in POSIX.1-2001, but  nevertheless  appears  on most  other UNIX systems, where its default action is typically to terminate the process with a core dump.
* SIGPWR (which is not specified in POSIX.1-2001) is typically ignored by default on those other UNIX systems where it appears.
* SIGIO (which is not specified in POSIX.1-2001) is ignored by default on several other UNIX systems.

## Real-time signals

## Async-signal-safe functions

## Interruption of system calls and library functions by signal handlers

## Interruption of system calls and library functions by stop signals

## 參考
1. man 7 signal
