# Hash table 雜湊表

所要查詢的關鍵字 (key) 經過雜湊函數映射到表中一個位置來加速查詢。

##
Malte Skarupke [I Wrote The Fastest Hashtable](https://probablydance.com/2017/02/26/i-wrote-the-fastest-hashtable/) 對高效能的 hash table 提供許多關鍵的分析，以及 cache miss 的探討。

重點提示:
1. 上界
2. lookup 效能
3. hash function 的設計
4. 新增和刪除的效率
5. key-value 操作
