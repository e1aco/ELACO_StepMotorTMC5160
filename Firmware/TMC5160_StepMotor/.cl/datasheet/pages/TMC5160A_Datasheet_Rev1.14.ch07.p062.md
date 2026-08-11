# TMC5160A_Datasheet_Rev1.14 — 第7章 · p62

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
62 
 
 
 
www.trinamic.com 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
 
7.3.1 
Lower Current Limit 
The StealthChop current regulator imposes a lower limit for motor current regulation. As the coil 
current can be measured in the shunt resistor during chopper on phase only, a minimum chopper 
duty cycle allowing coil current regulation is given by the blank time as set by TBL and by the 
chopper frequency setting. Therefore, the motor specific minimum coil current in StealthChop 
autoscaling mode rises with the supply voltage and with the chopper frequency. A lower blanking 
time allows a lower current limit. It is important for the correct determination of PWM_OFS_AUTO, 
that in AT#1 the run current set by the sense resistor, GLOBALSCALER and IRUN is well within the 
regulation range. Lower currents (e.g. for standstill power down) are automatically realized based on 
PWM_OFS_AUTO and PWM_GRAD_AUTO respectively based on PWM_OFS and PWM_GRAD with non-
automatic current scaling. The freewheeling option allows going to zero motor current.  
 
Lower motor coil current limit for StealthChop2 automatic tuning: 
 
𝐼𝐿𝑜𝑤𝑒𝑟 𝐿𝑖𝑚𝑖𝑡= 𝑡𝐵𝐿𝐴𝑁𝐾∗𝑓𝑃𝑊𝑀∗𝑉𝑀
𝑅𝐶𝑂𝐼𝐿
 
 
With VM the motor supply voltage and RCOIL the motor coil resistance. 
ILower Limit can be treated as a thumb value for the minimum nominal IRUN motor current setting. In 
case the lower current limit is not sufficient to reach the desired setting, the driver will retry with a 
lower chopper frequency in step AT#1, only. 
fPWM is the chopper frequency as determined by setting PWM_FREQ. In AT#1, the driver tries a lower, 
(roughly half frequency), in case it cannot reach the current. The frequency will remain active in 
standstill, while currentscale CS=IRUN. With automatic standstill reduction, this is a short moment. 
 
EXAMPLE: 
 
A motor has a coil resistance of 5Ω, the supply voltage is 24V. With TBL=%01 and PWM_FREQ=%00, 
tBLANK is 24 clock cycles, fPWM is 2/(1024 clock cycles): 
 
𝐼𝐿𝑜𝑤𝑒𝑟 𝐿𝑖𝑚𝑖𝑡= 24 𝑡𝐶𝐿𝐾∗
2
1024 𝑡𝐶𝐿𝐾
∗24𝑉
5Ω= 24
512 ∗24𝑉
5Ω= 225𝑚𝐴 
 
This means, the motor target current for automatic tuning must be 225mA or more, taking into 
account all relevant settings. This lower current limit also applies for modification of the motor 
current via the GLOBALSCALER. 
 
Attention  
For automatic tuning, a lower coil current limit applies. The motor current in automatic tuning phase 
AT#1 must exceed this lower limit. ILOWER LIMIT can be calculated or measured using a current probe. 
Setting the motor run-current or hold-current below the lower current limit during operation by 
modifying IRUN and IHOLD is possible after successful automatic tuning.  
 
The lower current limit also limits the capability of the driver to respond to changes of 
GLOBALSCALER.  
 
 
 

