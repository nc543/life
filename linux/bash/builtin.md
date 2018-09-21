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


## [shopt](builtin-shopt.md)

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
