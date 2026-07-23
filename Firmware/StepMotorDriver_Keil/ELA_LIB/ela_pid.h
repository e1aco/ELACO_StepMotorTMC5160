#ifndef _ELA_PID_H_
#define _ELA_PID_H_

#include "elaco_main.h"

/* PID控制模式 */
#define PID_MODE_POSITION   0   /* 位置闭环 */
#define PID_MODE_VELOCITY   1   /* 速度闭环 */

/* PID结构体 */
typedef struct {
    /* PID参数 */
    int kp;             /* 比例系数 (Q16定点数) */
    int ki;             /* 积分系数 (Q16定点数) */
    int kd;             /* 微分系数 (Q16定点数) */

    /* 控制变量 */
    int target;         /* 目标位置 */
    int error;          /* 当前误差 */
    int error_prev;     /* 上次误差 */
    int integral;       /* 积分累加 */
    int derivative;     /* 微分项 */
    int output;         /* PID输出(速度) */

    /* 限幅 */
    int out_max;        /* 输出最大值 */
    int out_min;        /* 输出最小值 */
    int integral_max;   /* 积分限幅 */

    /* 状态 */
    unsigned char mode; /* 控制模式 */
    unsigned char active; /* 1=PID运行中, 0=停止 */
} PID_T;

/* 函数原型 */
void Pid_Init(PID_T *pid);
void Pid_SetTarget(PID_T *pid, int target);
void Pid_SetParams(PID_T *pid, int kp, int ki, int kd);
void Pid_Start(PID_T *pid);
void Pid_Stop(PID_T *pid);
int  Pid_Calc(PID_T *pid, int actual);
void Pid_Reset(PID_T *pid);

#endif
