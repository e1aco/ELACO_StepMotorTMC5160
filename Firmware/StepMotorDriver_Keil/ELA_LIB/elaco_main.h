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

/* 用户可配置宏定义 */
#define ModTest
#define TMC5160_TEST_RETRY_COUNT  3  /* SPI通讯失败重试次数 */
#define TMC5160_TEST_GCONF_ENABLE 1  /* 1=启用GCONF写读验证 */

/* CAN命令码定义 */
#define CMD_ABS_POSITION    0x01    /* 绝对位置移动(PID闭环) */
#define CMD_REL_FORWARD     0x02    /* 相对位置正转(PID闭环) */
#define CMD_REL_REVERSE     0x03    /* 相对位置反转(PID闭环) */
#define CMD_VELOCITY_MODE   0x04    /* 速度模式(开环) */
#define CMD_STOP            0x05    /* 停止/刹车 */
#define CMD_PID_TUNING      0x06    /* PID调参 */

/* PID调参参数类型定义 (命令码0x06, 字节[6]) */
#define PID_PARAM_KP        0x01    /* 比例系数(Q16定点数) */
#define PID_PARAM_KI        0x02    /* 积分系数(Q16定点数) */
#define PID_PARAM_KD        0x03    /* 微分系数(Q16定点数) */
#define PID_PARAM_OUT_MAX   0x04    /* 最大输出速度(直接整数) */
#define PID_PARAM_OUT_MIN   0x05    /* 最小输出速度(直接整数) */
#define PID_PARAM_INT_MAX   0x06    /* 积分限幅(直接整数) */

#endif
