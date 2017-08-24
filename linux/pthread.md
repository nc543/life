
http://lirobo.blogspot.tw/2014/05/pthread.html

PTHREAD_MUTEX_RECURSIVE_NP

multi-threaded application，lightweight process (LWP)
* 一個程式有好幾個執行 flow，但共用絕大部分 application data structures
* 每個 thread associate a lightweight process，讓每個 thread 可以 scheduled independently by the kernel so that one may sleep while another remains runnable. Examples of POSIX-compliant pthread libraries that use Linux's lightweight processes areLinuxThreads, Native POSIX Thread Library (NPTL), and IBM's Next Generation Posix Threading Package (NGPT).
* 大部分用 pthread (POSIX thread) libraries 來寫，created, handled, and scheduled entirely in User Mode。
* Linux uses lightweight processes to offer better support for multithreaded applications. Basically, two lightweight processes may share some resources, like the address space, the open files, and so on. Whenever one of them modifies a shared resource, the other immediately sees the change. Of course, the two processes must synchronize themselves when accessing the shared resource.

參考：http://man7.org/linux/man-pages/man3/pthread_create.3.html
