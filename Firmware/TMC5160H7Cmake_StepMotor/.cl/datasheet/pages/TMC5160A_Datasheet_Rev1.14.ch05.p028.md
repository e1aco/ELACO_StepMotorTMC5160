# TMC5160A_Datasheet_Rev1.14 — 第5章 · p28

TMC5160/TMC5160A DATASHEET (Rev. 1.14 / 2020-MAY-19)  28 
 
 
 
www.trinamic.com 
5.2 CRC Calculation 
An 8 bit CRC polynomial is used for checking both read and write access. It allows detection of up to 
eight single bit errors. The CRC8 -ATM polynomial wi th an initial value of zero is applie d LSB to MSB, 
including the sync - and addressing byte. The sync nibble is assumed to always be correct. The 
TMC5160 responds only to correctly transmitted datagrams containing its own slave address. It 
increases its datagram counter for each correctly received write access datagram. 
 
𝐶𝑅𝐶 = 𝑥8 + 𝑥2 + 𝑥1 + 𝑥0 
SERIAL CALCULATION EXAMPLE  
CRC = (CRC << 1) OR (CRC.7 XOR CRC.1 XOR CRC.0 XOR [new incoming bit]) 
 
C-CODE EXAMPLE FOR CRC CALCULATION 
void swuart_calcCRC(UCHAR* datagram, UCHAR datagramLength) 
{ 
  int i,j; 
  UCHAR* crc = datagram + (datagramLength-1); // CRC located in last byte of message 
  UCHAR currentByte; 
 
  *crc = 0; 
  for (i=0; i<(datagramLength-1); i++) {      // Execute for all bytes of a message 
    currentByte = datagram[i];                // Retrieve a byte to be sent from Array 
    for (j=0; j<8; j++) { 
      if ((*crc >> 7) ^ (currentByte&0x01))   // update CRC based result of XOR operation 
      { 
        *crc = (*crc << 1) ^ 0x07; 
      } 
      else 
      { 
        *crc = (*crc << 1); 
      } 
      currentByte = currentByte >> 1; 
    } // for CRC bit 
  } // for message byte 
} 
5.3 UART Signals 
The UART interface on the TMC5160 comprises four signals: 
TMC5160 UART INTERFACE SIGNALS 
SWP Non-inverted data input and output 
SWN Inverted data input and output for use in differential transmission . Can be left open 
in a 5V IO voltage system. Tie to the half IO level voltage for best performance  in a 
3.3V single wire non-differential application. 
SDI_CFG1 
(NAI) 
Address increment pin for chained sequential addressing scheme 
SDO_CFG0 
(NAO) 
Next address output pin for chained sequential addressing scheme  (reset default= 
high) 
 
In UART mode (SPI_MODE low and SD_MODE low) the slave checks the s ingle wire SWP and SWN for 
correctly received datagr ams with its own address continuously. Both signals are switched as input 
during this time. It adapts to the baud rate based on the sync nibble, as described before. In case of 
a read access, it switches on its output drivers on SWP and SWN and sends its r esponse using the 
same baud rate. 
  
