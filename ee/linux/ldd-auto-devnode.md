

1. alloc_chrdev_region() 取得將使用的 major number 及 minor number 範圍 (/proc/devices 可看到)。相反：uregister_chrdev_region()
1. class_create() 建立 device class (GPL，/sys/class 可看到)。相反：class_destroy()
1. 每個 device 呼叫 cdev_init() 及 cdev_add() 新增 character device 到系統。相反：cdev_del()
1. 每個 device 呼叫 device_create(). As a result, among other things, Udev will create device nodes for your devices. 相反：device_destroy()

比較：register_chrdev()

ref from: http://stackoverflow.com/questions/5970595/create-a-device-node-in-code

https://coherentmusings.wordpress.com/2012/12/22/device-node-creation-without-using-mknod/

http://stackoverflow.com/questions/8697300/how-to-create-a-device-in-dev-automatically-upon-loading-of-the-kernel-module-f
 You can use class_create() and device_create for that
http://reactivated.net/writing_udev_rules.html


