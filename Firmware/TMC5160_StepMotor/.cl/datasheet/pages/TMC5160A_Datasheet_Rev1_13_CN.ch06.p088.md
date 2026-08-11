# TMC5160A_Datasheet_Rev1_13_CN — 第6章 · p88

TMC5160 DATASHEET (Rev. 1.08 / 2018-NOV-19)
88
www.trinamic.com
图6.5 成功确定了PWM_GRAD ( _AUTO)和PWM_OFS ( _AUTO)
快速启动
有关快速启动的信息，请参阅第20 章中的快速配置指南。
6.3.1 电流下限
StealthChop 电流调节过程需要一个最小电流值保证电机电流调节。StealthChop 电流调节只能在斩
波开通阶段通过采样电阻测量线圈电流，因此允许线圈电流调节的最小电流由TBL设置的消隐时间及斩
波频率决定。在StealthChop 电流自定标模式下，电机线圈的最小电流随电机供电电压和斩波频率增加
而增加。较低的消隐时间允许较低的电流最小值。在AT# 1中，PWM_OFS_AUTO非常重要，能控制由采
样电阻、GLOBALSCALER 和IRUN设置的运行电流很好地在调节范围内。更低的电流（例如静止态的自动
降电流）是通过自动定标模式下的PWM_OFS_AUTO和PWM_GRAD_AUTO参数或者是非自动定标模式下的
PWM _ OFS和PWM _ GRAD参数自动实现。空转选项允许电机电流为零。
StealthChop 2参数自调整中的电机线圈电流下限:
ܫܮ�mSݎܮ݅݉݅
ݐൌݐܤܮܣܭܣכ݂ܹܲ
ܯכܸ
ܯܴ
ܥܱܫܮ
VM-电机供电电压，RCOIL – 电机线圈电阻
ILower Limit可以看成是IRUN最小运行电流（拇指值）,如果电流最小值不足以达到所需设置，则芯片在
AT#1中且仅在AT#1中切换成较低斩波频率重试。

