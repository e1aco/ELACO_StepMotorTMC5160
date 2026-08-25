# TMC5160A_Datasheet_Rev1.14 — 第9章 9 Bit signed offset added to the

--- [PAGE 48] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  48 
 
 
 
www.trinamic.com 
DRIVER REGISTER SET (0X6C…0X7F)  
R/W Addr n Register Description / bit names Range [Unit] 
RW 0x6C 32 CHOPCONF chopper and driver configuration  
See separate table! 
reset default=  
0x10410150 
W 0x6D 25 COOLCONF 
CoolStep smart current control register 
and StallGuard2 configuration 
See separate table! 
 
W 0x6E 24 DCCTRL 
DcStep (DC) automatic commutation 
configuration register  (enable via pin DCEN  
or via VDCMIN):  
bit 9… 0: DC_TIME: Upper PWM on time 
limit for commutation (DC_TIME * 
1/fCLK). Set slightly above effective 
blank time TBL. 
bit 23… 16: DC_SG: Max. PWM on time for 
step loss detection using DcStep 
StallGuard2 in DcStep mode. 
(DC_SG * 16/fCLK) 
 Set slightly higher than 
DC_TIME/16 
 0=disable 
Hint: Using a higher microstep resolution or 
interpolated operation,  DcStep delivers a 
better StallGuard signal. 
DC_SG is also available above VHIGH if 
vhighfs is activat ed. For best result also set 
vhighchm. 
 
R 0x6F 32 DRV_ 
STATUS 
StallGuard2 value and driver error flags 
See separate table! 
 
W 0x70 22 PWMCONF Voltage PWM mode chopper configuration 
See separate table! 
reset default=  
0xC40C001E 
R 0x71 9+8 PWM_SCALE 
Results of StealthChop amplitude regulator. 
These values can be used to monitor 
automatic PWM amplitude scaling (255=max. 
voltage). 
 
bit 7… 0 
 
PWM_SCALE_SUM:  
 Actual PWM duty cycle. This 
value is used for scaling the 
values CUR_A and CUR_B read 
from the sine wave table. 
0…255 
 
bit 24… 16
  
 
PWM_SCALE_AUTO: 
9 Bit signed offset added to the 
calculated PWM duty cycle. This 
is the result of the automatic 
amplitude regulation based on 
current measurement. 
signed  
-255…+255 
R 0x72 8+8 PWM_AUTO 
These automatically generated values can be 
read out in order to determine a default / 
power up setting for PWM_GRAD and 
PWM_OFS. 
 
bit 7… 0  
 
PWM_OFS_AUTO:  
 Automatically determined offset 
value 
0…255 
--- [PAGE 49] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  49 
 
 
 
www.trinamic.com 
DRIVER REGISTER SET (0X6C…0X7F)  
R/W Addr n Register Description / bit names Range [Unit] 
bit 23… 16
  
PWM_GRAD_AUTO: 
Automatically determined 
gradient value 
0…255 
R 0x73 20 LOST_STEPS 
Number of input steps skipped due to higher 
load in DcStep operation, if step input does 
not stop when DC_OUT is low . This counter 
wraps around after 2^ 20 steps. Counts up or 
down depending on direction.  Only with 
SDMODE=1. 
 
 
 
 
 
 
 
 
 
  
MICROSTEP TABLE CALCULATION FOR A SINE WAVE EQUIVALENT TO THE POWER ON DEFAULT 
 
𝑟𝑜𝑢𝑛𝑑 (248 ∗  𝑠𝑖𝑛 (2 ∗ 𝑃𝐼 ∗ 𝑖
1024 + 𝑃𝐼
1024)) − 1 
 
- i:[0… 255] is the table index 
- The amplitude of the wave is 248. The resulting maximum positive value is 247 and the 
maximum negative value is -248. 
- The round function rounds values from 0.5 to 1.4999 to 1 
 
--- [PAGE 56] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  56 
 
 
 
www.trinamic.com 
6.5.5 DRV_STATUS – StallGuard2 Value and Driver Error Flags 
0X6F: DRV_STATUS – STALLGUARD2 VALUE AND DRIVER ERROR FLAGS 
Bit Name Function Comment 
31 stst standstill indicator This flag indicates motor stand still in each operation mode.  
This occurs 2^20 clocks after the last step pulse. 
30 olb open load indicator 
phase B 
1: Open load detected on phase A or B. 
Hint: This is just an informative flag. The driver takes no action 
upon it. False detection may occur in fast motion and 
standstill. Check during slow motion, only. 
29 ola open load indicator 
phase A 
28 s2gb short to ground 
indicator phase B 
1: Short to GND detected on phase A o r B. The driver becomes 
disabled. The flags stay active, until the driver is disabled by 
software (TOFF=0) or by the ENN input. 27 s2ga short to ground 
indicator phase A 
26 otpw overtemperature pre-
warning flag 
1: Overtemperature pre-warning threshold is exceeded. 
The overtempe rature pre -warning flag is common for both 
bridges. 
25 ot overtemperature flag 1: Overtemperature limit has been reached. Drivers become 
disabled until otpw is also cleared due to cooling down of the 
IC. 
The overtemperature flag is common for both bridges. 
24 StallGuard StallGuard2 status 1: Motor stall detected (SG_RESULT=0) or DcStep stall in DcStep 
mode. 
23 - reserved Ignore these bits 
22 
21 
20 CS 
ACTUAL 
actual motor current / 
smart energy current 
Actual current control scaling, for monitorin g smart energy 
current scaling controlled via settings in register COOLCONF, or 
for monitoring the function of the automatic current scaling. 
19 
18 
17 
16 
15 fsactive full step active 
indicator 
1: Indicates that the driver has switched to f ullstep as defined 
by chopper mode settings and velocity thresholds.  
14 stealth StealthChop indicator 1: Driver operates in StealthChop mode 
13 s2vsb short to supply 
indicator phase B 
1: Short to supply detected on phase A or B. The driver 
becomes di sabled. The flags stay active, until the driver is 
disabled by software ( TOFF=0) or by the ENN input.  Sense 
resistor voltage drop is included in the measurement! 12 s2vsa short to supply 
indicator phase A 
11 - reserved Ignore this bit 
10 - reserved Ignore this bit 
9 SG_ 
RESULT 
StallGuard2 result 
respectively PWM on 
time for coil A in stand 
still for motor 
temperature detection 
Mechanical load measurement: 
The StallGuard2 result gives a means to measure mecha nical 
motor load. A higher value means lower  mechanical load. A 
value of 0 signals highest load. With opti mum SGT setting, 
this is an indicator for a motor stall. The stall detection 
compares SG_RESULT to 0 in order to detect a stall. SG_RESULT 
is used as a base for CoolStep operation, by comparing it to a 
programmable upper and a lower limit.  It is not applicable in 
StealthChop mode. 
StallGuard2 works best with microstep operation or DcStep. 
Temperature measurement: 
In standstill, no StallGuard2 result can be obtained. SG_RESULT 
shows the chopper on-time for motor coil A instead. Move the 
motor to a determined micro step position at a certain current 
setting to get a rough estimation of motor temperature  by a 
reading the chopper on -time. As the motor heats up, its coil 
resistance rises and the chopper on-time increases.  
8 
7 
6 
5 
4 
3 
2 
1 
0 
 
--- [PAGE 74] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  74 
 
 
 
www.trinamic.com 
9 Selecting Sense Resistors 
The TMC5160 provides several means to set the motor current: Sense resistors, GLOBALSCALER and 
currentscale CS. To adapt a drive to the motor, choose a sense -resistor value fitting or slightly 
exceeding the maximum desired current  at 100% settings of the scalers. Fine -tune the current to the 
specific motor via the 8 bit GLOBALSCALER. Situation specific motor current adaptation is done by 5 
bit scalers (actual scale can be read via CS), controlled by CoolStep, run - and hold current ( IRUN, 
IHOLD). This makes the CS control compatible to other TRINAMIC ICs.  
 
Set the desired maximum motor current by selecting an appropriate value for the sense resistor. The 
following table shows the RMS current values which are reached using standard resistors. 
 
CHOICE OF RSENSE AND RESULTING MAX. MOTOR CURRENT 
WITH GLOBALSCALER=0 (RESP. VALUE 256) 
RSENSE [Ω] RMS current [A] 
(CS=31) 
Sine wave peak 
current [A] (CS=31) 
0.22 1.1 1.5 
0.15 1.6 2.2 
0.12 2.0 2.8 
0.10 2.3 3.3 
0.075 3.1 4.4 
0.066 3.5 5.0 
0.050 4.7 6.6 
0.033 7.1 10.0 
0.022 10.6 15.0 
 
Sense resistors should be carefully selected. The full m otor current flows through the sense resistors. 
Due to chopper operation the sense resistors  see pulsed current from the MOSFET bridges. Therefore, 
a low-inductance type such as film or composition re sistors is required to prevent voltage spikes 
causing ringing on the sense voltage inputs leading to unstable measurement results. A lso, a low-
inductance, low-resistance PCB layout is essential. A massive ground plane is best. Please also refer to 
layout considerations in chapter 29. 
 
The sense resistor sets the upper current which can be set by software settings IRUN, IHOLD and 
GLOBALSCALER. Choose the  sense resistor value so that the maximum desired current (or slightl y 
more) flows at the maximum current setting (GLOBALSCALER = 256 (setting 0) and IRUN = 31). 
 
CALCULATION OF RMS CURRENT 
𝐼𝑅𝑀𝑆 = 𝐺𝐿𝑂𝐵𝐴𝐿𝑆𝐶𝐴𝐿𝐸𝑅
256 ∗ 𝐶𝑆 + 1
32 ∗ 𝑉𝐹𝑆
𝑅𝑆𝐸𝑁𝑆𝐸
∗ 1
√2
 
 
The momentary motor current is calculated by: 
 
𝐼𝑀𝑂𝑇 = 𝐺𝐿𝑂𝐵𝐴𝐿𝑆𝐶𝐴𝐿𝐸𝑅
256 ∗ 𝐶𝑈𝑅𝐴/𝐵
248 ∗ 𝐶𝑆 + 1
32 ∗ 𝑉𝐹𝑆
𝑅𝑆𝐸𝑁𝑆𝐸
 
 
GLOBALSCALER is the global current scaler. A setting of 0 is treated as full scale (256). 
CS is the current scale setting as set by the IHOLD and IRUN and CoolStep. 
VFS is the full scale voltage (please refer to electrical characteristics, VSRT). 
CURA/B is the actual value from the internal sine wave table.  
248 is the amplitude of the internal sine wave table. 
 
The sense resistor needs to be able to conduct the peak motor coil current in motor standstill 
conditions, unless standby power is reduced. Under normal condit ions, the sense resistor conducts 
--- [PAGE 75] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  75 
 
 
 
www.trinamic.com 
less than the coil RMS current, because no current flows throug h the sense resistor during the slow 
decay phases. 
 
CALCULATION OF PEAK SENSE RESISTOR POWER DISSIPATION 
𝑃𝑅𝑆𝑀𝐴𝑋 = 𝐼𝐶𝑂𝐼𝐿
2 ∗ 𝑅𝑆𝐸𝑁𝑆𝐸 
 
Hint 
For best precision of current setting, it is advised to measure and fine tune  the current in the 
application. Choose the sense resistors to the next value covering the desired motor current. Set IRUN 
to 31 corresponding 100% of the desired motor current and fine -tune motor current using 
GLOBALSCALER. 
 
Attention 
Be sure to use a symmetrical sense resistor layout and short and straight sense resistor traces of 
identical length. Well matching sense resistors ensure best performance. 
A compact layout with massive ground plane is best to avoid parasitic resistance effects. 
 
 
Parameter Description Setting  Comment 
IRUN Current scale when motor is running. Scales coil 
current values as taken from the internal sine 
wave table. For high precision motor operation, 
work with a current scaling factor in the range 16 
to 31, because scaling down the current values 
reduces the ef fective microstep resolution by 
making microsteps coarser. This setting also 
controls the maximum current value set by 
CoolStep. 
0 … 31  
 
scaling factor 
1/32, 2/32, … 32/32 
IHOLD Identical to IRUN, but for motor in stand still. 
IHOLD 
DELAY 
Allows smooth current reduction from run current 
to hold current. IHOLDDELAY controls the number 
of clock cycles for motor power down after 
TZEROWAIT in increments of 2^18 clocks: 0=instant 
power down, 1..15: Current reduction delay per 
current step in multiple of 2^18 clocks. 
 
Example: When using IRUN=31 and IHOLD=16, 15 
current steps are required for hold current 
reduction. A IHOLDDELAY setting of 4 thus re sults 
in a power down time of 4*15*2^18 clock cycles, 
i.e. roughly one second at 16MHz. 
0 instant IHOLD 
1 … 15 
 
 
1*218 … 15*218  
clocks per current  
decrement 
GLOBAL 
SCALER 
Allows fine control of the motor current range 
setting 
0 … 255 scales in 1/256 steps 
0=full scale 
  
