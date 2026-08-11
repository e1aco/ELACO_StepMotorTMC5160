# TMC5160A_Datasheet_Rev1.14 — 第6章 · p31

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
31 
 
 
 
www.trinamic.com 
6 Register Mapping 
This chapter gives an overview of the complete register set. Some of the registers bundling a number 
of single bits are detailed in extra tables. The functional practical application of the settings is detailed 
in dedicated chapters.  
 
Note 
- All registers become reset to 0 upon power up, unless otherwise noted. 
- Add 0x80 to the address Addr for write accesses! 
 
NOTATION OF HEXADECIMAL AND BINARY NUMBERS 
0x 
precedes a hexadecimal number, e.g. 0x04  
% 
precedes a multi-bit binary number, e.g. %100 
 
NOTATION OF R/W FIELD 
R 
Read only 
W 
Write only 
R/W 
Read- and writable register 
R+C 
Clear by writing “1” bit 
 
OVERVIEW REGISTER MAPPING 
REGISTER 
DESCRIPTION 
General Configuration Registers 
These registers contain  
- 
global configuration 
- 
global status flags 
- 
interface configuration 
- 
and I/O signal configuration 
Ramp Generator Motion Control Register Set 
This register set offers registers for  
- 
choosing a ramp mode 
- 
choosing velocities 
- 
homing 
- 
acceleration and deceleration 
- 
target positioning 
- 
reference switch and StallGuard2 event 
configuration  
- 
ramp and reference switch status 
Velocity Dependent Driver Feature Control Register 
Set 
This register set offers registers for 
- 
driver current control 
- 
setting thresholds for CoolStep operation 
- 
setting thresholds for different chopper modes 
- 
setting thresholds for DcStep operation 
Encoder Register Set 
The encoder register set offers all registers needed for 
proper ABN encoder operation. 
Motor Driver Register Set 
This register set offers registers for 
- 
setting / reading out microstep table and 
counter 
- 
chopper and driver configuration 
- 
CoolStep and StallGuard2 configuration 
- 
DcStep configuration 
- 
reading out StallGuard2 values and driver error 
flags 
 
 
 


<!-- detected tables -->

|  | NOTATION OF HEXADECIMAL AND BINARY NUMBERS |  |  |  |
|---|---|---|---|---|
|  | 0x |  | precedes a hexadecimal number, e.g. 0x04 |  |
|  | % |  | precedes a multi-bit binary number, e.g. %100 |  |

|  | NOTATION OF R/W FIELD |  |  |  |
|---|---|---|---|---|
|  | R |  | Read only |  |
|  | W |  | Write only |  |
|  | R/W |  | Read- and writable register |  |
|  | R+C |  | Clear by writing “1” bit |  |

|  | REGISTER |  |  | DESCRIPTION |  |
|---|---|---|---|---|---|
| General Configuration Registers | General Configuration Registers |  | These registers contain - global configuration - global status flags - interface configuration - and I/O signal configuration |  |  |
| Ramp Generator Motion Control Register Set |  |  | This register set offers registers for - choosing a ramp mode - choosing velocities - homing - acceleration and deceleration - target positioning - reference switch and StallGuard2 event configuration - ramp and reference switch status |  |  |
| Velocity Dependent Driver Feature Control Register Set |  |  | This register set offers registers for - driver current control - setting thresholds for CoolStep operation - setting thresholds for different chopper modes - setting thresholds for DcStep operation |  |  |
| Encoder Register Set |  |  | The encoder register set offers all registers needed for proper ABN encoder operation. |  |  |
| Motor Driver Register Set |  |  | This register set offers registers for - setting / reading out microstep table and counter - chopper and driver configuration - CoolStep and StallGuard2 configuration - DcStep configuration - reading out StallGuard2 values and driver error flags |  |  |
