# shopt
shopt [-pqsu] [-o] [optname ...]

Toggle the values of settings controlling optional shell  behavior.   The settings can be either those listed below, or, if the
              -o option is used, those available to 內建指令 [set](builtin-set.md) 的 -o option
              .  With no options, or with the -p option, a list
              of all settable options is  displayed,  with  an  indication  of
              whether  or  not each is set.  The -p option causes output to be
              displayed in a form that may be reused as input.  Other  options
              have the following meanings:
              -s     Enable (set) each optname.
              -u     Disable (unset) each optname.
              -q     Suppresses  normal output (quiet mode); the return status
                     indicates whether the optname is set or unset.  If multi‐
                     ple  optname arguments are given with -q, the return sta‐
                     tus is zero if all optnames are enabled; non-zero  other‐
                     wise.
              -o     Restricts  the  values of optname to be those defined for
                     the -o option to the set builtin.

              If either -s or -u is used  with  no  optname  arguments,  shopt
              shows  only  those options which are set or unset, respectively.
              Unless otherwise noted, the shopt options are  disabled  (unset)
              by default.

              The  return  status when listing options is zero if all optnames
              are enabled, non-zero  otherwise.   When  setting  or  unsetting
              options,  the  return  status is zero unless an optname is not a
              valid shell option.

shopt 選項列表如下：

## autocd
If set, a command name that is the name of  a  directory
                      is  executed  as  if it were the argument to the cd com‐
                      mand.  This option is only used by interactive shells.
## cdable_vars
                      If set, an argument to the cd builtin  command  that  is
                      not  a directory is assumed to be the name of a variable
                      whose value is the directory to change to.
## cdspell
If set, minor errors in the spelling of a directory com‐
                      ponent  in  a  cd command will be corrected.  The errors
                      checked for are transposed characters, a missing charac‐
                      ter,  and  one  character  too many.  If a correction is
                      found, the corrected filename is printed, and  the  com‐
                      mand  proceeds.  This option is only used by interactive
                      shells.
## checkhash
If set, bash checks that a command found in the hash table  exists  before  trying  to execute it.  If a hashed
                      command no longer exists, a normal path search  is  per‐
                      formed. 見 [hash](http://lirobo.blogspot.com/2017/11/bash-hash.html)
## checkjobs
                      If set, bash lists the status of any stopped and running
                      jobs before exiting an interactive shell.  If  any  jobs
                      are running, this causes the exit to be deferred until a
                      second exit is attempted without an intervening  command
                      (see  JOB  CONTROL  above).   The shell always postpones
                      exiting if any jobs are stopped.
## checkwinsize
                      If set, bash checks the window size after  each  command
                      and,  if necessary, updates the values of LINES and COL‐
                      UMNS.
## cmdhist
If set, bash attempts to save all lines of  a  multiple-
                      line  command  in  the  same history entry.  This allows
                      easy re-editing of multi-line commands.
## compat31
                      If set, bash changes its behavior to that of version 3.1
                      with  respect  to quoted arguments to the [[ conditional
                      command's =~ operator and locale-specific string compar‐
                      ison  when  using  the  [[ conditional command's < and >
                      operators.  Bash versions prior to  bash-4.1  use  ASCII
                      collation and strcmp(3); bash-4.1 and later use the cur‐
                      rent locale's collation sequence and strcoll(3).
## compat32
                      If set, bash changes its behavior to that of version 3.2
                      with  respect  to locale-specific string comparison when
                      using the [[ conditional command's  <  and  >  operators
                      (see previous item).
## compat40
                      If set, bash changes its behavior to that of version 4.0
                      with respect to locale-specific string  comparison  when
                      using  the  [[  conditional  command's < and > operators
                      (see description of compat31) and the effect  of  inter‐
                      rupting  a  command  list.   Bash versions 4.0 and later
                      interrupt the list as if the shell received  the  inter‐
                      rupt;  previous  versions continue with the next command
                      in the list.
## compat41
                      If set, bash, when in posix mode, treats a single  quote
                      in  a  double-quoted  parameter  expansion  as a special
                      character.  The single quotes must match (an  even  num‐
                      ber)  and  the  characters between the single quotes are
                      considered quoted.  This is the behavior of  posix  mode
                      through  version 4.1.  The default bash behavior remains
                      as in previous versions.
## compat42
                      If set, bash does not process the replacement string  in
                      the  pattern  substitution  word  expansion  using quote
                      removal.
## complete_fullquote
                      If set, bash quotes all shell  metacharacters  in  file‐
                      names  and  directory  names when performing completion.
                      If not set, bash removes metacharacters such as the dol‐
                      lar  sign from the set of characters that will be quoted
                      in completed filenames when these metacharacters  appear
                      in  shell  variable references in words to be completed.
                      This means that dollar  signs  in  variable  names  that
                      expand  to  directories will not be quoted; however, any
                      dollar signs appearing in filenames will not be  quoted,
                      either.   This  is  active only when bash is using back‐
                      slashes to quote completed filenames.  This variable  is
                      set  by  default,  which is the default bash behavior in
                      versions through 4.2.
## direxpand
                      If set, bash replaces directory names with  the  results
                      of  word  expansion when performing filename completion.
                      This changes the contents of the readline  editing  buf‐
                      fer.   If  not  set,  bash attempts to preserve what the
                      user typed.
## dirspell
                      If set, bash attempts spelling correction  on  directory
                      names  during word completion if the directory name ini‐
                      tially supplied does not exist.
## dotglob
If set, bash includes filenames beginning with a `.'  in
                      the results of pathname expansion.
## execfail
                      If set, a non-interactive shell will not exit if it can‐
                      not execute the file specified as  an  argument  to  the
                      exec  builtin  command.   An  interactive shell does not
                      exit if exec fails.
## expand_aliases
                      If set, aliases are expanded as  described  above  under
                      ALIASES.  This option is enabled by default for interac‐
                      tive shells.
## extdebug
                      If set,  behavior  intended  for  use  by  debuggers  is
                      enabled:
                      1.     The -F option to the declare builtin displays the
                             source file name and line number corresponding to
                             each function name supplied as an argument.
                      2.     If  the  command  run by the DEBUG trap returns a
                             non-zero value, the next command is  skipped  and
                             not executed.
                      3.     If  the  command  run by the DEBUG trap returns a
                             value of 2, and the shell is executing in a  sub‐
                             routine  (a shell function or a shell script exe‐
                             cuted by the . or source  builtins),  a  call  to
                             return is simulated.
                      4.     BASH_ARGC  and BASH_ARGV are updated as described
                             in their descriptions above.
                      5.     Function tracing is enabled:   command  substitu‐
                             tion, shell functions, and subshells invoked with
                             ( command ) inherit the DEBUG and RETURN traps.
                      6.     Error tracing is enabled:  command  substitution,
                             shell  functions,  and  subshells  invoked with (
                             command ) inherit the ERR trap.
## extglob
If set, the extended pattern matching features described
                      above under Pathname Expansion are enabled.
## extquote
                      If  set,  $'string'  and  $"string" quoting is performed
                      within  ${parameter}  expansions  enclosed   in   double
                      quotes.  This option is enabled by default.
## failglob
                      If  set,  patterns  which fail to match filenames during
                      pathname expansion result in an expansion error.
## force_fignore
                      If set, the suffixes  specified  by  the  FIGNORE  shell
                      variable  cause words to be ignored when performing word
                      completion even if the ignored words are the only possi‐
                      ble  completions.   See  SHELL  VARIABLES  above  for  a
                      description of  FIGNORE.   This  option  is  enabled  by
                      default.
## globasciiranges
                      If  set,  range  expressions  used  in  pattern matching
                      bracket expressions (see Pattern Matching above)  behave
                      as  if  in the traditional C locale when performing com‐
                      parisons.   That  is,  the  current  locale's  collating
                      sequence  is  not taken into account, so b will not col‐
                      late between A and  B,  and  upper-case  and  lower-case
                      ASCII characters will collate together.
## globstar
                      If set, the pattern ** used in a pathname expansion con‐
                      text will match all files and zero or  more  directories
                      and  subdirectories.  If the pattern is followed by a /,
                      only directories and subdirectories match.
## gnu_errfmt
                      If set, shell error messages are written in the standard
                      GNU error message format.
## histappend
                      If  set,  the history list is appended to the file named
                      by the value of the HISTFILE  variable  when  the  shell
                      exits, rather than overwriting the file.
## histreedit
                      If  set, and readline is being used, a user is given the
                      opportunity to re-edit a failed history substitution.
## histverify
                      If set, and readline is being used, the results of  his‐
                      tory  substitution  are  not  immediately  passed to the
                      shell parser.  Instead, the  resulting  line  is  loaded
                      into the readline editing buffer, allowing further modi‐
                      fication.
## hostcomplete
                      If set, and readline is being used, bash will attempt to
                      perform  hostname  completion when a word containing a @
                      is  being completed (見 [READLINE](bash-readline.md) Completing
                      ).  This is enabled by default.

## huponexit
                      If set, bash will send SIGHUP to all jobs when an inter‐
                      active login shell exits.
## interactive_comments
                      預設是有設，允許互動 shell 有 # 註解功能
## lastpipe
                      If  set,  and  job control is not active, the shell runs
                      the last command of a pipeline not executed in the back‐
                      ground in the current shell environment.
## lithist
If  set,  and  the cmdhist option is enabled, multi-line
                      commands are saved to the history with embedded newlines
                      rather than using semicolon separators where possible.
## login_shell
                      The  shell  sets this option if it is started as a login
                      shell (see INVOCATION above).   The  value  may  not  be
                      changed.
## mailwarn
                      If  set,  and  a file that bash is checking for mail has
                      been accessed since the last time it  was  checked,  the
                      message  ``The  mail in mailfile has been read'' is dis‐
                      played.
## no_empty_cmd_completion
                      If set, and  readline  is  being  used,  bash  will  not
                      attempt to search the PATH for possible completions when
                      completion is attempted on an empty line.
## nocaseglob
                      If set, bash matches  filenames  in  a  case-insensitive
                      fashion when performing pathname expansion (see Pathname
                      Expansion above).
## nocasematch
                      If set, bash  matches  patterns  in  a  case-insensitive
                      fashion when performing matching while executing case or
                      [[ conditional commands.
## nullglob
                      If set, bash allows patterns which match no  files  (see
                      Pathname  Expansion  above)  to expand to a null string,
                      rather than themselves.
## progcomp
                      If set, the programmable completion facilities (see Pro‐
                      grammable Completion above) are enabled.  This option is
                      enabled by default.
## promptvars
                      If set, prompt strings undergo parameter expansion, com‐
                      mand   substitution,  arithmetic  expansion,  and  quote
                      removal after being expanded as described  in  PROMPTING
                      above.  This option is enabled by default.
## restricted_shell
                      The   shell  sets  this  option  if  it  is  started  in
                      restricted mode (見 [RESTRICTED SHELL](restricted-shell.md)).  The value
                      may  not be changed.  This is not reset when the startup
                      files are executed, allowing the startup files  to  dis‐
                      cover whether or not a shell is restricted.
## shift_verbose
                      If  set,  the shift builtin prints an error message when
                      the shift count exceeds the number of positional parame‐
                      ters.
## sourcepath
                      If set, the source (.) builtin uses the value of PATH to
                      find the directory containing the file  supplied  as  an
                      argument.  This option is enabled by default.
## xpg_echo
                      If   set,  the  echo  builtin  expands  backslash-escape
                      sequences by default.
