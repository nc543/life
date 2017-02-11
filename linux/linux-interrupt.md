## fast interrupt 及 slow interrupt
 
http://unix.stackexchange.com/questions/7138/fast-interrupts-in-linux

2.6.24+ 刪除了 SA_INTERRUPT，使用 IRQF_DISABLED 代替

signal 跟 interrupt

http://lists.infradead.org/pipermail/linux-mtd/2015-March/058135.html
The IRQF_DISABLED is a NOOP and has been scheduled for removal since
Linux v2.6.36

https://docs.blackfin.uclinux.org/doku.php?id=linux-kernel:interrupts
