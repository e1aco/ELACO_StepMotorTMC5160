/*****************************************************************************
 * @文件: timer_drv.h
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v1.0
 * @说明: 定时器硬件驱动层（HAL 原语）
 * @平台: STM32F407
 * @依赖: HAL_TIM
 ****************************************************************************/
#ifndef TIMER_DRV_H
#define TIMER_DRV_H

void DRV_TIMER_StartClosedLoop(void);
void DRV_TIMER_StopClosedLoop(void);

#endif /* TIMER_DRV_H */
