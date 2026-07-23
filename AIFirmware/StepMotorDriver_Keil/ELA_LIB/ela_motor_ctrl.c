/****
 * @ 文件: ela_motor_ctrl.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-23
 * @ 版本: 1.0.0
 * @ 说明: 电机控制中间层，封装电机选择 + 运动执行
 * @ 依赖: ela_tmc5160_usr
 ********/
#include "ela_motor_ctrl.h"
#include "ela_tmc5160_usr.h"

//----------------------------------------------------------------------------------
/* motor ctrl hlp start */

/****
 * @ 输入: motor: 电机编号
 * @ 输出: TMC5160_CHIP_T*: 芯片指针，无效编号返回 NULL
 * @ 说明: 根据电机编号获取 TMC5160 芯片指针
 ********/
static TMC5160_CHIP_T *get_chip(uint8_t motor)
{
    if (MOTOR_CTRL_U1 == motor)
    {
        return &g_tmc5160_chip1_st;
    }
    else if (MOTOR_CTRL_U2 == motor)
    {
        return &g_tmc5160_chip2_st;
    }
    return (void *)0;
}

/* motor ctrl hlp end */
//----------------------------------------------------------------------------------
/* motor ctrl usr start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 电机控制模块初始化
 ********/
void ela_motor_ctrl_init(void)
{
    /* 初始化由 ela_tmc5160_init() 完成，此处无需额外操作 */
}

/****
 * @ 输入: motor: 电机编号; target: 目标绝对位置
 * @ 输出: 无
 * @ 说明: 控制电机运动到目标位置，支持单电机或全部电机
 ********/
void ela_motor_ctrl_move_to(uint8_t motor, int32_t target)
{
    if (MOTOR_CTRL_ALL == motor)
    {
        ela_tmc5160_move_to(&g_tmc5160_chip1_st, target);
        ela_tmc5160_move_to(&g_tmc5160_chip2_st, target);
    }
    else
    {
        TMC5160_CHIP_T *chip = get_chip(motor);
        if ((void *)0 != chip)
        {
            ela_tmc5160_move_to(chip, target);
        }
    }
}

/****
 * @ 输入: motor: 电机编号; offset: 相对偏移量(正=正转, 负=反转)
 * @ 输出: 无
 * @ 说明: 控制电机运动指定偏移量
 ********/
void ela_motor_ctrl_move_by(uint8_t motor, int32_t offset)
{
    if (MOTOR_CTRL_ALL == motor)
    {
        ela_tmc5160_move_by(&g_tmc5160_chip1_st, offset);
        ela_tmc5160_move_by(&g_tmc5160_chip2_st, offset);
    }
    else
    {
        TMC5160_CHIP_T *chip = get_chip(motor);
        if ((void *)0 != chip)
        {
            ela_tmc5160_move_by(chip, offset);
        }
    }
}

/****
 * @ 输入: motor: 电机编号; velocity: 目标速度(正=正转, 负=反转)
 * @ 输出: 无
 * @ 说明: 切换速度模式持续旋转
 ********/
void ela_motor_ctrl_set_velocity(uint8_t motor, int32_t velocity)
{
    if (MOTOR_CTRL_ALL == motor)
    {
        ela_tmc5160_set_velocity(&g_tmc5160_chip1_st, velocity);
        ela_tmc5160_set_velocity(&g_tmc5160_chip2_st, velocity);
    }
    else
    {
        TMC5160_CHIP_T *chip = get_chip(motor);
        if ((void *)0 != chip)
        {
            ela_tmc5160_set_velocity(chip, velocity);
        }
    }
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: 无
 * @ 说明: 停止电机，切回定位模式保持锁轴
 ********/
void ela_motor_ctrl_stop(uint8_t motor)
{
    if (MOTOR_CTRL_ALL == motor)
    {
        ela_tmc5160_stop(&g_tmc5160_chip1_st);
        ela_tmc5160_stop(&g_tmc5160_chip2_st);
    }
    else
    {
        TMC5160_CHIP_T *chip = get_chip(motor);
        if ((void *)0 != chip)
        {
            ela_tmc5160_stop(chip);
        }
    }
}

/****
 * @ 输入: motor: 电机编号; group: 运动参数组 ID (1~4)
 * @ 输出: 无
 * @ 说明: 应用预定义的运动参数组
 ********/
void ela_motor_ctrl_apply_profile(uint8_t motor, uint8_t group)
{
    if (MOTOR_CTRL_ALL == motor)
    {
        ela_tmc5160_apply_profile(&g_tmc5160_chip1_st, group);
        ela_tmc5160_apply_profile(&g_tmc5160_chip2_st, group);
    }
    else
    {
        TMC5160_CHIP_T *chip = get_chip(motor);
        if ((void *)0 != chip)
        {
            ela_tmc5160_apply_profile(chip, group);
        }
    }
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: int32_t: 当前位置，无效电机返回 0
 * @ 说明: 读取电机当前位置
 ********/
int32_t ela_motor_ctrl_get_position(uint8_t motor)
{
    TMC5160_CHIP_T *chip = get_chip(motor);

    if ((void *)0 != chip)
    {
        return ela_tmc5160_get_position(chip);
    }
    return 0;
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: int32_t: 编码器当前位置 (X_ENC)
 ********/
int32_t ela_motor_ctrl_get_encoder_position(uint8_t motor)
{
    TMC5160_CHIP_T *chip = get_chip(motor);

    if ((void *)0 != chip)
    {
        return ela_tmc5160_get_encoder_position(chip);
    }
    return 0;
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: int32_t: XACTUAL 与 X_ENC 的偏差值
 * @ 说明: 正值=编码器超前, 负值=编码器滞后
 ********/
int32_t ela_motor_ctrl_get_encoder_deviation(uint8_t motor)
{
    TMC5160_CHIP_T *chip = get_chip(motor);

    if ((void *)0 != chip)
    {
        int32_t x_act = ela_tmc5160_get_position(chip);
        int32_t x_enc = ela_tmc5160_get_encoder_position(chip);
        return x_enc - x_act;
    }
    return 0;
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: uint8_t: 状态标志位
 * @ 说明: 读取电机状态标志
 ********/
uint8_t ela_motor_ctrl_get_status(uint8_t motor)
{
    TMC5160_CHIP_T *chip = get_chip(motor);

    if ((void *)0 != chip)
    {
        return ela_tmc5160_get_status_flags(chip);
    }
    return 0;
}

/****
 * @ 输入: motor: 电机编号
 * @ 输出: uint8_t: 运动阶段标志位
 * @ 说明: 读取电机运动阶段
 ********/
uint8_t ela_motor_ctrl_get_stage(uint8_t motor)
{
    TMC5160_CHIP_T *chip = get_chip(motor);

    if ((void *)0 != chip)
    {
        return ela_tmc5160_get_motion_phase(chip);
    }
    return 0;
}

/* motor ctrl usr end */
