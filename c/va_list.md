
va_list，宣告一個指標，讓它指向引數串列。 va_start，初始化這個指標，讓它真正指向正確的引數串列開頭。 va_arg，來取得va_list中的資料。 va_end，清除這個指標，把它設為NULL。範例如下： void func(int n, ...) { va_list args; va_start(args, n); while(n>0) { printf("%d\n", va_arg(args, int)); n--; } va_end(args); }


va_list

va_arg

va_start

va_end

##

__VA_ARGS__

int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);

https://zh.wikipedia.org/wiki/Stdarg.h
https://dotblogs.com.tw/simplecestlavie/2013/01/02/86637

