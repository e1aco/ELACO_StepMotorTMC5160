/****
 * @ 文件: ela_motor_ctrl.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: 电机控制中间层，封装电机选择 + 运动执行
 * @ 依赖: ela_tmc5160_usr
 ********/
#ifndef ELA_MOTOR_CTRL_H
#define ELA_MOTOR_CTRL_H

#include <stdint.h>

/* 电机编号 */
#define MOTOR_CTRL_U1   0x01
#define MOTOR_CTRL_U2   0x02
#define MOTOR_CTRL_ALL  0x06

/* 运动参数组 ID */
#define MOTION_GROUP_1  0x01
#define MOTION_GROUP_2  0x02
#define MOTION_GROUP_3  0x03
#define MOTION_GROUP_4  0x04

void ela_motor_ctrl_init(void);
void ela_motor_ctrl_move_to(uint8_t motor, int32_t target);
void ela_motor_ctrl_move_by(uint8_t motor, int32_t offset);
void ela_motor_ctrl_set_velocity(uint8_t motor, int32_t velocity);
void ela_motor_ctrl_stop(uint8_t motor);
void ela_motor_ctrl_apply_profile(uint8_t motor, uint8_t group);
int32_t ela_motor_ctrl_get_position(uint8_t motor);
int32_t ela_motor_ctrl_get_encoder_position(uint8_t motor);
int32_t ela_motor_ctrl_get_encoder_deviation(uint8_t motor);
uint8_t ela_motor_ctrl_get_status(uint8_t motor);
uint8_t ela_motor_ctrl_get_stage(uint8_t motor);

#endif
