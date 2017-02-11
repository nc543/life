ssh IP
ssh name@IP
自動登入
壓縮
ssh -X IP
跨 firewall

## SSH tunnel

### local port forwarding
開一個 SSH 隧道從一個近端 port 通到遠端 IP:port，存取近端 port 會轉到存取遠端 IP:port。
```
ssh -L 9000:remote.addr:80 user@example.com
```

### remote port forwarding
開一個 SSH 隧道從一個遠端 port 通到近端 localhost:port，存取遠端 port 會轉到存取近端 port。

```
ssh -R 9000:localhost:3000 user@example.com
```
遠端是 SSH server，預設不允許 remote port forwarding，啟用需要在 ```/etc/ssh/sshd_config``` 加
```
GatewayPorts yes
```
然後重啟
```
sudo service ssh restart
```
## 小技巧
ssh 加參數 -nNT 不開 tty

## 參考
http://blog.trackets.com/2014/05/17/ssh-tunnel-local-and-remote-port-forwarding-explained-with-examples.html
https://sites.google.com/site/ijonccc/ssh

## 待讀
https://www.bitvise.com/remote-desktop
http://www.howtogeek.com/114812/5-cool-things-you-can-do-with-an-ssh-server/
http://www.linuxjournal.com/content/more-secure-ssh-connections?utm_source=feedburner&utm_medium=feed&utm_campaign=Feed%3A+linuxjournalcom+%28Linux+Journal+-+The+Original+Magazine+of+the+Linux+Community%29
http://www.cyberciti.biz/faq/install-ssh-identity-key-remote-host/
[Linux 透過 SSH SOCKS 連線 來 使用 Firefox / Pidgin(MSN, GTalk..)](https://blog.longwin.com.tw/2010/01/linux-ssh-socks-firefox-pidgin-2010/)
