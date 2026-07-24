/****
 * @ 文件: elaco_main.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.1.0
 * @ 说明: 应用主入口，主循环 + HAL 回调 + 初始化调用
 ********/
#include "elaco_main.h"
#include "ela_queue.h"
#include "ela_can_drv.h"
#include "ela_can_usr.h"
#include "ela_tmc5160_usr.h"
#include "ela_motor_ctrl.h"
#include "ela_closed_loop.h"
#include "iwdg.h"
#include "ela_tmc5160_test.h"
#include "tim.h"
/* module hlp start */

/* 闭环周期标志：TIM7 ISR 置位，主循环消费 */
static volatile uint8_t s_cl_tick_flag;

/* module hlp end */
//----------------------------------------------------------------------------------
/* module drv start */

/* module drv end */
//----------------------------------------------------------------------------------
/* module usr start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 应用主入口，由 CubeMX main.c 在初始化后调用
 ********/
void elaco_main(void)
{
    /* 模块初始化 */
		// 初始化CAN队列
    ela_queue_init(&g_queue_st);
		// 设置过滤器并使能CAN
    ela_can_drv_init();
    ela_can_usr_init();
		// 读取flash内存储值并初始化电机芯片
    ela_tmc5160_init();
    ela_motor_ctrl_init();
		// 初始化PID
    ela_closed_loop_init();
	
    /* 电机测试 (注释下面一行可跳过测试) */
    // ela_tmc5160_test_run();

    /* 主循环 */
    while (1)
    {
        ela_can_usr_process();

        /* 闭环控制：TIM7 ISR 触发，在主循环中执行 SPI 操作 */
        if (s_cl_tick_flag)
        {
            s_cl_tick_flag = 0;
						// ela_closed_loop_tick(MOTOR_CTRL_U1);
            ela_closed_loop_tick(MOTOR_CTRL_U2);
        }

        ela_tmc5160_save_config();

        /* 独立看门狗喂狗 */
        // HAL_IWDG_Refresh(&hiwdg);
    }
}

/* module usr end */
//----------------------------------------------------------------------------------
/* module cac start */

/****
 * @ 输入: hcan: CAN 句柄
 * @ 输出: 无
 * @ 说明: CAN RX0 中断回调，校验后入队
 ********/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    uint8_t sum = 0;
    uint8_t i;

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) != HAL_OK)
    {
        return;
    }

    /* 校验和: 前7字节累加取低8位 */
    for (i = 0; i < 7; i++)
    {
        sum += rx_data[i];
    }
    if (sum != rx_data[7])
    {
        return;
    }

    ela_queue_insert(&g_queue_st, rx_data);
}

/****
 * @ 输入: htim: 定时器句柄
 * @ 输出: 无
 * @ 说明: 定时器周期中断回调（仅设标志，业务在主循环执行）
 * @ 注意: ISR 中禁止 SPI/Delay 操作，避免与主循环冲突
 ********/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM7)
    {
        s_cl_tick_flag = 1;
    }
}

/* module cac end */
