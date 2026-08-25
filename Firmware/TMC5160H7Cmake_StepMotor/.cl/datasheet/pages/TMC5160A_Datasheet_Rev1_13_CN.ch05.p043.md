# TMC5160A_Datasheet_Rev1_13_CN — 第5章 · p43

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19) 43
www.trinamic.com
通用配置寄存器(0X00…0X0F)
R/W 地址 n 寄存器 描述/ 位 名称
脚的输出极性。其主要目的是将 SDO_CFG 0 作为 NAO 下
一个地址输出信号，用于多个集成电路的链式寻址。
提示:重置值为 1，用作单线链中下一个芯片的 NAO。
W 0x05 32 X_COMPARE
位置比较寄存器用于运动控制器位置探测，位置脉冲输出在引脚
SWP_DIAG1.
XACTUAL = X_COMPARE:
­ 输出信号 PP (位置脉冲)置高，如果和目标位置不等，则
为低电平。
W 0x06 OTP_PROG
位 OTP_PROGRAM – OTP 编程
写操作是对 OTP 存储器设置(一次一位)
读操作是在写操作之后刷新 OTP 的读数据
2..0 OTPBIT
选择要编程到选定字节位置的 OTP 位( n = 0..7 :将位 n 编
程到逻辑 1 )
5..4 OTPBYTE
设置 00
15..8 OTPMAGIC
设置为 0xbd 使能编程。建议编程时间至少为每位 10ms
(通过读取 OTP _ READ 进行检查)。
R 0x07 OTP_READ
位 OTP_READ (访问 OTP 内存结果和更新)
请另见表格！
7..0 OTP0 字节 0 读数据
RW 0x08 5
FACTORY_
CONF
4..0 FCLKTRIM (复位缺省: OTP)
0…31: 最低到最高时钟频率。在电荷泵输出检测。频率
跨度并不保证，但经过测试，调到 12MHz 内部时钟是可
能的。通过 OTP 编程，芯片预设为 12MHz 时钟频率
(复位缺省值: OTP)
W 0x09 19 SHORT_
CONF
位 SHORT_CONF
3..0 S2VS_LEVEL:
低端场效应晶体管的对 VS 的短路电平。检测 LS MOSFET
