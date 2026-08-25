# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p16

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 16
www.trinamic.com
引脚 TQFP QFN 类型 功能
SRAL 7 8 AI A 相采样电阻的地。直接连到采样电阻的地，以补偿地互连上
的电压降。
SRAH 8 9 AI
A 相采样电阻。连到采样电阻的上侧。对于高电机电流，开尔
文连接是优选的。可在 SRAL 和 SRAH 设计对称 RC 滤波，以消
除来自其他驱动器或线圈 B 开关的高频开关尖峰。
SRBH 9 10 AI
B 相采样电阻。连到采样电阻的上侧。对于高电机电流，开尔文
连接是优选的。可在 SRBL 和 SRBH 设计对称 RC 滤波，以消除来
自其他驱动器或线圈 A 开关的高频开关尖峰。
SRBL 10 11 AI B 相采样电阻的地。直接连到采样电阻的地，以补偿地之间互连
上的电压降。
TST_MODE 11 12 DI 测试模式输入。尽量短的连接到地。
CLK 12 13 DI 时钟输入。如果用内部时钟，请尽量短的连接到地。或者连接
外部时钟。内含时钟故障切换电路防止外部时钟信号丢失。
CSN_CFG3 13 14 DI
SPI_MODE=1： SPI 片选信号(低有效)。
SPI_MODE=0： 配置输入脚。
SCK_CFG2 14 15 DI
SPI_MODE=1： SPI 时钟信号。
SPI_MODE=0： 配置输入脚。
SDI_CFG1 15 16 DI
SPI_MODE=1： SPI 数据输入信号。
SPI_MODE=0： 配置输入脚 或
单线接口的下一个地址输入( NAI )。
SDO_CFG0 16 17 DIO
SPI_MODE=1： SPI 数据输出信号 。
SPI_MODE=0： 配置输入 或
单线接口的下一个地址输出( NAO )。
REFL_STEP 17 18 DI
SD_MODE = 0 : 左参考输入(用于内部斜坡发生器)。
SD_MODE = 1 : 步进信号输入。
REFR_DIR 18 19 DI
SD_MODE = 0 : 右参考输入(用于内部斜坡发生器)。
SD_MODE = 1 : 方向信号输入。
GNDD 19,
30
25,
Pad 数字地。连接到引脚附近的地平面。
VCC_IO 20 20 所有数字口 IO 的供电电压，3.3V 到 5V。
