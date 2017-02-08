# READLINE
readline 是使用互動式 shell 時編輯輸入行的函式庫，除非 shell 執行時有設 --noediting 選項。
內建指令 read 使用 -e 選項也可以用 Line editing。

那些 line editing 指令預設跟 Emacs 類似。
另外還有 vi 形式的 line editing 界面。

任何時候都可以用內建指令 set 的選項 -o emacs 或 -o vi 來啟用 line editing。
Shell 執行時，可用內建指令 set 的選項 +o emacs 或 +o vi 來關閉 line editing。

## Readline Notation
       這裡使用 Emacs 形式的 notation 來表示按鍵
       Ctrl-
       Meta- (沒有 meta 按鍵的鍵盤使用 ESC)

In this section, the Emacs-style notation is used to denote keystrokes.
Control  keys  are  denoted by C-key, e.g., C-n means Control-N.
meta keys are denoted by M-key, so M-x means Meta-X. (沒有 meta 按鍵的鍵盤使用 ESC
       boards  without a meta key, M-x means ESC x, i.e., press the Escape key
       then the x key.  This makes ESC the meta prefix.  The combination M-C-x
       means  ESC-Control-x, or press the Escape key then hold the Control key
       while pressing the x key.)

       Readline commands 可以給數字引數, which normally act as
       a  repeat  count.   Sometimes,  however, it is the sign of the argument
       that is significant.  Passing a negative argument  to  a  command  that
       acts  in the forward direction (e.g., kill-line) causes that command to
       act in a backward direction.  Commands whose  behavior  with  arguments
       deviates from this are noted below.

       When  a command is described as killing text, the text deleted is saved
       for possible future retrieval (yanking).  The killed text is saved in a
       kill ring.  Consecutive kills cause the text to be accumulated into one
       unit, which can be yanked all at once.  Commands which do not kill text
       separate the chunks of text on the kill ring.

## Readline Initialization 初始化
Readline  is  customized  by putting commands in an initialization file
       (the inputrc file).

當使用 readline 函式庫的程式開始執行，會讀取來自 $INPUTRC 的初始化設定檔 (inputrc 檔)，預設是 ~/.inputrc，裡面包含 key bindings 及變數的設定。初始化設定檔只允許一些基本的 constructs。空白行忽略，「#」開始的行是註解，「$」開始的行表示 conditional constructs，其它則是 key bindings 及 variable 設定。

       預設的 key-bindings  may be changed with an inputrc file.  Other
       programs that use this library may add their own commands and bindings.

       For example, placing

              M-Control-u: universal-argument
       or
              C-Meta-u: universal-argument
       into the inputrc would make M-C-u execute the readline command  univer‐
       sal-argument.

       The  following  symbolic  character  names are recognized: RUBOUT, DEL,
       ESC, LFD, NEWLINE, RET, RETURN, SPC, SPACE, and TAB.

       In addition to command names, readline allows keys to  be  bound  to  a
       string that is inserted when the key is pressed (a macro).

## Readline Key Bindings
       The  syntax for controlling key bindings in the inputrc file is simple.
       All that is required is the name of the command or the text of a  macro
       and  a key sequence to which it should be bound.

按鍵可以用兩種方式表示：
1. a symbolic key name, possibly with Meta- or Control- prefixes
1. a key sequence.

       When using the form keyname:function-name or macro, keyname is the name
       of a key spelled out in English.  例如：

              Control-u: universal-argument
              Meta-Rubout: backward-kill-word
              Control-o: "> output"

       In the above example, C-u is bound to the function  universal-argument,
       M-DEL  is bound to the function backward-kill-word, and C-o is bound to
       run the macro expressed on the right hand side (that is, to insert  the
       text ``> output'' into the line).

       第二種形式："keyseq":function-name or macro, keyseq differs
       from keyname above in that strings denoting an entire key sequence  may
       be  specified  by  placing the sequence within double quotes. 有些 GNU
       Emacs 形式的 key escapes 可使用, as in the following  example,  but
       the symbolic character names are not recognized.

              "\C-u": universal-argument
              "\C-x\C-r": re-read-init-file
              "\e[11~": "Function Key 1"

       In this example, C-u is again bound to the function universal-argument.
       C-x C-r is bound to the function re-read-init-file, and ESC [ 1 1 ~  is
       bound to insert the text ``Function Key 1''.

       The full set of GNU Emacs style escape sequences is
              \C-    control prefix
              \M-    meta prefix
              \e     an escape character
              \\     backslash
              \"     literal "
              \'     literal '

       In  addition  to  the GNU Emacs style escape sequences, a second set of
       backslash escapes is available:
              \a     alert (bell)
              \b     backspace
              \d     delete
              \f     form feed
              \n     newline
              \r     carriage return
              \t     horizontal tab
              \v     vertical tab
              \nnn   the eight-bit character whose value is  the  octal  value
                     nnn (one to three digits)
              \xHH   the  eight-bit  character  whose value is the hexadecimal
                     value HH (one or two hex digits)

       When entering the text of a macro, single or double quotes must be used
       to indicate a macro definition.  Unquoted text is assumed to be a func‐
       tion name.  In the macro body, the backslash  escapes  described  above
       are  expanded.   Backslash  will quote any other character in the macro
       text, including " and '.

       Bash 可透過內建指令 bind 來顯示或修改 readline 的 key bindings。互動時的編輯模式可透過內建指令 set 的 -o 選項切換。
       The editing mode may be switched
       during interactive use by using the -o option to the set  builtin  com‐
       mand (見 [SHELL BUILTIN COMMANDS](builtin.md)).

## Readline Variables
Readline 有變數，可用來進一步客製化它的行為。
在 inputrc 檔用 a statement of the form 設定變數
              set variable-name value

       Except  where  noted,  readline 變數 can take the values On or Off
       (without regard to case).  會忽略不認得的 variable-names。
       如果值是空的或 null values、"on" (不分大小寫)、及 "1" 都相當於 On，其它都是 Off。
       The variables and their default values are:

       bell-style (audible)
              Controls  what  happens when readline wants to ring the terminal
              bell.  If set to none, readline never rings the bell.  If set to
              visible,  readline  uses a visible bell if one is available.  If
              set to audible, readline attempts to ring the terminal's bell.
       bind-tty-special-chars (On)
              If set to On, readline attempts to bind the  control  characters
              treated specially by the kernel's terminal driver to their read‐
              line equivalents.
       colored-stats (Off)
              If set to On, readline displays possible completions using  dif‐
              ferent  colors  to  indicate their file type.  The color defini‐
              tions are taken from the  value  of  the  LS_COLORS  environment
              variable.
       comment-begin (``#'')
              The  string  that  is  inserted when the readline insert-comment
              command is executed.  This command is bound to M-# in emacs mode
              and to # in vi command mode.
       completion-ignore-case (Off)
              If set to On, readline performs filename matching and completion
              in a case-insensitive fashion.
       completion-prefix-display-length (0)
              The length in characters of the common prefix of a list of  pos‐
              sible  completions that is displayed without modification.  When
              set to a value greater than zero, common  prefixes  longer  than
              this  value are replaced with an ellipsis when displaying possi‐
              ble completions.
       completion-query-items (100)
              This determines when the user is queried about viewing the  num‐
              ber  of  possible  completions generated by the possible-comple‐
              tions command.  It may be set to any integer value greater  than
              or  equal  to  zero.   If  the number of possible completions is
              greater than or equal to the value of this variable, the user is
              asked  whether or not he wishes to view them; otherwise they are
              simply listed on the terminal.
       convert-meta (On)
              If set to On, readline will convert characters with  the  eighth
              bit set to an ASCII key sequence by stripping the eighth bit and
              prefixing an escape character (in effect, using  escape  as  the
              meta prefix).
       disable-completion (Off)
              If set to On, readline will inhibit word completion.  Completion
              characters will be inserted into the line as if  they  had  been
              mapped to self-insert.
       editing-mode (emacs)
              Controls whether readline begins with a set of key bindings sim‐
              ilar to Emacs or vi.  editing-mode can be set to either emacs or
              vi.
       echo-control-characters (On)
              When  set to On, on operating systems that indicate they support
              it, readline echoes a character corresponding to a signal gener‐
              ated from the keyboard.
       enable-keypad (Off)
              When set to On, readline will try to enable the application key‐
              pad when it is called.  Some systems need  this  to  enable  the
              arrow keys.
       enable-meta-key (On)
              When  set  to  On, readline will try to enable any meta modifier
              key the terminal claims to support when it is called.   On  many
              terminals, the meta key is used to send eight-bit characters.
       expand-tilde (Off)
              If  set  to  On,  tilde  expansion  is  performed  when readline
              attempts word completion.
       history-preserve-point (Off)
              If set to On, the history code attempts to place  point  at  the
              same  location on each history line retrieved with previous-his‐
              tory or next-history.
       history-size (0)
              Set the maximum number of history entries saved in  the  history
              list.   If set to zero, any existing history entries are deleted
              and no new entries are saved.  If set to a value less than zero,
              the  number  of history entries is not limited.  By default, the
              number of history entries is not limited.
       horizontal-scroll-mode (Off)
              When set to On, makes readline use a single  line  for  display,
              scrolling the input horizontally on a single screen line when it
              becomes longer than the screen width rather than wrapping  to  a
              new line.
       input-meta (Off)
              If  set to On, readline will enable eight-bit input (that is, it
              will not strip the high  bit  from  the  characters  it  reads),
              regardless of what the terminal claims it can support.  The name
              meta-flag is a synonym for this variable.
       isearch-terminators (``C-[C-J'')
              The string of characters that should  terminate  an  incremental
              search  without  subsequently  executing the character as a com‐
              mand.  If this variable has not been given a value, the  charac‐
              ters ESC and C-J will terminate an incremental search.
       keymap (emacs)
              Set  the current readline keymap.  The set of valid keymap names
              is emacs, emacs-standard, emacs-meta,  emacs-ctlx,  vi,  vi-com‐
              mand,  and  vi-insert.  vi is equivalent to vi-command; emacs is
              equivalent to emacs-standard.  The default value is  emacs;  the
              value of editing-mode also affects the default keymap.
       keyseq-timeout (500)
              Specifies  the  duration readline will wait for a character when
              reading an ambiguous key sequence (one that can form a  complete
              key sequence using the input read so far, or can take additional
              input to complete a  longer  key  sequence).   If  no  input  is
              received  within  the timeout, readline will use the shorter but
              complete key sequence.  The value is specified in  milliseconds,
              so  a value of 1000 means that readline will wait one second for
              additional input.  If this variable is set to a value less  than
              or  equal to zero, or to a non-numeric value, readline will wait
              until another key is pressed to decide  which  key  sequence  to
              complete.
       mark-directories (On)
              If set to On, completed directory names have a slash appended.
       mark-modified-lines (Off)
              If  set  to  On,  history lines that have been modified are dis‐
              played with a preceding asterisk (*).
       mark-symlinked-directories (Off)
              If set to On, completed names which are symbolic links to direc‐
              tories   have   a  slash  appended  (subject  to  the  value  of
              mark-directories).
       match-hidden-files (On)
              This variable, when set to On, causes readline  to  match  files
              whose  names  begin  with  a  `.' (hidden files) when performing
              filename completion.  If set to Off, the  leading  `.'  must  be
              supplied by the user in the filename to be completed.
       menu-complete-display-prefix (Off)
              If  set to On, menu completion displays the common prefix of the
              list of possible completions (which may be empty) before cycling
              through the list.
       output-meta (Off)
              If  set  to On, readline will display characters with the eighth
              bit set directly rather than as a meta-prefixed escape sequence.
       page-completions (On)
              If set to On, readline uses an internal more-like pager to  dis‐
              play a screenful of possible completions at a time.
       print-completions-horizontally (Off)
              If  set  to  On,  readline will display completions with matches
              sorted horizontally in alphabetical order, rather than down  the
              screen.
       revert-all-at-newline (Off)
              If  set  to  On, readline will undo all changes to history lines
              before returning when accept-line is executed.  By default, his‐
              tory  lines  may  be  modified  and retain individual undo lists
              across calls to readline.
       show-all-if-ambiguous (Off)
              This alters the default behavior of  the  completion  functions.
              If set to On, words which have more than one possible completion
              cause the matches to be listed immediately  instead  of  ringing
              the bell.
       show-all-if-unmodified (Off)
              This  alters the default behavior of the completion functions in
              a fashion similar to show-all-if-ambiguous.  If set to On, words
              which  have more than one possible completion without any possi‐
              ble partial completion (the possible completions don't  share  a
              common  prefix)  cause  the  matches  to  be  listed immediately
              instead of ringing the bell.
       show-mode-in-prompt (Off)
              If set to On, add a character to the  beginning  of  the  prompt
              indicating  the  editing  mode:  emacs (@), vi command (:) or vi
              insertion (+).
       skip-completed-text (Off)
              If set to On, this alters the default completion  behavior  when
              inserting  a  single match into the line.  It's only active when
              performing completion in the middle  of  a  word.   If  enabled,
              readline  does  not  insert  characters from the completion that
              match characters after point in the  word  being  completed,  so
              portions of the word following the cursor are not duplicated.
       visible-stats (Off)
              If  set to On, a character denoting a file's type as reported by
              stat(2) is appended to the filename when listing  possible  com‐
              pletions.

## Readline Conditional Constructs
       Readline  implements  a  facility  similar in spirit to the conditional
       compilation features of the C preprocessor which  allows  key  bindings
       and  variable  settings  to be performed as the result of tests.  There
       are four parser directives used.

       $if    The $if construct allows bindings to be made based on the  edit‐
              ing  mode,  the  terminal  being  used, or the application using
              readline.  The text of the test extends to the end of the  line;
              no characters are required to isolate it.

              mode   The  mode=  form  of  the  $if  directive is used to test
                     whether readline is in emacs or vi  mode.   This  may  be
                     used  in  conjunction  with  the  set keymap command, for
                     instance, to  set  bindings  in  the  emacs-standard  and
                     emacs-ctlx  keymaps  only  if readline is starting out in
                     emacs mode.

              term   The term= form may be used to  include  terminal-specific
                     key bindings, perhaps to bind the key sequences output by
                     the terminal's function keys.  The word on the right side
                     of the = is tested against the both full name of the ter‐
                     minal and the portion of the  terminal  name  before  the
                     first  -.  This allows sun to match both sun and sun-cmd,
                     for instance.

              application
                     The application construct is used to include application-
                     specific  settings.   Each  program  using  the  readline
                     library sets the application name, and an  initialization
                     file can test for a particular value.  This could be used
                     to bind key sequences to functions useful for a  specific
                     program.   For instance, the following command adds a key
                     sequence that quotes the  current  or  previous  word  in
                     bash:

                     $if Bash
                     # Quote the current or previous word
                     "\C-xq": "\eb\"\ef\""
                     $endif

       $endif This command, as seen in the previous example, terminates an $if
              command.

       $else  Commands in this branch of the $if directive are executed if the
              test fails.

       $include
              This  directive takes a single filename as an argument and reads
              commands and bindings from that file.  For example, the  follow‐
              ing directive would read /etc/inputrc:

              $include  /etc/inputrc

## Searching
Readline 提供搜尋歷史指令 (見 HISTORY) 中含有特定字串的功能，有兩種搜尋模式：incremental 及 non-incremental.

       Incremental  searches  begin  before  the  user has finished typing the
       search string.  As each character of the search string is typed,  read‐
       line displays the next entry from the history matching the string typed
       so far.  An incremental search requires  only  as  many  characters  as
       needed  to  find  the desired history entry.  The characters present in
       the value of the isearch-terminators variable are used to terminate  an
       incremental search.  If that variable has not been assigned a value the
       Escape and Control-J characters will terminate an  incremental  search.
       Control-G  will  abort  an  incremental search and restore the original
       line.  When the search is terminated, the history entry containing  the
       search string becomes the current line.

       To  find  other matching entries in the history list, type Control-S or
       Control-R as appropriate.  This will search backward or forward in  the
       history  for  the  next  entry matching the search string typed so far.
       Any other key sequence bound to a readline command will  terminate  the
       search  and  execute that command.  For instance, a newline will termi‐
       nate the search and accept the line, thereby executing the command from
       the history list.

       Readline remembers the last incremental search string.  If two Control-
       Rs are typed without any intervening characters defining a  new  search
       string, any remembered search string is used.

       Non-incremental  searches read the entire search string before starting
       to search for matching history lines.  The search string may  be  typed
       by the user or be part of the contents of the current line.

## Readline Command Names
下面列出指令名稱及其預設綁定的
key sequences.  Command names without an accompanying key sequence are unbound by default.

In the following descriptions,

point 表示目前游標位置,
mark 表示指令 set-mark 儲存的游標位置。
region 表示 point 跟 mark 間的 text

## Commands for Moving 移動游標
* beginning-of-line (C-a)
* end-of-line (C-e)
* forward-char (C-f)：右移，但很可能跟終端機程式的搜尋攔截
* forward-word (M-f)：右移到下個字的結束.  Words are composed of alphanumeric characters (letters and digits).
* backward-char (C-b)：左移
* backward-word (M-b)：左移到目前字或前個字開頭的地方.  Words are composed of alphanumeric characters (letters and digits).
* shell-forward-word： Move forward to the end of the next word.  Words  are  delimited by non-quoted shell metacharacters.
* shell-backward-word：Move back to the start of the current or previous word.  Words are delimited by non-quoted shell metacharacters.
* clear-screen (C-l)：清除螢幕只留最後一行。With an argument, refresh the current line without clearing the screen.
* redraw-current-line：Refresh the current line.

## Commands for Manipulating the History
* accept-line (Newline, Return)
              Accept the line 不管游標位置。If this line
              is  non-empty, add it to the history list according to the state
              of the HISTCONTROL variable.  If the line is a modified  history
              line, then restore the history line to its original state.
* previous-history (C-p)
              Fetch the previous command from the history list, moving back in
              the list.
* next-history (C-n)
              Fetch the next command from the history list, moving forward  in
              the list.
* beginning-of-history (M-<)
              Move to the first line in the history.
* end-of-history (M->)
              Move  to  the end of the input history, i.e., the line currently
              being entered.
* reverse-search-history (C-r)
              Search backward starting at the current  line  and  moving  `up'
              through  the  history  as  necessary.   This  is  an incremental
              search.
* forward-search-history (C-s)
              Search forward starting at the current line  and  moving  `down'
              through  the  history  as  necessary.   This  is  an incremental
              search.
* non-incremental-reverse-search-history (M-p)
              Search backward through the history starting at the current line
              using  a  non-incremental  search  for  a string supplied by the
              user.
* non-incremental-forward-search-history (M-n)
              Search forward  through  the  history  using  a  non-incremental
              search for a string supplied by the user.
* history-search-forward
              Search  forward through the history for the string of characters
              between the start of the current line and the point.  This is  a
              non-incremental search.
* history-search-backward
              Search backward through the history for the string of characters
              between the start of the current line and the point.  This is  a
              non-incremental search.
* yank-nth-arg (M-C-y)
              Insert  the  first argument to the previous command (usually the
              second word on the previous line) at point.  With an argument n,
              insert  the nth word from the previous command (the words in the
              previous command  begin  with  word  0).   A  negative  argument
              inserts the nth word from the end of the previous command.  Once
              the argument n is computed, the argument is extracted as if  the
              "!n" history expansion had been specified.
* yank-last-arg (M-., M-_)
              Insert  the last argument to the previous command (the last word
              of the previous history entry).  With a numeric argument, behave
              exactly  like  yank-nth-arg.   Successive calls to yank-last-arg
              move back through the history list, inserting the last word  (or
              the  word  specified  by the argument to the first call) of each
              line in turn.  Any numeric argument supplied to these successive
              calls  determines  the direction to move through the history.  A
              negative argument switches the  direction  through  the  history
              (back or forward).  The history expansion facilities are used to
              extract the last word, as if the "!$" history expansion had been
              specified.
* shell-expand-line (M-C-e)
              Expand the line as the shell does.  This performs alias and his‐
              tory expansion as well as all of the shell word expansions.  See
              HISTORY EXPANSION below for a description of history expansion.
* history-expand-line (M-^)
              Perform  history  expansion  on  the  current line.  See HISTORY
              EXPANSION below for a description of history expansion.
* magic-space
              Perform history expansion on  the  current  line  and  insert  a
              space.  See HISTORY EXPANSION below for a description of history
              expansion.
* alias-expand-line
              Perform alias expansion on the current line.  See ALIASES  above
              for a description of alias expansion.
* history-and-alias-expand-line
              Perform history and alias expansion on the current line.
* insert-last-argument (M-., M-_)
              A synonym for yank-last-arg.
* operate-and-get-next (C-o)
              Accept  the  current  line for execution and fetch the next line
              relative to the current line from the history for editing.   Any
              argument is ignored.
* edit-and-execute-command (C-xC-e)
              Invoke  an  editor  on the current command line, and execute the
              result as shell commands.   Bash  attempts  to  invoke  $VISUAL,
              $EDITOR, and emacs as the editor, in that order.

## Commands for Changing Text
* end-of-file (usually C-d)：
              The  character  indicating  end-of-file  as set, for example, by
              ``stty''.  If this character is read when there are  no  charac‐
              ters  on  the  line,  and point is at the beginning of the line,
              Readline interprets it as the end of input and returns EOF.
* delete-char (C-d)：刪除一個字元，相當於 delete。如果是用在 tty EOF 字元, as C-d commonly is, see above for the effects.
       delete-char (C-d)
              Delete the character at point.  If this function is bound to the
              same character as the tty EOF character, as C-d commonly is, see
              above for the effects.
       backward-delete-char (Rubout)
              Delete the character behind the cursor.  When  given  a  numeric
              argument, save the deleted text on the kill ring.
       forward-backward-delete-char
              Delete  the  character under the cursor, unless the cursor is at
              the end of the line, in which case the character behind the cur‐
              sor is deleted.
       quoted-insert (C-q, C-v)
              Add  the next character typed to the line verbatim.  This is how
              to insert characters like C-q, for example.
       tab-insert (C-v TAB)
              Insert a tab character.
       self-insert (a, b, A, 1, !, ...)
              Insert the character typed.
       transpose-chars (C-t)
              Drag the character before point forward over  the  character  at
              point,  moving point forward as well.  If point is at the end of
              the line, then this transposes the two characters before  point.
              Negative arguments have no effect.
       transpose-words (M-t)
              Drag  the  word  before  point past the word after point, moving
              point over that word as well.  If point is at  the  end  of  the
              line, this transposes the last two words on the line.
       upcase-word (M-u)
              Uppercase  the  current  (or  following)  word.  With a negative
              argument, uppercase the previous word, but do not move point.
       downcase-word (M-l)
              Lowercase the current (or  following)  word.   With  a  negative
              argument, lowercase the previous word, but do not move point.
       capitalize-word (M-c)
              Capitalize  the  current  (or  following) word.  With a negative
              argument, capitalize the previous word, but do not move point.
       overwrite-mode
              Toggle overwrite mode.  With an explicit positive numeric  argu‐
              ment, switches to overwrite mode.  With an explicit non-positive
              numeric argument, switches to insert mode.  This command affects
              only  emacs mode; vi mode does overwrite differently.  Each call
              to readline() starts in insert mode.  In overwrite mode, charac‐
              ters  bound to self-insert replace the text at point rather than
              pushing the text  to  the  right.   Characters  bound  to  back‐
              ward-delete-char  replace  the  character  before  point  with a
              space.  By default, this command is unbound.

## Killing and Yanking
       kill-line (C-k)
              Kill the text from point to the end of the line.
       backward-kill-line (C-x Rubout)
              Kill backward to the beginning of the line.
       unix-line-discard (C-u)
              Kill backward from point to the  beginning  of  the  line.   The
              killed text is saved on the kill-ring.
       kill-whole-line
              Kill  all  characters on the current line, no matter where point
              is.
* kill-word (M-d)：刪除目前 word。Word boundaries are the same as those used by forward-word 或 shell-forward-word
       backward-kill-word (M-Rubout)
              Kill the word behind point.  Word boundaries  are  the  same  as
              those used by backward-word.
       shell-kill-word (M-d)
              Kill  from  point  to the end of the current word, or if between
              words, to the end of the next word.   Word  boundaries  are  the
              same as those used by shell-forward-word.
       shell-backward-kill-word (M-Rubout)
              Kill  the  word  behind  point.  Word boundaries are the same as
              those used by shell-backward-word.
* unix-word-rubout (C-w)：刪除前面的字，using white space as a  word  boundary. The killed text is saved on the kill-ring.
       unix-filename-rubout
              Kill  the  word  behind  point,  using white space and the slash
              character as the word boundaries.  The killed text is  saved  on
              the kill-ring.
       delete-horizontal-space (M-\)
              Delete all spaces and tabs around point.
       kill-region
              Kill the text in the current region.
       copy-region-as-kill
              Copy the text in the region to the kill buffer.
       copy-backward-word
              Copy  the word before point to the kill buffer.  The word bound‐
              aries are the same as backward-word.
       copy-forward-word
              Copy the word following point to  the  kill  buffer.   The  word
              boundaries are the same as forward-word.
       yank (C-y)
              Yank the top of the kill ring into the buffer at point.
       yank-pop (M-y)
              Rotate  the kill ring, and yank the new top.  Only works follow‐
              ing yank or yank-pop.

## Numeric Arguments
       digit-argument (M-0, M-1, ..., M--)
              Add this digit to the argument already accumulating, or start  a
              new argument.  M-- starts a negative argument.
       universal-argument
              This  is another way to specify an argument.  If this command is
              followed by one or more digits, optionally with a leading  minus
              sign,  those digits define the argument.  If the command is fol‐
              lowed by digits, executing  universal-argument  again  ends  the
              numeric  argument, but is otherwise ignored.  As a special case,
              if this command is immediately followed by a character  that  is
              neither  a  digit or minus sign, the argument count for the next
              command is multiplied by four.  The argument count is  initially
              one,  so  executing this function the first time makes the argu‐
              ment count four, a second time makes the argument count sixteen,
              and so on.

## Completing
       complete (TAB)
              Attempt  to  perform  completion on the text before point.  Bash
              attempts completion treating the text as a variable (if the text
              begins  with  $), username (if the text begins with ~), hostname
              (if the text begins with @), or command (including  aliases  and
              functions) in turn.  If none of these produces a match, filename
              completion is attempted.
       possible-completions (M-?)
              List the possible completions of the text before point.
       insert-completions (M-*)
              Insert all completions of the text before point that would  have
              been generated by possible-completions.
       menu-complete
              Similar  to complete, but replaces the word to be completed with
              a single match from the list of possible completions.   Repeated
              execution  of  menu-complete  steps through the list of possible
              completions, inserting each match in turn.  At the  end  of  the
              list of completions, the bell is rung (subject to the setting of
              bell-style) and the original text is restored.  An argument of n
              moves  n  positions  forward  in the list of matches; a negative
              argument may be used to move backward through  the  list.   This
              command  is  intended  to  be  bound  to  TAB, but is unbound by
              default.
       menu-complete-backward
              Identical to menu-complete, but moves backward through the  list
              of  possible  completions,  as if menu-complete had been given a
              negative argument.  This command is unbound by default.
       delete-char-or-list
              Deletes the character under the cursor if not at  the  beginning
              or  end  of  the  line (like delete-char).  If at the end of the
              line, behaves identically to possible-completions.  This command
              is unbound by default.
       complete-filename (M-/)
              Attempt filename completion on the text before point.
       possible-filename-completions (C-x /)
              List the possible completions of the text before point, treating
              it as a filename.
       complete-username (M-~)
              Attempt completion on the text before point, treating  it  as  a
              username.
       possible-username-completions (C-x ~)
              List the possible completions of the text before point, treating
              it as a username.
       complete-variable (M-$)
              Attempt completion on the text before point, treating  it  as  a
              shell variable.
       possible-variable-completions (C-x $)
              List the possible completions of the text before point, treating
              it as a shell variable.
       complete-hostname (M-@)
              Attempt completion on the text before point, treating  it  as  a
              hostname.
       possible-hostname-completions (C-x @)
              List the possible completions of the text before point, treating
              it as a hostname.
       complete-command (M-!)
              Attempt completion on the text before point, treating  it  as  a
              command  name.   Command  completion  attempts to match the text
              against  aliases,  reserved  words,   shell   functions,   shell
              builtins, and finally executable filenames, in that order.
       possible-command-completions (C-x !)
              List the possible completions of the text before point, treating
              it as a command name.
       dynamic-complete-history (M-TAB)
              Attempt completion on the text before point, comparing the  text
              against  lines  from  the  history  list for possible completion
              matches.
       dabbrev-expand
              Attempt menu completion on the text before point, comparing  the
              text against lines from the history list for possible completion
              matches.
       complete-into-braces (M-{)
              Perform filename completion and insert the list of possible com‐
              pletions  enclosed within braces so the list is available to the
              shell (see Brace Expansion above).

## Keyboard Macros
       start-kbd-macro (C-x ()
              Begin saving the characters  typed  into  the  current  keyboard
              macro.
       end-kbd-macro (C-x ))
              Stop saving the characters typed into the current keyboard macro
              and store the definition.
       call-last-kbd-macro (C-x e)
              Re-execute the last keyboard macro defined, by making the  char‐
              acters in the macro appear as if typed at the keyboard.
       print-last-kbd-macro ()
              Print  the  last keyboard macro defined in a format suitable for
              the inputrc file.

## Miscellaneous
       re-read-init-file (C-x C-r)
              Read in the contents of the inputrc file,  and  incorporate  any
              bindings or variable assignments found there.
       abort (C-g)
              Abort  the  current editing command and ring the terminal's bell
              (subject to the setting of bell-style).
       do-uppercase-version (M-a, M-b, M-x, ...)
              If the metafied character x is lowercase, run the  command  that
              is bound to the corresponding uppercase character.
       prefix-meta (ESC)
              Metafy the next character typed.  ESC f is equivalent to Meta-f.
       undo (C-_, C-x C-u)
              Incremental undo, separately remembered for each line.
       revert-line (M-r)
              Undo  all changes made to this line.  This is like executing the
              undo command enough times to return  the  line  to  its  initial
              state.
       tilde-expand (M-&)
              Perform tilde expansion on the current word.
       set-mark (C-@, M-<space>)
              Set  the  mark to the point.  If a numeric argument is supplied,
              the mark is set to that position.
       exchange-point-and-mark (C-x C-x)
              Swap the point with the mark.  The current  cursor  position  is
              set  to the saved position, and the old cursor position is saved
              as the mark.
       character-search (C-])
              A character is read and point is moved to the next occurrence of
              that  character.   A negative count searches for previous occur‐
              rences.
       character-search-backward (M-C-])
              A character is read and point is moved to  the  previous  occur‐
              rence  of  that character.  A negative count searches for subse‐
              quent occurrences.
       skip-csi-sequence
              Read enough characters to consume a multi-key sequence  such  as
              those  defined for keys like Home and End.  Such sequences begin
              with a Control Sequence Indicator (CSI), usually ESC-[.  If this
              sequence  is  bound  to "\[", keys producing such sequences will
              have no effect unless explicitly bound to  a  readline  command,
              instead  of  inserting stray characters into the editing buffer.
              This is unbound by default, but usually bound to ESC-[.
       insert-comment (M-#)
              Without a numeric argument,  the  value  of  the  readline  com‐
              ment-begin  variable is inserted at the beginning of the current
              line.  If a numeric argument is supplied, this command acts as a
              toggle:   if  the characters at the beginning of the line do not
              match the value of comment-begin, the value is inserted,  other‐
              wise the characters in comment-begin are deleted from the begin‐
              ning of the line.  In either case, the line is accepted as if  a
              newline  had  been  typed.   The  default value of comment-begin
              causes this command to make the current line  a  shell  comment.
              If  a  numeric  argument  causes  the  comment  character  to be
              removed, the line will be executed by the shell.
       glob-complete-word (M-g)
              The word before point is  treated  as  a  pattern  for  pathname
              expansion,  with  an asterisk implicitly appended.  This pattern
              is used to generate a list of matching  filenames  for  possible
              completions.
       glob-expand-word (C-x *)
              The  word  before  point  is  treated  as a pattern for pathname
              expansion, and the  list  of  matching  filenames  is  inserted,
              replacing  the  word.   If  a  numeric  argument is supplied, an
              asterisk is appended before pathname expansion.
       glob-list-expansions (C-x g)
              The list  of  expansions  that  would  have  been  generated  by
              glob-expand-word  is  displayed,  and the line is redrawn.  If a
              numeric argument is supplied, an  asterisk  is  appended  before
              pathname expansion.
       dump-functions
              Print  all  of the functions and their key bindings to the read‐
              line output stream.  If a numeric argument is supplied, the out‐
              put  is  formatted  in such a way that it can be made part of an
              inputrc file.
       dump-variables
              Print all of the settable readline variables and their values to
              the  readline output stream.  If a numeric argument is supplied,
              the output is formatted in such a way that it can be  made  part
              of an inputrc file.
       dump-macros
              Print  all of the readline key sequences bound to macros and the
              strings they output.  If a numeric  argument  is  supplied,  the
              output is formatted in such a way that it can be made part of an
              inputrc file.
       display-shell-version (C-x C-v)
              Display version information about the current instance of bash.

## Programmable Completion
       When word completion is attempted for an  argument  to  a  command  for
       which  a  completion  specification (a compspec) has been defined using
       the complete builtin (見 [SHELL BUILTIN COMMANDS](builtin.md)),  the  program‐
       mable completion facilities are invoked.

       First,  the  command  name  is  identified.  If the command word is the
       empty string (completion attempted at the beginning of an empty  line),
       any  compspec  defined  with  the  -E option to complete is used.  If a
       compspec has been defined for that command, the  compspec  is  used  to
       generate the list of possible completions for the word.  If the command
       word is a full pathname, a compspec for the full pathname  is  searched
       for  first.   If no compspec is found for the full pathname, an attempt
       is made to find a compspec for the portion following the  final  slash.
       If  those  searches  do  not result in a compspec, any compspec defined
       with the -D option to complete is used as the default.

       Once a compspec has been found, it is used  to  generate  the  list  of
       matching  words.   If a compspec is not found, the default bash comple‐
       tion as described above under Completing is performed.

       First, the actions specified by the compspec are  used.   Only  matches
       which  are prefixed by the word being completed are returned.  When the
       -f or -d option is used for filename or directory name completion,  the
       shell variable FIGNORE is used to filter the matches.

       Any  completions  specified  by  a pathname expansion pattern to the -G
       option are generated next.  The words generated by the pattern need not
       match  the  word being completed.  The GLOBIGNORE shell variable is not
       used to filter the matches, but the FIGNORE variable is used.

       Next, the string specified as the argument to the -W option is  consid‐
       ered.   The  string is first split using the characters in the IFS spe‐
       cial variable as delimiters.  Shell quoting is honored.  Each  word  is
       then  expanded  using  brace  expansion, tilde expansion, parameter and
       variable expansion, command substitution, and arithmetic expansion,  as
       見 [EXPANSION](bash-expansion.md).  The results are split using the rules
       described above under Word Splitting.  The results of the expansion are
       prefix-matched against the word being completed, and the matching words
       become the possible completions.

       After these matches have been generated, any shell function or  command
       specified  with  the -F and -C options is invoked.  When the command or
       function is invoked, the COMP_LINE, COMP_POINT, COMP_KEY, and COMP_TYPE
       variables are assigned values as described above under Shell Variables.
       If a shell function is being invoked,  the  COMP_WORDS  and  COMP_CWORD
       variables  are  also set.  When the function or command is invoked, the
       first argument ($1) is the name of  the  command  whose  arguments  are
       being  completed, the second argument ($2) is the word being completed,
       and the third argument ($3) is the word preceding the word  being  com‐
       pleted on the current command line.  No filtering of the generated com‐
       pletions against the word being completed is performed; the function or
       command has complete freedom in generating the matches.

       Any  function specified with -F is invoked first.  The function may use
       any of the shell facilities, including the  compgen  builtin  described
       below,  to  generate the matches.  It must put the possible completions
       in the COMPREPLY array variable, one per array element.

       Next, any command specified with the -C option is invoked in  an  envi‐
       ronment  equivalent to command substitution.  It should print a list of
       completions, one per line, to the standard output.   Backslash  may  be
       used to escape a newline, if necessary.

       After  all of the possible completions are generated, any filter speci‐
       fied with the -X option is applied to the list.  The filter is  a  pat‐
       tern  as  used  for  pathname expansion; a & in the pattern is replaced
       with the text of the word being completed.  A literal & may be  escaped
       with  a  backslash; the backslash is removed before attempting a match.
       Any completion that matches the pattern will be removed from the  list.
       A leading ! negates the pattern; in this case any completion not match‐
       ing the pattern will be removed.

       Finally, any prefix and suffix specified with the -P and -S options are
       added to each member of the completion list, and the result is returned
       to the readline completion code as the list of possible completions.

       If the previously-applied actions do not generate any matches, and  the
       -o  dirnames  option  was  supplied  to  complete when the compspec was
       defined, directory name completion is attempted.

       If the -o plusdirs option was supplied to complete  when  the  compspec
       was defined, directory name completion is attempted and any matches are
       added to the results of the other actions.

       By default, if a compspec is found, whatever it generates  is  returned
       to  the  completion  code as the full set of possible completions.  The
       default bash completions are not attempted, and the readline default of
       filename completion is disabled.  If the -o bashdefault option was sup‐
       plied to complete when the compspec was defined, the bash default  com‐
       pletions are attempted if the compspec generates no matches.  If the -o
       default option was supplied to complete when the compspec was  defined,
       readline's  default  completion will be performed if the compspec (and,
       if attempted, the default bash completions) generate no matches.

       When a compspec indicates that directory name  completion  is  desired,
       the  programmable completion functions force readline to append a slash
       to completed names which are symbolic links to directories, subject  to
       the  value of the mark-directories readline variable, regardless of the
       setting of the mark-symlinked-directories readline variable.

       There is some support for dynamically modifying completions.   This  is
       most  useful  when used in combination with a default completion speci‐
       fied with complete -D.  It's possible for shell functions  executed  as
       completion  handlers  to  indicate that completion should be retried by
       returning an exit status of 124.  If a shell function returns 124,  and
       changes the compspec associated with the command on which completion is
       being attempted (supplied as the first argument when  the  function  is
       executed), programmable completion restarts from the beginning, with an
       attempt to find a new compspec for that command.  This allows a set  of
       completions  to be built dynamically as completion is attempted, rather
       than being loaded all at once.

       For instance, assuming that there is a library of compspecs, each  kept
       in  a  file  corresponding  to  the  name of the command, the following
       default completion function would load completions dynamically:

       _completion_loader()
       {
            . "/etc/bash_completion.d/$1.sh" >/dev/null 2>&1 && return 124
       }
       complete -D -F _completion_loader -o bashdefault -o default

## 參考及延伸閱讀
* [Bash Shell 快速鍵](https://blog.longwin.com.tw/2006/09/bash_hot_key_2006/)
