# EXPANSION 擴展
指令行切成字後會依序進行下列擴展：
1. brace ({})
1. tilde (~)
1. parameter and variable、arithmetic、command substitution ($)
1. word splitting：上面 ($) 類擴展如不在雙引號內，會依據 IFS 進行字切割。
1. pathname

有些系統還有 process substitution，跟 tilde, parameter, variable, and arithmetic expansion and command substitution 同時進行。

只有 brace expansion, word splitting, 及 pathname expansion 會改變字的數目，其它擴展擴展一個字為一個字，唯一的例外是 "$@" 及 "${name[@]}" 的擴展 (見 PARAMETERS).

## Brace Expansion {}
包含有成對的 {}，產生 {} 間一系列以「,」區隔的字串，或是兩個數字或兩個單一字元以「..」區隔的序列擴展。序列擴展如果是數字的，前面可以加 0 來嘗試強迫產生相同位數的數字。數字或字元間的序列擴展預設的增減值是 1 或 -1，可以再加「..數字」設定增減值。{} 裡可以有 {} 進行巢狀擴展。

「${」不做 brace 擴展，以免跟 parameter 擴展衝突。

例如
* 「a{d,c,b}e」會擴展成「ade ace abe」.
* mkdir /usr/local/src/bash/{old,new,dist,bugs}
* chown root /usr/{ucb/{ex,edit},lib/{ex?.?*,how_ex}}

傳統的 sh 沒有 Brace 擴展，要停用 Brace 擴展可以使用 +B 選項。

## Tilde Expansion ~
以「~」開頭的字, 如果有「/」則開始省略。
* `~` 取代為 $HOME 值，如沒設則取代為執行 shell 使用者的家目錄。
* `~+` 取代為 $PWD 值
* `~-` 取代為 $OLDPWD 值
* `~數字` 或 `~+數字`
* `~-數字`
* `~login_name` 取代為 login_name 的家目錄。


       If the char-
       acters following the tilde in the tilde-prefix consist of a  number  N,
       optionally  prefixed  by  a  `+' or a `-', the tilde-prefix is replaced
       with the corresponding element from the directory stack, as it would be
       displayed by the dirs builtin invoked with the tilde-prefix as an argu-
       ment.  If the characters following the tilde in the  tilde-prefix  con-
       sist of a number without a leading `+' or `-', `+' is assumed.

如果 login name invalid 或 the tilde expansion fails, the word is
       unchanged.

       Each variable assignment is checked for unquoted tilde-prefixes immedi-
       ately following a : or the first =.  In these cases, tilde expansion is
       also performed.  Consequently, one may use  filenames  with  tildes  in
       assignments  to  PATH,  MAILPATH, and CDPATH, and the shell assigns the
       expanded value.

## Parameter Expansion
「$」字元引入參數擴展、指令取代、或算術擴展。參數名稱可用 {} 包起來，以避免跟緊接著的字元有錯誤連結。名稱是兩位以上數子，必須用 {} 包起來。

       ${parameter}
              The  value of parameter is substituted.  The braces are required
              when parameter is a positional  parameter  with  more  than  one
              digit, or when parameter is followed by a character which is not
              to be interpreted as part of its name.  The parameter is a shell
              parameter  as  described above PARAMETERS) or an array reference
              (Arrays).

       如果第一個字元是「!」,  it
       introduces a level of variable indirection.  Bash uses the value of the
       variable formed from the rest of parameter as the name of the variable;
       this  variable  is  then expanded and that value is used in the rest of
       the substitution, rather than the value of parameter itself.   This  is
       known as indirect expansion.  The exceptions to this are the expansions
       of ${!prefix*} and ${!name[@]} described below.

       In each of the cases below, word is subject to tilde expansion, parame-
       ter expansion, command substitution, and arithmetic expansion.

       When  not  performing  substring  expansion, using the forms documented
       below (e.g., :-), bash tests for a parameter that  is  unset  or  null.
       Omitting  the  colon  results  in  a  test only for a parameter that is
       unset.

       ${parameter:-word}
              使用預設值。當 parameter unset 或 null 時，傳回 word。
       ${parameter:=word}
              指定並使用預設值。當 parameter unset 或 null，parameter 指定為 word 並傳回 word。
              Positional  parameters  and  special parameters 不能用這種方式指定。
       ${parameter:?word}
              Display  Error if Null or Unset.  If parameter is null or unset,
              the expansion of word (or a message to that effect  if  word  is
              not  present) is written to the standard error and the shell, if
              it is not interactive, exits.  Otherwise, the value of parameter
              is substituted.
       ${parameter:+word}
              Use  Alternate Value.  If parameter is null or unset, nothing is
              substituted, otherwise the expansion of word is substituted.
       ${parameter:offset}
       ${parameter:offset:length}
              Substring Expansion.  Expands to up to length characters of  the
              value  of  parameter starting at the character specified by off-
              set.  If parameter is @, an indexed array subscripted by @ or *,
              or  an  associative  array name, the results differ as described
              below.  If length is omitted, expands to the  substring  of  the
              value of parameter starting at the character specified by offset
              and extending to the end of the value.  length  and  offset  are
              arithmetic expressions (see ARITHMETIC EVALUATION below).

              If  offset  evaluates  to  a number less than zero, the value is
              used as an offset in characters from the end  of  the  value  of
              parameter.   If  length evaluates to a number less than zero, it
              is interpreted as an offset in characters from the  end  of  the
              value  of  parameter rather than a number of characters, and the
              expansion is the characters  between  offset  and  that  result.
              Note  that a negative offset must be separated from the colon by
              at least one space to avoid being confused with  the  :-  expan-
              sion.

              If  parameter  is  @, the result is length positional parameters
              beginning at offset.  A negative offset is taken relative to one
              greater  than the greatest positional parameter, so an offset of
              -1 evaluates to the last positional parameter.  It is an  expan-
              sion error if length evaluates to a number less than zero.

              If parameter is an indexed array name subscripted by @ or *, the
              result is  the  length  members  of  the  array  beginning  with
              ${parameter[offset]}.   A  negative  offset is taken relative to
              one greater than the maximum index of the specified  array.   It
              is  an expansion error if length evaluates to a number less than
              zero.

              Substring expansion applied to  an  associative  array  produces
              undefined results.

              Substring  indexing  is zero-based unless the positional parame-
              ters are used, in  which  case  the  indexing  starts  at  1  by
              default.   If  offset  is  0,  and the positional parameters are
              used, $0 is prefixed to the list.

       ${!prefix*}
       ${!prefix@}
              Names matching prefix.  Expands to the names of variables  whose
              names begin with prefix, separated by the first character of the
              IFS special variable.  When @ is used and the expansion  appears
              within  double  quotes, each variable name expands to a separate
              word.

       ${!name[@]}
       ${!name[*]}
              List of array keys.  If name is an array  variable,  expands  to
              the  list  of array indices (keys) assigned in name.  If name is
              not an array, expands to 0 if name is set  and  null  otherwise.
              When  @  is used and the expansion appears within double quotes,
              each key expands to a separate word.

       ${#parameter}
              參數 parameter 的長度。
              If  parameter is * or @, the value
              substituted is the number of positional parameters.  If  parame-
              ter  is  an  array name subscripted by * or @, the value substi-
              tuted is the number of elements in the array.  If  parameter  is
              an  indexed  array  name  subscripted by a negative number, that
              number is interpreted as relative to one greater than the  maxi-
              mum  index of parameter, so negative indices count back from the
              end of the array, and an index of -1 references  the  last  ele-
              ment.

       ${parameter#word}
       ${parameter##word}
              移除符合的 prefix pattern.  The word is expanded to produce
              a pattern just as in pathname expansion.  If the pattern matches
              the  beginning of the value of parameter, then the result of the
              expansion is the expanded value of parameter with  the  shortest
              matching  pattern  (the ``#'' case) or the longest matching pat-
              tern (the ``##'' case) deleted.  If parameter is  @  or  *,  the
              pattern  removal operation is applied to each positional parame-
              ter in turn, and the expansion is the resultant list.  If param-
              eter  is  an array variable subscripted with @ or *, the pattern
              removal operation is applied to each  member  of  the  array  in
              turn, and the expansion is the resultant list.
從開頭開始比對，一比對到符合 word 時，回傳剩下的部份
從開頭開始比對，比對到最後符合 word 時，回傳剩下的部份

       ${parameter%word}
       ${parameter%%word}
              移除符合的 suffix pattern.  The word is expanded to produce
              a pattern just as in pathname expansion.  If the pattern matches
              a  trailing portion of the expanded value of parameter, then the
              result of the expansion is the expanded value of parameter  with
              the  shortest  matching  pattern (the ``%'' case) or the longest
              matching pattern (the ``%%'' case) deleted.  If parameter  is  @
              or  *,  the  pattern  removal operation is applied to each posi-
              tional parameter in turn, and the  expansion  is  the  resultant
              list.   If  parameter is an array variable subscripted with @ or
              *, the pattern removal operation is applied to  each  member  of
              the array in turn, and the expansion is the resultant list.
從尾端開始比對，一比對到符合 word 時，回傳剩下的部份
從尾端開始比對，比對到最後符合 word 時，回傳剩下的部份

* ${parameter/pattern/string}<br>
  ${parameter//pattern/string}<br>
  ${parameter/#pattern/string}
	* pattern 取代為 string.  The pattern is expanded to produce a pattern just as in pathname expansion.  Parameter is  expanded  and
              the  longest match of pattern against its value is replaced with
              string.  If pattern begins with /, all matches  of  pattern  are
              replaced   with  string.   Normally  only  the  first  match  is
              replaced.  If pattern begins with #, it must match at the begin-
              ning of the expanded value of parameter.  If pattern begins with
              %, it must match at the end of the expanded value of  parameter.
              If string is null, matches of pattern are deleted and the / fol-
              lowing pattern may be omitted.  If parameter is @ or *, the sub-
              stitution  operation  is applied to each positional parameter in
              turn, and the expansion is the resultant list.  If parameter  is
              an  array  variable  subscripted  with  @ or *, the substitution
              operation is applied to each member of the array  in  turn,  and
              the expansion is the resultant list.

* ${parameter^pattern}
       ${parameter^^pattern}
       ${parameter,pattern}
       ${parameter,,pattern}
              Case  modification.   This expansion modifies the case of alpha-
              betic characters in parameter.  The pattern is expanded to  pro-
              duce a pattern just as in pathname expansion.  Each character in
              the expanded value of parameter is tested against pattern,  and,
              if  it  matches the pattern, its case is converted.  The pattern
              should not attempt to match more  than  one  character.   The  ^
              operator  converts  lowercase letters matching pattern to upper-
              case; the , operator converts matching uppercase letters to low-
              ercase.  The ^^ and ,, expansions convert each matched character
              in the expanded value; the ^ and , expansions match and  convert
              only  the  first character in the expanded value.  If pattern is
              omitted, it is treated like a ?, which matches every  character.
              If  parameter  is  @  or  *,  the case modification operation is
              applied to each positional parameter in turn, and the  expansion
              is  the  resultant list.  If parameter is an array variable sub-
              scripted with @ or *, the case modification operation is applied
              to  each  member  of the array in turn, and the expansion is the
              resultant list.

## Command Substitution 指令取代
取代為指令執行的輸出 (移除 trailing newlines)，有兩種形式。
```
$(command)
```
及舊形的
```
`command`
```

`$(cat file)` 可以用更快的 `$(< file)` 取代。

       When  the  old-style  backquote form of substitution is used, backslash
       retains its literal meaning except when followed by $, `,  or  \.   The
       first backquote not preceded by a backslash terminates the command sub-
       stitution.  When using the $(command) form, all characters between  the
       parentheses make up the command; none are treated specially.

指令取代可以巢狀使用。To nest when using the backquoted
       form, escape the inner backquotes with backslashes.

如果指令取代放在雙引號裡面，之後就不進行 word  splitting 及 pathname expansion。

## Arithmetic Expansion
       Arithmetic  expansion allows the evaluation of an arithmetic expression
       and the substitution of the result.  The format for  arithmetic  expan-
       sion is:

              $((expression))

       The  old  format  $[expression]  is  deprecated  and will be removed in
       upcoming versions of bash.

       The expression is treated as if it were within  double  quotes,  but  a
       double  quote  inside  the  parentheses  is not treated specially.  All
       tokens in the expression undergo parameter and variable expansion, com-
       mand  substitution,  and  quote  removal.  The result is treated as the
       arithmetic expression to be evaluated.  Arithmetic  expansions  may  be
       nested.

       The  evaluation  is performed according to the rules listed below under
       ARITHMETIC EVALUATION.  If expression is invalid, bash prints a message
       indicating failure and no substitution occurs.

## Process Substitution
       Process  substitution  is supported on systems that support named pipes
       (FIFOs) or the /dev/fd method of naming open files.  It takes the  form
       of  <(list) or >(list).  The process list is run with its input or out-
       put connected to a FIFO or some file in /dev/fd.  The name of this file
       is  passed  as  an argument to the current command as the result of the
       expansion.  If the >(list) form is used, writing to the file will  pro-
       vide  input  for list.  If the <(list) form is used, the file passed as
       an argument should be read to obtain the output of list.

       When available, process substitution is performed  simultaneously  with
       parameter  and variable expansion, command substitution, and arithmetic
       expansion.

## Word Splitting 切割字
如果 parameter expansion、command substitution、及 arithmetic expansion 的結果不在雙引號內，會進行字切割。

會用 IFS 的每個字元作為分隔符號來切割。
如果 IFS 未設，或者其值剛好為預設的 \<space>\<tab>\<newline>，會再忽略其它擴展結果前後的這些字元。
如果 IFS 不同於預設值，
       then sequences of the whitespace characters space and
       tab are ignored at the beginning and end of the word, as  long  as  the
       whitespace  character is in the value of IFS (an IFS whitespace charac-
       ter).  Any character in IFS that is not IFS whitespace, along with  any
       adjacent  IFS  whitespace  characters, delimits a field.  A sequence of
       IFS whitespace characters is also treated as a delimiter.
如果 IFS 是 null，no word splitting occurs.

       Explicit  null  arguments  (""  or '') are retained.  Unquoted implicit
       null arguments, resulting from the expansion of parameters that have no
       values,  are  removed.  If a parameter with no value is expanded within
       double quotes, a null argument results and is retained.

## Pathname Expansion 路徑擴展
除非設 -f 選項，bash scans each  word  for the characters *, ?, and [.  If one of these characters
       appears, then the word is regarded as a pattern, and replaced  with  an
       alphabetically  sorted list of 所有符合 pattern 的檔名 (see Pat-
       tern Matching below).  If no matching  filenames  are  found,  and  the
       shell  option  nullglob is not enabled, the word is left unchanged.  If
       the nullglob option is set, and no  matches  are  found,  the  word  is
       removed.   If  the  failglob  shell  option  is set, and no matches are
       found, an error message is printed and the command is not executed.  If
       the  shell option nocaseglob is enabled, the match is performed without
       regard to the case of alphabetic  characters.   Note  that  when  using
       range expressions like [a-z] (see below), letters of the other case may
       be included, depending on the setting of LC_COLLATE.  When a pattern is
       used  for  pathname  expansion,  the character ``.''  at the start of a
       name or immediately following  a  slash  must  be  matched  explicitly,
       unless  the shell option dotglob is set.  When matching a pathname, the
       slash character must always be matched explicitly.  In other cases, the
       ``.''   character  is  not  treated  specially.  See the description of
       shopt below under SHELL BUILTIN  COMMANDS  for  a  description  of  the
       nocaseglob, nullglob, failglob, and dotglob shell options.

       The  GLOBIGNORE shell variable may be used to restrict the set of file-
       names matching a pattern.  If GLOBIGNORE is set, each matching filename
       that also matches one of the patterns in GLOBIGNORE is removed from the
       list of matches.  The filenames ``.''  and ``..''  are  always  ignored
       when  GLOBIGNORE is set and not null.  However, setting GLOBIGNORE to a
       non-null value has the effect of enabling the dotglob shell option,  so
       all other filenames beginning with a ``.''  will match.  To get the old
       behavior of ignoring filenames beginning with a ``.'', make ``.*''  one
       of  the  patterns  in  GLOBIGNORE.  The dotglob option is disabled when
       GLOBIGNORE is unset.

### Pattern Matching

       Any character that appears in a pattern, other than the special pattern
       characters  described below, matches itself.  The NUL character may not
       occur in a pattern.  A backslash escapes the following  character;  the
       escaping  backslash  is  discarded  when matching.  The special pattern
       characters must be quoted if they are to be matched literally.

       The special pattern characters have the following meanings:

              *      Matches any string, including the null string.  When  the
                     globstar  shell  option  is  enabled,  and * is used in a
                     pathname expansion context, two adjacent  *s  used  as  a
                     single  pattern  will  match  all  files and zero or more
                     directories and subdirectories.  If followed by a /,  two
                     adjacent  *s  will match only directories and subdirecto‐
                     ries.
              ?      符合任何單一字元
              [...]  Matches any one of the enclosed characters.   A  pair  of
                     characters  separated by a hyphen denotes a range expres‐
                     sion; any character that falls between those two  charac‐
                     ters,  inclusive,  using  the  current locale's collating
                     sequence and character set, is  matched.   If  the  first
                     character following the [ is a !  or a ^ then any charac‐
                     ter not enclosed is matched.  The sorting order of  char‐
                     acters  in range expressions is determined by the current
                     locale and the values of the LC_COLLATE or  LC_ALL  shell
                     variables, if set.  To obtain the traditional interpreta‐
                     tion of range expressions, where [a-d] is  equivalent  to
                     [abcd],  set  value of the LC_ALL shell variable to C, or
                     enable the globasciiranges shell  option.   A  -  may  be
                     matched by including it as the first or last character in
                     the set.  A ] may be matched by including it as the first
                     character in the set.

                     Within  [ and ], character classes can be specified using
                     the syntax [:class:], where class is one of the following
                     classes defined in the POSIX standard:
                     alnum  alpha  ascii  blank  cntrl digit graph lower print
                     punct space upper word xdigit
                     A character class matches any character belonging to that
                     class.  The word character class matches letters, digits,
                     and the character _.

                     Within [ and ], an equivalence  class  can  be  specified
                     using the syntax [=c=], which matches all characters with
                     the same collation weight  (as  defined  by  the  current
                     locale) as the character c.

                     Within [ and ], the syntax [.symbol.] matches the collat‐
                     ing symbol symbol.

       If the extglob shell option is enabled using the shopt builtin, several
       extended  pattern  matching operators are recognized.  In the following
       description, a pattern-list is a list of one or more patterns separated
       by a |.  Composite patterns may be formed using one or more of the fol‐
       lowing sub-patterns:

              ?(pattern-list)
                     Matches zero or one occurrence of the given patterns
              *(pattern-list)
                     Matches zero or more occurrences of the given patterns
              +(pattern-list)
                     Matches one or more occurrences of the given patterns
              @(pattern-list)
                     Matches one of the given patterns
              !(pattern-list)
                     Matches anything except one of the given patterns

## Quote Removal
最後移除所有非上述擴展產生的，unquoted 用的「\」、「'」、及「"」。

## 參考
* http://godleon.blogspot.tw/2007/06/shell-script-linux-pipe.html
