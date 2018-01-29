Fenwick (Binary Indexed) Trees

一個可修改的數列，以一種預先計算「部份和」的方式儲存，來加快取得「前綴和」。

應用：高效率計算數列的前綴和、區間和

複雜度|原始|segment tree|binary indexed tree
------|----|------------|-------------------
空間  |O(n)|            |O(n)
初始化|0   |O(n)        |O(n)
修改  |1   |O(log n)    |O(log n)
詢問  |O(n)|O(log n)    |O(log n)

## 預備函數
```
int lowbit(int x)
{
    return x&(-x);
}
```
找出二進位最右邊 1 位置所代表的數值。

## BIT 區間
原始陣列 arr[n]，索引值為 1 至 n。改用 BIT 需要預先計算 n 個區間的「部份和」-- bit[b]。
第 x 區間的右界是 x ，左界是 x - lowbit(x) + 1，[x-lowbit(x)+1, x]。
再由這些區間拼出真正詢問的區間。

畫成圖
<table>
<tr><td colspan="8">[1, 8]</td></tr>
<tr><td colspan="4">[1, 4]</td></tr>
<tr><td colspan="2">[1, 2]</td><td colspan="2"></td><td colspan="2">[5, 6]</td></tr>
<tr><td>[1, 1]</td><td></td><td>[3, 3]</td><td></td><td>[5, 5]</td><td></td><td>[7, 7]</td></tr>
</table>

```
12345678
1234
12  56
1 3 5 7
```

## 求前綴和
[1, x]
可拆成 [1, x-lowbit(x)] 加 [x-lowbit(x)+1, x]，
也就是 [1, x-lowbit(x)] 加 bit[x]。
[1, x-lowbit(x)] 是另一個前綴和，依同樣方式遞迴或迴圈產生。
由於每次計算， x 最低的 1 變為 0，最多 ⌈log<sub>2</sub>x⌉ 次。

```
int query(int x)
{
     int sum = 0;
     for(; x > 0; x -= lowbit(x))
         sum += bit[x];
     return sum;
}
```

## 單項修改
修改單項 x 時，是以增加多少的方式，要修改 bit[] 中所有包含 x 的區間，
第一個 bit[] 索引值是 x，下一個索引值是 x + lowbit(x)，一直加新索引值的 lowbit()，最大到 n。
要修改 bit[] 的數目，最多 ⌈log<sub>2</sub>n⌉ 次。

```
void update(int x, int val)
{
    for(; x <= n; x += lowbit(x))
          bit[x] += val;
}
```

## 初始化
一開始都是 0 的話，bit[] 只需要都填為 0。
如果不是，可以使用 update() 函數，需要修改 n 項，所以複雜度 O(n log n)。
也可以使用特別的初始化函數，x 由小到大計算 bit [x]，使用已經計算好的 bit[x]
來計算未知的 bit[x]。
[x-lowbit(x)+1, x] = arr[x] + [x-lowbit(x)+1, x-1]

```
void init(int n)
{
    for (int x = 1; x <= n; ++x) {
        bit[x] = arr[x];
        int y = x - lowbit(x);
        for (int i = x-1; i > y; i -= lowbit(i))
            bit[x] += bit[i];
    }
}
```

```
void init2(int n)
{
    for (int x=1; x<=n; ++x)
        bit[x] = 0;

    for (int x=1; x<=n; ++x) {
        bit[x] += arr[x];
        int y = x + lowbit(x);
        if (y <= n)
            arr[y] += arr[x];
    }
}
```

## 參考
1. https://www.csie.ntu.edu.tw/~sprout/algo2016/homework/week11.pdf -- 介紹及進階習題
2. 比較：segment tree (線段樹)

## ...
a[] 原始數列
bit[] 數列以 Binary Indexed Tree 方式儲存

數列前 x 項和
將 x 以二進位表示，所有 1 的位置所代表的數值作為 bit[] index 相加
例如 x = 13 = (1101)<sub>2</sub>
BIT[1] + BIT[4] + BIT[8]

BIT[13], BIT[14], BIT[16]
