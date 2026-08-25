# TMC5160A_Datasheet_Rev1.14 — 第8章 8 SpreadCycle and Classic Chopper

--- [PAGE 68] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  68 
 
 
 
www.trinamic.com 
8 SpreadCycle and Classic Chopper 
While StealthChop is a voltage mode  PWM controlled chopper, SpreadCycle is a cycle-by-cycle current 
control. Therefore, it can react extremely fast to changes in motor velocity or motor load. The currents 
through both motor coils are controlled using choppers. The choppers work independently of each 
other. In Figure 8.1 the different chopper phases are shown.  
RSENSE
ICOIL
On Phase: 
current flows in 
direction of target 
current
RSENSE
ICOIL
Fast Decay Phase: 
current flows in 
opposite direction 
of target current
RSENSE
ICOIL
Slow Decay Phase: 
current re-circulation
+VM +VM +VM
 
Figure 8.1 Chopper phases 
Although the current could be regulated using only on phases and fast decay phases , insertion of the 
slow decay phase is important to reduce electrical losses and current ripple in the motor. The 
duration of the slow decay phase is specified in a control parameter and sets an upper limit on the 
chopper frequency. The current comparator can measure coil current during phases when the current 
flows through the sense resistor, but not during the slow decay phase, so the slow decay phase is 
terminated by a timer. The on phase is terminat ed by the comparator when the current through the 
coil reaches the target current. The fast decay phase may be terminated by either the comparator or 
another timer. 
When the coil current is switched, spikes at the sense resistors occur due to charging and discharging 
parasitic capacitances. During this time, t ypically one or two microseconds, the current cannot be 
measured. Blanking is the time when the input to the comparator is masked to block these spikes.  
There are two cycle-by-cycle chopper modes avail able: a new high -performance chopper algorithm 
called SpreadCycle and a proven constant off -time chopper mode. The constant off -time mode cycles 
through three phases: on, fast decay, and slow decay. The SpreadCycle mode cycles through four 
phases: on, slow decay, fast decay, and a second slow decay. 
The chopper frequency is an important parameter for a chopped motor driver. A too low frequency 
might generate audible noise. A higher frequency reduces current ripple in the motor, but with a too 
high frequency magnetic losses may rise. Also power dissipation in th e driver rises with increasing 
frequency due to the increased influence of switching slopes causing dynamic dissipation. Therefore, a 
compromise needs to be found. Most motors are optimally working in a frequency range of 16 kHz to 
30 kHz. The chopper freq uency is influenced by a number of parameter settings as well as by the 
motor inductivity and supply voltage.  
 
Hint 
A chopper frequency in the range of 16 kHz to 30 kHz gives a good result for most motors when 
using SpreadCycle. A higher frequency leads to increased switching losses.  
 
  
--- [PAGE 69] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  69 
 
 
 
www.trinamic.com 
Three parameters are used for controlling both chopper modes: 
8.1 SpreadCycle Chopper 
The SpreadCycle (patented) chopper algorithm is a precise and simple to use chopper mode which 
automatically determines the optimum length for the fast -decay phase. The SpreadCycle will provide 
superior microstepping quality even with default s ettings. Se veral parameters are avail able to 
optimize the chopper to the application. 
 
Each chopper cycle is comprised of an on phase, a slow decay phase, a fast decay phase and a 
second slow decay phase (see Figure 8.3). The two slow decay phases and the two blank times per 
chopper cycle put an upper limit to the chopper frequency. The slow decay phases typically make up 
for about 30%-70% of the chopper cycle  in standstill and are important for low motor  and driver 
power dissipation.  
 
Calculation of a starting value for the slow decay time TOFF: 
 
EXAMPLE:  
 
Target Chopper frequency: 25kHz.  
Assumption: Two slow decay cycles make up for 50% of overall chopper cycle time 
 
𝑡𝑂𝐹𝐹 = 1
25𝑘𝐻𝑧 ∗ 50
100 ∗ 1
2 = 10µ𝑠 
For the TOFF setting this means: 
𝑇𝑂𝐹𝐹 = (𝑡𝑂𝐹𝐹 ∗ 𝑓𝐶𝐿𝐾 − 12)/32 
 
With 12 MHz clock this gives a setting of TOFF=3.0, i.e. 3.  
With 16 MHz clock this gives a setting of TOFF=4.25, i.e. 4 or 5.  
 
The hysteresis start setting forc es the driver to i ntroduce a minimum amount of current ripple into 
the motor coils. The current ripple must be higher than the current ripple which is caused by resistive 
losses in the motor in order to give best microstepping res ults. This will allow the chopper to 
precisely regulate the current both for rising and for falling target current. The time required to 
introduce the current ripple into the motor coil also reduces  the chopper frequency . Therefore, a 
higher hysteresis set ting will lead to a lower chopper frequency.  The motor inductance limits the 
Parameter Description Setting Comment 
TOFF Sets the slow decay time ( off time ). This setting also 
limits the maximum chopper frequency. 
 
For operation with StealthChop, this parameter is not 
used, but it is required to enable the motor. In case of 
operation with StealthChop only, any setting is OK. 
 
Setting this param eter to zero completely disables all 
driver transistors and the motor can free-wheel. 
0 chopper off 
1…15  off time setting  
NCLK= 24 + 32*TOFF 
(1 will work with minimum 
blank time of 24 clocks) 
TBL Selects the comparator blank time. This time needs to 
safely cover the switching event and the duration of the 
ringing on the sense resistor. For most  applications, a 
setting of 1 or 2 is good. For highly capacitive loads, 
e.g. when filter networks are used, a setting of 2 or 3 
will be required. 
0 16 tCLK 
1 24 tCLK 
2 36 tCLK 
3 54 tCLK 
chm Selection of the chopper mode 0 SpreadCycle 
1 classic const. off time 
TPFD Adds passive fast decay  time after bridge polarity 
change. Starting from 0, increase value, in case the 
motor suffers from mid-range resonances.  
0…15 
Fast decay time in multiple 
of 128 clocks (128 clocks 
are roughly 10µs) 
--- [PAGE 70] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  70 
 
 
 
www.trinamic.com 
ability of the chopper to follow a changing motor current. Further the duration of the on phase and 
the fast decay must be longer than the blanking time, because the current compa rator is disabled 
during blanking.  
 
It is easiest to find the best setting by starting from a low hysteresis setting (e.g. HSTRT=0, HEND=0) 
and increasing HSTRT, until the motor runs smooth ly at low velocity settings . This can best be 
checked when measuri ng the motor current either with a current p robe or by probing the sense 
resistor voltages (see Figure 8.2). Checking the sine wave shape near zero transition will show a small 
ledge between both half waves in case the hysteresis setting is too small . At medium velocities  (i.e. 
100 to 400 fullsteps per second) , a too low hysteresis setting will lead to increased humming and 
vibration of the motor.  
 
 
Figure 8.2 No ledges in current w ave with sufficient hysteresis (magenta: current A, yellow & 
blue: sense resistor voltages A and B) 
A too high hysteresis setting will lead to reduced chopper frequency and increased chopper noise but 
will not yield any benefit for the wave shape. 
 
Quick Start 
For a quick start, see the Quick Configuration Guide in chapter 22. 
For detail procedure see Application Note AN001 - Parameterization of SpreadCycle 
 
As experiments show, the setting is quite independent of the motor, bec ause higher current motors 
typically also have a lower coil resistance. Therefore choosing a low to medium default value for the 
hysteresis (for example, effective hysteresis = 4) normally fits most applications. The setting can be 
optimized by experimenti ng with the motor: A too low setting will result in reduced microstep 
accuracy, while a too high setting will lead to more chopper noise and motor power dissipation. 
When measuring the sense resistor voltage in motor standstill at a medium coil current wit h an 
oscilloscope, a too low setting shows a fast decay phase not longer than the blanking time. When 
the fast decay time becomes slightly longer than the blanking time, the setting is optimum. You can 
reduce the off-time setting, if this is hard to reach. 
 
The hysteresis principle could in some cases lead to the chopper frequency becoming too low, e.g. 
when the coil resistance is high when compared to the supply voltage. This is avoided  by splitting 
the hysteresis setting into a start setting ( HSTRT+HEND) and an end setting ( HEND). An automatic 
hysteresis decrementer (HDEC) interpolates between both settings, by decrementing the hysteresis 
value stepwise each 16 system clocks. At the beg inning of each chopper cycle, the hysteresis begins 
with a value which is the sum of the start and the end values ( HSTRT+HEND), and decrements during 
the cycle, until either the chopper cycle ends or the hysteresis end value ( HEND) is reached. This way, 

--- [PAGE 71] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  71 
 
 
 
www.trinamic.com 
the chopper frequency is stabilized at high amplitudes and low supply vol tage situations, if the 
frequency gets too low. This avoids the frequency reaching the audible range. 
t
I
target current
target current - hysteresis start
target current + hysteresis start
on sd fd sd
target current + hysteresis end
target current - hysteresis end
HDEC
 
Figure 8.3 SpreadCycle chopper scheme showing coil current during a chopper cycle 
Two parameters control SpreadCycle mode: 
 
Parameter Description Setting Comment 
HSTRT Hysteresis start  setting. This value is an offset 
from the hysteresis end value HEND. 
0…7 HSTRT=1…8 
This value adds to HEND. 
HEND Hysteresis end  setting. Sets the hysteresis end 
value after a number of decrements. The sum 
HSTRT+HEND must be ≤16. At a current setting of 
max. 30 (amplitude reduced to 240), the sum is 
not limited. 
0…2 -3…-1: negative HEND 
3 0: zero HEND 
4…15 1…12: positive HEND 
 
With HSTRT=0 and HEND=0, the hysteresis is 0 (off). 
 
EXAMPLE: 
 
A hysteresis of 4 has been chosen. You might decide to not use hysteresis decrement. In this case 
set: 
 
HEND=6 (sets an effective end value of 6-3=3) 
HSTRT=0 (sets minimum hysteresis, i.e. 1: 3+1=4) 
 
In order to take advantage of the variable hysteresis, we can set most of the value to the HSTRT, i.e. 
4, and the remaining 1 to hysteresis end. The resulting configuration register values are as follows:  
 
HEND=0  (sets an effective end value of -3) 
HSTRT=6  (sets an effective start value of hysteresis end +7: 7-3=4) 
 
Hint 
Highest motor velocities sometimes benefit from setting TOFF to 2 or 3 and a short TBL of 2 or 1. 
  
--- [PAGE 72] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  72 
 
 
 
www.trinamic.com 
8.2 Classic Constant Off Time Chopper 
The classic constant off time chopper is an alternative to SpreadCycle. Perfectly tuned, it also  gives 
good results. Also, the classic constant off time chopper (automatically) is used in combination with 
fullstepping in DcStep operation. 
 
The classic constant off-time chopper uses a fixed -time fast decay following each on phase. While the 
duration of the on phase is determined by the chopper comparator, the fast decay time needs to be 
long enough for the driver to follow the falling slope of the sine wave, but it should not be so long 
that it causes excess motor curr ent ripple and power dis sipation. This can be tuned using an 
oscilloscope or evaluating motor smoothness at different velocities. A good starting value is a fast 
decay time setting similar to the slow decay time setting. 
t
I
mean value = target current
target current + offset
on sdfd sdon fd
 
Figure 8.4 Classic const. off time chopper with offset showing coil current 
 
After tuning the fast decay time, the offset should be tuned for a smooth zero crossing. This is 
necessary because the fast decay phase makes the absolute value of the motor current lower than the 
target current (see Figure 8.5). If the zero offset is too low, the motor stands still for a short moment 
during current zero cr ossing. If it is set too high, it makes a larger microstep. Typically, a positive 
offset setting is required for smoothest operation. 
 
t
I
Target current
Coil current
t
I
Target current
Coil current
Coil current does not have optimum shape Target current corrected for optimum shape of coil current
 
Figure 8.5 Zero crossing with classic chopper and correction using sine wave offset 
Three parameters control constant off-time mode: 
 
--- [PAGE 73] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  73 
 
 
 
www.trinamic.com 
Parameter Description Setting Comment 
TFD 
(fd3 & 
HSTRT) 
Fast decay time  setting. With CHM=1, these bits 
control the portion of fast decay for each chopper 
cycle. 
0 slow decay only 
1…15 duration of fast decay 
phase 
OFFSET 
(HEND) 
Sine wave offset . With CHM=1, these bits control 
the sine wave offset. A positive offset corrects for 
zero crossing error. 
0…2 negative offset: -3…-1 
3 no offset: 0 
4…15 positive offset 1…12 
disfdcc Selects usage of the current comparator  for 
termination of the fast decay  cycle. If current 
comparator is enabled, it terminates the fast decay 
cycle in case the current reaches a higher negative 
value than the actual positive value. 
0 enable comparator 
termination of fast decay 
cycle 
1 end by time only 
 
  
