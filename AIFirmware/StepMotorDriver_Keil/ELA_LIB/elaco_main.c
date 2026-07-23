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
#include "iwdg.h"
#include "ela_tmc5160_test.h"
/* module hlp start */

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
    ela_queue_init(&g_queue_st);
    ela_can_drv_init();
    ela_can_usr_init();
    ela_tmc5160_init();
    ela_motor_ctrl_init();

    /* 电机测试 (注释下面一行可跳过测试) */
    // ela_tmc5160_test_run();

    /* 主循环 */
    while (1)
    {
        ela_can_usr_process();

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

/* module cac end */
