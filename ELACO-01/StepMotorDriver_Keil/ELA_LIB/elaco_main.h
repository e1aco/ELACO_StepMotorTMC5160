#ifndef _ELACO_MAIN_H_
#define _ELACO_MAIN_H_

#include "stdbool.h" // C库
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "stm32f4xx_hal.h" // HAL库 — 必须在 ELA 头文件之前
#include "main.h"
#include "tim.h"
#include "spi.h" 
#include "can.h"

#include "ela_uart.h"
#include "ela_queue.h"
#include "ela_can.h"
#include "ela_timer.h"
#include "ela_tmc5160.h"
#include "ela_eeprom.h"
#include "ela_button.h"



void elaco_main(void);
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);

#endif
