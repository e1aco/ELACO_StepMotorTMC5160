#include "ela_timer.h"

/* timer drv start */

/****
 * @ 说明: 使能定时器5中断并启动定时器5，
 *        配置定时器4通道1为PWM输出
 ********/
void Timer_Init(void)
{
    HAL_TIM_Base_Start_IT(&htim5); // 启动定时器5并使能中断

    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 3);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

/* timer drv end */
