# Array
陣列是包含多個值的變數，bash 提供一維 indexed 及 associative 陣列。
任何變數也是 indexed 陣列，index 從 0 開始，沒最大限制，也不需要連續指定。
index 可由 arithmetic expressions 算出的整數。

associative arrays 使用字串作為 reference.

An indexed array is created automatically if any 變數 is  assigned
       to using the syntax name[subscript]=value.
要明確宣告 an  indexed 陣列, use `declare -a name` (見 [SHELL BUILTIN COMMANDS](builtin.md)).  `declare -a name[subscript]` 也可以，會忽略 subscript。

Associative arrays 使用 `declare -A` 建立。

       Attributes may be specified for an array using the declare and
       readonly builtins.  Each attribute applies to all members of an array.

指定多個陣列的值使用 `name=(value1  ...  valuen)`，valuen 的形式是 [subscript]=string.
省略 `[subscript]=` 會指定上個 index 加一，一開始的省略從 0 開始。

指定個別陣列 element：`name[subscript]=value`。
負的 subscript：相對最大的 index，-1 表示最後 element.

Any element of an array may  be  referenced  using  ${name[subscript]}.
       The braces 是需要得來避免跟 pathname expansion 衝突。If
       subscript is @ or *, the word expands to all members  of  name.   These
       subscripts  differ only when the word appears within double quotes.
double-quoted `${name[*]}`：擴展為單一 word with 每個 member 中間以特殊變數 IFS 第一個字元分隔。
double-quoted `${name[@]}`：擴展每個 element 為各自的 word。
如果陣列沒 member，`${name[@]}` 擴展為 nothing.
參考特殊參數 * 和 @。

`${#name[subscript]}`：`${name[subscript]}` 的長度。
`${#name[*]}`：陣列 element 數目。
`${#name[@]}`：陣列 element 數目。
Referencing an array without a subscript 相當於 referencing the array with a subscript of 0.

陣列視為 set 只要有一個 subscript 有指定值，null 字串也是 valid 的值。

       It is possible to obtain the keys (indices) of an array as well as  the
       values.   ${!name[@]} and ${!name[*]} expand to the indices assigned in
       array name.  The treatment when in double quotes is similar to
       the expansion of the special parameters @ and * within double quotes.

`unset name`、`unset name[*]`、`unset name[@]`：移除陣列
`unset name[subscript]`：移除 the array element at index subscript.
Care must be taken to 避免 unwanted side effects caused by pathname expansion.

       The declare, local, and readonly builtins each accept a  -a  option  to
       specify  an  indexed  array  and  a -A option to specify an associative
       array.  If both options are supplied, -A takes  precedence.   The  read
       builtin  accepts  a  -a  option to assign a list of words read from the
       standard input to an array.  The set and declare builtins display array
       values in a way that allows them to be reused as assignments.

參考：
1. man bash
1. [bash下array的幾種使用方法](http://go-linux.blogspot.tw/2007/03/basharray.html)
1. http://tldp.org/LDP/Bash-Beginners-Guide/html/sect_10_02.html
1. https://www.gnu.org/software/bash/manual/html_node/Arrays.html
1. http://www.thegeekstuff.com/2010/06/bash-array-tutorial/
1. http://www.linuxjournal.com/content/bash-arrays
1. 內建指令：declare、local、readonly、read、set、unset
