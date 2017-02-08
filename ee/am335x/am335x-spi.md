# Multichannel Serial Port Interface (McSPI)

a general-purpose receive/transmit master/slave controller that can interface with up to four
slave external devices or one single external master. It allows a duplex, synchronous, serial
communication between a CPU and SPI compliant external devices (Slaves and Masters).

AM335x 有兩個 SPI (SPI0 及 SPI1) 可作為 Master 或 Slave
* SPIx_SCLK I/O SPI serial clock (output when master, input when slave)
* SPIx_D0 I/O Can be configured as either input or output (MOSI or MISO)
* SPIx_D1 I/O Can be configured as either input or output (MOSI or MISO)
* SPIx_CS0 I/O SPI chip select 0 output when master, input when slave (active low)
* SPIx_CS1 O SPI chip select 1 output when master, input when slave (active low)
data pins 可用 兩根或一根

http://processors.wiki.ti.com/index.php/AM335x_McSPI_Driver's_Guide

http://www.myir-tech.com/bbs/thread-6840-1-1.html
drivers/spi/spi-omap2-mcspi.c
