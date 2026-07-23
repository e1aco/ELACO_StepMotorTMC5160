/****
 * @ 文件: ela_can_usr.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.0.0
 * @ 说明: CAN 协议解析层，命令解析 + 反馈组装
 ********/
#ifndef ELA_CAN_USR_H
#define ELA_CAN_USR_H

#include "stdint.h"

/* module hlp start */

#define BIT(n)          (1UL << (n))

/* 命令码 */
#define CMD_ABS_POS     0x01
#define CMD_REL_CW      0x02
#define CMD_REL_CCW     0x03
#define CMD_VELOCITY    0x04
#define CMD_STOP        0x05
#define CMD_PID_ADJUST  0x06

/* 电机选择 */
#define MOTOR_U1        0x01
#define MOTOR_U2        0x02
#define MOTOR_ALL       0x06

/* 运动参数组 */
#define MOTION_GROUP_1  0x01
#define MOTION_GROUP_2  0x02
#define MOTION_GROUP_3  0x03
#define MOTION_GROUP_4  0x04

/* PID 参数类型 */
#define PID_KP          0x01
#define PID_KI          0x02
#define PID_KD          0x03
#define PID_OUT_MAX     0x04
#define PID_OUT_MIN     0x05
#define PID_INT_MAX     0x06

/* 状态标志位 */
#define STATUS_DONE     BIT(0)
#define STATUS_STALL    BIT(1)
#define STATUS_OTW      BIT(2)
#define STATUS_DRV_ERR  BIT(3)
#define STATUS_SPI_ERR  BIT(4)

/* 运动阶段标志 */
#define STAGE_ACCEL     BIT(0)
#define STAGE_CRUISE    BIT(1)
#define STAGE_DECEL     BIT(2)
#define STAGE_HOME_WAIT BIT(3)
#define STAGE_LOCKED    BIT(4)

/* module hlp end */

typedef struct {
    int32_t  value;
    uint8_t  cmd;
    uint8_t  motor;
    uint8_t  param;
    uint8_t  checksum;
} CAN_CMD_T;

void ela_can_usr_init(void);
void ela_can_usr_process(void);
uint8_t ela_can_usr_send_motion_feedback(uint8_t motor, int32_t pos, uint8_t status, uint8_t stage);
uint8_t ela_can_usr_send_pid_feedback(uint8_t motor, uint8_t pid_type, int32_t value);

#endif
