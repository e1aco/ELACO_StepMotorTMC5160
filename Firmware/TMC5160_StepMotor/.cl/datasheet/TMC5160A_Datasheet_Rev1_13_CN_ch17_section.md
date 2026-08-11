# TMC5160A_Datasheet_Rev1_13_CN — 第17章 紧急停止

--- [PAGE 146] ---
TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
146
www.trinamic.com
17. 紧急停止
驱动器低有效ENN 使能引脚以安全关闭所有功率MOSFET，并可设置电机为空转状态。该ENN
引脚实现非软件所需的紧急停止功能。一些应用可能要求驱动器静止情况下有保持电流或处于被动制动
模式的状态。可配置引脚ENCA_DCIN 禁用步进输入信号。设置GCONF 标志stop_enable 使能此选项。每
当ENCA_DCIN 被拉高，电机将根据设置的静止IHOLD、IHOLDDELAY 和StealthChop 进入电流降低状态。
ENN 禁用驱动器将需要三个时钟周期来安全地关闭驱动器。

