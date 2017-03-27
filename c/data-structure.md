## arrays
bit array
circular buffer
dynamic array
hash table
hashed array tree
sparse array

## linked-list
* 缺點
	* 因為需要儲存指標，需要較多記憶體
	* 只能按順序存取
	* Nodes 可能儲存在非連續的記憶體空間而增加了存取時間，特別在 CPU cache
doubly linked-list
* linked-list 新增反向指標
multiply linked-list
* 依各種不同條件的 linked-list
circular linked-list (ring)
double ring
unrolled linked list
* 每個 node 儲存多個固定最大數目 element 的 linked list，可增進 cache 效能、減少需要的記憶體 (可能需要多一個欄位紀錄有多捨 element)。node 可設計成 cache line 大小或小倍數
hash

## 搜尋用資料結構
