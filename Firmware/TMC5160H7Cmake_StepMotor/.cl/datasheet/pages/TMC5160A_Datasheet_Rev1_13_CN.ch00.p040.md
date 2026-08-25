# TMC5160A_Datasheet_Rev1_13_CN — 第0章 · p40

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 40
www.trinamic.com
通用配置寄存器(0X00…0X0F)
R/W 地址 n 寄存器 描述/ 位 名称
1: 使能 DIAG0 输出步进 STEP 信号(半频，双边缘触
发)，可控制外部 STEP/DIR 驱动器
8 diag1_stall (SD_MODE=1)
1: 使能 DIAG1 输出电机堵转信号 (在使用此功能之前
设置 TCOOLTHRS)
diag1_dir (SD_MODE=0)
0: DIAG1 输出位置比较信号
1: 使 能 DIAG1 输 出 方 向 DIR 信 号 ， 可 控 制 外 部
STEP/DIR 驱动器
9 diag1_index (仅在 SD_MODE=1)
1: 使能 DIAG1 输出 索引位置信号 (微步查找表 0 位
置)
10 diag1_onstate (仅在 SD_MODE=1)
1: 使能 DIAG1 输出斩波器导通阶段指示信号(线圈全
步的第二部分)
11 diag1_steps_skipped (仅在 SD_MODE=1)
1: 使 能 DIAG1 在 DcStep 模 式 下 失 步 时 翻 转 输 出 信 号
(LOST_STEPS 增加)。不要与其他 DIAG1 选项一起使
能
12 diag0_int_pushpull
0: SWN_DIAG0 集电极开路输出(低电平有效)
1: SWN_DIAG0 推挽输出(高电平有效)
13 diag1_poscomp_pushpull
0: SWP_DIAG1 集电极开路输出(低电平有效)
1: SWP_DIAG1 推挽输出(高电平有效)
14 small_hysteresis
0: 步进 step 频率的比较磁滞是 1 / 16
1: 步进 step 频率的比较磁滞是 1/32
15 stop_enable
0: 正常操作
1: 紧急停止: ENCA_DCIN 在高电平时停止定序器(定序
