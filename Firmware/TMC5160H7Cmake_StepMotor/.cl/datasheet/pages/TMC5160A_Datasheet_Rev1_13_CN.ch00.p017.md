# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p17

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 17
www.trinamic.com
引脚 TQFP QFN 类型 功能
SD_MODE 21 21 DI
模式选择输入。
SD_MODE =0 : 内部斜坡发生器产生步进信号。
SD_MODE = 1 : STEP / DIR 输入引脚控制驱动器
SD _ MODE = 0 和 SPI _ MODE = 0 使能 UART 操作。
SPI_MODE 22 22 DI
(pd)
模式选择脚。
SPI_MODE =0 : 芯片为独立模式，引脚为 CFG 功能脚。
SPI_MODE = 1 :使能 SPI 接口 。
内部集成下拉电阻。
ENCB_DCEN_
CFG4 23 23
DI
(pd)
SD_MOD=0：内部斜坡发生器模式下的编码器 B 通道输入脚。
SD _ MODE = 1，SPI_MODE = 1 : DcStep 使能输入脚 。如果不需
要使能 DcStep， 将该引脚开路或者接到地, 以确保正常工作。
SPI_MODE=0：CFG 配置引脚。
ENCA_DCIN_
CFG5 24 24
DI
(pd)
SD_MODE=0：内部斜坡发生器模式下的编码器 A 通道输入脚。
SD _MODE =1，SPI_MODE = 1 : DcStep 信号，用于同步控制。
SPI_MODE=0：CFG 配置引脚。
ENCN_DCO_
CFG6
25 26 DIO
SD_MODE =0 : 编码器 N 信号输入脚。
SD_MOD = 1：DcStep 就绪输出信号。
SD_MODE=0，如果不接编码器，将该信号拉高或者接地。
DIAG0_SWN 26 27
DIO
(pu+
pd)
诊断输出信号 DIAG0。
SD_MODE=0, SPI_MODE=1：内部斜坡发生器模式下的中断输出
或步进输出。在漏极开路模式下，使用 47k 或更小的外部上拉
电阻。
SD_MODE=0 , SPI_MODE=0： 单线 I / O 通讯的负端信号
DIAG1_SWP 27 28
DIO
(pd)
诊断输出信号 DIAG1。
SD_MODE=0, SPI_MODE=1：内部斜坡发生器模式下的位置比较
输出或方向输出。在漏极开路模式下，使用 47k 或更小的外部
上拉电阻
SD_MODE=0 , SPI_MODE=0： 单线 I / O 通讯的正端信号
DRV_ENN 28 29 DI 使能输入。当该引脚被驱动到高电平时，功率 MOSFET 输出关
闭(所有电机输出为悬浮（FLOATING）状态)。
