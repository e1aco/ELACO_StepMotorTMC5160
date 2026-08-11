# TMC5160A_Datasheet_Rev1.14 — 第6章 · p48

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
48 
 
 
 
www.trinamic.com 
DRIVER REGISTER SET (0X6C…0X7F)  
R/W 
Addr 
n 
Register 
Description / bit names 
Range [Unit] 
RW 
0x6C 
32 
CHOPCONF 
chopper and driver configuration  
See separate table! 
reset default=  
0x10410150 
W 
0x6D 
25 
COOLCONF 
CoolStep smart current control register 
and StallGuard2 configuration 
See separate table! 
 
W 
0x6E 
24 
DCCTRL 
DcStep 
(DC) 
automatic 
commutation 
configuration register (enable via pin DCEN 
or via VDCMIN):  
bit 9… 0: 
DC_TIME: Upper PWM on time 
limit for commutation (DC_TIME * 
1/fCLK). Set slightly above effective 
blank time TBL. 
bit 23… 16: DC_SG: Max. PWM on time for 
step loss detection using DcStep 
StallGuard2 
in 
DcStep 
mode. 
(DC_SG * 16/fCLK) 
 
Set 
slightly 
higher 
than 
DC_TIME/16 
 
0=disable 
Hint: Using a higher microstep resolution or 
interpolated operation, DcStep delivers a 
better StallGuard signal. 
DC_SG is also available above VHIGH if 
vhighfs is activated. For best result also set 
vhighchm. 
 
R 
0x6F 
32 
DRV_ 
STATUS 
StallGuard2 value and driver error flags 
See separate table! 
 
W 
0x70 
22 
PWMCONF 
Voltage PWM mode chopper configuration 
See separate table! 
reset default=  
0xC40C001E 
R 
0x71 
9+8 
PWM_SCALE 
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
R 
0x72 
8+8 
PWM_AUTO 
These automatically generated values can be 
read out in order to determine a default / 
power up setting for PWM_GRAD and 
PWM_OFS. 
 
bit 7… 0  
 
PWM_OFS_AUTO:  
 Automatically determined offset 
value 
0…255 


<!-- detected tables -->

|  | DRIVER REGISTER SET (0X6C…0X7F) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Addr |  |  | n |  |  | Register |  |  | Description / bit names |  |  |  |  | Range [Unit] |  |
| RW |  |  | 0x6C |  |  | 32 |  |  | CHOPCONF |  |  |  | chopper and driver configuration |  |  |  | reset default= 0x10410150 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | See separate table! |  |  |  |  |  |  |
| W |  |  | 0x6D |  |  | 25 |  |  | COOLCONF |  |  |  | CoolStep smart current control register |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | and StallGuard2 configuration |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | See separate table! |  |  |  |  |  |  |
| W |  |  | 0x6E |  |  | 24 |  |  | DCCTRL |  |  | DcStep (DC) automatic commutation configuration register (enable via pin DCEN or via VDCMIN): bit 9… 0: DC TIME: Upper PWM on time _ limit for commutation (DC TIME * _ 1/f ). Set slightly above effective CLK blank time TBL. bit 23… 16: DC SG: Max. PWM on time for _ step loss detection using DcStep StallGuard2 in DcStep mode. (DC SG * 16/f ) _ CLK Set slightly higher than DC TIME/16 _ 0=disable Hint: Using a higher microstep resolution or interpolated operation, DcStep delivers a better StallGuard signal. DC SG is also available above VHIGH if _ vhighfs is activated. For best result also set vhighchm. |  |  |  |  |  |  |  |
| R |  |  | 0x6F |  |  | 32 |  |  | DRV _ STATUS |  |  |  | StallGuard2 value and driver error flags |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | See separate table! |  |  |  |  |  |  |
| W |  |  | 0x70 |  |  | 22 |  |  | PWMCONF |  |  |  | Voltage PWM mode chopper configuration |  |  |  | reset default= 0xC40C001E |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | See separate table! |  |  |  |  |  |  |
| R |  |  | 0x71 |  |  | 9+8 |  |  | PWM SCALE _ |  |  |  | Results of StealthChop amplitude regulator. |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | These values can be used to monitor |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | automatic PWM amplitude scaling (255=max. |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | voltage). |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | bit 7… 0 | bit 7… 0 |  | PWM SCALE SUM: |  | 0…255 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | _ _ Actual PWM duty cycle. This |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | value is used for scaling the |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | values CUR A and CUR B read |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | _ _ from the sine wave table. |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | bit 24… 16 |  |  | PWM SCALE AUTO: |  | signed -255…+255 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | _ _ 9 Bit signed offset added to the |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | calculated PWM duty cycle. This |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | is the result of the automatic |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | amplitude regulation based on |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | current measurement. |  |  |  |  |
| R |  |  | 0x72 |  |  | 8+8 |  |  | PWM AUTO _ |  |  |  | These automatically generated values can be |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | read out in order to determine a default / |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | power up setting for PWM GRAD and |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | _ PWM OFS. _ |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  | bit 7… 0 | bit 7… 0 |  | PWM OFS AUTO: |  | 0…255 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | _ _ Automatically determined offset |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | value |  |  |  |  |
