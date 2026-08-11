# TMC5160A_Datasheet_Rev1.14 — 第8章 · p68

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
68 
 
 
 
www.trinamic.com 
8 SpreadCycle and Classic Chopper 
While StealthChop is a voltage mode PWM controlled chopper, SpreadCycle is a cycle-by-cycle current 
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
+VM
+VM
+VM
 
Figure 8.1 Chopper phases 
Although the current could be regulated using only on phases and fast decay phases, insertion of the 
slow decay phase is important to reduce electrical losses and current ripple in the motor. The 
duration of the slow decay phase is specified in a control parameter and sets an upper limit on the 
chopper frequency. The current comparator can measure coil current during phases when the current 
flows through the sense resistor, but not during the slow decay phase, so the slow decay phase is 
terminated by a timer. The on phase is terminated by the comparator when the current through the 
coil reaches the target current. The fast decay phase may be terminated by either the comparator or 
another timer. 
When the coil current is switched, spikes at the sense resistors occur due to charging and discharging 
parasitic capacitances. During this time, typically one or two microseconds, the current cannot be 
measured. Blanking is the time when the input to the comparator is masked to block these spikes. 
There are two cycle-by-cycle chopper modes available: a new high-performance chopper algorithm 
called SpreadCycle and a proven constant off-time chopper mode. The constant off-time mode cycles 
through three phases: on, fast decay, and slow decay. The SpreadCycle mode cycles through four 
phases: on, slow decay, fast decay, and a second slow decay. 
The chopper frequency is an important parameter for a chopped motor driver. A too low frequency 
might generate audible noise. A higher frequency reduces current ripple in the motor, but with a too 
high frequency magnetic losses may rise. Also power dissipation in the driver rises with increasing 
frequency due to the increased influence of switching slopes causing dynamic dissipation. Therefore, a 
compromise needs to be found. Most motors are optimally working in a frequency range of 16 kHz to 
30 kHz. The chopper frequency is influenced by a number of parameter settings as well as by the 
motor inductivity and supply voltage.  
 
Hint 
A chopper frequency in the range of 16 kHz to 30 kHz gives a good result for most motors when 
using SpreadCycle. A higher frequency leads to increased switching losses.  
 
 
 

