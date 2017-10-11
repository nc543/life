`__builtin_expect`

Linux kernel 定義了兩個簡單的界面 likely() 和 unlikely() 在 include/linux/compiler.h：
```
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)
```
