相依性
```sh
make
make V=s
make menuconfig
make kernel_menuconfig
```
套件編譯
```sh
make package/the_package_dir/compile
make package/the_package_dir/clean
make package/the_package_dir/prepare QUILT=1
make package/the_package_dir/refresh
```
