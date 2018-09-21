shell 特別為互動使用提供許多功能，包括 job control、[command line editing](bash-readline.md)、command history 及 aliases。

## shell 運作

shell 運作的簡略描述：
1. 讀取輸入，可能從一個檔案 (shell 腳本)、從搭配選項 -c 的一個引數、或從使用者的終端機 (互動模式)。如果遇到註解開始，shell 忽略註解符號「#」及當行剩下的部份。
2. 用 metacharacter 區分出是字還是運算子，採用 [quoting](http://lirobo.blogspot.tw/2017/10/bash-quoting.html) 規則。並進行 Alias 擴展 (見 ALIASES)。
3. 解析這些 token 成 simple 及 compound 指令 (see Shell Commands).
4. 進行擴展 (見 [EXPANSION](bash-expansion.md))、分辨出檔名 lists of filenames (see Filename Expansion) and 指令 and 引數。
5. [輸出入導向](bash-redirection.md)。
6. 執行指令 (see Executing Commands see COMMAND EXECUTING)。
7. 選擇性等候指令結束並得到結束狀態 (see Exit Status)，可作為進一步的檢查或處理。

運算子 (operator) 包括[導向運算子](bash-redirection.md)及控制運算子

有 x 屬性：可直接執行

## SHELL GRAMMAR 語法

### Compound Commands 複合指令

[[ expression ]]
              Return a status of 0 or 1 depending on  the  evaluation  of  the
              conditional  expression.  Expressions are composed of
              the primaries described  below  under  CONDITIONAL  EXPRESSIONS.
              進行 tilde  expansion,  parameter  and
              變數 expansion, arithmetic expansion, command substitution,
              process substitution, and [quote](http://lirobo.blogspot.tw/2017/10/bash-quoting.html) removal，但不進行
	      Word  splitting  and pathname expansion。
              Conditional operators such as -f must be unquoted to be recognized as
              primaries.

              When used with [[, the < and > operators sort  lexicographically
              using the current locale.

       見 [SHELL BUILTIN COMMANDS](builtin.md) test 的描述 for the handling of parameters (i.e.   missing  parameters).

       When  the  == and != operators are used, the string to the right of the
       operator is considered a pattern and matched  according  to  the  rules
       described  below under Pattern Matching, as if the extglob shell option
       were enabled.  The = operator is equivalent to ==.  If the shell option
       nocasematch  is  enabled,  the match is performed without regard to the
       case of alphabetic characters.  The return value is  0  if  the  string
       matches  (==) or does not match (!=) the pattern, and 1 otherwise.  Any
       part of the pattern may be quoted to force the  quoted  portion  to  be
       matched as a string.

       An  additional  binary operator, =~, is available, with the same prece‐
       dence as == and !=.  When it is used, the string to the  right  of  the
       operator  is  considered  an  extended  regular  expression and matched
       accordingly (as in regex(3)).  The return value  is  0  if  the  string
       matches  the  pattern,  and  1 otherwise.  If the regular expression is
       syntactically incorrect, the conditional expression's return  value  is
       2.   If the shell option nocasematch is enabled, the match is performed
       without regard to the case of alphabetic characters.  Any part  of  the
       pattern  may  be  quoted to force the quoted portion to be matched as a
       string.  Bracket expressions in regular  expressions  must  be  treated
       carefully,  since normal quoting characters lose their meanings between
       brackets.  If the pattern is stored in a shell 變數,  quoting  the
       變數 expansion forces the entire pattern to be matched as a string.
       Substrings matched by parenthesized subexpressions within  the  regular
       expression  are  saved in the array BASH_REMATCH.  The element
       of BASH_REMATCH with index 0 is the portion of the string matching  the
       entire regular expression.  The element of BASH_REMATCH with index n is
       the portion of the string matching the nth parenthesized subexpression.

       Expressions may be combined using the following  operators,  listed  in
       decreasing order of precedence:

              ( expression )
                     Returns  the  value  of  expression.  This may be used to
                     override the normal precedence of operators.
              ! expression
                     True if expression is false.
              expression1 && expression2
                     True if both expression1 and expression2 are true.
              expression1 || expression2
                     True if either expression1 or expression2 is true.

              The && and || operators do not evaluate expression2 if the value
              of  expression1  is  sufficient to determine the return value of
              the entire conditional expression.

## PARAMETERS 參數
參數泛指變數，代表一個儲存值的地方。有下列表示方式：
* name (非數字開頭由英文字母、數字及「_」組成的字)：變數，有一個值，並可能有一些屬性。屬性是透過內建指令 declare 指定。
* 數字
* 特殊字元 (下面特殊參數所列)

變數經過指定產生。
```
名稱=[值]
```

如果沒給值，值是 null，也是存在的變數。變數要移除只能透過內建指令 unset。
所有值會經歷 tilde 擴展、parameter and 變數擴展、指令取代、算術擴展、及 [quote](http://lirobo.blogspot.tw/2017/10/bash-quoting.html) 移除。(見 [EXPANSION](bash-expansion.md))
如果變數的屬性為整數，即使 $((...)) 擴展沒使用，值仍會 evaluated 為 arithmetic expression。(見 Arithmetic Expansion)
除了「$@」外，不進行 Word splitting。
不進行 Pathname expansion。
Assignment statements 亦可作為內建指令 alias、declare、typeset、export、readonly、及 local 的參數。
當用在 posix 模式，these builtins may appear in a command after one or more instances of the command builtin and retain these assignment statement properties.

變數有哪幾種？整數、字串、陣列、[nameref 變數](nameref.md)？

使用 `+=` 指定一個值給 shell 變數或 array index：
* 整數變數：加法加上目前的值。
* array using compound assignment (見 [陣列](array.md)), 變數的值 is not unset (as it is when using =), and new values are appended to the array beginning at one greater than the array's maximum  index  (for  indexed arrays) or added as additional key-value pairs in an associative array.
* 字串變數：值擴展後 appended to 變數的值。

### Positional Parameters 位置參數
       A  positional  parameter  is a parameter denoted by one or more digits,
       other than the single digit 0.  Positional parameters are assigned from
       the  shell's  arguments when it is invoked, and may be reassigned using
       the set builtin command.  Positional parameters may not be assigned  to
       with  assignment statements.  The positional parameters are temporarily
       replaced when a shell function is executed (see FUNCTIONS below).

       When a positional parameter consisting of more than a single  digit  is
       expanded, it must be enclosed in braces (見 [EXPANSION](bash-expansion.md)).

### Special Parameters 特殊參數
只能讀，不能寫。

       *      擴展為從 1 開始的所有位置參數，每個位置參數擴展為個別的字。
              In contexts where  it  is
              performed, those words are subject to further word splitting and
              pathname expansion.  如果在雙引號裡面，擴展為
              每個參數由特殊變數 IFS 第一個字元連接起來的一個字。
              如果 IFS 沒設，則用 space 連接。如果 IFS 是 null，則不插入字元直接連接。
       @      擴展為從 1 開始的所有 positional parameters。When
              the  expansion  occurs  within  double  quotes,  each  parameter
              expands to a separate word.  That is, "$@" is equivalent to "$1"
              "$2"  ...   If the double-quoted expansion occurs within a word,
              the expansion of the first parameter is joined with  the  begin‐
              ning  part  of  the original word, and the expansion of the last
              parameter is joined with the last part  of  the  original  word.
              When  there  are no positional parameters, "$@" and $@ expand to
              nothing (i.e., they are removed).
       #      位置參數的數目
       ?      最後前景執行 pipeline 的 exit status
       -      Expands  to  the  current option flags as specified upon invoca‐
              tion, by the set builtin command, or  those  set  by  the  shell
              itself (such as the -i option).
       $      Expands  to  the  process ID of the shell.  In a () subshell, it
              expands to the process ID of the current  shell,  not  the  sub‐
              shell.
       !      Expands  to  the process ID of the job most recently placed into
              the background, whether executed as an asynchronous  command  or
              using the bg builtin (see JOB CONTROL below).
       0      Expands  to  the name of the shell or shell script.  This is set
              at shell initialization.  If bash is invoked with a file of com‐
              mands,  $0  is set to the name of that file.  If bash is started
              with the -c option, then $0 is set to the first  argument  after
              the  string to be executed, if one is present.  Otherwise, it is
              set to the filename used to invoke bash, as  given  by  argument
              zero.
       _      At  shell  startup,  set to the absolute pathname used to invoke
              the shell or shell script being executed as passed in the  envi‐
              ronment  or  argument  list.   Subsequently, expands to the last
              argument to the previous command, after expansion.  Also set  to
              the  full  pathname  used  to  invoke  each command executed and
              placed in the environment exported to that command.  When check‐
              ing  mail,  this  parameter holds the name of the mail file cur‐
              rently being checked.

### [Shell 變數](shell-variables.md)

### [陣列](array.md)

## [CONDITIONAL EXPRESSIONS](http://lirobo.blogspot.tw/2013/11/blog-post_26.html)
       Conditional expressions are used by the [[  compound  command  及內建指令
       test 跟 [ 來測試檔案屬性、進行字串或算術比較。
       Expressions are formed from the  following
       unary  or  binary  primaries.   If any file argument to one of the pri‐
       maries is of the form /dev/fd/n, then file descriptor n is checked.  If
       the  file  argument  to  one  of  the  primaries  is one of /dev/stdin,
       /dev/stdout, or /dev/stderr, file descriptor 0, 1, or 2,  respectively,
       is checked.

       Unless otherwise specified, primaries that operate on files follow sym‐
       bolic links and operate on the target of the link, rather than the link
       itself.

       When  used  with [[, the < and > operators sort lexicographically using
       the current locale.  The test command sorts using ASCII ordering.

       -a file
              file 存在
       -b file
              file 為 block special file.
       -c file
              file 為 character special file.
       -d file
              file 為 directory.
       -e file
              file 存在 (exist)
       -f file
              file 為 regular file.
       -g file
              file exists and is set-group-id.
       -h file
              file 為 symbolic link.
       -k file
              file 的 ``sticky'' bit is set.
       -p file
              file 存在為 named pipe (FIFO).
       -r file
              file 存在為 readable.
       -s file
              file 大小 (size) 大於 0
       -t fd  file descriptor fd is open and refers to a terminal.
       -u file
              file 的 set-user-id bit is set.
       -w file
              file 為 writable.
       -x file
              file 為 executable.
       -G file
              file exists and is owned by the effective group id.
       -L file
              file 為 symbolic link.
       -N file
              file exists and has been  modified  since  it  was  last
              read.
       -O file
              file exists and is owned by the effective user id.
       -S file
              file 為 socket.
       file1 -ef file2
              True  if file1 and file2 refer to the same device and inode num‐
              bers.
       file1 -nt file2
              file1 is newer than
              file2, or if file1 exists and file2 does not.
       file1 -ot file2
              file1 is older than file2, or if file2 exists and file1
              does not.
       -o optname
              shell 選項 optname is enabled.  See  the  list  of
              options  under  the  description  of  the  -o  option to the set
              builtin below.
       -v varname
              shell 變數 varname is set (has been  assigned  a
              value).
       -R varname
              shell 變數 varname is set and is a name refer‐
              ence.
       -z string
              字串長度 0 (zero)
       string
       -n string
              字串長度非 0 (non-zero)

       string1 == string2
       string1 = string2
              子串相等.  = should be used with  the  test
              command  for  POSIX conformance.  When used with the [[ command,
              this performs pattern matching as described above (Compound Com‐
              mands).

       string1 != string2
              字串不相等

       string1 < string2
              True if string1 sorts before string2 lexicographically.

       string1 > string2
              True if string1 sorts after string2 lexicographically.

       arg1 OP arg2
              OP  is one of -eq, -ne, -lt, -le, -gt, or -ge.  These arithmetic
              binary operators return true if arg1 is equal to, not equal  to,
              less  than, less than or equal to, greater than, or greater than
              or equal to arg2, respectively.  Arg1 and arg2 may  be  positive
              or negative integers.

## SIMPLE COMMAND EXPANSION
當要執行簡單指令時，由左而右進行下列動作：

1. the parser has  marked  as 變數 assignments 的字 (指令名稱前面) 及轉向的部份 saved for later processing.
2. 剩下的部份進行擴展後如有任何字，第一個字是指令名稱，剩下的為其引數。
3. 進行[輸出入導向](bash-redirection.md)
4. 在變數指定前，= 後面的部份進行 tilde expansion、parameter expansion、command substitution、arithmetic expansion、及 quote removal

如果沒指令名稱，變數指定影響目前 shell 的環境變數；否則成為執行指令的環境變數。If  any  of  the assignments attempts to assign a value to a
       唯讀變數, an error occurs, and the command exits with  a  non-
       zero status.

如果無指令名稱，仍進行[輸出入導向](bash-redirection.md)，但不影響目前 shell 環境。[輸出入導向](bash-redirection.md) 失敗導致指令結束回傳非 0。

如果有指令名稱，
       execution proceeds as
       described below. Otherwise, the command exits. If one of  the  expan‐
       sions  contained a command substitution, the exit status of the command
       is the exit status of the  last  command  substitution  performed.   If
       there were no command substitutions, the command exits with a status of
       zero.

## COMMAND EXECUTION 指令執行
       After a command has been split into words, if it results  in  a  simple
       command  and  an  optional list of arguments, 進行下列動作：

1. 指令名稱不含「/」，依下列順序哪個先搜尋到找到執行
	1. shell function (invoked as described above in FUNCTIONS)
	1. [內建指令](builtin.md)
	1. [hash 表](http://lirobo.blogspot.com/2017/11/bash-hash.html)
	1. PATH 路徑中同名的執行檔
	1. 有 shell function command_not_found_handle，以原本指令 (含引數) 作為引數執行 command_not_found_handle
	1. 印錯誤訊息並回傳 exit status of 127.

       Bash 使用 [hash 表](http://lirobo.blogspot.com/2017/11/bash-hash.htmltin-hash.md) 快取執行檔的完整路徑。

shell 在 a separate 執行環境執行 the named program.

如果找到的檔案不是執行檔，會假設為 shell script，會初始化一個新的 subshell 來執行
       with  the  exception  that
       the  locations  of  commands  remembered  by the parent (見 [hash](http://lirobo.blogspot.com/2017/11/bash-hash.html) are retained by the child.

shell script, a file containing shell commands.

如果腳本的第一行開始是「#!」，是用來指定解釋並執行腳本的程式，
格式是「#!\<interpreter> \<a single optional argument> \<script name> \<command arguments>」

例如：#!/bin/sh。

## COMMAND EXECUTION ENVIRONMENT 指令執行環境
The shell has an 執行環境，包含：
* open files 繼承 the shell at invocation, as modified by redirections supplied to 內建指令 exec
* 工作目錄 as set by cd, pushd, or popd, or 繼承 the shell at invocation
* the  file  creation  mode mask as set by umask or 繼承自 the shell's parent
* current traps set by trap
* shell parameters that are set by 變數 assignment or with set or inherited from the shell's parent in the environment
* shell  functions  defined during execution or inherited from the shell's parent in the environment
* options enabled at invocation (either by default  or  with  command-line arguments) or by set
* options enabled by shopt
* shell aliases defined with alias
* various  process  IDs,  including  those of background jobs, the value of $$, and the value of PPID

當不是內建指令或 shell function 的簡單指令，會執行在另一個執行環境，其值大多繼承自 shell，除非另外說明，如下：

* 開啟的檔案，會加上指令的[輸出入導向](bash-redirection.md)
* 工作目錄
* the file creation mode mask
* shell 變數 and functions  marked  for  export,  along  with 變數 exported for the command, passed in the environment
* traps caught by the shell are reset to the values inherited from the shell's parent, and traps ignored by the shell are ignored

       A command invoked  in  this  separate  environment  cannot  affect  the
       shell's execution environment.

       Command  substitution, commands grouped with parentheses, and asynchro‐
       nous commands are invoked in a subshell environment that is a duplicate
       of  the  shell  environment,  except that traps caught by the shell are
       reset to the values that the shell inherited from its parent at invoca‐
       tion.  Builtin commands that are invoked as part of a pipeline are also
       executed in a subshell environment.  Changes made to the subshell envi‐
       ronment cannot affect the shell's execution environment.

       Subshells spawned to execute command substitutions inherit the value of
       the -e option from the parent shell.  When  not  in  posix  mode,  bash
       clears the -e option in such subshells.

       If  a  command  is  followed  by a & and job control is not active, the
       default standard input for the command is  the  empty  file  /dev/null.
       Otherwise,  the  invoked  command  inherits the file descriptors of the
       calling shell as modified by redirections.

## ENVIRONMENT
環境變數是 a list  of  name-value  pairs,  of  the  form name=value.

       The shell provides several ways  to  manipulate  the  environment.   On
       invocation, the shell scans its own environment and creates a parameter
       for each name found, automatically marking it for export to child  pro‐
       cesses.   Executed  commands  inherit  the environment.  The export and
       declare -x commands allow parameters and functions to be added  to  and
       deleted from the environment.  If the value of a parameter in the envi‐
       ronment is modified, the new value becomes  part  of  the  environment,
       replacing  the  old.  The environment inherited by any executed command
       consists of the shell's initial environment, whose values may be  modi‐
       fied  in  the  shell, less any pairs removed by the unset command, plus
       any additions via the export and declare -x commands.

       The environment for any simple command or  function  may  be  augmented
       temporarily  by  prefixing  it with parameter assignments, as described
       above in PARAMETERS.  These assignment statements affect only the envi‐
       ronment seen by that command.

       If  the  -k option is set (see the set builtin command below), then all
       parameter assignments are placed in the environment for a command,  not
       just those that precede the command name.

       When  bash  invokes  an  external command, the 變數 _ is set to the
       full filename of the command and passed to that command in its environ‐
       ment.

## EXIT STATUS
exit status 是系統呼叫 waitpid 或 equivalent 回傳的值，落在 0 ~ 255。

* 0 (true)：成功 (非 0 為失敗, false)
* 2：內建指令不正確使用
* 126：檔案找到，但檔案不含可執行屬性
* 127：檔案沒找到
* 128+N：因 fatal signal N 而結束

       Bash itself returns the exit  status  of  the  last  command  executed,
       unless  a  syntax  error occurs, in which case it exits with a non-zero
       value.  See also the exit builtin command below.

## SIGNALS
       When bash is interactive, in the  absence  of  any  traps,  it  ignores
       SIGTERM (so that kill 0 does not kill an interactive shell), and SIGINT
       is caught and handled (so that the wait builtin is interruptible).   In
       all  cases,  bash  ignores  SIGQUIT.  If job control is in effect, bash
       ignores SIGTTIN, SIGTTOU, and SIGTSTP.

       Non-builtin commands run by bash have signal handlers set to the values
       inherited  by  the  shell  from its parent.  When job control is not in
       effect, asynchronous commands ignore SIGINT and SIGQUIT in addition  to
       these  inherited handlers.  Commands run as a result of command substi‐
       tution ignore the keyboard-generated job control signals SIGTTIN, SIGT‐
       TOU, and SIGTSTP.

       The  shell  exits by default upon receipt of a SIGHUP.  Before exiting,
       an interactive shell  resends  the  SIGHUP  to  all  jobs,  running  or
       stopped.  Stopped jobs are sent SIGCONT to ensure that they receive the
       SIGHUP.  To prevent the shell from sending the signal to  a  particular
       job,  it  should be removed from the jobs table with the disown builtin
       (見 [SHELL BUILTIN COMMANDS](builtin.md)) or  marked  to  not  receive  SIGHUP
       using disown -h.

       If  the  huponexit  shell  option has been set with shopt, bash sends a
       SIGHUP to all jobs when an interactive login shell exits.

       If bash is waiting for a command to complete and receives a signal  for
       which a trap has been set, the trap will not be executed until the com‐
       mand completes.  When bash is waiting for an asynchronous  command  via
       the  wait  builtin, the reception of a signal for which a trap has been
       set will cause the wait builtin to return immediately with an exit sta‐
       tus greater than 128, immediately after which the trap is executed.

## JOB CONTROL
       Job  control  refers  to  the ability to selectively stop (suspend) the
       execution of processes and continue (resume) their execution at a later
       point.   A  user  typically  employs  this  facility via an interactive
       interface supplied jointly by the operating  system  kernel's  terminal
       driver and bash.

       The  shell  associates  a  job with each pipeline.  It keeps a table of
       currently executing jobs, which may be listed with  the  jobs  command.
       When  bash starts a job asynchronously (in the background), it prints a
       line that looks like:

              [1] 25647

       indicating that this job is job number 1 and that the process ID of the
       last process in the pipeline associated with this job is 25647.  All of
       the processes in a single pipeline are members of the same  job.   Bash
       uses the job abstraction as the basis for job control.

       To  facilitate the implementation of the user interface to job control,
       the operating system maintains the notion of a current terminal process
       group ID.  Members of this process group (processes whose process group
       ID is equal to the current terminal process group ID) receive keyboard-
       generated  signals  such  as SIGINT.  These processes are said to be in
       the foreground.  Background processes are those whose process group  ID
       differs from the terminal's; such processes are immune to keyboard-gen‐
       erated signals.  Only foreground processes are allowed to read from or,
       if  the  user  so  specifies  with  stty tostop, write to the terminal.
       Background processes which attempt to read from  (write  to  when  stty
       tostop  is  in effect) the terminal are sent a SIGTTIN (SIGTTOU) signal
       by the kernel's terminal driver, which,  unless  caught,  suspends  the
       process.

       If  the operating system on which bash is running supports job control,
       bash contains facilities to use it.  Typing the suspend character (typ‐
       ically ^Z, Control-Z) while a process is running causes that process to
       be stopped and returns control to bash.   Typing  the  delayed  suspend
       character  (typically  ^Y,  Control-Y) causes the process to be stopped
       when it attempts to read input from the terminal,  and  control  to  be
       returned  to bash.  The user may then manipulate the state of this job,
       using the bg command to continue it in the background, the  fg  command
       to continue it in the foreground, or the kill command to kill it.  A ^Z
       takes effect immediately, and has the additional side effect of causing
       pending output and typeahead to be discarded.

       There are a number of ways to refer to a job in the shell.  The charac‐
       ter % introduces a job specification (jobspec).  Job number  n  may  be
       referred to as %n.  A job may also be referred to using a prefix of the
       name used to start it, or using a substring that appears in its command
       line.   For  example,  %ce  refers  to  a  stopped ce job.  If a prefix
       matches more than one job, bash reports an error.  Using %?ce,  on  the
       other  hand,  refers to any job containing the string ce in its command
       line.  If the substring matches more than  one  job,  bash  reports  an
       error.   The  symbols %% and %+ refer to the shell's notion of the cur‐
       rent job, which is the last job stopped while it was in the  foreground
       or started in the background.  The previous job may be referenced using
       %-.  If there is only a single job, %+ and %- can both be used to refer
       to  that  job.   In  output pertaining to jobs (e.g., the output of the
       jobs command), the current job is always flagged with a +, and the pre‐
       vious  job  with  a -.  A single % (with no accompanying job specifica‐
       tion) also refers to the current job.

       Simply naming a job can be used to bring it into the foreground: %1  is
       a  synonym  for  ``fg %1'', bringing job 1 from the background into the
       foreground.  Similarly, ``%1 &''  resumes  job  1  in  the  background,
       equivalent to ``bg %1''.

       The  shell  learns immediately whenever a job changes state.  Normally,
       bash waits until it is about to print a prompt before reporting changes
       in  a  job's status so as to not interrupt any other output.  If the -b
       option to the set builtin command is enabled, bash reports such changes
       immediately.   Any  trap  on  SIGCHLD  is  executed for each child that
       exits.

       If an attempt to exit bash is made while jobs are stopped (or,  if  the
       checkjobs  shell  option has been enabled using the shopt builtin, run‐
       ning), the shell prints a warning message, and, if the checkjobs option
       is  enabled,  lists  the jobs and their statuses.  The jobs command may
       then be used to inspect their status.  If a second attempt to  exit  is
       made  without  an intervening command, the shell does not print another
       warning, and any stopped jobs are terminated.

## PROMPTING
       When executing interactively, bash displays the primary prompt PS1 when
       it  is  ready  to  read a command, and the secondary prompt PS2 when it
       needs more input to complete  a  command.   Bash  allows  these  prompt
       strings  to  be  customized  by inserting a number of backslash-escaped
       special characters that are decoded as follows:
              \a     an ASCII bell character (07)
              \d     the date in "Weekday Month Date" format (e.g.,  "Tue  May
                     26")
              \D{format}
                     the  format  is  passed  to strftime(3) and the result is
                     inserted into the prompt string; an empty format  results
                     in a locale-specific time representation.  The braces are
                     required
              \e     an ASCII escape character (033)
              \h     the hostname up to the first `.'
              \H     the hostname
              \j     the number of jobs currently managed by the shell
              \l     the basename of the shell's terminal device name
              \n     newline
              \r     carriage return
              \s     the name of the shell, the basename of  $0  (the  portion
                     following the final slash)
              \t     the current time in 24-hour HH:MM:SS format
              \T     the current time in 12-hour HH:MM:SS format
              \@     the current time in 12-hour am/pm format
              \A     the current time in 24-hour HH:MM format
              \u     the username of the current user
              \v     the version of bash (e.g., 2.00)
              \V     the release of bash, version + patch level (e.g., 2.00.0)
              \w     the  current  working  directory,  with $HOME abbreviated
                     with a tilde (uses the value of the PROMPT_DIRTRIM  vari‐
                     able)
              \W     the basename of the current working directory, with $HOME
                     abbreviated with a tilde
              \!     the history number of this command
              \#     the command number of this command
              \$     if the effective UID is 0, a #, otherwise a $
              \nnn   the character corresponding to the octal number nnn
              \\     a backslash
              \[     begin a sequence of non-printing characters, which  could
                     be  used  to  embed  a terminal control sequence into the
                     prompt
              \]     end a sequence of non-printing characters

       The command number and the history number are  usually  different:  the
       history  number of a command is its position in the history list, which
       may include commands  restored  from  the  history  file  (see  HISTORY
       below),  while  the  command  number is the position in the sequence of
       commands executed during the current shell session.  After  the  string
       is  decoded,  it is expanded via parameter expansion, command substitu‐
       tion, arithmetic expansion, and quote removal, subject to the value  of
       the  promptvars  shell option (見 [SHELL BUILTIN COMMANDS](builtin.md) shopt 的描述
       ).

## [READLINE](bash-readline.md)

## HISTORY
       When the -o history option to the set builtin  is  enabled,  the  shell
       provides access to the command history, the list of commands previously
       typed.  The value of the HISTSIZE 變數 is used  as  the  number  of
       commands to save in a history list.  The text of the last HISTSIZE com‐
       mands (default 500) is saved.  The shell stores  each  command  in  the
       history  list  prior to parameter and 變數 expansion (見 [EXPANSION](bash-expansion.md)
       ) but after history expansion is performed, subject to the  values
       of the shell 變數 HISTIGNORE and HISTCONTROL.

       On startup, the history is initialized from the file named by the vari‐
       able HISTFILE (default ~/.bash_history).  The file named by  the  value
       of  HISTFILE  is  truncated,  if necessary, to contain no more than the
       number of lines specified by the value of HISTFILESIZE.   If  HISTFILE‐
       SIZE  is unset, or set to null, a non-numeric value, or a numeric value
       less than zero, the history file is not truncated.   When  the  history
       file  is  read, lines beginning with the history comment character fol‐
       lowed immediately by a digit are interpreted as timestamps for the pre‐
       ceding history line.  These timestamps are optionally displayed depend‐
       ing on the value of the HISTTIMEFORMAT 變數.   When  a  shell  with
       history  enabled  exits,  the  last $HISTSIZE lines are copied from the
       history list to $HISTFILE.  If the histappend shell option  is  enabled
       (見 [SHELL BUILTIN COMMANDS](builtin.md) shopt 的描述), the
       lines are appended to the history file, otherwise the history  file  is
       overwritten.   If  HISTFILE  is  unset,  or  if  the  history  file  is
       unwritable, the history is not saved.  If the  HISTTIMEFORMAT 變數
       is  set,  time  stamps are written to the history file, marked with the
       history comment character, so they may be preserved across  shell  ses‐
       sions.   This  uses  the history comment character to distinguish time‐
       stamps from other history lines.  After saving the history, the history
       file is truncated to contain no more than HISTFILESIZE lines.  If HIST‐
       FILESIZE is unset, or set to null, a non-numeric value,  or  a  numeric
       value less than zero, the history file is not truncated.

       The  builtin  command fc (見 [SHELL BUILTIN COMMANDS](builtin.md)) may be used
       to list or edit and re-execute a portion of the history list.  The his‐
       tory  builtin  may  be  used  to display or modify the history list and
       manipulate the history file.  When using command-line  editing,  search
       commands  are available in each editing mode that provide access to the
       history list.

       The shell allows control over which commands are saved on  the  history
       list.  The HISTCONTROL and HISTIGNORE 變數 may be set to cause the
       shell to save only a subset of the commands entered.  The cmdhist shell
       option,  if enabled, causes the shell to attempt to save each line of a
       multi-line command in the same history entry, adding  semicolons  where
       necessary  to preserve syntactic correctness.  The lithist shell option
       causes the shell to save the command with embedded newlines instead  of
       semicolons.  見 [SHELL BUILTIN COMMANDS](builtin.md) shopt
       for  information  on  setting  and  unsetting  shell
       options.

## HISTORY EXPANSION
bash 支援類似 csh 的歷史擴展。This section describes what syntax  features
are  available. 互動式 shell 預設開啟歷史擴展，可以透過內建指令 set 的選項 +H 關閉。非互動式 shell 預設不使用歷史擴展。

       History expansions introduce words from the history list into the input
       stream,  making  it  easy to repeat commands, insert the arguments to a
       previous command into the current input line, or fix errors in previous
       commands quickly.

       History  expansion  is  performed  immediately after a complete line is
       read, before the shell breaks it into words.  It  takes  place  in  two
       parts.   The  first is to determine which line from the history list to
       use during substitution.  The second is to select portions of that line
       for inclusion into the current one.  The line selected from the history
       is the event, and the portions of that line that  are  acted  upon  are
       words.   Various  modifiers  are  available  to manipulate the selected
       words.  The line is broken into words in the same fashion as when read‐
       ing  input, so that several metacharacter-separated words surrounded by
       quotes are considered one word.  History expansions are  introduced  by
       the  appearance  of  the  history  expansion  character,  which is ! by
       default.  Only backslash (\) and single quotes can  quote  the  history
       expansion character.

       Several  characters inhibit history expansion if found immediately fol‐
       lowing the history expansion character, even if it is unquoted:  space,
       tab,  newline,  carriage return, and =.  If the extglob shell option is
       enabled, ( will also inhibit expansion.

       Several shell options settable with the shopt builtin may  be  used  to
       tailor  the  behavior  of  history  expansion.  If the histverify shell
       option is enabled (see the description of the shopt builtin below), and
       readline  is  being  used,  history  substitutions  are not immediately
       passed to the shell parser.  Instead, the  expanded  line  is  reloaded
       into the readline editing buffer for further modification.  If readline
       is being used, and the histreedit shell option  is  enabled,  a  failed
       history  substitution will be reloaded into the readline editing buffer
       for correction.  The -p option to the history builtin  command  may  be
       used  to  see what a history expansion will do before using it.  The -s
       option to the history builtin may be used to add commands to the end of
       the  history  list  without  actually  executing them, so that they are
       available for subsequent recall.

The shell allows control of the various characters used by the  history
       expansion mechanism (see the description of histchars above under [Shell 變數](shell-variables.md)
       ).  The shell uses the history comment character to mark  his‐
       tory timestamps when writing the history file.

   Event Designators
       An  event designator is a reference to a command line entry in the his‐
       tory list.  Unless the reference is absolute, events  are  relative  to
       the current position in the history list.

       !      Start  a  history substitution, except when followed by a blank,
              newline, carriage return, = or ( (when the extglob shell  option
              is enabled using the shopt builtin).
       !n     Refer to command line n.
       !-n    Refer to the current command minus n.
       !!     Refer to the previous command.  This is a synonym for `!-1'.
       !string
              Refer  to the most recent command preceding the current position
              in the history list starting with string.
       !?string[?]
              Refer to the most recent command preceding the current  position
              in  the  history  list containing string.  The trailing ? may be
              omitted if string is followed immediately by a newline.
       ^string1^string2^
              Quick substitution.   Repeat  the  previous  command,  replacing
              string1  with  string2.  Equivalent to ``!!:s/string1/string2/''
              (see Modifiers below).
       !#     The entire command line typed so far.

   Word Designators
       Word designators are used to select desired words from the event.  A  :
       separates  the event specification from the word designator.  It may be
       omitted if the word designator begins with a ^, $, *, -, or  %.   Words
       are  numbered from the beginning of the line, with the first word being
       denoted by 0 (zero).  Words are inserted into the  current  line  sepa‐
       rated by single spaces.

       0 (zero)
              The zeroth word.  For the shell, this is the command word.
       n      The nth word.
       ^      The first argument.  That is, word 1.
       $      The  last  word.   This  is  usually the last argument, but will
              expand to the zeroth word if there is only one word in the line.
       %      The word matched by the most recent `?string?' search.
       x-y    A range of words; `-y' abbreviates `0-y'.
       *      All of the words but the zeroth.  This is a synonym  for  `1-$'.
              It  is  not  an  error to use * if there is just one word in the
              event; the empty string is returned in that case.
       x*     Abbreviates x-$.
       x-     Abbreviates x-$ like x*, but omits the last word.

       If a word designator is supplied without an  event  specification,  the
       previous command is used as the event.

   Modifiers
       After  the optional word designator, there may appear a sequence of one
       or more of the following modifiers, each preceded by a `:'.

       h      Remove a trailing filename component, leaving only the head.
       t      Remove all leading filename components, leaving the tail.
       r      Remove a trailing suffix of the form .xxx, leaving the basename.
       e      Remove all but the trailing suffix.
       p      Print the new command but do not execute it.
       q      Quote the substituted words, escaping further substitutions.
       x      Quote the substituted words as with q, but break into  words  at
              blanks and newlines.
       s/old/new/
              Substitute  new  for  the  first  occurrence of old in the event
              line.  Any delimiter can be used  in  place  of  /.   The  final
              delimiter  is  optional if it is the last character of the event
              line.  The delimiter may be quoted in old and new with a  single
              backslash.   If & appears in new, it is replaced by old.  A sin‐
              gle backslash will quote the &.  If old is null, it  is  set  to
              the  last  old substituted, or, if no previous history substitu‐
              tions took place, the last string in a !?string[?]  search.
       &      Repeat the previous substitution.
       g      Cause changes to be applied over the entire event line.  This is
              used  in  conjunction  with `:s' (e.g., `:gs/old/new/') or `:&'.
              If used with `:s', any delimiter can be used in place of /,  and
              the  final  delimiter is optional if it is the last character of
              the event line.  An a may be used as a synonym for g.
       G      Apply the following `s' modifier once to each word in the  event
              line.

## [RESTRICTED SHELL](restricted-shell.md)

## BUG REPORTS
       If you find a bug in bash, you should report it.  But first, you should
       make sure that it really is a bug, and that it appears  in  the  latest
       version   of  bash.   The  latest  version  is  always  available  from
       ftp://ftp.gnu.org/pub/gnu/bash/.

       Once you have determined that a bug actually exists,  use  the  bashbug
       command  to submit a bug report.  If you have a fix, you are encouraged
       to mail that as well!  Suggestions and `philosophical' bug reports  may
       be  mailed  to  bug-bash@gnu.org  or  posted  to  the  Usenet newsgroup
       gnu.bash.bug.

       ALL bug reports should include:

       The version number of bash
       The hardware and operating system
       The compiler used to compile
       A description of the bug behaviour
       A short script or `recipe' which exercises the bug

       bashbug inserts the first three items automatically into  the  template
       it provides for filing a bug report.

       Comments and bug reports concerning this manual page should be directed
       to chet.ramey@case.edu.

## BUGS
太大且太慢。(有又小又快的 shell 嗎？)
	* dash http://unix.stackexchange.com/questions/148035/is-dash-or-some-other-shell-faster-than-bash

bash 跟傳統 sh 間有些微的差別，大多是因為 POSIX 規範。

       Shell builtin commands and functions are not stoppable/restartable.

       Compound commands and command sequences of the form `a ; b ; c' are not
       handled gracefully  when  process  suspension  is  attempted.   When  a
       process  is stopped, the shell immediately executes the next command in
       the sequence.  It suffices to place the sequence  of  commands  between
       parentheses  to  force  it  into  a subshell, which may be stopped as a
       unit.

       Array may not (yet) be exported.

       There may be only one active coprocess at a time.

## 參考及延伸閱讀
1. The Gnu Readline Library
1. The Gnu History Library
1. Portable Operating System Interface (POSIX) Part 2:  Shell  and  Utilities, IEEE -- http://pubs.opengroup.org/onlinepubs/9699919799/。POSIX 是一種基於 Unix 開放系統標準家族
1. http://tiswww.case.edu/~chet/bash/POSIX -- a description of posix mode
1. sh(1), ksh(1), csh(1)
1. emacs(1), vi(1)
1. readline(3)
