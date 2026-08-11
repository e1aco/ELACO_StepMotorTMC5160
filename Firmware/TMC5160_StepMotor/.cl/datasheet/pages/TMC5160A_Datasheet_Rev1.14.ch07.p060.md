# TMC5160A_Datasheet_Rev1.14 — 第7章 · p60

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
60 
 
 
 
www.trinamic.com 
7.2 StealthChop Options 
In order to match the motor current to a certain level, the effective PWM voltage becomes scaled 
depending on the actual motor velocity. Several additional factors influence the required voltage level 
to drive the motor at the target current: The motor resistance, its back EMF (i.e. directly proportional 
to its velocity) as well as the actual level of the supply voltage. Two modes of PWM regulation are 
provided: The automatic tuning mode (AT) using current feedback (pwm_autoscale = 1, pwm_autograd 
= 1) and a feed forward velocity-controlled mode (pwm_autoscale = 0). The feed forward velocity-
controlled mode will not react to a change of the supply voltage or to events like a motor stall, but it 
provides very stable amplitude. It does not use nor require any means of current measurement. This 
is perfect when motor type and supply voltage are well known. Therefore, we recommend the 
automatic mode, unless current regulation is not satisfying in the given operating conditions. 
 
It is recommended to use application specific initial tuning parameters, fitting the motor type and 
supply voltage. Additionally, operate in automatic tuning mode in order to respond to parameter 
change, e.g. due to motor heat-up or change of supply voltage. 
Non-automatic mode (pwm_autoscale=0) should be taken into account only with well-known motor 
and operating conditions. In this case, careful programming via the interface is required. The 
operating parameters PWM_GRAD and PWM_OFS can be determined in automatic tuning mode 
initially.  
 
The StealthChop PWM frequency can be chosen in four steps in order to adapt the frequency divider 
to the frequency of the clock source. A setting in the range of 20-50kHz is good for most applications. 
It balances low current ripple and good higher velocity performance vs. dynamic power dissipation.  
 
CHOICE OF PWM FREQUENCY FOR STEALTHCHOP 
Clock frequency 
fCLK 
PWM_FREQ=%00 
fPWM=2/1024 fCLK 
PWM_FREQ=%01  
fPWM=2/683 fCLK 
PWM_FREQ=%10 
fPWM=2/512 fCLK 
PWM_FREQ=%11 
fPWM=2/410 fCLK 
18MHz 
35.2kHz 
52.7kHz  
70.3kHz 
87.8kHz 
16MHz 
31.3kHz 
46.9kHz 
62.5kHz 
78.0kHz 
12MHz (internal) 
23.4kHz 
35.1kHz 
46.9kHz 
58.5kHz 
10MHz 
19.5kHz 
29.3kHz 
39.1kHz 
48.8kHz 
8MHz 
15.6kHz 
23.4kHz 
31.2kHz 
39.0kHz 
Table 7.1 Choice of PWM frequency – green / light green: recommended 
7.3 StealthChop Current Regulator 
In StealthChop voltage PWM mode, the autoscaling function (pwm_autoscale = 1, pwm_auto_grad = 1) 
regulates the motor current to the desired current setting. Automatic scaling is used as part of the 
automatic tuning process (AT), and for subsequent tracking of changes within the motor parameters. 
The driver measures the motor current during the chopper on time and uses a proportional regulator 
to regulate PWM_SCALE_AUTO in order match the motor current to the target current. PWM_REG is the 
proportionality coefficient for this regulator. Basically, the proportionality coefficient should be as 
small as possible in order to get a stable and soft regulation behavior, but it must be large enough to 
allow the driver to quickly react to changes caused by variation of the motor target current (e.g. 
change of VREF). During initial tuning step AT#2, PWM_REG also compensates for the change of motor 
velocity. Therefore, a high acceleration during AT#2 will require a higher setting of PWM_REG. With 
careful selection of homing velocity and acceleration, a minimum setting of the regulation gradient 
often is sufficient (PWM_REG=1). PWM_REG setting should be optimized for the fastest required 
acceleration and deceleration ramp (compare Figure 7.3 and Figure 7.4). The quality of the setting 
PWM_REG in phase AT#2 and the finished automatic tuning procedure (or non-automatic settings for 
PWM_OFS and PWM_GRAD) can be examined when monitoring motor current during an acceleration 
phase Figure 7.5.  


<!-- detected tables -->

|  | CHOICE OF PWM FREQUENCY FOR STEALTHCHOP |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Clock frequency |  |  | PWM FREQ=%00 |  |  | PWM FREQ=%01 |  |  | PWM FREQ=%10 |  |  | PWM FREQ=%11 |  |
|  | f CLK |  |  | _ f =2/1024 f PWM CLK |  |  | _ f =2/683 f PWM CLK |  |  | _ f =2/512 f PWM CLK |  |  | _ f =2/410 f PWM CLK |  |
| 18MHz |  |  |  | 35.2kHz |  | 52.7kHz |  |  | 70.3kHz |  |  | 87.8kHz |  |  |
| 16MHz |  |  |  | 31.3kHz |  |  | 46.9kHz |  | 62.5kHz |  |  | 78.0kHz |  |  |
| 12MHz (internal) |  |  |  | 23.4kHz |  |  | 35.1kHz |  |  | 46.9kHz |  | 58.5kHz |  |  |
| 10MHz |  |  | 19.5kHz |  |  |  | 29.3kHz |  |  | 39.1kHz |  |  | 48.8kHz |  |
| 8MHz |  |  | 15.6kHz |  |  |  | 23.4kHz |  |  | 31.2kHz |  |  | 39.0kHz |  |
