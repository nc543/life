macros, preprocessor

## Macro replacement
C11 6.10.3

限制
1. idenitical
2. 重複定義
3. object-like macro 在 identifier 跟 replacement list 之間要有 white-space
4. ?
5. identifier `__VA_ARGS__` 只能出現在參數使用省略符號 (ellipsis) 的 function-like macro 的 replacement-list
6. ?

語意 (semantics)
7. identifier 稱為 macro name，replacement list 前後的 white-space 不作為 replacement list 的一部分。
8. 如果 `# identifier` lexically 出現在 preprocessing directive could begin，`identifier` 不作為 macro replacement (看沒)
9. object-like macro `# define identifier replacement-list new-line` 導致接下來每個符合 identifier 的 macro name 取代為 the replacement list of preprocessing tokens that constitute the remainder of the directive. The replacement list is then rescanned for more macro names as specified below.
10. 可以有參數的 function-like macro
	```
	# define identifier lparen ) replacement-list new-line
	# define identifier lparen identifier-list ) replacement-list new-line
	# define identifier lparen ... ) replacement-list new-line
	# define identifier lparen identifier-list , ... ) replacement-list new-line
	```
	用法類似函式呼叫，參數由選擇性的 identifier-list 指定，scope 到此定義結束。接下來每個符合 identifier 且跟隨著 ( 的 function-like macro name 會取代為 replacement-list，直到 ) , 進行時其中的 new-line 視為一般 white-space。
11. ?
12. ?

##### Argument substitution
C11 6.10.3.1 function-like macro 的引數取代

1. After the arguments for the invocation of a function-like macro have been identified, argument substitution takes place. 在 replacement-list 的參數, 除非前置 `#` 或 `##`、或 followed  `##`，取代為對應的引數 after all macros contained therein have been expanded. Before being substituted, each argument’s preprocessing tokens are completely macro replaced as if they formed the rest of the preprocessing file; no other preprocessing tokens are available.
2.  replacement-list 的 `__VA_ARGS__` 視為一個參數，取代為引數 variable arguments。

##### The # operator
C11 6.10.3.2

C 前置處理器的類函數取代巨集可以將引數轉換成字串，只要在參數前面加「#」。

限制
1. Each # preprocessing token in the replacement list for a function-like macro shall be followed by a parameter as the next preprocessing token in the replacement list.

語意
2. 在 replacement-list 前置 `#` 的參數，含 `#` 取代為 a single character string literal preprocessing token that contains the spelling of the preprocessing token sequence for the corresponding argument. 引數中間的 white space，無論有幾個，會變成單一 space 字元。White space before the first preprocessing token and after the last preprocessing token composing the argument is deleted. Otherwise, the original spelling of each preprocessing token in the argument is retained in the character string literal, except for special handling for producing the spelling of string literals and character constants: a \ character is inserted before each " and \ character of a character constant or string literal (including the delimiting " characters), except that it is implementation-defined whether a \ character is inserted before the \ character beginning a universal character name. If the replacement that results is not a valid character string literal, the behavior is undefined. The character string literal corresponding to an empty argument is "".
	* evaluation `#` 及 `##` 的順序未指定

Object-like macros resemble data objects when used, function-like macros resemble function calls


may define any valid identifier as a macro

變數前面加上#表示轉換為string 
```
#define SHOW(msg) printf(#msg)
```

## 其它
__FUNCTION__
