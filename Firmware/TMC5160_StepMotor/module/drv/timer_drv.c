/*****************************************************************************
 * @文件: timer_drv.c
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v1.0
 * @说明: 定时器硬件驱动层（HAL 原语）
 * @平台: STM32F407
 * @依赖: HAL_TIM
 ****************************************************************************/
#include "drv/timer_drv.h"
#include "tim.h"

/* ==== 接口实现 ==== */

/**
 * @输入 无
 * @输出 无
 * @说明 启动闭环控制定时器（TIM7 周期中断，置闭环节拍标志）
 * @注意 TIM7 周期由 CubeMX 配置：PSC=83, ARR=1999
 *       时钟依据：APB1 timer clock=84MHz(SYSCLK84M/APB1/2×2)，
 *       84M/(84×2000)=500Hz=2ms（待实测确认）
 */
void DRV_TIMER_StartClosedLoop(void)
{
    HAL_TIM_Base_Start_IT(&htim7);
}

/**
 * @输入 无
 * @输出 无
 * @说明 停止闭环控制定时器
 */
void DRV_TIMER_StopClosedLoop(void)
{
    HAL_TIM_Base_Stop_IT(&htim7);
}
