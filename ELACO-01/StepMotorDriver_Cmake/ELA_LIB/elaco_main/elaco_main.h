#ifndef _ELACO_MAIN_H_
#define _ELACO_MAIN_H_

#include "cmd_queue.h"
#include "stm32f4xx_hal.h"
#include "can.h"
#include "tim.h"
#include "tmc5160.h"
#include "iwdg.h"

extern volatile unsigned char Receive_Count;

/* 命令定义 */
#define CHANGE_LIGHT            0x01 
#define CHANGE_CONSTANT_LIGHT   0x02
#define CAN_TEST                0x08
/* 有效数据长度 */
#define DATA_LENGTH             6
#define RX_LENGTH               4
#define RX_CAN_ID               0x1AA55F02

typedef volatile struct LIGHT_CANS
{
    unsigned char Constant_Light_Flag;      // 是否为常亮模式的标志
    unsigned char Rx_Lights[DATA_LENGTH]; // 接收的灯光数据
    unsigned char Light_Changed_Flag;     // 灯光状态是否改变的标志
    unsigned char Tx_CAN_Buffer[RX_LENGTH]; // 发送CAN消息的缓冲区
}LIGHT_CANS_T;

extern LIGHT_CANS_T CAN_COL; // 定义一个全局的灯光和CAN数据结构实例

void elaco_main_proc(void);

#endif
