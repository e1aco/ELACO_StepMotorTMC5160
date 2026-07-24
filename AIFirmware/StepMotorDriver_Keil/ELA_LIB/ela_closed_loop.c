/****
 * @ 文件: ela_closed_loop.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: 闭环控制模块，PID + 编码器反馈
 * @ 依赖: ela_tmc5160_usr, ela_motor_ctrl, ela_timer_drv
 ********/
#include "ela_closed_loop.h"
#include "ela_pid.h"
#include "ela_motor_ctrl.h"
#include "ela_tmc5160_usr.h"
#include "ela_timer_drv.h"

//----------------------------------------------------------------------------------
/* closed loop hlp start */

/* 默认 PID 参数（保守值，首次测试用） */
#define PID_KP_DEFAULT      10
#define PID_KI_DEFAULT      1
#define PID_KD_DEFAULT      2

/* 输出限幅（每周期最大修正量） */
#define PID_OUT_MIN         (-200)
#define PID_OUT_MAX         200

/* closed loop hlp end */
//----------------------------------------------------------------------------------
/* closed loop usr start */

static PID_T g_pid_st;

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 初始化闭环 PID 参数
 * @ 注意: 闭环使能标志由 ela_tmc5160_init 从 Flash 加载
 ********/
void ela_closed_loop_init(void)
{
    ela_pid_init(&g_pid_st,
                 PID_KP_DEFAULT, PID_KI_DEFAULT, PID_KD_DEFAULT,
                 PID_OUT_MIN, PID_OUT_MAX);
    ela_timer_drv_start_cl();
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: 无
 * @ 说明: 使能闭环控制，已使能时跳过
 * @ 注意: 状态变化时自动标记脏位，由主循环写入 Flash
 ********/
void ela_closed_loop_enable(uint8_t motor)
{	
    TMC5160_CHIP_T *chip = ela_motor_ctrl_get_chip(motor);
    if ((void *)0 != chip)
    {
        if (CLOSED_LOOP_ON == chip->closed_loop) return;
        chip->closed_loop = CLOSED_LOOP_ON;
        ela_tmc5160_set_dirty();
    }
    ela_pid_reset(&g_pid_st);
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: 无
 * @ 说明: 禁用闭环控制，已禁用时跳过
 * @ 注意: 状态变化时自动标记脏位，由主循环写入 Flash
 ********/
void ela_closed_loop_disable(uint8_t motor)
{
    TMC5160_CHIP_T *chip = ela_motor_ctrl_get_chip(motor);
    if ((void *)0 != chip)
    {
        if (CLOSED_LOOP_OFF == chip->closed_loop) return;
        chip->closed_loop = CLOSED_LOOP_OFF;
        ela_tmc5160_set_dirty();
    }
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: uint8_t: 闭环模式状态
 * @ 说明: 获取当前闭环模式
 ********/
uint8_t ela_closed_loop_get_mode(uint8_t motor)
{
    TMC5160_CHIP_T *chip = ela_motor_ctrl_get_chip(motor);
    if ((void *)0 != chip)
    {
        return chip->closed_loop;
    }
    return CLOSED_LOOP_OFF;
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: 无
 * @ 说明: 闭环控制周期（定时器中断调用）
 *   1. 读取编码器位置 (X_ENC)
 *   2. 读取目标位置 (XTARGET)
 *   3. PID 计算修正量
 *   4. 更新 XTARGET
 ********/
void ela_closed_loop_tick(uint8_t motor)
{
    TMC5160_CHIP_T *chip;
    int32_t actual, target, correction, new_target;

    chip = ela_motor_ctrl_get_chip(motor);
    if ((void *)0 == chip) return;

    if (CLOSED_LOOP_OFF == chip->closed_loop)
    {
        return;
    }

    /* 读取编码器位置（实际位置） */
    actual = ela_motor_ctrl_get_encoder_position(motor);

    /* 读取目标位置 */
    target = ela_motor_ctrl_get_position(motor);

    /* PID 计算修正量 */
    correction = ela_pid_calculate(&g_pid_st, target, actual);

    /* 更新目标位置 */
    new_target = target + correction;
    ela_tmc5160_move_to(
        (MOTOR_CTRL_U1 == motor) ?
        &g_tmc5160_chip1_st : &g_tmc5160_chip2_st,
        new_target);
}

/* closed loop usr end */
