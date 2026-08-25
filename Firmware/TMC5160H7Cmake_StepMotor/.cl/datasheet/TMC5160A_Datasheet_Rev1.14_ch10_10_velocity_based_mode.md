# TMC5160A_Datasheet_Rev1.14 — 第10章 10 Velocity Based Mode Control

--- [PAGE 76] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  76 
 
 
 
www.trinamic.com 
10 Velocity Based Mode Control 
The TMC 5160 allows the configuration of different chopper modes and modes of operation  for 
optimum motor control . Depending on the motor load, the different modes can be optimized for 
lowest noise & high precision, highest dynamics, or maximum torque at highest velocity. Some of the 
features like CoolStep or StallGuard2 are useful in a limited velocity range. A number of velocity 
thresholds allow combining the different modes of operation within an application requiring a wide 
velocity range.  
 
option
option
option
option
optionoption
option
microstep
microstep
high velocity fullstep
microstep + coolStep
microstep + coolStep
microstepping
microstepping
motor stand still
motor going to standby
motor in standby
motor in standby
v
t
VPWMTHRS+Δ 
VPWMTHRS
0
VCOOLTHRS+Δ 
VHIGH+Δ 
VACTUAL
~1/TSTEP
VCOOLTHRS
VHIGH
current
TZEROWAIT
RMS current
I_HOLD
I_RUN
dI * IHOLDDELAY
coolStep current reduction
stealthChop
spreadCycle
const. Toff
Chopper mode
TRINAMIC, B. Dwersteg, 14.3.14
 
Figure 10.1 Choice of velocity dependent modes 
Figure 10.1 shows all available thresholds and the required ordering . VPWMTHRS, VHIGH and 
VCOOLTHRS are determined by the settings TPWMTHRS, THIGH and TCOOLTHRS. The velocity is 
described by the time int erval TSTEP between each two step pulses. This allows determination of the 
velocity when an external step source is used.  TSTEP always becomes normalized to 256 
microstepping. This way, the thresholds do not have to be adapted when the microstep resolution  is 
changed. The thresholds represent the same motor velocity, independent of the microstep settings. 
TSTEP becomes compared to these threshold values. A hysteresis of 1/16 TSTEP resp. 1/32 TSTEP is 
applied to avoid continuous toggling of the comparison re sults when a jitter in the TSTEP 
measurement occurs. The upper switching velocity is higher by 1/16, resp. 1/32 of the va lue set as 
threshold. The StealthChop threshold TPWMTHRS is not shown. It can be included with VPWMTHRS < 
VCOOLTHRS. The motor current can be programmed to a run and a hold level, dependent on the 
standstill flag stst.  
 
Using automatic velocity thresholds  allows tuning the application for different velocity ranges. 
Features like CoolStep will integrate completely transparently in your setup. This way, once 
parameterized, they do not require any activation or deactivation via software. 
 
