/****
 * @ 文件: ela_timer_drv.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-24
 * @ 版本: 1.0.0
 * @ 说明: 定时器硬件驱动层，HAL 原语
 ********/
#include "ela_timer_drv.h"
#include "tim.h"

//----------------------------------------------------------------------------------
/* timer drv start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 启动闭环控制定时器 (TIM7, 2ms 中断)
 ********/
void ela_timer_drv_start_cl(void)
{
    HAL_TIM_Base_Start_IT(&htim7);
}

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 停止闭环控制定时器
 ********/
void ela_timer_drv_stop_cl(void)
{
    HAL_TIM_Base_Stop_IT(&htim7);
}

/* timer drv end */
