Link-time optimization

In LTO mode, the compiler proves that there is no usage of the symbol and the function is removed. Behavior is similar to keyword static that allows a compiler to do the same job even in non-LTO mode. To be sure a function symbol is not optimized out, add __attribute__((used)): 

https://gcc.gnu.org/onlinedocs/gccint/LTO.html


https://gcc.gnu.org/wiki/LinkTimeOptimizationFAQ
