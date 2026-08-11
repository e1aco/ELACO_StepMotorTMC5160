# TMC5160A_Datasheet_Rev1_13_CN — 第21章 入门

--- [PAGE 160] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
160
www.trinamic.com
21. 入门
请参考tmc5160 评估板, 快速入门, 还可以用应用程序配置调整。正确设置所有寄存器的过程在20
章节介绍。
21.1 初始化例程
以下SPI 数据示例支持步进和方向模式, 12mhz 时钟，配置小于30 rpm 运行StealthChop 及大于30
rpm 运行spreadCycle 的斩波器参数。
SPI 发送: 0xEC000100C3;
// CHOPCONF: TOFF=3, HSTRT=4, HEND=1, TBL=2, CHM=0 (spreadCycle)
SPI 发送: 0x9000061F0A;
// IHOLD_IRUN: IHOLD=10, IRUN=31 (最大电流), IHOLDDELAY=6
SPI 发送: 0x910000000A;
// TPOWERDOWN=10: 电机静止到电流减小之间的延时
SPI 发送: 0x8000000004;
// EN_PWM_MODE=1 enables StealthChop (缺省PWM_CONF 值)
SPI 发送: 0x93000001F4;
// TPWM_THRS=500 对应切换速度35000 = ca. 30RPM
以下SPI 数据示例使能并初始化运动控制器，内部斜坡发生器控制电机运行一圈（51200微步），最
后查询读取当前位置。
SPI 发送: 0xA4000003E8;
// A1
= 1 000 第一阶段加速度
SPI 发送: 0xA50000C350;
// V1
= 50 000 加速度阈值速度V1
SPI 发送: 0xA6000001F4;
// AMAX
= 500 大于V1 的加速度
SPI 发送: 0xA700030D40;
// VMAX
= 200 000
SPI 发送: 0xA8000002BC;
// DMAX
= 700 大于V1 的减速度
SPI 发送: 0xAA00000578;
// D1
= 1400 小于V1 的减速度
SPI 发送: 0xAB0000000A;
// VSTOP
= 10 停止速度(接近于0)
SPI 发送: 0xA000000000;
// RAMPMODE = 0 (目标位置运动)
// 电机就绪!
SPI 发送: 0xADFFFF3800;
// XTARGET = -51200 (向左运动一圈(200*256 微步)
// 现在电机1 开始旋转

