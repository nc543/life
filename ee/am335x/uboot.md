## U-Boot 2015.10
會自動執行 `bootcmd`
```
run findfdt;
run mmcboot;
setenv mmcdev 1; setenv bootpart 1:2; run mmcboot;
run nandboot;
```

首先執行 `findfdt` 決定 dtb 檔，然後嘗試開機。執行 `mmcboot` 嘗試從 mmc0 開機，如果失敗再次執行 `mmcboot` 嘗試從 mmc1 開機，最後執行 `nandboot` 嘗試 NAND 開機。

findfdt
```
if test $board_name = A335BONE; then setenv fdtfile am335x-bone.dtb; fi;
if test $board_name = A335BNLT; then setenv fdtfile am335x-boneblack.dtb; fi;
if test $board_name = A33515BB; then setenv fdtfile am335x-evm.dtb; fi;
if test $board_name = A335X_SK; then setenv fdtfile am335x-evmsk.dtb; fi;
if test $fdtfile = undefined; then echo WARNING: Could not determine device tree to use; fi;
```
由 board_name 決定 fdtfile，也就是用哪個 dtb 檔。board_name 讀自板子的 eeprom，BBB 是 A335BNLT，dtb 檔是 am335x-boneblack.dtb。
亦可在後續讀取的 `uEnv.txt` 提供 `fdtfilea`。

mmcboot
```
mmc dev ${mmcdev};
if mmc rescan; then
	echo SD/MMC found on device ${mmcdev};
	if run loadbootscript; then
		run bootscript;
	else
		if run loadbootenv; then
			echo Loaded environment from ${bootenv};
			run importbootenv;
		fi;
		if test -n $uenvcmd; then
			echo Running uenvcmd ...;
			run uenvcmd;
		fi;
		if run loadimage; then
			run mmcloados;
		fi;
	fi ;
fi;
```
`mmcdev` 決定 MMC device，`mmc rescan` 有找到的話，才會執行相關動作。

`loadbootscript` 及 `bootscript`

`loadbootenv` 將預設是 `uEnv.tx` 的 `bootenv` 載入到記憶體，再用 `importbootenv` 設定環境變數

loadbootenv
```
load mmc ${mmcdev} ${loadaddr} ${bootenv}
```

importbootenv
```
echo Importing environment from mmc ...; env import -t -r $loadaddr $filesize
```

如果有 `uenvcmd`，則執行它。一般 uenvcmd 是來自 uEnv.txt。

loadimage
```
load mmc ${bootpart} ${loadaddr} ${bootdir}/${bootfile}
```

mmcloados;
```
run args_mmc;
if test ${boot_fdt} = yes || test ${boot_fdt} = try; then
	if run loadfdt; then
		bootz ${loadaddr} - ${fdtaddr};
	else
		if test ${boot_fdt} = try; then
			bootz;
		else
			echo WARN: Cannot load the DT;
		fi;
	fi;
else
	bootz;
fi;
```

args_mmc
```
run finduuid;
setenv bootargs console=${console} ${optargs} root=PARTUUID=${uuid} rw rootfstype=${mmcrootfstype}
```

finduuid
```
part uuid mmc 0:2 uuid
```
應該改成
```
part uuid mmc ${bootpart} uuid
```

loadfdt
```
load mmc ${bootpart} ${fdtaddr} ${bootdir}/${fdtfile}
```

bootz：從記憶體啟動 Linux zImage 影像檔

http://lirobo.blogspot.tw/2014/09/uenvtxt.html
http://lirobo.blogspot.tw/2014/06/am335x-booting.html


##


run loadimage 載入 bootfile 成功的話，run mmcloados 設定 bootargs，並嘗試載入 fdtfile 後 bootz。預設載入的 bootfile 是位於第二分割的 boot/zImage，執行 bootz 後控制權轉移了，bootcmd 就結束了

nandboot：設定 bootargs，從 nand 載入 bootfile 後，bootz。

在 ti EZSDK 也是類似

    把原本的 bootcmd 分成 bootcmd_mmc0 及 bootcmd_nand，bootcmd_nand 就是 run nandboot。另外有 bootcmd_usb 給 usb 開機用
    bootcmd_mmc0 是 run mmc_boot，會嘗試從 mmc0 及 mmc1 開機，但在 run mmcboot 前，先 run scan_boot，可從多種可能的 bootdir 及 bootfile run script_boot 來嘗試開機。不過 script_boot 看起來有些錯誤。scan_boot 也用在 bootcmd_usb。

