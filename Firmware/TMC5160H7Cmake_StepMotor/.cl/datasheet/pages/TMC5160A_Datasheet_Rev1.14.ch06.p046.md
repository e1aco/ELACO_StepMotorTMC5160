# TMC5160A_Datasheet_Rev1.14 — 第6章 · p46

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  46 
 
 
 
www.trinamic.com 
6.4.1 ENCMODE – Encoder Register 
0X38: ENCMODE – ENCODER REGISTER 
Bit Name Comment 
10 enc_sel_decimal 0 Encoder prescaler divisor binary mode:  
Counts ENC_CONST(fractional part) /65536 
1 Encoder prescaler divisor decimal mode:  
Counts in ENC_CONST(fractional part) /10000 
9 latch_x_act 1: Also latch XACTUAL position together with X_ENC. 
Allows latching the ramp generator position upon an N channel event as 
selected by pos_edge and neg_edge. 
8 clr_enc_x 0 Upon N event, X_ENC becomes latched to ENC_LATCH only 
1 Latch and additionally clear encoder counter X_ENC at N-event 
7 neg_edge n p N channel event sensitivity 
6 pos_edge 0 0 N channel event is active during an active N event level 
0 1 N channel is valid upon active going N event 
1 0 N channel is valid upon inactive going N event 
1 1 N channel is valid upon active going and inactive going N event 
5 clr_once 1: Latch or latch and c lear X_ENC on the next N event following the write 
access 
4 clr_cont 1: Always latch or latch and clear X_ENC upon an N event (once per 
revolution, it is recommended to combine this setting with edge sensitive 
N event) 
3 ignore_AB 0 An N event occurs only when polarities given by  
pol_N, pol_A and pol_B match. 
1 Ignore A and B polarity for N channel event 
2 pol_N Defines active polarity of N (0=low active, 1=high active) 
1 pol_B Required B polarity for an N channel event (0=neg., 1=pos.) 
0 pol_A Required A polarity for an N channel event (0=neg., 1=pos.) 
  
