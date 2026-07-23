#include "ela_pid.h"

/* pid hlp start */

/****
 * @ 输入: pid:PID_T结构体指针
 * @ 输出: void
 * @ 说明: 限幅函数
 ********/
static int Pid_Clamp(int value, int min, int max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/* pid hlp end */
//----------------------------------------------------------------------------------
/* pid drv start */

/* pid drv end */
//----------------------------------------------------------------------------------
/* pid usr start */

/****
 * @ 输入: pid:PID_T结构体指针
 * @ 输出: void
 * @ 说明: 初始化PID结构体,设置默认参数
 ********/
void Pid_Init(PID_T *pid)
{
    pid->kp = 8192;       /* Kp = 0.125 (Q16: 8192 / 65536) */
    pid->ki = 2048;       /* Ki = 0.03125 */
    pid->kd = 4096;       /* Kd = 0.0625 */

    pid->target = 0;
    pid->error = 0;
    pid->error_prev = 0;
    pid->integral = 0;
    pid->derivative = 0;
    pid->output = 0;

    pid->out_max = 50000;     /* 最大速度 */
    pid->out_min = -50000;    /* 最小速度(负=反转) */
    pid->integral_max = 32768; /* 积分限幅 */

    pid->mode = PID_MODE_POSITION;
    pid->active = 0;
}

/****
 * @ 输入: pid:PID_T结构体指针
 *        target:目标位置(微步数)
 * @ 输出: void
 * @ 说明: 设置PID目标位置
 ********/
void Pid_SetTarget(PID_T *pid, int target)
{
    pid->target = target;
}

/****
 * @ 输入: pid:PID_T结构体指针
 *        kp,ki,kd:PID参数(Q16定点数)
 * @ 输出: void
 * @ 说明: 设置PID参数
 ********/
void Pid_SetParams(PID_T *pid, int kp, int ki, int kd)
{
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;
}

/****
 * @ 输入: pid:PID_T结构体指针
 * @ 输出: void
 * @ 说明: 启动PID控制
 ********/
void Pid_Start(PID_T *pid)
{
    pid->integral = 0;
    pid->error_prev = 0;
    pid->active = 1;
}

/****
 * @ 输入: pid:PID_T结构体指针
 * @ 输出: void
 * @ 说明: 停止PID控制
 ********/
void Pid_Stop(PID_T *pid)
{
    pid->active = 0;
    pid->output = 0;
}

/****
 * @ 输入: pid:PID_T结构体指针
 *        actual:当前位置(编码器值)
 * @ 输出: int:PID输出(速度值)
 * @ 说明: 执行一次PID计算
 ********/
int Pid_Calc(PID_T *pid, int actual)
{
    int p_term, i_term, d_term;

    if (0 == pid->active)
    {
        return 0;
    }

    /* 计算误差 */
    pid->error = pid->target - actual;

    /* 比例项 */
    p_term = (pid->kp * pid->error) >> 16;

    /* 积分项(带限幅) */
    pid->integral += pid->error;
    pid->integral = Pid_Clamp(pid->integral,
                              -pid->integral_max,
                              pid->integral_max);
    i_term = (pid->ki * pid->integral) >> 16;

    /* 微分项 */
    pid->derivative = pid->error - pid->error_prev;
    d_term = (pid->kd * pid->derivative) >> 16;
    pid->error_prev = pid->error;

    /* 输出 = P + I + D */
    pid->output = p_term + i_term + d_term;

    /* 输出限幅 */
    pid->output = Pid_Clamp(pid->output,
                            pid->out_min,
                            pid->out_max);

    /* 误差很小时停止积分累积 */
    if (pid->error > -10 && pid->error < 10)
    {
        pid->integral = 0;
    }

    return pid->output;
}

/****
 * @ 输入: pid:PID_T结构体指针
 * @ 输出: void
 * @ 说明: 复位PID状态(清零积分/微分)
 ********/
void Pid_Reset(PID_T *pid)
{
    pid->error = 0;
    pid->error_prev = 0;
    pid->integral = 0;
    pid->derivative = 0;
    pid->output = 0;
}

/* pid usr end */
//----------------------------------------------------------------------------------
