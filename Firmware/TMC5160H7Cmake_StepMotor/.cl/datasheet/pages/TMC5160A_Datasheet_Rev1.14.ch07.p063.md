# TMC5160A_Datasheet_Rev1.14 — 第7章 · p63

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  63 
 
 
 
www.trinamic.com 
7.4 Velocity Based Scaling 
Velocity based scaling scales the StealthChop amplitude based on the time between each two steps, 
i.e. based on TSTEP, measured in clock cycles . This concept basically does not require a curren t 
measurement, because no regulation loop is necessary. A pure velocit y-based scaling is available via 
programming, only, when setting pwm_autoscale = 0. The basic idea is to have a linear approximation 
of the voltage required to drive the target current into the motor. The stepper motor has a certain coil 
resistance and thu s needs a certain voltage amplitude to yield a target current based on the basic 
formula I=U/R. With R being the coil resistance, U the supply voltage scaled by the PWM value, the 
current I results. The initial value for PWM_OFS can be calculated: 
 
𝑃𝑊𝑀_𝑂𝐹𝑆 = 374 ∗ 𝑅𝐶𝑂𝐼𝐿 ∗ 𝐼𝐶𝑂𝐼𝐿
𝑉𝑀
 
 
With VM the motor supply voltage and ICOIL the target RMS current 
 
The effective PWM voltage U PWM (1/SQRT(2) x peak value) results considering the 8 bit resolution and 
248 sine wave peak for the actual PWM amplitude shown as PWM_SCALE: 
 
𝑈𝑃𝑊𝑀 = 𝑉𝑀 ∗ 𝑃𝑊𝑀_𝑆𝐶𝐴𝐿𝐸
256 ∗ 248
256 ∗ 1
√2
= 𝑉𝑀 ∗ 𝑃𝑊𝑀_𝑆𝐶𝐴𝐿𝐸
374  
 
 
With rising motor velocity, the motor generates an increasing back EMF voltage. The back EMF voltage 
is proportional to t he motor velocity. It reduces the PWM voltage effective at the coil resistance and 
thus current decreases. The TMC 5160 provides a second velocity dependent factor ( PWM_GRAD) to 
compensate for this. The overall effective PWM amplitude ( PWM_SCALE_SUM) in thi s mode 
automatically is calculated in dependence of the microstep frequency as: 
 
𝑃𝑊𝑀_𝑆𝐶𝐴𝐿𝐸_𝑆𝑈𝑀 = 𝑃𝑊𝑀_𝑂𝐹𝑆 + 𝑃𝑊𝑀_𝐺𝑅𝐴𝐷 ∗ 256 ∗ 𝑓𝑆𝑇𝐸𝑃
𝑓𝐶𝐿𝐾
  
With fSTEP being the microstep frequency for 256 microstep resolution equivalent 
and fCLK the clock frequency supplied to the driver or the actual internal frequency 
 
As a first approximation, the back EMF subtracts from the supply voltage and thus the effective current 
amplitude decreases. This way, a first approximation for PWM_GRAD setting can be calculated: 
 
𝑃𝑊𝑀_𝐺𝑅𝐴𝐷 = 𝐶𝐵𝐸𝑀𝐹 [ 𝑉
𝑟𝑎𝑑
𝑠
] ∗ 2𝜋 ∗ 𝑓𝐶𝐿𝐾 ∗ 1.46
𝑉𝑀 ∗ 𝑀𝑆𝑃𝑅 
 
CBEMF is the back EMF constant of the motor in Volts per radian/second. 
MSPR is the number of microsteps per rotation, e.g. 51200 = 256µsteps multiplied by 200 fullste ps for 
a 1.8° motor. 
 
