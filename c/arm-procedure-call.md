# ARM calling convention

AAPCS：[Procedure Call Standard for the ARM® Architecture](http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042f/IHI0042F_aapcs.pdf)

暫存器使用

Registers|Function|Value preserved during call
---------|--------|---------------------------
R0-R3    |Arguments / Return values| No
R4-R11   |Local variables| Yes
R12 (IP) |Intra-procedure-call scratch reg.|No
R13 (SP) |Stack Pointer|Yes
R14 (LR) |Link register，BL 指令用來存返回位址|No
R15 (PC) |Program Counter| No 

* 前四個引數用 R0-R3 傳，剩下的放在 stack
* The stack must be of the Full-Descending type
* Local variables 可用 R0-R3、R12、甚至 LR，特別在 “leaf” subroutines

BL instructions are unable to address the full 32-bit address space, so it may be 
necessary for the linker to insert a veneer between the calling routine and the called subroutine.  Veneers may 
also be needed to support ARM-
Thumb inter
-working or dynamic linking.  Any veneer inserted must preserve the 
contents of all registers except IP (r12)
 and the condition code flags
; a conforming program must assume that a 
veneer that alters IP may be inserted at any branch instruction that is exposed to a relocation that supports inter
-
working or long branches.
12 (IP) 可作為 by a linker as a scratch register between a routine and any subroutine it calls (see §5.3.1.1).

PC
BL

典型 subroutine prologue:
```
stmfd sp!,{r4-r6,lr}
```
依序將 LR、R6、R5、及 R4 存到堆疊，還會呼叫其它 subroutines 所以存 LR，R4-R6 準備作為區域變數使用。

典型 subroutine epilogue:
```
ldmfd sp!,{r4-r6,pc}
```
從 stack 回復 R4、R5、及 R6。PC 回復自儲存的 LR 同時作為 subroutine return

自 ARM 呼叫 thumb subroutine (interworking):
```
	.arm
	...
	ldr r12,=(tmbrout+1)
	mov lr,pc	@return addr.
	bx r12		@jump to thumb
	...

	.thumb
	...
tmbrout: ...
	...
	bx lr		@return (interworking)
```

註：
* PC is 8 bytes (2 instructions) ahead of “mov lr,pc”
* Bit 0 of R12 is 1, meaning a jump to thumb code in “bx r12”
* Bit 0 of LR is 0, meaning a jump to ARM code in “bx lr”

## 其它
一個 stack frame 包含一個 function call 所有需要的資料：引數、返回位址、暫存器備份、local variables. Stack-allocated objects are part of these local variables.

只存在 during the execution time of a function，不用擔心 memory leaks。

Only objects of fixed size known at compile time can be allocated on the stack. (除了 funny things like Variable-Length Arrays in C99. GCC allocates them on the stack.) This way we know the size of a stack frame at compile time, and can access objects on the stack with fixed offsets relative to the stack pointer.
