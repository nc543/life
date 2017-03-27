[「你所不知道的 C 語言」系列講座](http://hackfoldr.org/dykc/)

## for
```
for (起始值; 條件式; 更新值) {
	指令;
};
```
一開始執行起始值的動作，然後每次迴圈開始時做條件式檢查、結束時執行更新值的動作。
相當於
```
起始值;
while (條件式) {
	指令;
	更新值;
};
```

http://dhcp.tcgs.tc.edu.tw/c/p007.htm

## call-by-value, call-by-reference
http://denniskubes.com/2012/08/20/is-c-pass-by-value-or-reference/

pass-by-value：passing a copy of the variable to a function.
pass-by-reference：passing an alias of the variable to a function.

嚴格來說，C 傳遞參數只有 pass-by-value，都會複製引數的值作為參數，包括代表指標、陣列的位址也會複製，而 structs 則是每個 ... 都會複製。
這些複製到函數裡面用的值，在函數裡經過修改並不會改變原本的值

那什麼是 call-by-reference 呢？

在 C++，a reference is an alias for another variable. C doesn’t have this concept.

In C when passing a pointer, the syntax requires a dereference to be applied to get the value。
在真正 pass-by-reference 的程式語言，例如 Pascal (parameters declared with var) and C++ (parameters declared with &)，不需要 dereference。
It is more correct to refer to the C mechanism as “passing a reference”.


## 回傳 struct
* 實際上會在堆疊傳入結果的指標，並複製
* 夠小的 struct 直接回傳
* http://stackoverflow.com/questions/22957175/how-does-function-actually-return-struct-variable-in-c

## 其它
http://www.embedded.com/electronics-blogs/embedded-round-table/4419407/The-ring-buffer
[運算子順序](http://lirobo.blogspot.tw/2015/12/blog-post_12.html)
https://github.com/mcinglis/c-style
