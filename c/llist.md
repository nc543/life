# Linux Lock-less Linked List
Last In First Out

https://github.com/torvalds/linux/blob/master/include/linux/llist.h
https://github.com/torvalds/linux/blob/master/lib/llist.c

不需要 lock 的情況
1. llist_add 用在多個 producers 及 llist_del_all 用在多個 consumers
2. llist_add 用在多個 producers 及 一個 consumer 使用 llist_del_first
 
需要 lock 的情況
* llist_del_first 是用在一個 consumer，且 llist_del_first() 或 llist_del_all() 使用在另一個 consumers
* This is because llist_del_first depends on list->first->next not
* changing, but without lock protection, there's no way to be sure about that
* if a preemption happens in the middle of the delete operation and on being
* preempted back, the list->first is the same as before causing the cmpxchg in
* llist_del_first to succeed. For example, while a llist_del_first operation
* is in progress in one consumer, then a llist_del_first, llist_add,
* llist_add (or llist_del_all, llist_add, llist_add) sequence in another
* consumer may cause violations.
