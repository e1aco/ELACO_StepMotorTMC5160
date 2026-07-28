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
#define PID_KP_DEFAULT      5
#define PID_KI_DEFAULT      0
#define PID_KD_DEFAULT      0

/* 输出限幅（每周期最大修正量） */
#define PID_OUT_MIN         (-200)
#define PID_OUT_MAX         200

/* 命令目标位置（用户要求的位置，闭环对比基准） */
static int32_t s_cmd_target[2];

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
    s_cmd_target[0] = 0;
    s_cmd_target[1] = 0;
    ela_timer_drv_start_cl();
}

/****
 * @ 输入: motor: 电机编号; target: 命令目标位置
 * @ 输出: 无
 * @ 说明: 设置闭环命令基准目标，由电机控制层在发出运动指令时调用
 ********/
void ela_closed_loop_set_target(uint8_t motor, int32_t target)
{
    if (MOTOR_CTRL_U1 == motor)
    {
        s_cmd_target[0] = target;
    }
    else if (MOTOR_CTRL_U2 == motor)
    {
        s_cmd_target[1] = target;
    }
    ela_pid_reset(&g_pid_st);
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
 * @ 说明: 闭环控制周期（主循环调用）
 *   1. 等待斜坡完成（XACTUAL == 命令目标）后才介入
 *   2. 读取编码器 (X_ENC)，对比命令目标
 *   3. 偏差超出容差 → 补步 + 更新命令目标
 * @ 注意: 不干涉正在运行的斜坡，防止目标跑飞
 ********/
void ela_closed_loop_tick(uint8_t motor)
{
    TMC5160_CHIP_T *chip;
    int32_t x_actual, x_enc, cmd_target, deviation, new_target;
    int32_t idx;

    chip = ela_motor_ctrl_get_chip(motor);
    if ((void *)0 == chip) return;

    if (CLOSED_LOOP_OFF == chip->closed_loop)
    {
        return;
    }

    /* 取命令目标（固定值） */
    idx = (MOTOR_CTRL_U1 == motor) ? 0 : 1;
    cmd_target = s_cmd_target[idx];

    /* 斜坡未完成 → 不干涉，让 TMC5160 自行到位 */
    x_actual = ela_motor_ctrl_get_position(motor);
    if (x_actual != cmd_target)
    {
        return;
    }

    /* 读编码器，算偏差 */
    x_enc = ela_motor_ctrl_get_encoder_position(motor);
    deviation = cmd_target - x_enc;

    /* 偏差在容差内 → 不动 */
    if (deviation > -TMC5160_ENC_TOLERANCE &&
        deviation <  TMC5160_ENC_TOLERANCE)
    {
        return;
    }

    /* 偏差超出容差 → 补步，同时更新命令目标 */
    new_target = cmd_target + deviation;
    ela_closed_loop_set_target(motor, new_target);
    ela_tmc5160_move_to(chip, new_target);
}

/* closed loop usr end */
