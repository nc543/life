# REDIRECTION
重新導向指令的輸入或輸出。
Redirection 允許指令的 file handles to be duplicated, opened, closed, made to  refer
       to different files, and can change the files the command reads from and
       writes to.  Redirection may also be used to modify file handles in  the
       current  shell execution environment.  The following redirection opera‐
       tors may precede or appear anywhere within a simple command or may fol‐
       low  a  command.   Redirections are processed in the order they appear,
       from left to right.

fd (file descriptor) 檔案描述子

可前置 file descriptor number 的轉向，可以改前置
       a word of the form {varname}.  In this case, for
       each redirection operator except >&- and <&-, the shell will allocate a
       file  descriptor  greater than or equal to 10 and assign it to varname.
       If >&- or <&- is preceded by {varname}, the value  of  varname  defines
       the file descriptor to close.

省略 file descriptor number
* `<` refers to 標準輸入 (file descriptor 0)
* `>` refers to 標準輸出 (file descriptor 1)

接下來的字，除非特別 noted, is subjected to brace  expansion,  tilde
       expansion,  parameter  and  variable  expansion,  command substitution,
       arithmetic expansion,  quote  removal,  pathname  expansion,  and  word
       splitting.  如果擴展成多於一個字是錯誤的。

轉向的順序是 significant，例如
```
ls > dirlist 2>&1
```
同時將標準輸出及標準錯誤轉向檔案 dirlist，然而
```
ls 2>&1 > dirlist
```
只轉向標準輸出到檔案 dirlist，因為標準錯誤
       was duplicated from the standard output before the standard  out‐
       put was redirected to dirlist.

       在這裡，Bash 處理幾個特殊檔名：

              /dev/fd/fd
                     If fd is a valid integer, file descriptor  fd  is  dupli‐
                     cated.
              /dev/stdin
                     File descriptor 0 is duplicated.
              /dev/stdout
                     File descriptor 1 is duplicated.
              /dev/stderr
                     File descriptor 2 is duplicated.
              /dev/tcp/host/port 或 /dev/udp/host/port
                     嘗試開啟對應的 TCP 或 UDP socket。host 需要是有效的 hostname 或 Internet address，且 port 需要是一個整數的 port number 或 service 名稱。
                     If host is a valid hostname or Internet address, and port
                     is an integer port number or service name, bash  attempts
                     to open the corresponding UDP socket.
                     [Bash shell 連接 Socket 寫法](https://blog.longwin.com.tw/2012/09/bash-shell-socket-connect-2012/)

使用大於 9 的 file descriptors 轉向要小心，可能跟 shell 內部使用的衝突。

       Note that the exec builtin command can make redirections take effect in
       the current shell.

## Redirecting Input
輸入導向
```
[n]<word
```
如果 n 未指定，表示標準輸入 (fd 0)。word 擴展後成為檔名，開啟作為 fd n 讀取用。

## Redirecting Output
輸出導向
```
[n]>word
```
如果 n 未指定，表示標準輸出 (fd 1)。word 擴展後成為檔名，開啟作為 fd n 寫入用。
如果檔案不存在則建立，存在則清空。

       If the redirection operator is >, and 啟用內建指令 set 的選項 noclobber
       , the redirection will fail 如果檔案存在為 regular  file.
       If the redirection operator is >|, or the redirection operator is > and
       the noclobber option to the set builtin command is not enabled, the re‐
       direction is attempted even if the file named by word exists.

系統內部動作是關閉原本 fd 對應的檔案，再開啟或 dup 要導向的檔案成為 fd 對應的檔案。

## Appending Redirected Output
       Redirection  of  output  in  this  fashion  causes  the file whose name
       results from the expansion of word to be opened for appending  on  file
       descriptor  n,  or  the standard output (file descriptor 1) if n is not
       specified.  If the file does not exist it is created.

       The general format for appending output is:

              [n]>>word

## Redirecting Standard Output and Standard Error
       This construct allows both the standard output (file descriptor 1)  and
       the  standard  error output (file descriptor 2) to be redirected to the
       file whose name is the expansion of word.

       There are two formats for  redirecting  standard  output  and  standard
       error:

              &>word
       and
              >&word

       Of the two forms, the first is preferred.  This is semantically equiva‐
       lent to

              >word 2>&1

       When using the second form, word may not expand to a number or  -.   If
       it  does,  other  redirection  operators  apply  (see  Duplicating File
       Descriptors below) for compatibility reasons.

## Appending Standard Output and Standard Error
       This construct allows both the standard output (file descriptor 1)  and
       the  standard  error  output  (file descriptor 2) to be appended to the
       file whose name is the expansion of word.

       The format for appending standard output and standard error is:

              &>>word

       This is semantically equivalent to

              >>word 2>&1

       (see Duplicating File Descriptors below).

## Here Documents
       This type of redirection instructs the shell to  read  input  from  the
       current source until a line containing only delimiter (with no trailing
       blanks) is seen.  All of the lines read up to that point are then  used
       as the standard input for a command.

       The format of here-documents is:

              <<[-]word
                      here-document
              delimiter

       No  parameter  and variable expansion, command substitution, arithmetic
       expansion, or pathname expansion is performed on word.  If any  charac‐
       ters  in  word are quoted, the delimiter is the result of quote removal
       on word, and the lines in the here-document are not expanded.  If  word
       is  unquoted, all lines of the here-document are subjected to parameter
       expansion, command substitution, and arithmetic expansion, the  charac‐
       ter  sequence  \<newline>  is  ignored, and \ must be used to quote the
       characters \, $, and `.

       If the redirection operator is <<-, then all leading tab characters are
       stripped  from  input  lines  and  the line containing delimiter.  This
       allows here-documents within shell scripts to be indented in a  natural
       fashion.

## Here Strings
       A variant of here documents, the format is:

              <<<word

       The  word  undergoes  brace  expansion,  tilde expansion, parameter and
       variable expansion, command  substitution,  arithmetic  expansion,  and
       quote  removal.   Pathname  expansion  and  word splitting are not per‐
       formed.  The result is supplied as a single string to  the  command  on
       its standard input.

## Duplicating File Descriptors
       The redirection operator

              [n]<&word

       is used to duplicate input file descriptors.  If word expands to one or
       more digits, the file descriptor denoted by n is made to be a  copy  of
       that  file  descriptor.   If  the  digits in word do not specify a file
       descriptor open for input, a redirection error occurs.  If word  evalu‐
       ates  to  -,  file  descriptor n is closed.  If n is not specified, the
       standard input (file descriptor 0) is used.

       The operator

              [n]>&word

       is used similarly to duplicate output file descriptors.  If  n  is  not
       specified,  the  standard  output  (file descriptor 1) is used.  If the
       digits in word do not specify a file descriptor open for output, a  re‐
       direction  error  occurs.  If word evaluates to -, file descriptor n is
       closed.  As a special case, if n is omitted, and word does  not  expand
       to  one or more digits or -, the standard output and standard error are
       redirected as described previously.

## Moving File Descriptors
       The redirection operator

              [n]<&digit-

       moves the file descriptor digit to file descriptor n, or  the  standard
       input (file descriptor 0) if n is not specified.  digit is closed after
       being duplicated to n.

       Similarly, the redirection operator

              [n]>&digit-

       moves the file descriptor digit to file descriptor n, or  the  standard
       output (file descriptor 1) if n is not specified.

## Opening File Descriptors for Reading and Writing
       The redirection operator

              [n]<>word

       causes  the  file  whose name is the expansion of word to be opened for
       both reading and writing on file descriptor n, or on file descriptor  0
       if n is not specified.  If the file does not exist, it is created.

## 延伸閱讀
* 系統呼叫 dup()、dup2()、dup3()。
* [Linux 對 標準輸入的文字做 Diff](https://blog.longwin.com.tw/2017/01/linux-diff-url-standard-input-2017)
* [忽略 stdout 及 stderr 輸出](http://lirobo.blogspot.tw/2013/02/stdout-stderr.html)
