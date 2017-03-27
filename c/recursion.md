# 遞迴呼叫
Recursion is the process of repeating items in a self-similar way.
在程式語言是在函數裡面再呼叫自己，在解決許多數學問題非常有用，例如計算階乘 (Number Factorial)、產生 Fibonacci 數列等。

使用遞迴呼叫需要注意判斷函數結束的條件，否則會成為無限迴圈。

https://www.tutorialspoint.com/cprogramming/c_recursion.htm

## Euclid’s Algorithm
找出兩個整數的最大公因數

If a divides b, GCD(a,b) is a
Otherwise, find the largest integer t such that at + r = b, GCD(a,b) = GCD(r,a)

```c
int gcd(int a, int b)
{
	if (a == 0)
		return b;
	return gcd(b % a, a);
}
```

##

http://csg.sph.umich.edu/abecasis/class/2006/615.05.pdf (看到第 9 頁)
Dynamic Programming
* Related to Markov processes in Statistics
Divide-and-Conquer Algorithms
Tree Processing
