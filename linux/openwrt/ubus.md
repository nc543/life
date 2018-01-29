ubus (OpenWrt micro bus architecture)

包含 daemon ubusd、函式庫 libubus、和一些額外的 helpers.

ubusd 是 ubus 的心臟，提供界面給其它 daemons 註冊和送訊息，採用 Unix sockets 和 TLV (type-length-value) 訊息。

libubus 簡化使用 ubus 的軟體開發。

Every daemon registers a set of paths under a specific namespace. Every path can provide multiple procedures with any number of arguments. Procedures can reply with a message. 

http://git.openwrt.org/project/ubus.git

## Command-line tool
工具指令

和註冊到 ubus 的服務互動。It's useful for investigating/debugging registered namespaces as well as writing shell scripts. For calling procedures with parameters and returning responses it uses the user-friendly JSON format.

```
Usage: ubus [<options>] <command> [arguments...]
Options:
 -s <socket>:           設定要連結的 unix socket，沒指定預設是「/var/run/ubus.sock」
 -t <timeout>:          設定指令 timeout 秒數
 -S:                    Use simplified output (for scripts)
 -v:                    More verbose output
 -m <type>:             (for monitor): include a specific message type
                        (can be used more than once)
 -M <r|t>               (for monitor): only capture received or transmitted traffic

Commands:
 - list [<path>]                        列出已註冊的 namespace，-v 的話包含 procedures 和其 argument signatures 也列出。
 - call <path> <method> [<message>]     呼叫 namespace 的 procedure，可含以 JSON 表示的引數
 - listen [<path>...]                   Listen for events
 - send <type> [<message>]              送事件通知。
 - wait_for <object> [<object>...]      Wait for multiple objects to appear on ubus
 - monitor                              Monitor ubus traffic
```

* `ubus listen &`：建立一個 listening socket 來 observe incoming 事件。

範例
```
ubus
ubus list
ubus -v list system
ubus call system info
```

## 透過 HTTP 存取 ubus
uhttpd 有 ubus plugin -- uhttpd-mod-ubus 讓 ...

## 在 lua 使用 ubus

## Namespaces & Procedures
使用 ubus 常見的專案。

### netifd

### rpcd
for file, iwinfo, session, uci

## Example code snippets

## ubusd

ubusd 內部是一個 [uloop](http://lirobo.blogspot.com/2014/07/libubox-uloop.html)，監視預設 bind 到「/var/run/ubus.sock」的 fd 所發生的事件，

## 參考和延伸閱讀

* https://wiki.openwrt.org/doc/techref/ubus
* [用ubus實現Inter-Process Communication](https://bryceknowhow.blogspot.tw/2017/02/openwrt-ubusinter-process-communication.html)
* [ubus_invoke()使用介紹](https://bryceknowhow.blogspot.tw/2017/02/openwrt-ubusinvoke.html)

http://wiki.openwrt.org/doc/techref/netifd

延伸閱讀：http://data.pavlix.net/installfest/2014/openwrt-software.pdf
