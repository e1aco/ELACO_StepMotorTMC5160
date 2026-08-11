# TMC5160A_Datasheet_Rev1.14 — 第6章 · p50

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  
50 
 
 
 
www.trinamic.com 
6.5.1 
MSLUTSEL – Look up Table Segmentation Definition 
0X68: MSLUTSEL – LOOK UP TABLE SEGMENTATION DEFINITION 
Bit 
Name 
Function 
Comment 
31 
X3 
LUT segment 3 start 
The sine wave look up table can be divided into up to 
four segments using an individual step width control 
entry Wx. The segment borders are selected by X1, X2 
and X3. 
 
Segment 0 goes from 0 to X1-1. 
Segment 1 goes from X1 to X2-1. 
Segment 2 goes from X2 to X3-1. 
Segment 3 goes from X3 to 255. 
 
For defined response the values shall satisfy: 
0<X1<X2<X3 
 
30 
29 
28 
27 
26 
25 
24 
23 
X2 
LUT segment 2 start 
22 
21 
20 
19 
18 
17 
16 
15 
X1 
LUT segment 1 start 
14 
13 
12 
11 
10 
9 
8 
7 
W3 
LUT width select from 
ofs(X3) to ofs255 
Width control bit coding W0…W3: 
%00:  
MSLUT entry 0, 1 select: -1, +0 
%01:  
MSLUT entry 0, 1 select: +0, +1 
%10:  
MSLUT entry 0, 1 select: +1, +2 
%11:  
MSLUT entry 0, 1 select: +2, +3 
6 
5 
W2 
LUT width select from 
ofs(X2) to ofs(X3-1) 
4 
3 
W1 
LUT width select from 
ofs(X1) to ofs(X2-1) 
2 
1 
W0 
LUT width select from 
ofs00 to ofs(X1-1) 
0 
 
 
 


<!-- detected tables -->

|  | 0X68: MSLUTSEL – LOOK UP TABLE SEGMENTATION DEFINITION |  |  |  |  |  |  |  |  |  |  |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  | Bit |  |  | Name |  |  | Function |  |  | Comment |  |
| 31 |  |  | X3 |  |  | LUT segment 3 start |  |  | The sine wave look up table can be divided into up to four segments using an individual step width control entry Wx. The segment borders are selected by X1, X2 and X3. Segment 0 goes from 0 to X1-1. Segment 1 goes from X1 to X2-1. Segment 2 goes from X2 to X3-1. Segment 3 goes from X3 to 255. For defined response the values shall satisfy: 0<X1<X2<X3 |  |  |
| 30 |  |  |  |  |  |  |  |  |  |  |  |
| 29 |  |  |  |  |  |  |  |  |  |  |  |
| 28 |  |  |  |  |  |  |  |  |  |  |  |
|  | 27 |  |  |  |  |  |  |  |  |  |  |
|  | 26 |  |  |  |  |  |  |  |  |  |  |
|  | 25 |  |  |  |  |  |  |  |  |  |  |
|  | 24 |  |  |  |  |  |  |  |  |  |  |
| 23 |  |  | X2 |  |  | LUT segment 2 start |  |  |  |  |  |
| 22 |  |  |  |  |  |  |  |  |  |  |  |
| 21 |  |  |  |  |  |  |  |  |  |  |  |
| 20 |  |  |  |  |  |  |  |  |  |  |  |
|  | 19 |  |  |  |  |  |  |  |  |  |  |
|  | 18 |  |  |  |  |  |  |  |  |  |  |
|  | 17 |  |  |  |  |  |  |  |  |  |  |
|  | 16 |  |  |  |  |  |  |  |  |  |  |
| 15 |  |  | X1 |  |  | LUT segment 1 start |  |  |  |  |  |
| 14 |  |  |  |  |  |  |  |  |  |  |  |
| 13 |  |  |  |  |  |  |  |  |  |  |  |
| 12 |  |  |  |  |  |  |  |  |  |  |  |
|  | 11 |  |  |  |  |  |  |  |  |  |  |
|  | 10 |  |  |  |  |  |  |  |  |  |  |
|  | 9 |  |  |  |  |  |  |  |  |  |  |
|  | 8 |  |  |  |  |  |  |  |  |  |  |
| 7 |  |  | W3 |  |  | LUT width select from ofs(X3) to ofs255 |  |  | Width control bit coding W0…W3: %00: MSLUT entry 0, 1 select: -1, +0 %01: MSLUT entry 0, 1 select: +0, +1 %10: MSLUT entry 0, 1 select: +1, +2 %11: MSLUT entry 0, 1 select: +2, +3 |  |  |
| 6 |  |  |  |  |  |  |  |  |  |  |  |
| 5 |  |  | W2 |  |  | LUT width select from ofs(X2) to ofs(X3-1) |  |  |  |  |  |
| 4 |  |  |  |  |  |  |  |  |  |  |  |
|  | 3 |  | W1 |  |  | LUT width select from ofs(X1) to ofs(X2-1) |  |  |  |  |  |
|  | 2 |  |  |  |  |  |  |  |  |  |  |
|  | 1 |  | W0 |  |  | LUT width select from ofs00 to ofs(X1-1) |  |  |  |  |  |
|  | 0 |  |  |  |  |  |  |  |  |  |  |
