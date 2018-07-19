## alias
```
alias [-p] [name[=value] ...]
```
沒有引數或用選項 -p 列出 aliases (格式 alias name=value)

When
              arguments  are supplied, an alias is defined for each name whose
              value is given.  A trailing space in  value causes the next word
              to be checked for alias substitution when the alias is expanded.

For each name in the argument list for which no  value  is  sup‐
              plied,  the  name  and  value  of  the  alias is printed.

## bind
```
bind [-m keymap] [-lpsvPSVX]
bind [-m keymap] [-q function] [-u function] [-r keyseq]
bind [-m keymap] -f filename
bind [-m keymap] -x keyseq:shell-command
bind [-m keymap] keyseq:function-name
bind readline-command
```
顯示目前 [readline](bash-readline.md) key 及 function 的綁定、綁定 key sequence 到 readline function 或 macro、或設定 readline 變數。

每個非選項的引數是如同 .inputrc 的指令，但 binding 跟 command 需要用不同引數傳遞。例如「"\C-x\C-r":  re-read-init-file」.

選項：
* -m keymap
	* keymap 可為 emacs (emacs-standard)、emacs-meta、emacs-ctlx、vi (vi-command)、vi-move、及 vi-insert，影響後續的綁定。
* -l
	* 列出所有 readline 功能名稱
* -p
	* 顯示 readline 功能名稱及綁定 (可輸入格式)
* -P
	* 列出目前 readline 功能名稱及綁定
* -s
	* 顯示 readline key sequences bound to macros and the strings they output (可輸入格式)
* -S
	* 顯示 readline key sequences bound to macros and the strings they output.
* -v
	* 顯示 readline variable names and values (可輸入格式)
* -V
	* 列出目前 readline 變數名稱及值
* -f filename
	* 自 filename 讀取 key bindings
* -q function
	* 詢問 function 綁定的 key
* -u function
	* 取消 function 綁定的 key
* -r keyseq
	* 移除任何目前 keyseq 的綁定
* -x keyseq:shell-command
	* 輸入 keyseq 執行 shell-command。shell-command 執行時, shell 設定變數 READLINE_LINE 為 readline line buffer 內容及 READLINE_POINT 為目前游標位置。如果執行的指令改變 READLINE_LINE 或 READLINE_POINT 的值，將會反應在編輯狀態。
* -X
	* 列出所有 key sequences bound to shell commands and the associated commands (可輸入格式)

## break
```
break [n]
```
跳脫 n 層 for、while、until、或 select 迴圈，n 預設為 1。回傳值是 0，除非 n < 1。

## builtin
```
builtin shell-builtin [arguments]
```
用內建指令執行。
當定義的 function 名稱跟內建指令相同時，用來強制使用內建指令。

內建指令 cd 常常用 function 重新定義。

如果 shell-builtin 不是一個內建指令，回傳值是 false。

## complete
```
complete [-abcdefgjksuv] [-o comp-option] [-DE] [-A action]  [-G  glob‐pat] [-W wordlist] [-F function] [-C command] [-X filterpat] [-P prefix] [-S suffix] name [name ...]
complete -pr [-DE] [name ...]
```
              Specify  how arguments to each name should be completed.  If the
              -p option is supplied, or if no options are  supplied,  existing
              completion  specifications are printed in a way that allows them
              to be reused as input.  The -r option removes a completion spec‐
              ification  for each name, or, if no names are supplied, all com‐
              pletion  specifications.   The  -D  option  indicates  that  the
              remaining  options  and  actions should apply to the ``default''
              command completion; that is, completion attempted on  a  command
              for  which  no  completion  has previously been defined.  The -E
              option indicates that the remaining options and  actions  should
              apply  to  ``empty''  command  completion;  that  is, completion
              attempted on a blank line.

              The process of applying  these  completion  specifications  when
              word  completion  is attempted is described above under Program‐
              mable Completion.

              Other options, if specified, have the following  meanings.   The
              arguments  to the -G, -W, and -X options (and, if necessary, the
              -P and -S options) should be quoted to protect them from  expan‐
              sion before the complete builtin is invoked.
              -o comp-option
                      The  comp-option  controls  several aspects of the comp‐
                      spec's behavior beyond the simple generation of  comple‐
                      tions.  comp-option may be one of:
                      bashdefault
                              Perform the rest of the default bash completions
                              if the compspec generates no matches.
                      default Use readline's default  filename  completion  if
                              the compspec generates no matches.
                      dirnames
                              Perform  directory  name completion if the comp‐
                              spec generates no matches.
                      filenames
                              Tell readline that the compspec generates  file‐
                              names,  so  it can perform any filename-specific
                              processing (like adding  a  slash  to  directory
                              names,  quoting special characters, or suppress‐
                              ing trailing spaces).  Intended to be used  with
                              shell functions.
                      noquote Tell  readline  not to quote the completed words
                              if they are filenames (quoting filenames is  the
                              default).
                      nospace Tell   readline  not  to  append  a  space  (the
                              default) to words completed at the  end  of  the
                              line.
                      plusdirs
                              After  any  matches  defined by the compspec are
                              generated,   directory   name   completion    is
                              attempted  and  any  matches  are  added  to the
                              results of the other actions.
              -A action
                      The action may be one of the  following  to  generate  a
                      list of possible completions:
                      alias   Alias names.  May also be specified as -a.
                      arrayvar
                              Array variable names.
                      binding Readline key binding names.
                      builtin Names  of  shell  builtin commands.  May also be
                              specified as -b.
                      command Command names.  May also be specified as -c.
                      directory
                              Directory names.  May also be specified as -d.
                      disabled
                              Names of disabled shell builtins.
                      enabled Names of enabled shell builtins.
                      export  Names of exported shell variables.  May also  be
                              specified as -e.
                      file    File names.  May also be specified as -f.
                      function
                              Names of shell functions.
                      group   Group names.  May also be specified as -g.
                      helptopic
                              Help topics as accepted by the help builtin.
                      hostname
                              Hostnames,  as  taken from the file specified by
                              the HOSTFILE shell variable.
                      job     Job names, if job control is active.   May  also
                              be specified as -j.
                      keyword Shell  reserved words.  May also be specified as
                              -k.
                      running Names of running jobs, if job control is active.
                      service Service names.  May also be specified as -s.
                      setopt  Valid arguments for the -o  option  to  the  set
                              builtin.
                      shopt   Shell  option  names  as  accepted  by the shopt
                              builtin.
                      signal  Signal names.
                      stopped Names of stopped jobs, if job control is active.
                      user    User names.  May also be specified as -u.
                      variable
                              Names of all shell variables.  May also be spec‐
                              ified as -v.
              -C command
                      command  is  executed in a subshell environment, and its
                      output is used as the possible completions.
              -F function
                      The shell function function is executed in  the  current
                      shell  environment.   When the function is executed, the
                      first argument ($1) is the name  of  the  command  whose
                      arguments  are being completed, the second argument ($2)
                      is the word being completed, and the third argument ($3)
                      is  the  word  preceding the word being completed on the
                      current command line.  When it  finishes,  the  possible
                      completions  are retrieved from the value of the COMPRE‐
                      PLY array variable.
              -G globpat
                      The pathname expansion pattern globpat  is  expanded  to
                      generate the possible completions.
              -P prefix
                      prefix  is  added at the beginning of each possible com‐
                      pletion after all other options have been applied.
              -S suffix
                      suffix is appended to each possible completion after all
                      other options have been applied.
              -W wordlist
                      The  wordlist  is  split using the characters in the IFS
                      special variable as delimiters, and each resultant  word
                      is  expanded.   The possible completions are the members
                      of the resultant list which match the  word  being  com‐
                      pleted.
              -X filterpat
                      filterpat  is  a pattern as used for pathname expansion.
                      It is applied to the list of possible completions gener‐
                      ated  by  the  preceding options and arguments, and each
                      completion matching filterpat is removed from the  list.
                      A  leading  !  in filterpat negates the pattern; in this
                      case, any completion not matching filterpat is removed.

              The return value is true unless an invalid option  is  supplied,
              an  option  other than -p or -r is supplied without a name argu‐
              ment, an attempt is made to remove  a  completion  specification
              for a name for which no specification exists, or an error occurs
              adding a completion specification.

[Bash ssh 由歷史資料來自動補齊主機名稱](https://blog.longwin.com.tw/2012/02/bash-autocomplete-ssh-2012/)

## continue [n]
直接開始下一回 for、while、until、或 select 封閉的控制迴圈。如果有 n，開始第 n 層封閉迴圈。如果 n 超出所有封閉迴圈層數，則使用最外層。回傳值 0，除非 n < 1。

## enable [-a] [-dnps] [-f filename] [name ...]
啟用及停用內建指令。
停用某個內建指令可以不用指令完整路徑執行同名的外部指令

範例：
* `enable -n test` 停用內建指令 test
* `enable test` 啟用內建指令 test
* `enable` 或 `enable -p` 列出啟用的內建指令
* `enable -n` 列出停用的內建指令
* `enable -a` 列出所有內建指令，無論啟用及停用的
* `enable -s` 列出啟用的 POSIX 內建指令
* `enable -f filename` 載入來自 shared object filename 的內建指令
* `enable -d` 移除之前透過 -f 載入的內建指令

## let arg [arg ...]
              每個 arg 是要 evaluated 的 arithmetic expression (見 ARITHMETIC EVALUATION)。如果最後 arg evaluates 為 0，回傳 1，否則回傳 1。

## logout
Exit a login shell.

## read [-ers] [-a aname] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]
              從標準輸入或 fd 讀入一行，
              first word 指定給 first name, the second word 給
              second  name, 以此類推, with leftover words and their interven‐
              ing separators 指定給 last name.  如果輸入的
              words 少於 name 數目，剩下的 name 指定為空的值。
              在 IFS 的字元用來
              split  the  line  為 words using the same rules the shell uses
              for expansion (described above under Word Splitting).  The back‐
              slash  character  (\)  may be used to remove any special meaning
              for the next character read and for line continuation.  Options,
              if supplied, have the following meanings:
              -a aname
                     The words are assigned to sequential indices of the array
                     variable aname, starting at 0.  aname is unset before any
                     new  values  are  assigned.   Other  name  arguments  are
                     ignored.
              -d delim
                     delim 第一字元用來結束一行，而不是 newline。
              -e     如果標準輸入來自終端機，使用 [readline](bash-readline.md)
                     obtain the line. Readline 使用目前的 (或預設的，如果 line
                     編輯原本沒啟用) 編輯設定。
              -i text
                     If readline is being used  to  read  the  line,  text  is
                     placed into the editing buffer before editing begins.
              -n nchars
                     read  returns after reading nchars characters rather than
                     waiting for a complete line of input, but honor a  delim‐
                     iter  if fewer than nchars characters are read before the
                     delimiter.
              -N nchars
                     read returns  after  reading  exactly  nchars  characters
                     rather  than waiting for a complete line of input, unless
                     EOF is encountered or read times out.  Delimiter  charac‐
                     ters  encountered  in the input are not treated specially
                     and do not cause read to return until  nchars  characters
                     are read.
              -p prompt
                     Display prompt on standard error, without a trailing new‐
                     line, before attempting to read any input.  The prompt is
                     displayed only if input is coming from a terminal.
              -r     Backslash does not act as an escape character.  The back‐
                     slash is considered to be part of the line.  In  particu‐
                     lar,  a  backslash-newline pair may not be used as a line
                     continuation.
              -s     Silent mode.  If input is coming from a terminal, charac‐
                     ters are not echoed.
              -t timeout
                     Cause  read  to time out and return failure if a complete
                     line of input (or a specified number  of  characters)  is
                     not  read within timeout seconds.  timeout may be a deci‐
                     mal number with a fractional portion following the  deci‐
                     mal  point.   This  option  is  only effective if read is
                     reading input from a terminal,  pipe,  or  other  special
                     file;  it  has no effect when reading from regular files.
                     If read times out, read saves any partial input read into
                     the  specified  variable  name.   If  timeout  is 0, read
                     returns immediately, without trying  to  read  any  data.
                     The  exit status is 0 if input is available on the speci‐
                     fied file descriptor, non-zero otherwise.  The exit  sta‐
                     tus is greater than 128 if the timeout is exceeded.
              -u fd  Read input from file descriptor fd.

              If no names are supplied, the line read is assigned to the vari‐
              able REPLY.  The return code  is  zero,  unless  end-of-file  is
              encountered,  read  times  out (in which case the return code is
              greater than 128), a variable assignment error (such as  assign‐
              ing  to a readonly variable) occurs, or an invalid file descrip‐
              tor is supplied as the argument to -u.


## [set](builtin-set.md)

## shift [n]
所有位置參數往前位移 n 個位置，沒給 n 值時當作 1。n 超出範圍不動作，回傳大於 0 的值；正常回傳 0。

## [shopt](builtin-shopt.md)

## times
印出累積的 user 及 system times for  the  shell  and
              for processes run from the shell.

## type
內建指令
```
type [-aftpP] name [name ...]
```
查所有 name 作為指令的型態，有 alias、keyword (shell 保留字)、function、builtin、和 file。
所有 name 都找到回傳 true，否則回傳 false，可用來看指令是否存在。

選項
* 無：印出每個 name 的解釋
* -t： 印出 alias、keyword、function、builtin、或 file 之一；如果找不到，不印。
* If  the  -p  option is used, type either returns the name of the disk file that would be executed if name were specified as a command name, or nothing if ``type -t name'' would not return file.
* The -P option forces a PATH search for each  name, even if ``type -t name'' would not return file.  If a command is hashed, -p and -P print the hashed value, which is not necessarily  the  file  that appears first in PATH. [hash](http://lirobo.blogspot.com/2017/11/bash-hash.html)
* If the -a option is used, type prints all of the places that contain  an  executable named name.  This includes aliases and functions, if and only if the -p option is not also used.  The table of hashed commands is not  consulted  when  using  -a.
* The -f option suppresses shell function lookup, as with the command builtin.

## unset [-fv] [-n] [name ...]
              For  each  name,  移除 corresponding variable or function.
              -v：移除變數。唯讀變數不能移除。
              -f：移除 shell 函數。
              If the -n option
              is supplied, and name is a variable with the nameref  attribute,
              name  will  be unset rather than the variable it references.  -n
              has no effect if the -f option is supplied.  If no  options  are
              supplied,  each  name refers to a variable; if there is no vari‐
              able by that name, any function with that name is  unset.   Each
              unset  variable  or  function  is  removed  from the environment
              passed to subsequent commands.  If any of COMP_WORDBREAKS,  RAN‐
              DOM, SECONDS, LINENO, HISTCMD, FUNCNAME, GROUPS, or DIRSTACK are
              unset, they lose their special properties, even if they are sub‐
              sequently reset.  The exit status is true unless a name is read‐
              only.
