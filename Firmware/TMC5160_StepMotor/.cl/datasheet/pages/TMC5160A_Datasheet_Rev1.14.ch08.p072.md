# TMC5160A_Datasheet_Rev1.14 — 第8章 · p72

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
72 
 
 
 
www.trinamic.com 
8.2 Classic Constant Off Time Chopper 
The classic constant off time chopper is an alternative to SpreadCycle. Perfectly tuned, it also gives 
good results. Also, the classic constant off time chopper (automatically) is used in combination with 
fullstepping in DcStep operation. 
 
The classic constant off-time chopper uses a fixed-time fast decay following each on phase. While the 
duration of the on phase is determined by the chopper comparator, the fast decay time needs to be 
long enough for the driver to follow the falling slope of the sine wave, but it should not be so long 
that it causes excess motor current ripple and power dissipation. This can be tuned using an 
oscilloscope or evaluating motor smoothness at different velocities. A good starting value is a fast 
decay time setting similar to the slow decay time setting. 
t
I
mean value = target current
target current + offset
on
sd
fd
sd
on
fd
 
Figure 8.4 Classic const. off time chopper with offset showing coil current 
 
After tuning the fast decay time, the offset should be tuned for a smooth zero crossing. This is 
necessary because the fast decay phase makes the absolute value of the motor current lower than the 
target current (see Figure 8.5). If the zero offset is too low, the motor stands still for a short moment 
during current zero crossing. If it is set too high, it makes a larger microstep. Typically, a positive 
offset setting is required for smoothest operation. 
 
t
I
Target current
Coil current
t
I
Target current
Coil current
Coil current does not have optimum shape
Target current corrected for optimum shape of coil current
 
Figure 8.5 Zero crossing with classic chopper and correction using sine wave offset 
Three parameters control constant off-time mode: 
 


<!-- detected tables -->

| on fd sd on fd sd t |  |  |  |  |
|---|---|---|---|---|
|  |  |  |  |  |
|  |  |  |  |  |
| on | fd | sd | on | fd |
