# TMC5160A_Datasheet_Rev1.14 — 第1章 · p51

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  51 
 
 
 
www.trinamic.com 
6.5.2 CHOPCONF – Chopper Configuration 
0X6C: CHOPCONF – CHOPPER CONFIGURATION 
Bit Name Function Comment 
31 diss2vs short to supply 
protection disable 
0: Short to VS protection is on 
1: Short to VS protection is disabled 
30 diss2g short to GND 
protection disable 
0: Short to GND protection is on 
1: Short to GND protection is disabled 
29 dedge enable double edge 
step pulses 
1: Enable step impulse at each step edge to reduce step 
frequency requirement.  
28 intpol interpolation to 256 
microsteps 
1: The actual microstep resolution (MRES) becomes 
extrapolated to 256 microsteps for smoothest motor 
operation (useful for STEP/DIR operation, only) 
27 mres3 MRES  
micro step resolution 
%0000: 
Native 256 microstep setting. Normally use this setting 
with the internal motion controller. 
26 mres2 
25 mres1 
24 mres0 %0001 … %1000:  
128, 64, 32, 16, 8, 4, 2, FULLSTEP 
Reduced microstep resolution esp. for STEP/DIR operation.  
The resolution gives the number of microstep entries per 
sine quarter wave. 
The driver automatically uses microstep positions which 
result in a symmetrical wave, when choosing a lower 
microstep resolution. 
step width=2^MRES [microsteps] 
23 tpfd3 TPFD 
passive fast decay time 
TPFD allows dampening of motor mid-range resonances. 
Passive fast decay  time setting controls duration of the 
fast decay phase inserted after bridge polarity change 
NCLK= 128*TPFD 
%0000: Disable 
%0001 … %1111: 1 … 15 
22 tpfd2 
21 tpdf1 
20 tpfd0 
19 vhighchm high velocity chopper 
mode 
This bit enables switching to chm=1 and fd=0, when VHIGH 
is exceeded. This way, a higher velocity can be achieved. 
Can be combined with vhighfs=1. If set, the TOFF setting 
automatically becomes doubled during high velocity 
operation in order to avoid doubling of the chopper 
frequency. 
18 vhighfs high velocity fullstep 
selection 
This bit enables switching to fullstep, when VHIGH is 
exceeded. Switching takes place only at 45° positio n. 
The fullstep target current uses the current value from 
the microstep table at the 45° position. 
17 - reserved reserved, set to 0 
16 tbl1 TBL 
blank time select 
%00 … %11:  
Set comparator blank time to 16, 24, 36 or 54 clocks 
Hint: %01 or %10 is recommended for most applications 
(Reset Default: OTP %01 or %10) 
15 tbl0 
14 chm chopper mode 0 Standard mode (SpreadCycle)  
1 
 
 
Constant off time with fast decay time.  
Fast decay time is also terminated when the 
negative nominal current is reached. Fast decay is 
after on time. 
13 - reserved Reserved, set to 0  
12 disfdcc fast decay mode chm=1: 
disfdcc=1 disables current comparator usage for termi -
nation of the fast decay cycle 
 
