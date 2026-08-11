# TMC5160A_Datasheet_Rev1_13_CN — 第22章 独立操作模式

--- [PAGE 161] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
161
www.trinamic.com
SPI send: 0x2100000000;
// 查询XACTUAL – 下一个读操作返回XACTUAL
SPI read;
// 读XACTUAL
对于基于UART 的操作, 确保CRC 字节是正确的是很重要的。下面的示例演示具有从属地址1 (NAI 引脚高)
的驱动程序的初始化。配置驱动斩波模式为spreadCycle, 并对运动控制器进行恒定速度移动控制, 最后读
取位置和实际速度寄存器:
UART write: 0x05 0x01 0xEC 0x00 0x01 0x00 0xC5 0xD3;
// TOFF=5, HEND=1, HSTR=4,
// TBL=2, MRES=0, CHM=0
UART write: 0x05 0x01 0x90 0x00 0x01 0x14 0x05 0xD8;
// IHOLD=5, IRUN=20, IHOLDDELAY=1
UART write: 0x05 0x01 0xA6 0x00 0x00 0x13 0x88 0xB4;
// AMAX=5000
UART write: 0x05 0x01 0xA7 0x00 0x00 0x4E 0x20 0x85;
// VMAX=20000
UART write: 0x05 0x01 0xA0 0x00 0x00 0x00 0x01 0xA3;
// RAMPMODE=1 (正速度)
// 现在电机旋转
UART write: 0x05 0x01 0x21 0x6B;
// Query XACTUAL
UART read 8 bytes;
UART write: 0x05 0x01 0x22 0x25;
// Query VACTUAL
UART read 8 bytes;
提示
根据电机和应用配置参数, 以获得最佳性能。
22. 独立操作模式
独立操作模式下，TMC5160 无需通过SPI 配置内部寄存器，所有尾缀有CFG0 到CFG6 的引脚有特殊
定义，能被拉高或者接地。

--- [PAGE 162] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
162
www.trinamic.com
图22.1 TMC5160 (以独立模式名称显示的引脚)工作模式
SPI_MODE 引脚接地GND 且SD_MODE 引脚拉高使能独立模式。该模式下，驱动器是一个纯步进和
方向驱动器。SPI 和单线通讯接口关闭, 驱动器工作在spreadCycle 模式或者StealthChop 模式。

--- [PAGE 163] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
163
www.trinamic.com
以下设置受CFG 引脚的影响, 以确保正确的配置:
CFG0/CFG1: STEP 输入的细分配置
CFG1
CFG0
细分设置
GND
GND
8 微步, MRES=5
GND
VCC_IO
16 微步, MRES=4
VCC_IO
GND
32 微步, MRES=3
VCC_IO
VCC_IO
64 微步, MRES=2
CFG4/CFG3/CFG2: 运行电流配置
CFG4
CFG3
CFG2
IRUN 设置
GND
GND
GND
IRUN=16
GND
GND
VCC_IO
IRUN=18
GND
VCC_IO
GND
IRUN=20
GND
VCC_IO
VCC_IO
IRUN=22
VCC_IO
GND
GND
IRUN=24
VCC_IO
GND
VCC_IO
IRUN=26
VCC_IO
VCC_IO
GND
IRUN=28
VCC_IO
VCC_IO
VCC_IO
IRUN=31


<!-- detected tables -->

| CFG0/CFG1: STEP 输入的细分配置 |  |  |
|---|---|---|
| CFG1 | CFG0 | 细分设置 |
| GND | GND | 8 微步, MRES=5 |
| GND | VCC IO _ | 16 微步, MRES=4 |
| VCC IO _ | GND | 32 微步, MRES=3 |
| VCC IO _ | VCC IO _ | 64 微步, MRES=2 |

| CFG4/CFG3/CFG2: 运行电流配置 |  |  |  |
|---|---|---|---|
| CFG4 | CFG3 | CFG2 | IRUN 设置 |
| GND | GND | GND | IRUN=16 |
| GND | GND | VCC IO _ | IRUN=18 |
| GND | VCC IO _ | GND | IRUN=20 |
| GND | VCC IO _ | VCC IO _ | IRUN=22 |
| VCC IO _ | GND | GND | IRUN=24 |
| VCC IO _ | GND | VCC IO _ | IRUN=26 |
| VCC IO _ | VCC IO _ | GND | IRUN=28 |
| VCC IO _ | VCC IO _ | VCC IO _ | IRUN=31 |
--- [PAGE 164] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
164
www.trinamic.com
CFG5: 斩波模式选择
CFG5
斩波器设置
GND
SpreadCycle 操作. (TOFF=3)
VCC_IO
StealthChop 操作. (GCONF.en_PWM_mode=1)
CFG6:保持电流配置
CFG6*)
斩波器设置
GND
保持电流不减小。IHOLD=IRUN
VCC_IO
50%. IHOLD=1/2 IRUN
提示
StealthChop 使能前，请确保电机保持至少100 毫秒复位(假设fCLK 最小为10MHz)。用于驱动器调节
电流设置电机的初始电流。
*) CFG6: 注意
CFG6 引脚电平与CFG5 不同时会产生电流(20mA), 因为输出驱动器试图使CFG6 电平等于CFG5。
因此, 需要一个0 欧姆电阻来拉低/高CFG6。建议仅在外部VCC_IO 电源在3.3 v 情况下CFG6 与CFG5 电
平值不同。
注意：
默认情况下，不会配置DIAG 输出。在切换到独立模式之前，可以用接口使能它们。


<!-- detected tables -->

| CFG5: 斩波模式选择 |  |
|---|---|
| CFG5 | 斩波器设置 |
| GND | SpreadCycle 操作. (TOFF=3) |
| VCC IO _ | StealthChop 操作. (GCONF.en PWM mode=1) _ _ |

| CFG6:保持电流配置 |  |
|---|---|
| CFG6*) | 斩波器设置 |
| GND | 保持电流不减小。 IHOLD=IRUN |
| VCC IO _ | 50%. IHOLD=1/2 IRUN |
