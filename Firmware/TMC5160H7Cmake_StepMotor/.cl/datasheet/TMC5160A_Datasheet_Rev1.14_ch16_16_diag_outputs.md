# TMC5160A_Datasheet_Rev1.14 — 第16章 16 DIAG Outputs

--- [PAGE 97] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  97 
 
 
 
www.trinamic.com 
16 DIAG Outputs  
16.1 STEP/DIR Mode 
Operation with an external  motion controller often requires quick reaction to certain states of the 
stepper motor driver. Therefore, the DIAG outputs supply a configurable set of different real time 
information complementing the STEP/DIR interface. 
 
Both, the information available at DIAG0 and DIAG1 can be selected as well as the type of output 
(low active open drain – default setting, or high active push-pull). In order to determine a reset of the 
driver, DIAG0 always shows a power -on reset condition by pulling low during a reset c ondition. 
Figure 16.1 shows the available signals and control bits. 
 
DIAG1
DIAG0 PMD
PDD
PDD=100k pulldown
PMD=50k to VCC/2
Power-on reset
Driver error
diag0_error
Overtemp. prewarning
diag0_otpw
Stall
diag0_stall
diag0_pushpull
Sequencer microstep 0 index
diag1_index
Chopper on-state
diag1_onstate
diag1_steps_skipped
diag1_pushpull
diag1_stall
dcStep steps skipped
 
Figure 16.1 DIAG outputs in STEP/DIR mode 
The stall output signal allows StallGuard2 to be handled by the external motion cont roller like a stop 
switch. The index output signals the microstep counter zero position, to allow the application to 
reference the drive to a certain current pattern. Chopp er on -state shows the on -state of both coi l 
choppers (alternating) when working in SpreadCycle or constant off time in order to determine the 
duty cycle. The DcStep skipped information is an alternative way to find out when DcStep runs with a 
velocity below the step velocity. It toggles with each step not taken by the sequencer.  
 
Attention 
The duration of the index pulse corresponds to the duration of the microstep . When working without 
interpolation at less than 256 microsteps, the index time goes down to two CLK clock cycles. 
 
16.2 Motion Controller Mode 
In motion controller mode, the DIAG outputs deliver a position compare signal to allow exact 
triggering of external l ogic, and an interrupt signal in order to trigger software to certain conditions 
within the motion ramp. Either an open drain (active low) output signal can be chosen (default), or an 
active high push-pull output signal. When using the open drain output, a n external pull up resistor in 
the range 4.7kΩ to 33kΩ is required. DIAG0 also becomes driven low upon a reset c ondition. However 
--- [PAGE 98] ---
TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  98 
 
 
 
www.trinamic.com 
the end of the reset condition cannot be determined by monitoring DIAG0 in this configuration, 
because event_pos_reached flag also becomes active upon reset and thus the pin stays actively low  
after the reset condition. In order to safely determine a reset condition, monitor the reset flag by SPI 
or read out any register to confirm that the chip is powered up.  
 
DIAG1
DIAG0 PMD
PDD
PDD=100k pulldown
PMD=50k to VCC/2
Power-on reset
Toggle upon each step
diag0_step
diag0_pushpull
diag1_pushpull
event_pos_reached event_stop_sgevent_stop_r event_stop_l
N_event
Direction
diag1_dir Position compare 
XACTUAL = X_COMPARE
Interrupt-signal deviation_warn
 
Figure 16.2 DIAG outputs with SD_MODE=0 
   
