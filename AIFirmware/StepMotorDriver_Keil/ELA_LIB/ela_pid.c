/****
 * @ 文件: ela_pid.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: PID 控制器，增量式算法
 ********/
#include "ela_pid.h"

//----------------------------------------------------------------------------------
/* pid hlp start */

/****
 * @ 输入: pid: PID 结构体; value: 原始值; min: 下限; max: 上限
 * @ 输出: int32_t: 限幅后的值
 * @ 说明: 输出限幅
 ********/
static int32_t pid_clamp(int32_t value,
                         int32_t min, int32_t max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

/* pid hlp end */
//----------------------------------------------------------------------------------
/* pid usr start */

/****
 * @ 输入: pid: PID 结构体
 *        kp/ki/kd: PID 参数
 *        out_min/out_max: 输出限幅范围
 * @ 输出: 无
 * @ 说明: 初始化 PID 控制器
 ********/
void ela_pid_init(PID_T *pid,
                  int32_t kp, int32_t ki, int32_t kd,
                  int32_t out_min, int32_t out_max)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
    pid->integral = 0;
    pid->last_error = 0;
    pid->out_min = out_min;
    pid->out_max = out_max;
}

/****
 * @ 输入: pid: PID 结构体
 * @ 输出: 无
 * @ 说明: 复位 PID 状态（积分清零，误差清零）
 ********/
void ela_pid_reset(PID_T *pid)
{
    pid->integral = 0;
    pid->last_error = 0;
}

/****
 * @ 输入: pid: PID 结构体
 *        setpoint: 目标值
 *        actual: 实际值
 * @ 输出: int32_t: PID 输出（修正量）
 * @ 说明: 计算 PID 输出
 ********/
int32_t ela_pid_calculate(PID_T *pid,
                          int32_t setpoint,
                          int32_t actual)
{
    int32_t error;
    int32_t p_out, i_out, d_out, output;

    /* 计算误差 */
    error = setpoint - actual;

    /* P: 比例项 = Kp × 误差 */
    p_out = pid->kp * error;

    /* I: 积分项 = Ki × ∑误差 */
    pid->integral += error;
    i_out = pid->ki * pid->integral;

    /* D: 微分项 = Kd × (本次误差 - 上次误差) */
    d_out = pid->kd * (error - pid->last_error);
    pid->last_error = error;

    /* 合成输出 */
    output = p_out + i_out + d_out;

    /* 输出限幅 */
    output = pid_clamp(output, pid->out_min, pid->out_max);

    return output;
}

/****
 * @ 输入: pid: PID 结构体
 *        kp/ki/kd: 新的 PID 参数
 * @ 输出: 无
 * @ 说明: 在线调整 PID 参数
 ********/
void ela_pid_set_params(PID_T *pid,
                        int32_t kp, int32_t ki, int32_t kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

/* pid usr end */
