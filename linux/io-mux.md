blocking I/O
* recvfrom() 等候到 datagram、複製到 user buffer 後 return
* 如果有多個 socket 等候接收，勢必需要各自 thread 來避免卡住
nonblocking I/O
* recvfrom() 也可以 non-blocking 使用，一直詢問，直到收到 datagram 並複製到 user buffer
* 如果有多個 socket 等候接收，需要每個 socket 詢問
I/O multiplexing (select and poll)
* 先用 select() 系統呼叫等候到有 datagram，再用 recvfrom() 讀取。使用 select() 的好處是一次可以等候多個 fd，內部會一直詢問。
* 需要掃描每個 fd
signal driven I/O (SIGIO)
* sigacion() 註冊 SIGIO 的 sigal hander，有 I/O 動作時呼叫，再用 recvfrom() 讀取。
asynchronous I/O (POSIX aio)
* aio_read() 
* windows iocp

## select()
int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

限制
1. readfds、writefds、exceptfds 這些是 bitmap，有數量 FD_SETSIZE 限制，通常是 1024。
2. kernel 會複寫 bitmap，使用者每次呼叫時要重寫。
3. kernel 及使用者每次需要掃描整個 bitmap 來知道哪些有設，如果很 sparse，效率會很差
4. kernel 需要不斷地每個 bitmap 檢查，直到有 ready

## pselect()

## poll()
int poll(struct pollfd *fds, nfds_t nfds, int timeout);

           struct pollfd {
               int   fd;         /* file descriptor */
               short events;     /* requested events */
               short revents;    /* returned events */
           };

類似 select()，但把 bitmap 改為 fd 陣列 (解 #1 問題)，並將詢問跟結果的欄位分開 (如果使用者適當維護並再使用陣列，可解 #2 問題)。如果 poll 將詢問跟結果的陣列分開可解 #3 問題。

造成 #4 問題在於 select()/poll() 每次都要給所有詢問跟結果 (stateless)，可以改成 statefull 方式，逐步給要需要詢問的 (decalre_interest())、每次取得一個事件 get_next_event()。

## epoll
epoll 是 Linux stateful 的實作，包含三個系統呼叫
1. epoll_create() 建立一個 epoll instance 回傳 file descriptor。
2. epoll_ctl() 註冊要詢問的 file descriptors，成為 epoll set。
3. epoll_wait() 等候 I/O 事件發生

## kqueue
kqueue 是 FreeBSD stateful 的實作
kqueue is technically superior to epoll

## 參考及延伸閱讀
http://people.eecs.berkeley.edu/~sangjin/2012/12/21/epoll-vs-kqueue.html
