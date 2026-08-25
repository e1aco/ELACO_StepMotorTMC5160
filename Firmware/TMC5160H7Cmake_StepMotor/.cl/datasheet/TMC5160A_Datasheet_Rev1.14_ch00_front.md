# TMC5160A_Datasheet_Rev1.14 — 第0章 0 Driver off

--- [PAGE 1] ---
  
POWER DRIVER FOR STEPPER MOTORS    INTEGRATED CIRCUITS 
 
TRINAMIC Motion Control GmbH & Co. KG  
Hamburg, Germany 
TMC5160 / TMC5160A DATASHEET 
 
   
    
   
   
 
  
 
 
        
         
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
  
FEATURES AND BENEFITS 
2-phase stepper motors up to 20A coil current (external MOSFETs) 
Motion Controller with SixPoint™ ramp  
Step/Dir Interface with microstep interpolation MicroPlyer™ 
Voltage Range 8 … 60V DC  
SPI & Single Wire UART  
Encoder Interface and 2x Ref.-Switch Input 
Highest Resolution 256 microsteps per full step 
StealthChop2™ for quiet operation and smooth motion  
Resonance Dampening for mid-range resonances 
spreadCycle™ highly dynamic motor control chopper 
dcStep™ load dependent speed control 
StallGuard2™ high precision sensorless motor load detection 
CoolStep™ current control for energy savings up to 75% 
Passive Braking and freewheeling mode  
Full Protection & Diagnostics 
Compact Size 7x7mm2 (body) TQFP48 package / 8x8mm² QFN  
 
 
 
APPLICATIONS 
Robotics & Industrial Drives 
Textile, Sewing Machines 
Packing Machines 
Factory & Lab Automation 
High-speed 3D Printers 
Liquid Handling 
Medical 
Office Automation 
CCTV 
ATM, Cash Recycler 
Pumps and Valves 
 
 DESCRIPTION 
The TMC5160 / TMC5160A is a high-power 
stepper motor controller and driver IC 
with serial communication interface s. It 
combines a flexible ramp generator for 
automatic target positioning with indus -
tries’ most advanced stepper mot or 
driver. Using external transistors, highly 
dynamic, high torque drives can be 
realized. Based on TRINAMICs sophisti -
cated SpreadCycle and StealthChop 
choppers, the driver ensures absolutely 
noiseless operation combined with maxi -
mum efficiency and best motor torque. 
High integration, high energy efficiency 
and a small form factor enable miniatu -
rized and scalable systems for cost 
effective solutions. The complete solution 
reduces learning curve to a minimum 
while giving best performance in class. 
Universal high voltage controller/driver for two-phase bipolar stepper motor. StealthChop™ for quiet 
movement. External MOSFETs for up to 20A motor current per coil. With Step/Dir Interface and SPI.  
BLOCK DIAGRAM 
 

--- [PAGE 2] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  2 
 
 
 
www.trinamic.com 
APPLICATION EXAMPLES: HIGH VOLTAGE – MULTIPURPOSE USE 
The TMC5160 scores with complete motion controlling features , powerful external MOSFET  driver stages, 
and high-quality current regulation. It offers a versatility that covers a wide spectrum of applications from 
battery powered, high efficiency systems up to embedded applications with 20A motor current per coil. The 
TMC5160 contains the complete intelligence which is required to drive a motor. Receiving target positions, 
the TMC 5160 manages motor movement . Based on  TRINAMICs unique features  StallGuard2, CoolStep, 
DcStep, SpreadCycle, and StealthChop, it optimizes drive performance. It trades off  velocity vs. motor 
torque, optimizes energy efficiency , smoothness of the drive , and noiselessness. The small form factor of 
the TMC5160 keeps costs down and allows for miniaturized layouts. Extensive support at the chip, board, 
and software lev els enables rapid design cycle s and fast time -to-market with competitive products. High 
energy efficiency and reliability deliver cost savings in related systems such as power supplies and cooling.  
For smaller designs, the compatible, integrated TMC5130 driver provides 1.4A of motor current. 
 
CPU TMC5160
High-Level 
Interface
SPI
CPUHigh-Level 
Interface TMC5160
TMC5160
More TMC5160 or TMC5130 or TMC5072
SPI or 
UART 
MINIATURIZED DESIGN FOR ONE STEPPER MOTOR
COMPACT DESIGN FOR MULTIPLE STEPPER MOTORS 
M
Encoder
Ref.
Switches
M
M
Addr.
Addr.
NCS signal for SPI
Chaining 
with UART  
 
ORDER CODES 
Order code PN Description Size [mm2] 
TMC5160A-TA 00-0179 stepper controller/driver for external MOSFETs; TQFP48  7 x 7 (body) 
TMC5160A-WA 00-0192 stepper controller/driver f. ext. MOSFETs; wett. QFN8x8 8 x 8  
TMC5160A-xx-T …-T -T denotes tape on reel packing (xx= TA or WA)  
TMC5160-EVAL 40-0138 Evaluation board for TMC5160 (/A) 85 x 55 
LANDUNGSBRÜCKE 40-0167 Baseboard for TMC5160-EVAL and further boards.  85 x 55 
ESELSBRÜCKE 40-0098 Connector board fitting to Landungsbrücke 61 x 38 
 
Hint: TMC5160 in this manual always refers to both, the TMC5160A and TMC5160, unless explicitly noted 
with “non-A-version” or “A-version”. The A-version compatibly replaces the non-A-version. 
An ABN encoder interface with scaler unit 
and two reference switch inputs are used to 
ensure correct motor movement.  Automatic 
interrupt upon deviation is available. 
An application with 2 stepper motors is 
shown. Additionally, the ABN Encoder 
interface and two reference switches can be 
used for each motor. A single CPU control s 
the whole system, as there are no real time 
tasks required to move a motor . The CPU-
board and the controller / driver boards are 
highly economical and space saving.   
 
The TMC5160-EVAL is part of TRINAMICs 
universal evaluation board system which 
provides a convenient handling of the 
hardware as well as a user -friendly 
software tool for evaluation. The 
TMC5160 evaluation board system 
consists of three parts: 
LANDUNGSBRÜCKE (base boar d), 
ESELSBRÜCKE (connector board including 
several test points), and TMC5160-EVAL.  
--- [PAGE 67] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  67 
 
 
 
www.trinamic.com 
PARAMETERS RELATED TO STEALTHCHOP 
Parameter Description Setting  Comment 
en_spread_ 
cycle 
General disable for use of StealthChop (register 
GCONF). 
1 Do not use StealthChop 
0 StealthChop enabled 
TPWMTHRS Specifies the upper velocity for operation in 
StealthChop. Entry the TSTEP reading (time 
between two microsteps) when operating at the 
desired threshold velocity. 
0 … 
1048575 
StealthChop is disabled if 
TSTEP falls TPWMTHRS   
PWM_LIM Limiting value for limiting the current jerk when 
switching from SpreadCycle to StealthChop. 
Reduce the value to yield a lower current jerk. 
0 … 15 Upper four bits of 8 bit 
amplitude limit 
(Default=12) 
pwm_ 
autoscale 
Enable automatic current scaling using current 
measurement. If off,  use forward controlled 
velocity-based mode. 
0 Forward controlled mode 
1 Automatic scaling with 
current regulator 
pwm_ 
autograd 
Enable automatic tuning of PWM_GRAD_AUTO 0 disable, use PWM_GRAD 
from register instead 
1 enable 
PWM_FREQ PWM frequency selection. Use the lowest setting 
giving good results.  The frequency measured at 
each of the chopper outputs is half of the 
effective chopper frequency fPWM. 
0 fPWM=2/1024 fCLK 
1 fPWM=2/683 fCLK 
2 fPWM=2/512 fCLK 
3 fPWM=2/410 fCLK 
PWM_REG User defined PWM amplitude regulation loop  P-
coefficient. A higher value leads to a higher 
adaptation speed when pwm_autoscale=1. 
1 … 15 Results in 0.5 to 7.5 steps 
for PWM_SCALE_AUTO 
regulator per fullstep 
PWM_OFS User defined PWM amplitude (offset) for velocity 
based scaling and initialization value for automatic 
tuning of PWM_OFFS_AUTO. 
0 … 255 PWM_OFS=0 disables 
linear current scaling 
based on current setting 
PWM_GRAD User defined PWM amplitude ( gradient) for 
velocity based scaling  and initialization value for 
automatic tuning of PWM_GRAD_AUTO. 
0 … 255  
FREEWHEEL Stand still option when motor c urrent setting is 
zero ( I_HOLD=0). Only available with StealthChop 
enabled. The freewheeling option makes the 
motor easy movable, while both coil short options 
realize a passive brake.  
0 Normal operation 
1 Freewheeling 
2 Coil short via LS drivers 
3 Coil short cia HS drivers 
PWM_SCALE 
_AUTO 
Read back of the actual StealthChop voltage PWM 
scaling correction as determined by the current 
regulator. Shall regulate close to 0 during tuning. 
-255 … 
255 
 
(read only) Scaling value 
becomes frozen when 
operating in SpreadCycle 
PWM_GRAD 
_AUTO 
PWM_OFS 
_AUTO 
Allow monitoring of the automatic tuning and 
determination of initial values for PWM_OFS and 
PWM_GRAD.  
0 … 255 
 
(read only) 
TOFF General enable for the motor driver, the actual 
value does not influence StealthChop 
0 Driver off 
1 … 15 Driver enabled 
TBL Comparator blank time. This time needs to safely 
cover the switching event and the duration of the 
ringing on the sense resistor. Choose a setting of 
1 or 2 for typical applications. For higher 
capacitive loads, 3 may be required. Lower 
settings allow StealthChop to regulate d own to 
lower coil current values.  
0 16 tCLK 
1 24 tCLK 
2 36 tCLK 
3 54 tCLK 
  
--- [PAGE 94] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  94 
 
 
 
www.trinamic.com 
15 STEP/DIR Interface 
The STEP and DIR inputs provide a simple, standard interface compatible with many existing motion 
controllers. The MicroPlyer STEP pulse interpolator brings the smooth motor operation of high -
resolution microstepping to applications ori ginally designed for coarser stepping. In case an external 
step source is used, the complete integrated motion controller can be switche d off. The only motion 
controller registers remaining active in this case are the current settings in register IHOLD_IRUN.  
15.1 Timing 
Figure 15.1 shows the timing parameters for the STEP and DIR signals, and the table below gives 
their specifications. When the dedge mode bit in the CHOPCONF register is set, both edges of STEP 
are active. If dedge is c leared, only rising edges are active. STEP and DI R are sampled and 
synchronized to the system clock. An internal analog filter removes glitches on the signals, such as 
those caused by long PCB traces. If the signal source is far from the chip, and especial ly if the signals 
are carried on cables, the signals should be filtered or differentially transmitted. 
  
+VCC_IO
SchmittTrigger
0.44 VCC_IO
0.56 VCC_IO83k
C
Input filter
R*C = 20ns +-30%
STEP 
or DIR
Input
Internal 
Signal
DIR
STEP
tDSHtSH tSLtDSU
Active edge 
(DEDGE=0)
Active edge 
(DEDGE=0)
 
Figure 15.1 STEP and DIR timing, Input pin filter 
 
STEP and DIR interface timing  AC-Characteristics 
clock period is tCLK 
Parameter Symbol Conditions Min Typ Max Unit 
step frequency (at maximum 
microstep resolution) 
fSTEP dedge=0   ½ fCLK  
dedge=1   ¼ fCLK  
fullstep frequency fFS    fCLK/512  
STEP input low time *) tSL  max(tFILTSD, 
tCLK+20) 
100  ns 
STEP input high time *) tSH  max(tFILTSD, 
tCLK+20) 
100  ns 
DIR to STEP setup time tDSU  20   ns 
DIR after STEP hold time tDSH  20   ns 
STEP and DIR spike filtering time 
*) 
tFILTSD rising and falling 
edge 
13 20 30 ns 
STEP and DIR sampling relative 
to rising CLK input 
tSDCLKHI before rising edge 
of CLK input 
 tFILTSD  ns 
 
*) These values are valid with full input logic level swing, only. Asymmetric logic levels will increase 
filtering delay tFILTSD, due to an internal input RC filter. 
  
--- [PAGE 122] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  122 
 
 
 
www.trinamic.com 
Linear regulator DC-Characteristics 
VVS = VVSA = 24.0V 
Parameter Symbol Conditions Min Typ Max Unit 
Output voltage V5VOUT TJ = 25°C 4.80 5.0 5.20 V 
Deviation of output voltage over 
the full temperature range 
V5VOUT(DEV) drivers disabled 
TJ = full range 
 +/-30 +/-100 mV 
Deviation of output voltage over 
the full supply voltage range 
V5VOUT(DEV) drivers disabled, 
internal clock  
TA = 25°C 
VVSA = 10V to 30V 
  +/-50 mV / 
10V 
Output voltage V12VOUT operating, internal 
clock 
TJ = 25°C 
10.8 11.5 12.2 V 
 
Clock oscillator and input Timing-Characteristics 
Parameter Symbol Conditions Min Typ Max Unit 
Clock oscillator frequency 
(factory calibrated) 
fCLKOSC tJ=-50°C  11.7  MHz 
fCLKOSC tJ=50°C 11.5 12.0 12.5 MHz 
fCLKOSC tJ=150°C  12.1  MHz 
External clock frequency 
(operating) 
fCLK  4 10-16 18 MHz 
External clock high / low level 
time  
tCLKH / 
tCLKL 
CLK driven to  
0.1 VVIO / 0.9 VVIO 
16   ns 
External clock first pulse to 
trigger switching to external CLK 
tCLKH / 
tCLKL 
CLK driven high 
A-version 
16   ns 
External clock first pulse to 
trigger switching to external CLK 
tCLKH / 
tCLKL 
CLK driven high 
non-A-version only 
30 25  ns 
External clock timeout detection 
in cycles of internal fCLKOSC 
tCLKH1 CLK driven high 32  48 cycles 
fCLKOSC 
 
Short detection DC-Characteristics 
Parameter Symbol Conditions Min Typ Max Unit 
Short to GND / Short to VS 
detector delay (Start of gate 
switch on to short detected) 
Including 100ns filtering time 
tSD0 FILT_ISENSE=0 
S2xx_LEVEL=6 
shortdelay=0 
0.5 0.85 1.1 µs 
tSD1 shortdelay=1 1.1 1.6 2.2 µs 
Short detector level S2VS 
(measurement includes drop in 
sense resistor) 
VBM S2VS_LEVEL=15 1.4 1.56 1.72 V 
S2VS_LEVEL=6 0.55 0.625 0.70 V 
Short detector level S2G VS - VBM S2G_LEVEL=15; 
VS<52V 
1.2 1.56 1.9 V 
S2G_LEVEL=15; 
VS<55V 
0.85   V 
S2G_LEVEL=6;  
VS<50V 
0.46 0.625 0.80 V 
 
