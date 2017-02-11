# bash 內建指令 set 及選項
切換選項、設位置參數、列變數
```
set [--abefhkmnptuvxBCEHPT] [-o option-name] [arg ...]
set [+abefhkmnptuvxBCEHPT] [+o option-name] [arg ...]
```
沒有選項的話，顯示 shell 變數的名稱及值 in a format that can be reused as input for setting or resetting the currently-set variables. 唯讀的變數不能重置。在 posix 模式，只列出 shell 變數。輸出會依據 locale 排序。當有指定選項時，set 或 unset shell 屬性。選項之後如有任何引數視為 positional parameters，會依序指定為 $1、$2、...、$n 的值。

除非特別說明，選項預設是關閉的。使用 + 關閉選項，- 開啟選項。

The options  can  also be specified as arguments to an invocation of
the shell.  The current set of options may be found in $-.   The
return status is always true unless an invalid option is encountered.

Options, if specified, have the following meanings:

## -a
Automatically mark variables and functions which are modified or created for export to the environment of subsequent commands.

## -b
Report the status of terminated background jobs immediately, rather than before the next primary prompt. This is effective only when job control is enabled.

## -e
Exit  immediately  if a pipeline (which may consist of a
single simple command), a list, or  a  compound  command
(see  SHELL  GRAMMAR above),  exits with a non-zero sta‐
tus.  The shell does not exit if the command that  fails
is  part  of  the  command  list immediately following a
while or until keyword, part of the test  following  the
if  or elif reserved words, part of any command executed
in a && or || list  except  the  command  following  the
final  && or ||, any command in a pipeline but the last,
or if the command's return value is being inverted  with
!.   If a compound command other than a subshell returns
a non-zero status because a command failed while -e  was
being  ignored, the shell does not exit.  A trap on ERR,
if set, is executed before the shell exits.  This option
applies to the shell environment and each subshell envi‐
ronment separately (see  COMMAND  EXECUTION  ENVIRONMENT
above), and may cause subshells to exit before executing
all the commands in the subshell.

If a compound command or shell function  executes  in  a
context  where -e is being ignored, none of the commands
executed within the compound command  or  function  body
will  be  affected  by the -e setting, even if -e is set
and a command returns a failure status.  If  a  compound
command  or  shell function sets -e while executing in a
context where -e is ignored, that setting will not  have
any  effect  until  the  compound command or the command
containing the function call completes.

## -f
停用 pathname expansion.

## -h
記憶執行時 looked up 的指令路徑，預設是開啟的。

## -k
All  arguments  in the form of assignment statements are
                      placed in the environment for a command, not just  those
                      that precede the command name.

## -m
Monitor  mode.   Job control is enabled.  This option is
                      on by default for interactive  shells  on  systems  that
                      support  it  (see JOB CONTROL above).  All processes run
                      in a separate process group.  When a background job com‐
                      pletes, the shell prints a line containing its exit sta‐
                      tus.

## -n      Read commands but do not execute them.  This may be used
                      to  check  a  shell  script  for syntax errors.  This is
                      ignored by interactive shells.

## -o
-o：列出目前選項設定<br>
+o：顯示一系列 set 指令，可用來重新建立目前選項設定<br>
-o option-name：The option-name can be one of the following:
* allexport：跟 -a 一樣
* braceexpand：跟 -B 一樣。
* emacs：Use an emacs-style command line editing interface. This is enabled by default when the shell is interactive, unless the shell is started with the --noediting option. This also affects the editing interface used for read -e.
* errexit：跟 -e 一樣。
* errtrace：跟 -E 一樣。
* functrace：跟 -T 一樣。
* hashall：跟 -h 一樣。
* histexpand：跟 -H 一樣。
* history：Enable command history, as described above under HISTORY. This option is on by default in interactive shells.
* ignoreeof：The effect is as if the shell command ``IGNOREEOF=10'' had been executed (see Shell Variables above).
* keyword：跟 -k 一樣。
* monitor：跟 -m 一樣。
* noclobber：跟 -C 一樣。
* noexec：跟 -n 一樣。
* noglob：跟 -f 一樣。
* nolog：目前忽略
* notify：跟 -b 一樣。
* nounset：跟 -u 一樣。
* onecmd：跟 -t 一樣。
* physical：跟 -P 一樣。
* pipefail：If set, 回傳值 of a pipeline is the value of the last (rightmost) command to exit with a non-zero status, or zero if all commands in the pipeline exit successfully.
* posix：Change the behavior of bash where the default operation differs from the POSIX standard to match the standard (posix mode). See SEE ALSO below for a reference to a document that details how posix mode affects bash's behavior.
* privileged：跟 -p 一樣。
* verbose：跟 -v 一樣。
* vi：使用 vi-style command line editing interface. This also affects the editing interface used for read -e.
* xtrace：跟 -x 一樣。

## -p
開啟特權 (privileged) 模式，此時 $ENV 及 $BASH_ENV files 不處理，不繼承 shell 函數，忽略變數 SHELLOPTS、BASHOPTS、CDPATH、及 GLOBIGNORE。

如果 shell 開始時 effective user (group) id 跟 real user (group) id 不同，也進行這些動作。此時如果 -p 沒設，effective user id (group) 會設為 real user (group) id；如果有設，則不動 effective user (group) id。

## -t
Exit after reading and executing one command.

## -u
Treat unset variables and parameters other than the spe‐
                      cial parameters "@" and "*" as an error when  performing
                      parameter  expansion.   If  expansion is attempted on an
                      unset variable or parameter, the shell prints  an  error
                      message,  and, if not interactive, exits with a non-zero
                      status.

## -v
印出讀到的輸入行。

## -x
After expanding each simple command, for  command,  case
                      command, select command, or arithmetic for command, dis‐
                      play the expanded value of PS4, followed by the  command
                      and its expanded arguments or associated word list.

## -B
The  shell performs brace expansion (see Brace Expansion
                      above).  This is on by default.

## -C
>,  >&,  and <> [redirection operators](bash-redirection.md) 不覆寫存在的檔案。

對 >| 則不影響。

## -E
If set, any trap on ERR is inherited by shell functions,
                      command substitutions, and commands executed in  a  sub‐
                      shell  environment.  The ERR trap is normally not inher‐
                      ited in such cases.

## -H
Enable !  style history substitution.  This option is on
                      by default when the shell is interactive.

## -P
If  set,  the shell does not resolve symbolic links when
                      executing commands such as cd that  change  the  current
                      working  directory.   It  uses  the  physical  directory
                      structure instead.  By default, bash follows the logical
                      chain  of  directories  when  performing  commands which
                      change the current directory.

## -T
If set, any traps on DEBUG and RETURN are  inherited  by
                      shell  functions,  command  substitutions,  and commands
                      executed in  a  subshell  environment.   The  DEBUG  and
                      RETURN traps are normally not inherited in such cases.

##
              --      If  no arguments follow this option, then the positional
                      parameters are unset.  Otherwise, the positional parame‐
                      ters  are  set  to  the args, even if some of them begin
                      with a -.
* --：接下來的參數不是選項，即使以「-」開頭。

## -
Signal the end of options, cause all remaining  args  to
                      be assigned to the positional parameters.  The -x and -v
                      options are turned off.  If there are no args, the posi‐
                      tional parameters remain unchanged.
