```
ifreq ifr;
memset(&ifr, 0, sizeof(ifr));
strcpy(ifr.ifr_name, "eth0"); //set to whatever your ethernet device is
mii_ioctl_data* mii = (mii_ioctl_data*)(&ifr.ifr_data);
mii->phy_id = phyId; //set to your phy's ID
mii->reg_num = reg; //the register you want to read
mii->val_in = 0;
mii->val_out = 0;

int fd = socket(AF_INET, SOCK_DGRAM, 0);
int err = ioctl(fd, SIOCGMIIREG, &ifr);
```

ethernet driver
```
static int mdio_read(struct net_device *dev, int phy_id, int location)
static void mdio_write(struct net_device *dev, int phy_id, int location, int value)
```

generic_mii_ioctl()

(driver's private data)->mii.phy_id_mask


https://groups.google.com/forum/#!topic/comp.os.linux.embedded/VOA0K3kLZec

## mdio-bitbang

int mdiobus_register(struct mii_bus *bus)
bring up all the PHYs on a given bus and attach them to bus

## mdio-gpio
drivers/net/phy/mdio-gpio.c
of_match_table "virtual,mdio-gpio"

mdio-gpio 提供 probe 及 remove 功能
* probe：取得 MDIO bus id 及 platform data，..., 註冊 mdio bus
* remove：釋出

gpio_set_value()
gpio_direction_output()
gpio_direction_input()
gpio_get_value()

mdio-bitbang.c 提供兩個函數 -- alloc_mdio_bitbang() 及 free_mdio_bitbang()。
alloc_mdio_bitbang

## 使用方式
```
aliases {
        mdio-gpio0 = &mdio0;
};

mdio0: mdio {
        compatible = "virtual,mdio-gpio";
        #address-cells = <1>;
        #size-cells = <0>;
        gpios = <&qe_pio_a 11
                 &qe_pio_c 6>;
};
```
## 如何使用 MDIO bus？
