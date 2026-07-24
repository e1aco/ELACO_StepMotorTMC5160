/****
 * @ 文件: ela_pid.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: PID 控制器，增量式算法
 ********/
#ifndef ELA_PID_H
#define ELA_PID_H

#include <stdint.h>

/* PID 结构体 */
typedef struct {
    int32_t kp;          /* 比例系数 */
    int32_t ki;          /* 积分系数 */
    int32_t kd;          /* 微分系数 */
    int32_t integral;    /* 积分累加 */
    int32_t last_error;  /* 上次误差 */
    int32_t out_min;     /* 输出下限 */
    int32_t out_max;     /* 输出上限 */
} PID_T;

void ela_pid_init(PID_T *pid,
                  int32_t kp, int32_t ki, int32_t kd,
                  int32_t out_min, int32_t out_max);
void ela_pid_reset(PID_T *pid);
int32_t ela_pid_calculate(PID_T *pid,
                          int32_t setpoint,
                          int32_t actual);
void ela_pid_set_params(PID_T *pid,
                        int32_t kp, int32_t ki, int32_t kd);

#endif
