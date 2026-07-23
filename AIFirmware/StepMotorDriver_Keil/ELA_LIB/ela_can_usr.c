/****
 * @ 文件: ela_can_usr.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.0.0
 * @ 说明: CAN 协议解析层，命令解析 + 反馈组装
 ********/
#include "ela_can_usr.h"
#include "ela_can_drv.h"
#include "ela_queue.h"
#include "ela_motor_ctrl.h"

/* module hlp start */

/****
 * @ 输入: data: 8字节原始数据
 * @ 输出: uint8_t: 校验和值
 * @ 说明: 前7字节累加取低8位
 ********/
static uint8_t calc_checksum(uint8_t *data)
{
    uint8_t sum = 0;
    uint8_t i;

    for (i = 0; i < 7; i++)
    {
        sum += data[i];
    }
    return sum;
}

/****
 * @ 输入: data: 4字节小端数据
 * @ 输出: int32_t: 解析后的32位有符号值
 * @ 说明: 4字节小端转 int32
 ********/
static int32_t bytes_to_int32(uint8_t *data)
{
    int32_t val;

    val  = (int32_t)data[0];
    val |= (int32_t)data[1] << 8;
    val |= (int32_t)data[2] << 16;
    val |= (int32_t)data[3] << 24;
    return val;
}

/****
 * @ 输入: val: 32位值; data: 输出缓冲区(4字节)
 * @ 输出: 无
 * @ 说明: int32 转 4字节小端
 ********/
static void int32_to_bytes(int32_t val, uint8_t *data)
{
    data[0] = (uint8_t)(val & 0xFF);
    data[1] = (uint8_t)((val >> 8) & 0xFF);
    data[2] = (uint8_t)((val >> 16) & 0xFF);
    data[3] = (uint8_t)((val >> 24) & 0xFF);
}

/* module hlp end */
//----------------------------------------------------------------------------------
/* module drv start */

/* module drv end */
//----------------------------------------------------------------------------------
/* module usr start */

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: CAN 协议模块初始化
 ********/
void ela_can_usr_init(void)
{
    /* TODO: 初始化电机控制相关变量 */
}

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 主循环调用，从队列取命令并解析执行
 ********/
void ela_can_usr_process(void)
{
    uint8_t *cmd_data;
    CAN_CMD_T cmd;

    if (ela_queue_is_empty(&g_queue_st))
    {
        return;
    }

    cmd_data = (uint8_t *)ela_queue_first(&g_queue_st);
    if (NULL == cmd_data)
    {
        return;
    }

    /* 解析命令帧 (中断中已完成校验) */
    cmd.value    = bytes_to_int32(&cmd_data[0]);
    cmd.cmd      = cmd_data[4];
    cmd.motor    = cmd_data[5];
    cmd.param    = cmd_data[6];
    cmd.checksum = cmd_data[7];

    /* 出队 */
    ela_queue_delete(&g_queue_st);

    /* 命令分发 */
    switch (cmd.cmd)
    {
    case CMD_ABS_POS:
    {
				// 获取编码器偏差
        int32_t dev = ela_motor_ctrl_get_encoder_deviation(cmd.motor);
				// 获取状态
        uint8_t status = ela_motor_ctrl_get_status(cmd.motor);
				// 获取运动状态
        uint8_t stage = ela_motor_ctrl_get_stage(cmd.motor);
				
				// 设置速度
        ela_motor_ctrl_apply_profile(cmd.motor, cmd.param);
				// 写入目标值
        ela_motor_ctrl_move_to(cmd.motor, cmd.value);
        ela_can_usr_send_motion_feedback(
            cmd.motor, dev, status, stage);
        break;
    }

    case CMD_REL_CW:
    {
        int32_t dev = ela_motor_ctrl_get_encoder_deviation(cmd.motor);
        uint8_t status = ela_motor_ctrl_get_status(cmd.motor);
        uint8_t stage = ela_motor_ctrl_get_stage(cmd.motor);

        ela_motor_ctrl_apply_profile(cmd.motor, cmd.param);
        ela_motor_ctrl_move_by(cmd.motor, cmd.value);
        ela_can_usr_send_motion_feedback(
            cmd.motor, dev, status, stage);
        break;
    }

    case CMD_REL_CCW:
    {
        int32_t dev = ela_motor_ctrl_get_encoder_deviation(cmd.motor);
        uint8_t status = ela_motor_ctrl_get_status(cmd.motor);
        uint8_t stage = ela_motor_ctrl_get_stage(cmd.motor);

        ela_motor_ctrl_apply_profile(cmd.motor, cmd.param);
        ela_motor_ctrl_move_by(cmd.motor, -cmd.value);
        ela_can_usr_send_motion_feedback(
            cmd.motor, dev, status, stage);
        break;
    }

    case CMD_VELOCITY:
    {
        int32_t dev = ela_motor_ctrl_get_encoder_deviation(cmd.motor);
        uint8_t status = ela_motor_ctrl_get_status(cmd.motor);
        uint8_t stage = ela_motor_ctrl_get_stage(cmd.motor);

        ela_motor_ctrl_apply_profile(cmd.motor, cmd.param);
        ela_motor_ctrl_set_velocity(cmd.motor, cmd.value);
        ela_can_usr_send_motion_feedback(
            cmd.motor, dev, status, stage);
        break;
    }

    case CMD_STOP:
    {
        int32_t dev = ela_motor_ctrl_get_encoder_deviation(cmd.motor);
        uint8_t status = ela_motor_ctrl_get_status(cmd.motor);

        ela_motor_ctrl_stop(cmd.motor);
        ela_can_usr_send_motion_feedback(
            cmd.motor, dev, status, 0);
        break;
    }

    case CMD_PID_ADJUST:
        /* PID 调参 (暂未实现) */
        break;

    default:
        break;
    }
}

/****
 * @ 输入: motor: 电机选择; dev: 偏差值; status: 状态标志; stage: 运动阶段
 * @ 输出: uint8_t: 0=成功, 1=发送失败
 * @ 说明: 发送运动反馈帧 (ID: 0x1AA55F43)
 *   byte[0-3]: 偏差值 (X_ENC - XACTUAL)
 *   byte[4]: 状态标志位
 *   byte[5]: 电机选择
 *   byte[6]: 运动阶段
 *   byte[7]: 校验和
 ********/
uint8_t ela_can_usr_send_motion_feedback(uint8_t motor, int32_t dev, uint8_t status, uint8_t stage)
{
    uint8_t tx_data[8];

    int32_to_bytes(dev, &tx_data[0]);
    tx_data[4] = status;
    tx_data[5] = motor;
    tx_data[6] = stage;
    tx_data[7] = calc_checksum(tx_data);

    return ela_can_drv_send(CAN_TX_ID, tx_data);
}

/****
 * @ 输入: motor: 电机选择; pid_type: PID参数类型; value: 参数值
 * @ 输出: uint8_t: 0=成功, 1=发送失败
 * @ 说明: 发送调参反馈帧 (ID: 0x1AA55F43)
 ********/
uint8_t ela_can_usr_send_pid_feedback(uint8_t motor, uint8_t pid_type, int32_t value)
{
    uint8_t tx_data[8];

    int32_to_bytes(value, &tx_data[0]);
    tx_data[4] = pid_type;
    tx_data[5] = motor;
    tx_data[6] = CMD_PID_ADJUST;
    tx_data[7] = calc_checksum(tx_data);

    return ela_can_drv_send(CAN_TX_ID, tx_data);
}

/* module usr end */
