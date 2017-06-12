# L4 port

來源跟目的各有 16-bit，0~65535

https://en.wikipedia.org/wiki/List_of_TCP_and_UDP_port_numbers

ephemeral ports
dynamic or private ports

xxx|range
--|--
well-known|0 ~ 1023
registered | 1024 ~ 49151
Internet Assigned Numbers Authority (IANA) suggests<br>FreeBSD 4.6+<br>Windows Vista, Windows 7, Server 2008<br>Windows Server 2003 after MS08-037 from 2008 is installed|49152 ~ 65535 (MSB 2-bit 為 1)
FreeBSD <4.6|1024 ~ 5000
Many Linux kernels|32768 ~ 61000
XP<br>Windows Server 2003 before MS08-037 from 2008 is installed|1025 ~ 5000
Windows Server 2008 with Exchange Server 2007 installed|1025 ~ 60000

all versions of Windows since Windows 2000 have the option of specifying a custom range anywhere within 1025–65535.

/proc/sys/net/ipv4/ip_local_port_range
