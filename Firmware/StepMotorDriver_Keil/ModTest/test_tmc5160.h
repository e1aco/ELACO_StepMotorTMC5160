#ifndef _TEST_TMC5160_H_
#define _TEST_TMC5160_H_

#include "elaco_main.h"

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 测试芯片1 SPI通讯 (IOIN + IFCNT + GCONF)
 ********/
unsigned char Test_TMC5160_Comm_Chip1(void);

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 测试芯片2 SPI通讯 (IOIN + IFCNT + GCONF)
 ********/
unsigned char Test_TMC5160_Comm_Chip2(void);

/****
 * @ 输入: void
 * @ 输出: 0=通过, 非0=失败
 * @ 说明: 依次测试芯片1和芯片2的SPI通讯,
 *        任一失败则停止并返回错误
 ********/
unsigned char Test_TMC5160_Comm(void);

#endif
