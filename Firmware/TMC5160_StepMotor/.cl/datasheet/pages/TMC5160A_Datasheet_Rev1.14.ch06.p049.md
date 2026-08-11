# TMC5160A_Datasheet_Rev1.14 — 第6章 · p49

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
49 
 
 
 
www.trinamic.com 
DRIVER REGISTER SET (0X6C…0X7F)  
R/W 
Addr 
n 
Register 
Description / bit names 
Range [Unit] 
bit 23… 16
  
PWM_GRAD_AUTO: 
Automatically 
determined 
gradient value 
0…255 
R 
0x73 
20 
LOST_STEPS 
Number of input steps skipped due to higher 
load in DcStep operation, if step input does 
not stop when DC_OUT is low. This counter 
wraps around after 2^20 steps. Counts up or 
down depending on direction. Only with 
SDMODE=1. 
 
 
 
 
 
 
 
 
 
 
 
MICROSTEP TABLE CALCULATION FOR A SINE WAVE EQUIVALENT TO THE POWER ON DEFAULT 
 
𝑟𝑜𝑢𝑛𝑑 (248 ∗ 𝑠𝑖𝑛(2 ∗𝑃𝐼∗
𝑖
1024 +
𝑃𝐼
1024)) −1 
 
- 
i:[0… 255] is the table index 
- 
The amplitude of the wave is 248. The resulting maximum positive value is 247 and the 
maximum negative value is -248. 
- 
The round function rounds values from 0.5 to 1.4999 to 1 


<!-- detected tables -->

|  | DRIVER REGISTER SET (0X6C…0X7F) |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
|  | R/W |  |  | Addr |  |  | n |  |  | Register |  |  | Description / bit names |  |  |  |  | Range [Unit] |  |
|  |  |  |  |  |  |  |  |  |  |  |  | bit 23… 16 | bit 23… 16 |  | PWM GRAD AUTO: |  | 0…255 |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | _ _ Automatically determined |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  | gradient value |  |  |  |  |
| R |  |  | 0x73 |  |  | 20 |  |  | LOST STEPS _ |  |  |  | Number of input steps skipped due to higher |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | load in DcStep operation, if step input does |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | not stop when DC OUT is low. This counter |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | _ wraps around after 2^20 steps. Counts up or |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | down depending on direction. Only with |  |  |  |  |  |  |
|  |  |  |  |  |  |  |  |  |  |  |  |  | SDMODE=1. |  |  |  |  |  |  |
