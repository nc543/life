# 內建指令
shell 本身提供的指令，有些 shell 用外部指令取代。

除非特別說明，接受「-」開頭選項的內建指令接受「--」來表示選項的結束。
但「:」、「true」、「false」、及「test」並不接受選項，也就不處理「--」。
exit、logout、break、continue、let、及 shift 接受及處理「-」開始的引數，不需要「--」作為結束。
其它接受引數、但不接受選項的內建指令，「-」開始的引數會解釋為無效的選項，需要「--」來避免這種情況。

## :
```
: [arguments]
```
擴展 arguments 及進行指定的轉向。回傳值是 0。

## . filename [arguments]
## source filename [arguments]
執行外部程式會建立一個子程序執行，也就是 subshell。如果用「.」或 source，就不會開另一個子程序執行。
              If filename  does  not  contain  a  slash,
              filenames  in  PATH  are  used  to find the directory containing
              filename.  The file searched for in PATH need not be executable.
              When  bash  is  not  in  posix  mode,  the  current directory is
              searched if no file is found in PATH.  If the sourcepath  option
              to  the  shopt  builtin  command  is turned off, the PATH is not
              searched.

如有任何 arguments，會成為其位置參數；否則 positional parameters are unchanged.

如果 filename 無法讀取回傳 false。

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

## bg [jobspec ...]
              Resume  each  suspended  job jobspec in the background, as if it
              had been started with &.  If jobspec is not present, the shell's
              notion  of the current job is used.  bg jobspec returns 0 unless
              run when job control is disabled or, when run with  job  control
              enabled,  any  specified  jobspec  was  not found or was started
              without job control.

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

## caller [expr]
              Returns the context of any active subroutine call (a shell func‐
              tion or a script executed with the . or source builtins).  With‐
              out expr, caller displays the line number and source filename of
              the current subroutine call.  If a non-negative integer is  sup‐
              plied as expr, caller displays the line number, subroutine name,
              and source file corresponding to that position  in  the  current
              execution  call  stack.  This extra information may be used, for
              example, to print a stack trace.  The current frame is frame  0.
              The  return  value is 0 unless the shell is not executing a sub‐
              routine call or expr does not correspond to a valid position  in
              the call stack.

## cd [-L|[-P [-e]] [-@]] [dir]
              Change  the  current  directory to dir.  if dir is not supplied,
              the value of the HOME shell variable is the default.  Any  addi‐
              tional arguments following dir are ignored.  The variable CDPATH
              defines the search path for the directory containing  dir:  each
              directory  name  in  CDPATH  is  searched  for dir.  Alternative
              directory names in CDPATH are separated by a colon (:).  A  null
              directory  name  in CDPATH is the same as the current directory,
              i.e., ``.''.  If dir begins with a slash (/), then CDPATH is not
              used.  The  -P  option  causes  cd to use the physical directory
              structure by resolving symbolic links while traversing  dir  and
              before processing instances of .. in dir (see also the -P option
              to the set builtin command); the -L option forces symbolic links
              to  be followed by resolving the link after processing instances
              of .. in dir.  If .. appears in dir, it is processed by removing
              the  immediately previous pathname component from dir, back to a
              slash or the beginning of dir.  If the  -e  option  is  supplied
              with  -P,  and  the current working directory cannot be success‐
              fully determined after a successful directory  change,  cd  will
              return  an unsuccessful status.  On systems that support it, the
              -@ option presents the extended  attributes  associated  with  a
              file  as  a directory.  An argument of - is converted to $OLDPWD
              before the directory change is attempted.  If a non-empty direc‐
              tory  name  from  CDPATH is used, or if - is the first argument,
              and the directory change is successful, the absolute pathname of
              the  new  working  directory  is written to the standard output.
              The return value is  true  if  the  directory  was  successfully
              changed; false otherwise.

## command [-pVv] command [arg ...]
              Run  command  with  args  suppressing  the normal shell function
              lookup. Only builtin commands or commands found in the PATH  are
              executed.   If the -p option is given, the search for command is
              performed using a default value for PATH that is  guaranteed  to
              find  all  of  the  standard  utilities.  If either the -V or -v
              option is supplied, a description of command is printed.  The -v
              option  causes  a single word indicating the command or filename
              used to invoke command to be displayed; the -V option produces a
              more  verbose  description.  If the -V or -v option is supplied,
              the exit status is 0 if command was found, and  1  if  not.   If
              neither option is supplied and an error occurred or command can‐
              not be found, the exit status is 127.  Otherwise, the exit  sta‐
              tus of the command builtin is the exit status of command.

## compgen [option] [word]
              Generate  possible  completion matches for word according to the
              options, which may  be  any  option  accepted  by  the  complete
              builtin  with  the exception of -p and -r, and write the matches
              to the standard output.  When using the -F or  -C  options,  the
              various  shell  variables  set  by  the  programmable completion
              facilities, while available, will not have useful values.

              The matches will be generated in the same way as if the program‐
              mable completion code had generated them directly from a comple‐
              tion specification with the same flags.  If word  is  specified,
              only those completions matching word will be displayed.

              The  return  value is true unless an invalid option is supplied,
              or no matches were generated.

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

## compopt [-o option] [-DE] [+o option] [name]
              Modify  completion  options  for  each  name  according  to  the
              options,  or  for the currently-executing completion if no names
              are supplied.  If no options are given, display  the  completion
              options  for  each name or the current completion.  The possible
              values of option  are  those  valid  for  the  complete  builtin
              described  above.   The  -D  option indicates that the remaining
              options should apply to the ``default'' command completion; that
              is,  completion  attempted  on a command for which no completion
              has previously been defined.  The -E option indicates  that  the
              remaining  options should apply to ``empty'' command completion;
              that is, completion attempted on a blank line.

              The return value is true unless an invalid option  is  supplied,
              an attempt is made to modify the options for a name for which no
              completion specification exists, or an output error occurs.

## continue [n]
直接開始下一回 for、while、until、或 select 封閉的控制迴圈。如果有 n，開始第 n 層封閉迴圈。如果 n 超出所有封閉迴圈層數，則使用最外層。回傳值 0，除非 n < 1。

## declare [-aAfFgilnrtux] [-p] [name[=value] ...]
## typeset [-aAfFgilnrtux] [-p] [name[=value] ...]
              Declare  variables and/or give them attributes.  If no names are
              given then display the values of variables.  The -p option  will
              display the attributes and values of each name.  When -p is used
              with name arguments, additional options, other than -f  and  -F,
              are  ignored.   When  -p  is supplied without name arguments, it
              will display the attributes and values of all  variables  having
              the attributes specified by the additional options.  If no other
              options  are  supplied  with  -p,  declare  will   display   the
              attributes  and  values  of  all shell variables.  The -f option
              will restrict the display to shell  functions.   The  -F  option
              inhibits  the display of function definitions; only the function
              name and attributes are printed.  If the extdebug  shell  option
              is  enabled  using  shopt,  the source file name and line number
              where the function is defined are displayed  as  well.   The  -F
              option implies -f.  The -g option forces variables to be created
              or modified at the global scope, even when declare  is  executed
              in  a  shell  function.   It is ignored in all other cases.  The
              following options can be used to restrict  output  to  variables
              with the specified attribute or to give variables attributes:
              -a     Each  name  is  an  indexed  array  variable  (see Arrays
                     above).
              -A     Each name is an associative array  variable  (see  Arrays
                     above).
              -f     Use function names only.
              -i     The variable is treated as an integer; arithmetic evalua‐
                     tion (see ARITHMETIC EVALUATION above) is performed  when
                     the variable is assigned a value.
              -l     When  the  variable  is  assigned a value, all upper-case
                     characters are converted to lower-case.   The  upper-case
                     attribute is disabled.
              -n     Give  each  name  the nameref attribute, making it a name
                     reference to another variable.  That  other  variable  is
                     defined by the value of name.  All references and assign‐
                     ments to name,  except  for  changing  the  -n  attribute
                     itself,  are  performed  on  the  variable  referenced by
                     name's value.  The -n  attribute  cannot  be  applied  to
                     array variables.
              -r     Make names readonly.  These names cannot then be assigned
                     values by subsequent assignment statements or unset.
              -t     Give each name the  trace  attribute.   Traced  functions
                     inherit  the  DEBUG  and  RETURN  traps  from the calling
                     shell.  The trace attribute has no  special  meaning  for
                     variables.
              -u     When  the  variable  is  assigned a value, all lower-case
                     characters are converted to upper-case.   The  lower-case
                     attribute is disabled.
              -x     Mark  names  for  export  to  subsequent commands via the
                     environment.

              Using `+' instead of `-' turns off the attribute  instead,  with
              the exceptions that +a may not be used to destroy an array vari‐
              able and +r will not remove the readonly attribute.   When  used
              in a function, declare and typeset make each name local, as with
              the local command, unless the -g option is supplied.  If a vari‐
              able  name  is  followed by =value, the value of the variable is
              set to value.  When using -a or -A and the  compound  assignment
              syntax  to  create array variables, additional attributes do not
              take effect until subsequent assignments.  The return value is 0
              unless  an  invalid option is encountered, an attempt is made to
              define a function using ``-f foo=bar'', an attempt  is  made  to
              assign  a  value  to  a readonly variable, an attempt is made to
              assign a value to an array variable without using  the  compound
              assignment  syntax (see Arrays above), one of the names is not a
              valid shell variable name, an attempt is made to turn off  read‐
              only  status for a readonly variable, an attempt is made to turn
              off array status for an array variable, or an attempt is made to
              display a non-existent function with -f.

## dirs [-clpv] [+n] [-n]
              Without  options,  displays  the  list  of  currently remembered
              directories.  The default display  is  on  a  single  line  with
              directory  names  separated by spaces.  Directories are added to
              the list with  the  pushd  command;  the  popd  command  removes
              entries from the list.
              -c     Clears  the  directory  stack  by  deleting  all  of  the
                     entries.
              -l     Produces a listing  using  full  pathnames;  the  default
                     listing format uses a tilde to denote the home directory.
              -p     Print the directory stack with one entry per line.
              -v     Print  the  directory stack with one entry per line, pre‐
                     fixing each entry with its index in the stack.
              +n     Displays the nth entry counting from the left of the list
                     shown by dirs when invoked without options, starting with
                     zero.
              -n     Displays the nth entry counting from  the  right  of  the
                     list shown by dirs when invoked without options, starting
                     with zero.

              The return value is 0 unless an invalid option is supplied or  n
              indexes beyond the end of the directory stack.

## disown [-ar] [-h] [jobspec ...]
              Without  options,  remove  each jobspec from the table of active
              jobs.  If jobspec is not present, and neither the -a nor the  -r
              option  is  supplied, the current job is used.  If the -h option
              is given, each jobspec is not removed from  the  table,  but  is
              marked  so  that  SIGHUP  is  not  sent  to the job if the shell
              receives a SIGHUP.  If no jobspec is  supplied,  the  -a  option
              means  to  remove or mark all jobs; the -r option without a job‐
              spec argument restricts operation to running jobs.   The  return
              value is 0 unless a jobspec does not specify a valid job.

## echo [-neE] [arg ...]
              Output  the  args,  separated  by spaces, followed by a newline.
              The return status is 0 unless a write error occurs.   If  -n  is
              specified, the trailing newline is suppressed.  If the -e option
              is given,  interpretation  of  the  following  backslash-escaped
              characters  is  enabled.  The -E option disables the interpreta‐
              tion of these escape characters, even on systems where they  are
              interpreted  by  default.  The xpg_echo shell option may be used
              to dynamically determine  whether  or  not  echo  expands  these
              escape  characters  by  default.   echo does not interpret -- to
              mean the end of options.  echo interprets the  following  escape
              sequences:
              \a     alert (bell)
              \b     backspace
              \c     suppress further output
              \e
              \E     an escape character
              \f     form feed
              \n     new line
              \r     carriage return
              \t     horizontal tab
              \v     vertical tab
              \\     backslash
              \0nnn  the  eight-bit  character  whose value is the octal value
                     nnn (zero to three octal digits)
              \xHH   the eight-bit character whose value  is  the  hexadecimal
                     value HH (one or two hex digits)
              \uHHHH the  Unicode (ISO/IEC 10646) character whose value is the
                     hexadecimal value HHHH (one to four hex digits)
              \UHHHHHHHH
                     the Unicode (ISO/IEC 10646) character whose value is  the
                     hexadecimal value HHHHHHHH (one to eight hex digits)

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

## eval [arg ...]
http://lirobo.blogspot.tw/2013/02/eval.html
              The  args  are read and concatenated together into a single com‐
              mand.  This command is then read and executed by the shell,  and
              its  exit status is returned as the value of eval.  If there are
              no args, or only null arguments, eval returns 0.

## exec [-cl] [-a name] [command [arguments]]
如果有 command，執行 `command [arguments]` 取代 shell，不產生新的 process。
* -l：執行 command 時，passes - at the beginning  of  the  zeroth  argument，如同指令 login。
* -c：以空的環境變數執行 command
* -a name：執行 command 時，使用 name 作為 zeroth 引數 (指令名稱)

如果因某些原因 command 無法執行 , a non-interactive shell exits,
              除非 the execfail shell option is enabled.  In that  case,  it
              returns  failure.   An  interactive shell returns failure if the
              file cannot be executed.

If command is not specified, redirections 成功 in the current shell, 回傳 0，否則回傳 1。

## exit [n]
              Cause the shell to exit with a status of n.  If  n  is  omitted,
              the exit status is that of the last command executed.  A trap on
              EXIT is executed before the shell terminates.

## export [-fn] [name[=word]] ...
## export -p
              http://lirobo.blogspot.tw/2013/11/export.html
              The supplied names are marked for automatic export to the  envi‐
              ronment  of subsequently executed commands.  If the -f option is
              given, the names refer to functions.  If no names are given,  or
              if  the  -p  option is supplied, a list of names of all exported
              variables is printed.  The -n option causes the export  property
              to be removed from each name.  If a variable name is followed by
              =word, the value of the variable is set to word.  export returns
              an exit status of 0 unless an invalid option is encountered, one
              of the names is not a valid shell variable name, or -f  is  sup‐
              plied with a name that is not a function.

## fc [-e ename] [-lnr] [first] [last]
## fc -s [pat=rep] [cmd]
              The  first  form  selects a range of commands from first to last
              from the history list and  displays  or  edits  and  re-executes
              them.   First  and  last may be specified as a string (to locate
              the last command beginning with that string) or as a number  (an
              index  into the history list, where a negative number is used as
              an offset from the current command  number).   If  last  is  not
              specified  it is set to the current command for listing (so that
              ``fc -l -10'' prints the last 10 commands) and to  first  other‐
              wise.   If first is not specified it is set to the previous com‐
              mand for editing and -16 for listing.

              The -n option suppresses the command numbers when listing.   The
              -r  option reverses the order of the commands.  If the -l option
              is given, the commands are listed on  standard  output.   Other‐
              wise,  the editor given by ename is invoked on a file containing
              those commands.  If ename is not given, the value of the  FCEDIT
              variable  is used, and the value of EDITOR if FCEDIT is not set.
              If neither variable is set, vi is used.  When  editing  is  com‐
              plete, the edited commands are echoed and executed.

              In  the  second form, command is re-executed after each instance
              of pat is replaced by rep.  Command is intepreted  the  same  as
              first  above.  A useful alias to use with this is ``r="fc -s"'',
              so that typing ``r cc'' runs the  last  command  beginning  with
              ``cc'' and typing ``r'' re-executes the last command.

              If  the  first  form  is  used,  the return value is 0 unless an
              invalid option is encountered or first or last  specify  history
              lines  out  of  range.  If the -e option is supplied, the return
              value is the value of the last command executed or failure if an
              error occurs with the temporary file of commands.  If the second
              form is used, the return status is that of the  command  re-exe‐
              cuted,  unless  cmd  does  not  specify a valid history line, in
              which case fc returns failure.

## fg [jobspec]
              Resume jobspec in the foreground, and make it the  current  job.
              If jobspec is not present, the shell's notion of the current job
              is used.  The return value is that of the  command  placed  into
              the  foreground,  or failure if run when job control is disabled
              or, when run with job control enabled, if jobspec does not spec‐
              ify  a  valid  job  or  jobspec specifies a job that was started
              without job control.

## getopts optstring name [args]
              getopts is used by shell procedures to parse positional  parame‐
              ters.   optstring  contains  the  option characters to be recog‐
              nized; if a character is followed by  a  colon,  the  option  is
              expected  to have an argument, which should be separated from it
              by white space.  The colon and question mark characters may  not
              be  used as option characters.  Each time it is invoked, getopts
              places the next option in the shell variable name,  initializing
              name if it does not exist, and the index of the next argument to
              be processed into the variable OPTIND.  OPTIND is initialized to
              1  each  time  the  shell or a shell script is invoked.  When an
              option requires an argument, getopts places that  argument  into
              the  variable OPTARG.  The shell does not reset OPTIND automati‐
              cally; it must be  manually  reset  between  multiple  calls  to
              getopts within the same shell invocation if a new set of parame‐
              ters is to be used.

              When the end of options is encountered,  getopts  exits  with  a
              return  value  greater than zero.  OPTIND is set to the index of
              the first non-option argument, and name is set to ?.

              getopts normally parses the positional parameters, but  if  more
              arguments are given in args, getopts parses those instead.

              getopts  can  report errors in two ways.  If the first character
              of optstring is a colon, silent error  reporting  is  used.   In
              normal  operation,  diagnostic messages are printed when invalid
              options or missing option arguments  are  encountered.   If  the
              variable  OPTERR  is  set  to  0, no error messages will be dis‐
              played, even if the first character of optstring is not a colon.

              If an invalid option is seen, getopts places ? into name and, if
              not  silent,  prints  an  error  message  and unsets OPTARG.  If
              getopts is silent, the  option  character  found  is  placed  in
              OPTARG and no diagnostic message is printed.

              If  a required argument is not found, and getopts is not silent,
              a question mark (?) is placed in name, OPTARG is  unset,  and  a
              diagnostic  message  is  printed.   If getopts is silent, then a
              colon (:) is placed in name and OPTARG  is  set  to  the  option
              character found.

              getopts  returns true if an option, specified or unspecified, is
              found.  It returns false if the end of options is encountered or
              an error occurs.

## hash
見 [hash](http://lirobo.blogspot.com/2017/11/bash-hash.html)

## help [-dms] [pattern]
              Display  helpful information about builtin commands.  If pattern
              is specified, help gives detailed help on all commands  matching
              pattern;  otherwise  help for all the builtins and shell control
              structures is printed.
              -d     Display a short description of each pattern
              -m     Display the description of each pattern in a manpage-like
                     format
              -s     Display only a short usage synopsis for each pattern

              The return status is 0 unless no command matches pattern.

## history [n]
## history -c
## history -d offset
## history -anrw [filename]
## history -p arg [arg ...]
## history -s arg [arg ...]
              With no options, display the command history list with line num‐
              bers.  Lines listed with a * have been modified.  An argument of
              n  lists only the last n lines.  If the shell variable HISTTIME‐
              FORMAT is set and not null, it is used as a  format  string  for
              strftime(3)  to display the time stamp associated with each dis‐
              played history entry.  No intervening blank is  printed  between
              the  formatted  time stamp and the history line.  If filename is
              supplied, it is used as the name of the history  file;  if  not,
              the  value  of HISTFILE is used.  Options, if supplied, have the
              following meanings:
              -c     Clear the history list by deleting all the entries.
              -d offset
                     Delete the history entry at position offset.
              -a     Append the ``new'' history lines (history  lines  entered
                     since  the  beginning of the current bash session) to the
                     history file.
              -n     Read the history lines not already read from the  history
                     file  into  the  current  history  list.  These are lines
                     appended to the history file since the beginning  of  the
                     current bash session.
              -r     Read  the contents of the history file and append them to
                     the current history list.
              -w     Write the current history list to the history file, over‐
                     writing the history file's contents.
              -p     Perform  history  substitution  on the following args and
                     display the result on  the  standard  output.   Does  not
                     store  the results in the history list.  Each arg must be
                     quoted to disable normal history expansion.
              -s     Store the args in the history list  as  a  single  entry.
                     The  last  command  in the history list is removed before
                     the args are added.

              If the HISTTIMEFORMAT variable is set, the time  stamp  informa‐
              tion  associated  with each history entry is written to the his‐
              tory file, marked with the history comment character.  When  the
              history  file  is read, lines beginning with the history comment
              character followed immediately by a  digit  are  interpreted  as
              timestamps for the previous history line.  The return value is 0
              unless an invalid option is encountered, an error  occurs  while
              reading  or  writing the history file, an invalid offset is sup‐
              plied as an argument to -d, or the history expansion supplied as
              an argument to -p fails.

## jobs [-lnprs] [ jobspec ... ]
## jobs -x command [ args ... ]
              The first form lists the active jobs.  The options have the fol‐
              lowing meanings:
              -l     List process IDs in addition to the normal information.
              -n     Display information only about  jobs  that  have  changed
                     status since the user was last notified of their status.
              -p     List  only  the  process  ID  of  the job's process group
                     leader.
              -r     Display only running jobs.
              -s     Display only stopped jobs.

              If jobspec is given, output is restricted to  information  about
              that  job.   The  return status is 0 unless an invalid option is
              encountered or an invalid jobspec is supplied.

              If the -x option is supplied, jobs replaces any jobspec found in
              command  or  args  with  the corresponding process group ID, and
              executes command passing it args, returning its exit status.

## kill [-s sigspec | -n signum | -sigspec] [pid | jobspec] ...
## kill -l [sigspec | exit_status]
              Send the signal named by sigspec  or  signum  to  the  processes
              named  by  pid or jobspec.  sigspec is either a case-insensitive
              signal name such as SIGKILL (with or without the SIG prefix)  or
              a  signal  number; signum is a signal number.  If sigspec is not
              present, then SIGTERM is assumed.  An argument of -l  lists  the
              signal  names.   If any arguments are supplied when -l is given,
              the names of the signals  corresponding  to  the  arguments  are
              listed, and the return status is 0.  The exit_status argument to
              -l is a number specifying either a signal  number  or  the  exit
              status  of  a process terminated by a signal.  kill returns true
              if at least one signal was successfully sent,  or  false  if  an
              error occurs or an invalid option is encountered.

## let arg [arg ...]
              每個 arg 是要 evaluated 的 arithmetic expression (見 ARITHMETIC EVALUATION)。如果最後 arg evaluates 為 0，回傳 1，否則回傳 1。

## local [option] [name[=value] ...]
              For  each  argument, a local variable named name is created, and
              assigned value.  The option can be any of the  options  accepted
              by declare.  When local is used within a function, it causes the
              variable name to have a visible scope restricted to  that  func‐
              tion and its children.  With no operands, local writes a list of
              local variables to the standard output.  It is an error  to  use
              local when not within a function.  The return status is 0 unless
              local is used outside a function, an invalid name  is  supplied,
              or name is a readonly variable.

## logout
Exit a login shell.

## mapfile  [-n  count]  [-O origin] [-s count] [-t] [-u fd] [-C callback] [-c quantum] [array]
## readarray [-n count] [-O origin] [-s count] [-t] [-u fd] [-C  callback] [-c quantum] [array]
              Read  lines from the standard input into the indexed array vari‐
              able array, or from file descriptor fd if the -u option is  sup‐
              plied.   The variable MAPFILE is the default array.  Options, if
              supplied, have the following meanings:
              -n     Copy at most count lines.  If count is 0, all  lines  are
                     copied.
              -O     Begin  assigning  to  array at index origin.  The default
                     index is 0.
              -s     Discard the first count lines read.
              -t     Remove a trailing newline from each line read.
              -u     Read lines from file descriptor fd instead of  the  stan‐
                     dard input.
              -C     Evaluate  callback each time quantum lines are read.  The
                     -c option specifies quantum.
              -c     Specify the number of lines read  between  each  call  to
                     callback.

              If  -C  is  specified  without  -c, the default quantum is 5000.
              When callback is evaluated, it is supplied the index of the next
              array element to be assigned and the line to be assigned to that
              element as additional arguments.  callback  is  evaluated  after
              the line is read but before the array element is assigned.

              If  not  supplied  with  an  explicit origin, mapfile will clear
              array before assigning to it.

              mapfile returns successfully unless an invalid option or  option
              argument  is  supplied,  array is invalid or unassignable, or if
              array is not an indexed array.

## popd [-n] [+n] [-n]
              Removes entries from the directory stack.   With  no  arguments,
              removes  the  top directory from the stack, and performs a cd to
              the new top directory.  Arguments, if supplied, have the follow‐
              ing meanings:
              -n     Suppresses  the  normal change of directory when removing
                     directories from the stack, so that  only  the  stack  is
                     manipulated.
              +n     Removes  the nth entry counting from the left of the list
                     shown by dirs, starting with zero.  For  example:  ``popd
                     +0'' removes the first directory, ``popd +1'' the second.
              -n     Removes the nth entry counting from the right of the list
                     shown by dirs, starting with zero.  For  example:  ``popd
                     -0''  removes the last directory, ``popd -1'' the next to
                     last.

              If the popd command is successful, a dirs is performed as  well,
              and  the  return  status is 0.  popd returns false if an invalid
              option is encountered, the directory stack is empty, a non-exis‐
              tent directory stack entry is specified, or the directory change
              fails.

## printf [-v var] format [arguments]
              Write the formatted arguments to the standard output  under  the
              control  of  the  format.  The -v option causes the output to be
              assigned to the variable var rather than being  printed  to  the
              standard output.

              The  format  is a character string which contains three types of
              objects: plain characters, which are simply copied  to  standard
              output,  character  escape  sequences,  which  are converted and
              copied to the standard output, and format  specifications,  each
              of  which  causes  printing of the next successive argument.  In
              addition to the standard printf(1) format specifications, printf
              interprets the following extensions:
              %b     causes printf to expand backslash escape sequences in the
                     corresponding argument (except that \c terminates output,
                     backslashes  in \', \", and \? are not removed, and octal
                     escapes beginning with \0 may contain up to four digits).
              %q     causes printf to output the corresponding argument  in  a
                     format that can be reused as shell input.
              %(datefmt)T
                     causes  printf  to  output the date-time string resulting
                     from using datefmt as a format  string  for  strftime(3).
                     The corresponding argument is an integer representing the
                     number of seconds since the epoch.  Two special  argument
                     values  may  be used: -1 represents the current time, and
                     -2 represents the time the  shell  was  invoked.   If  no
                     argument  is  specified,  conversion behaves as if -1 had
                     been given.  This is an exception  to  the  usual  printf
                     behavior.

              Arguments  to non-string format specifiers are treated as C con‐
              stants, except that a leading plus or minus sign is allowed, and
              if  the leading character is a single or double quote, the value
              is the ASCII value of the following character.

              The format is reused as necessary to consume all  of  the  argu‐
              ments.  If the format requires more arguments than are supplied,
              the extra format specifications behave as if  a  zero  value  or
              null  string,  as  appropriate,  had  been supplied.  The return
              value is zero on success, non-zero on failure.

## pushd [-n] [+n] [-n]
## pushd [-n] [dir]
              Adds a directory to the top of the directory stack,  or  rotates
              the  stack,  making the new top of the stack the current working
              directory.  With no arguments, exchanges the top two directories
              and  returns 0, unless the directory stack is empty.  Arguments,
              if supplied, have the following meanings:
              -n     Suppresses the normal change  of  directory  when  adding
                     directories  to  the  stack,  so  that  only the stack is
                     manipulated.
              +n     Rotates the stack so that  the  nth  directory  (counting
                     from  the  left  of the list shown by dirs, starting with
                     zero) is at the top.
              -n     Rotates the stack so that  the  nth  directory  (counting
                     from  the  right of the list shown by dirs, starting with
                     zero) is at the top.
              dir    Adds dir to the directory stack at the top, making it the
                     new  current working directory as if it had been supplied
                     as the argument to the cd builtin.

              If the pushd command is successful, a dirs is performed as well.
              If  the first form is used, pushd returns 0 unless the cd to dir
              fails.  With the second form, pushd returns 0 unless the  direc‐
              tory  stack  is empty, a non-existent directory stack element is
              specified, or the directory change to the specified new  current
              directory fails.

## pwd [-LP]
              Print  the  absolute  pathname of the current working directory.
              The pathname printed contains no symbolic links if the -P option
              is supplied or the -o physical option to the set builtin command
              is enabled.  If the -L option is used, the pathname printed  may
              contain  symbolic links.  The return status is 0 unless an error
              occurs while reading the name of the  current  directory  or  an
              invalid option is supplied.

## read [-ers] [-a aname] [-d delim] [-i text] [-n nchars] [-N nchars] [-p prompt] [-t timeout] [-u fd] [name ...]
              One line is read from the  standard  input,  or  from  the  file
              descriptor  fd supplied as an argument to the -u option, and the
              first word is assigned to the first name, the second word to the
              second  name, and so on, with leftover words and their interven‐
              ing separators assigned to the last name.  If  there  are  fewer
              words read from the input stream than names, the remaining names
              are assigned empty values.  The characters in IFS  are  used  to
              split  the  line  into words using the same rules the shell uses
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
                     The first character of delim is  used  to  terminate  the
                     input line, rather than newline.
              -e     如果標準輸入來自終端機，[readline](bash-readline.md) 用來
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

## readonly [-aAf] [-p] [name[=word] ...]
              The given names are marked readonly; the values of  these  names
              may  not  be changed by subsequent assignment.  If the -f option
              is supplied, the functions corresponding to  the  names  are  so
              marked.   The  -a  option  restricts  the  variables  to indexed
              arrays; the -A option restricts  the  variables  to  associative
              arrays.   If both options are supplied, -A takes precedence.  If
              no name arguments are given, or if the -p option is supplied,  a
              list of all readonly names is printed.  The other options may be
              used to restrict the output to a subset of the set  of  readonly
              names.   The -p option causes output to be displayed in a format
              that may be reused as input.  If a variable name is followed  by
              =word,  the  value  of  the variable is set to word.  The return
              status is 0 unless an invalid option is encountered, one of  the
              names is not a valid shell variable name, or -f is supplied with
              a name that is not a function.

## return [n]
              Causes a function to stop executing and return the value  speci‐
              fied  by n to its caller.  If n is omitted, the return status is
              that of the last command executed  in  the  function  body.   If
              return  is  used  outside  a function, but during execution of a
              script by the .  (source) command, it causes the shell  to  stop
              executing  that script and return either n or the exit status of
              the last command executed within the script as the  exit  status
              of  the script.  If n is supplied, the return value is its least
              significant 8 bits.  The return status is non-zero if return  is
              supplied  a  non-numeric argument, or is used outside a function
              and not during execution of a script by . or source.   Any  com‐
              mand  associated  with the RETURN trap is executed before execu‐
              tion resumes after the function or script.

## [set](builtin-set.md)

## shift [n]
所有位置參數往前位移 n 個位置，沒給 n 值時當作 1。n 超出範圍不動作，回傳大於 0 的值；正常回傳 0。

## [shopt](builtin-shopt.md)

## suspend [-f]
              Suspend the execution of this shell until it receives a  SIGCONT
              signal.  A login shell cannot be suspended; the -f option can be
              used to override this and force the suspension.  The return sta‐
              tus  is  0  unless the shell is a login shell and -f is not sup‐
              plied, or if job control is not enabled.

## test expr
## [ expr ]
              Return a status of 0 (true) or 1 (false) depending on the evalu‐
              ation of the conditional expression expr.  Each operator and op‐
              erand must be a separate argument.  Expressions are composed  of
              the  primaries  described  above  under CONDITIONAL EXPRESSIONS.
              test does not accept any options, nor does it accept and  ignore
              an argument of -- as signifying the end of options.

              Expressions  may  be  combined  using  the  following operators,
              listed  in  decreasing  order  of  precedence.   The  evaluation
              depends  on the number of arguments; see below.  Operator prece‐
              dence is used when there are five or more arguments.
              ! expr True if expr is false.
              ( expr )
                     Returns the value of expr.  This may be used to  override
                     the normal precedence of operators.
              expr1 -a expr2
                     True if both expr1 and expr2 are true.
              expr1 -o expr2
                     True if either expr1 or expr2 is true.

              test and [ evaluate conditional expressions using a set of rules
              based on the number of arguments.

              0 arguments
                     The expression is false.
              1 argument
                     The expression is true if and only if the argument is not
                     null.
              2 arguments
                     If the first argument is !, the expression is true if and
                     only if the second argument is null.  If the first  argu‐
                     ment  is  one  of  the unary conditional operators listed
                     above under CONDITIONAL EXPRESSIONS,  the  expression  is
                     true if the unary test is true.  If the first argument is
                     not a valid unary conditional operator, the expression is
                     false.
              3 arguments
                     The following conditions are applied in the order listed.
                     If the second argument is one of the  binary  conditional
                     operators listed above under CONDITIONAL EXPRESSIONS, the
                     result of the expression is the result of the binary test
                     using  the first and third arguments as operands.  The -a
                     and -o operators are  considered  binary  operators  when
                     there  are  three arguments.  If the first argument is !,
                     the value is the negation of the two-argument test  using
                     the second and third arguments.  If the first argument is
                     exactly ( and the third argument is exactly ), the result
                     is  the one-argument test of the second argument.  Other‐
                     wise, the expression is false.
              4 arguments
                     If the first argument is !, the result is the negation of
                     the  three-argument  expression composed of the remaining
                     arguments.  Otherwise, the expression is parsed and eval‐
                     uated  according  to  precedence  using  the rules listed
                     above.
              5 or more arguments
                     The expression  is  parsed  and  evaluated  according  to
                     precedence using the rules listed above.

              When  used  with  test  or [, the < and > operators sort lexico‐
              graphically using ASCII ordering.

## times
印出累積的 user 及 system times for  the  shell  and
              for processes run from the shell.  The return status is 0.

## trap [-lp] [[arg] sigspec ...]
              The  command  arg  is  to  be  read  and executed when the shell
              receives signal(s) sigspec.  If arg is absent (and  there  is  a
              single  sigspec)  or  -,  each  specified signal is reset to its
              original disposition (the value it  had  upon  entrance  to  the
              shell).   If arg is the null string the signal specified by each
              sigspec is ignored by the shell and by the commands it  invokes.
              If  arg  is  not present and -p has been supplied, then the trap
              commands associated with each  sigspec  are  displayed.   If  no
              arguments  are  supplied or if only -p is given, trap prints the
              list of commands associated with each  signal.   The  -l  option
              causes  the shell to print a list of signal names and their cor‐
              responding numbers.   Each  sigspec  is  either  a  signal  name
              defined  in  <signal.h>,  or  a signal number.  Signal names are
              case insensitive and the SIG prefix is optional.

              If a sigspec is EXIT (0) the command arg  is  executed  on  exit
              from  the shell.  If a sigspec is DEBUG, the command arg is exe‐
              cuted before every simple command, for  command,  case  command,
              select  command,  every  arithmetic  for command, and before the
              first command executes in a shell function  (see  SHELL  GRAMMAR
              above).   Refer to the description of the extdebug option to the
              shopt builtin for details of its effect on the DEBUG trap.  If a
              sigspec is RETURN, the command arg is executed each time a shell
              function or a script executed with the . or source builtins fin‐
              ishes executing.

              If  a  sigspec  is ERR, the command arg is executed whenever a a
              pipeline (which may consist of a single simple command), a list,
              or a compound command returns a non-zero exit status, subject to
              the following conditions.  The ERR trap is not executed  if  the
              failed command is part of the command list immediately following
              a while or until keyword, part of the test in an  if  statement,
              part of a command executed in a && or || list except the command
              following the final && or ||, any command in a pipeline but  the
              last,  or  if the command's return value is being inverted using
              !.  These are the same conditions obeyed  by  the  errexit  (-e)
              option.

              Signals  ignored  upon  entry  to the shell cannot be trapped or
              reset.  Trapped signals that are not being ignored are reset  to
              their original values in a subshell or subshell environment when
              one is created.  The return status is false if  any  sigspec  is
              invalid; otherwise trap returns true.

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

## ulimit [-HSTabcdefilmnpqrstuvx [limit]]
控制 shell 及衍生的 process 可用的資源。參數沒指定資源時，預設是 -f，指檔案最大可寫入的大小。預設亦同時設定 hard limit 及 soft limit，用 -H 及 -S 選項分別可指定只設定 hard limt 或 soft limit。soft limit 可設定增加到 hard limit。hard limit 設定之後 root 才能增加。

limit 可以是一個數字 (依據特定資源的單位)，或是 hard、soft、或 unlimited 之一，分別表示採用目前的 hard limit、目前的 soft limit、及不限制。值大多以 1024-byte 為單位，除了 -p、-t、-T、-b、-n、及-u。

如果省略 limit，預設印出目前的 soft limit，除非加 -H 選項。如果一次要印出多個資源，資源名稱及單位會印在值之前。

其它選項說明如下：
* -a：印出所有資源限制
* -b：最大 socket buffer 大小
* -c：最大  size of core files created
* -d：process 的 data segment 最大大小。
* -e：最大 scheduling priority ("nice")
* -f：shell 或衍生 process 檔案最大可寫入的大小
* -i：最多 pending signals 的數目
* -l：最大 size that may be locked into memory
* -m：最大 resident set size (many systems do not honor this limit)
* -n：最多可開啟的 file descriptors (大部分系統不允許設定)
* -p： The pipe size in 512-byte blocks (this may not be set)
* -q：最大 number of bytes in POSIX message queues
* -r：最大 real-time scheduling priority
* -s：最大 stack 大小。
* -t：最大 amount of cpu time in seconds
* -u：最大 number of processes available to a single user
* -v：最大 amount of virtual memory available to the shell and, on some systems, to its children
* -x：最多可鎖定的檔案數目
* -T：最大 thread 數目

## umask [-p] [-S] [mode]
              The user file-creation mask is set to mode.  If mode begins with
              a  digit,  it is interpreted as an octal number; otherwise it is
              interpreted as a symbolic mode mask similar to that accepted  by
              chmod(1).   If mode is omitted, the current value of the mask is
              printed.  The -S option causes the mask to be  printed  in  sym‐
              bolic  form;  the  default output is an octal number.  If the -p
              option is supplied, and mode is omitted, the output is in a form
              that may be reused as input.  The return status is 0 if the mode
              was successfully changed or if no mode  argument  was  supplied,
              and false otherwise.

## unalias [-a] [name ...]
              Remove  each  name  from  the list of defined aliases.  If -a is
              supplied, all alias definitions are removed.  The  return  value
              is true unless a supplied name is not a defined alias.

## unset [-fv] [-n] [name ...]
              For  each  name,  remove the corresponding variable or function.
              If the -v option is given, each name refers to a shell variable,
              and  that  variable  is removed.  Read-only variables may not be
              unset.  If -f is specified, each name refers to  a  shell  func‐
              tion,  and the function definition is removed.  If the -n option
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

## wait [-n] [n ...]
              Wait for each specified child process and return its termination
              status.  Each n may be a process ID or a job specification; if a
              job spec is given, all processes  in  that  job's  pipeline  are
              waited  for.  If n is not given, all currently active child pro‐
              cesses are waited for, and the return status is zero.  If the -n
              option  is  supplied,  wait  waits  for any job to terminate and
              returns its exit status.  If n specifies a non-existent  process
              or  job, the return status is 127.  Otherwise, the return status
              is the exit status of the last process or job waited for.
