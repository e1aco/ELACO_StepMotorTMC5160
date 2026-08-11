# TMC5160A_Datasheet_Rev1.14 — 第8章 · p73

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
73 
 
 
 
www.trinamic.com 
Parameter 
Description 
Setting Comment 
TFD 
(fd3 
& 
HSTRT) 
Fast decay time setting. With CHM=1, these bits 
control the portion of fast decay for each chopper 
cycle. 
0 
slow decay only 
1…15 
duration of fast decay 
phase 
OFFSET 
(HEND) 
Sine wave offset. With CHM=1, these bits control 
the sine wave offset. A positive offset corrects for 
zero crossing error. 
0…2 
negative offset: -3…-1 
3 
no offset: 0 
4…15 
positive offset 1…12 
disfdcc 
Selects usage of the current comparator for 
termination of the fast decay cycle. If current 
comparator is enabled, it terminates the fast decay 
cycle in case the current reaches a higher negative 
value than the actual positive value. 
0 
enable comparator 
termination of fast decay 
cycle 
1 
end by time only 
 
 
 


<!-- detected tables -->

|  | Parameter |  |  | Description |  |  | Setting |  |  | Comment |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
| TFD (fd3 & HSTRT) | TFD |  | Fast decay time setting. With CHM=1, these bits control the portion of fast decay for each chopper cycle. |  |  | 0 |  |  | slow decay only |  |  |
|  | (fd3 & |  |  |  |  | 1…15 |  |  | duration of fast decay phase |  |  |
|  | HSTRT) |  |  |  |  |  |  |  |  |  |  |
| OFFSET (HEND) |  |  | Sine wave offset. With CHM=1, these bits control the sine wave offset. A positive offset corrects for zero crossing error. |  |  | 0…2 |  |  | negative offset: -3…-1 |  |  |
|  |  |  |  |  |  | 3 |  |  | no offset: 0 |  |  |
|  |  |  |  |  |  | 4…15 |  |  | positive offset 1…12 |  |  |
| disfdcc |  |  | Selects usage of the current comparator for termination of the fast decay cycle. If current comparator is enabled, it terminates the fast decay cycle in case the current reaches a higher negative value than the actual positive value. |  |  | 0 |  |  | enable comparator termination of fast decay cycle |  |  |
|  |  |  |  |  |  | 1 |  |  | end by time only |  |  |
