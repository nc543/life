# 執行檔完整路徑的快取

bash 會將透過 $PATH 找到的執行檔完整路徑存在 hash 表裡，下次使用就不用再找 $PATH 而直接採用 hash 表紀錄的完整路徑。

`hash [-lr] [-p filename] [-dt] [name]`

* `hash` 或 `hast -d`：印出 hash 表中所有記錄的完整路徑及使用次數
* `hash -d name`：刪除 hash 表中 name 的紀錄 (可有多個 name)
* `hash -r`：刪除 hash 表中所有的記錄
* `hosh -t name`：印出 hash 表中 name 的完整路徑 (可有多個 name)
* `hash -p filename name`：為 name 在 hash 表建立使用 filename 作為完整的檔名。可用來非標準路徑的執行檔
* `hash -l`：印出 hash 表中所有的記錄的完整路徑，採用可輸入格式，可用來事先建立 hash 表用
