# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p40

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
40
www.trinamic.com
通用配置寄存器(0X00…0X0F)
R/W
地址
n
寄存器
描述/ 位名称
1:
使能DIAG0 输出步进STEP 信号(半频，双边缘触
发)，可控制外部STEP/DIR 驱动器
8
diag1_stall (SD_MODE=1)
1:
使能DIAG1 输出电机堵转信号(在使用此功能之前
设置TCOOLTHRS)
diag1_dir (SD_MODE=0)
0:
DIAG1 输出位置比较信号
1:
使能DIAG1 输出方向DIR 信号，可控制外部
STEP/DIR 驱动器
9
diag1_index (仅在SD_MODE=1)
1:
使能DIAG1 输出索引位置信号(微步查找表0 位
置)
10
diag1_onstate (仅在SD_MODE=1)
1:
使能DIAG1 输出斩波器导通阶段指示信号(线圈全
步的第二部分)
11
diag1_steps_skipped (仅在SD_MODE=1)
1:使能DIAG1 在DcStep 模式下失步时翻转输出信号
(LOST_STEPS 增加)。不要与其他DIAG1 选项一起使
能
12
diag0_int_pushpull
0:
SWN_DIAG0 集电极开路输出(低电平有效)
1:
SWN_DIAG0 推挽输出(高电平有效)
13
diag1_poscomp_pushpull
0:
SWP_DIAG1 集电极开路输出(低电平有效)
1:
SWP_DIAG1 推挽输出(高电平有效)
14
small_hysteresis
0:
步进step 频率的比较磁滞是1 / 16
1:
步进step 频率的比较磁滞是1/32
15
stop_enable
0:
正常操作
1:
紧急停止: ENCA_DCIN 在高电平时停止定序器(定序


<!-- detected tables -->

| 通用配置寄存器(0X00…0X0F) |  |  |  |  |  |
|---|---|---|---|---|---|
| R/W | 地址 | n | 寄存器 | 描述/ 位名称 |  |
|  |  |  |  |  | 1: 使能 DIAG0 输出步进 STEP 信号(半频，双边缘触 发)，可控制外部STEP/DIR 驱动器 |
|  |  |  |  | 8 | diag1 stall (SD MODE=1) _ _ 1: 使能DIAG1 输出电机堵转信号(在使用此功能之前 设置TCOOLTHRS) diag1 dir (SD MODE=0) _ _ 0: DIAG1 输出位置比较信号 1: 使能 DIAG1 输出方向 DIR 信号，可控制外部 STEP/DIR 驱动器 |
|  |  |  |  | 9 | diag1 index (仅在SD MODE=1) _ _ 1: 使能 DIAG1 输出 索引位置信号 (微步查找表 0 位 置) |
|  |  |  |  | 10 | diag1 onstate (仅在SD MODE=1) _ _ 1: 使能DIAG1 输出斩波器导通阶段指示信号(线圈全 步的第二部分) |
|  |  |  |  | 11 | diag1 steps skipped (仅在SD MODE=1) _ _ _ 1:使能 DIAG1 在 DcStep 模式下失步时翻转输出信号 (LOST STEPS 增加)。不要与其他DIAG1 选项一起使 _ 能 |
|  |  |  |  | 12 | diag0 int pushpull _ _ 0: SWN DIAG0 集电极开路输出(低电平有效) _ 1: SWN DIAG0 推挽输出(高电平有效) _ |
|  |  |  |  | 13 | diag1 poscomp pushpull _ _ 0: SWP DIAG1 集电极开路输出(低电平有效) _ 1: SWP DIAG1 推挽输出(高电平有效) _ |
|  |  |  |  | 14 | small hysteresis _ 0: 步进step 频率的比较磁滞是1 / 16 1: 步进step 频率的比较磁滞是1/32 |
|  |  |  |  | 15 | stop enable _ 0: 正常操作 1: 紧急停止: ENCA DCIN 在高电平时停止定序器(定序 _ |
