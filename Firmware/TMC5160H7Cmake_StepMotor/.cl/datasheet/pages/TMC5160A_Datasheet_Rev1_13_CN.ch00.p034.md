# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p34

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 34
www.trinamic.com
4.1.2 每次 SPI 数据报读回时传送的状态位
新的状态信息在每次访问结束时被锁存，并可用于下一次 SPI 传输。
SPI_STATUS –每个 SPI 访问时 39 到 32 位之间的状态标志
位 名称 备注
7 status_stop_r RAMP_STAT[1] – 1:仅限运动控制器模式下，右参考开关停止标志。
6 status_stop_l RAMP_STAT[0] – 1:仅限运动控制器模式下，左参考开关停止标志。
5 position_reached RAMP_STAT[9] – 1: 仅限运动控制器模式下，目标位置到达标志 。
4 velocity_reached RAMP_STAT[8] – 1: 仅限运动控制器模式下，目标速度到达标志。
3 standstill DRV_STATUS[31] – 1:电机静止标志。
2 sg2 DRV_STATUS[24] – 1: StallGuard 标志有效标志。
1 driver_error GSTAT[1] – 1: 驱动器错误指示 (通过 读 GSTAT 清标志)。
0 reset_flag GSTAT[0] – 1: 复位发生指示(通过 读 GSTAT 清标志)。
4.1.3 数据排列
所有数据都是右对齐。寄存器格式包含无符号(正)值，二进制补码的整数值(有符号)，单个位或位
组分别代表单个位或整数组。
4.2 SPI 信号
TMC 5160 上的 SPI 总线有四个信号:
­ SCK -总线时钟输入
­ SDI -串行数据输入
­ SDO -串行数据输出
­ CSN -芯片选择输入(低电平有效)
SPI 芯片选择输入 CSN 上的低电平使能 SPI。位传输与总线时钟 SCK 同步，从设备在 SCK 的上升沿锁
存来自 SDI 的数据，并在下降沿之后驱动数据到 SDO。首先发送最高有效位。一个完整的与 TMC5160 进
行总线传输至少需要 40 个 SCK 时钟周期。
如果驱动的时钟超过 40 个，则内部移位寄存器延迟 40 个时钟后，多余的 SDI 位在 SDO 上被移出。
这可用于多个芯片的菊花链连接。
在整个 SPI 总线通讯期间，CSN 必须为低。当 CSN 变高时，内部移位寄存器的内容被锁存到内部控
制寄存器中，并被识别为从主设备到从设备的命令。如果发送超过 40 位，则只有 CSN 上升沿之前接收
