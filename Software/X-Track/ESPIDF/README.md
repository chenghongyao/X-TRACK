# 编译说明
记得下载esp分支
```
git clone -b esp https://github.com/chenghongyao/X-TRACK.git
```

按ESP官方说明装好esp-idf环境,然后在本目录下运行
```BASH
idf.py build
```
上电自动跑地图程序




# 引脚说明
## LCD
 LCD    | ESP32 
--------|-----
 CLK    | GPIO18 
 MOSI   | GPIO23
 CS     | GPIO5 
 DC     | GPIO19
 RESET  | GPIO22 
 BLK    | - 

## SD Card(未测试)

ESP32 pin     | SD card pin | SPI pin | Notes
--------------|-------------|---------|------------
GPIO14 (MTMS) | CLK         | SCK     | 10k pullup in SD mode
GPIO15 (MTDO) | CMD         | MOSI    | 10k pullup, both in SD and SPI modes
GPIO2         | D0          | MISO    | 10k pullup in SD mode, pull low to go into download mode (see Note about GPIO2 below!)
GPIO4         | D1          | N/C     | not used in 1-line SD mode; 10k pullup in 4-line SD mode
GPIO12 (MTDI) | D2          | N/C     | not used in 1-line SD mode; 10k pullup in 4-line SD mode (see Note about GPIO12 below!)
GPIO13 (MTCK) | D3          | CS      | not used in 1-line SD mode, but card's D3 pin must have a 10k pullup
N/C           | CD          |         | optional, not used in the example
N/C           | WP          |         | optional, not used in the example


# TODO
[] 只完成了LCD,SD卡驱动,需要完成其他硬件驱动(`main/HAL/HAL_*.cpp`)
[] ESP32好像对一些未初始化的数据不会清零，导致启动时的数据很大
[] 使用主工程的lvgl组件？

