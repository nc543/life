## sigaction() system cal
改變 process 收到特定 signal 的動作
```
#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
* signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.
* If act is non-NULL, the new action for signal signum is installed from act. 
* If oldact is non-NULL, the previous action is saved in oldact.
