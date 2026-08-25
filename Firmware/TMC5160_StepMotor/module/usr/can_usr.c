/*****************************************************************************
 * @文件: can_usr.c
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v2.0
 * @说明: CAN 协议解析层（命令解析 + 反馈组装）
 * @依赖: drv/can_drv, usr/queue, usr/motor_ctrl, usr/closed_loop
 ****************************************************************************/
#include "usr/can_usr.h"
#include "drv/can_drv.h"
#include "usr/queue.h"
#include "usr/motor_ctrl.h"
#include "usr/closed_loop.h"

/* ==== 内部工具 ==== */

/**
 * @输入 data: 4字节小端数据
 * @输出 int32_t: 解析后的有符号值
 */
static int32_t CAN_BytesToInt32(uint8_t *data)
{
    int32_t val;

    val  = (int32_t)data[0];
    val |= (int32_t)data[1] << 8;
    val |= (int32_t)data[2] << 16;
    val |= (int32_t)data[3] << 24;
    return val;
}

/**
 * @输入 val: 32位值; data: 输出缓冲区(4字节)
 * @输出 无
 * @说明 int32 转 4 字节小端
 */
static void CAN_Int32ToBytes(int32_t val, uint8_t *data)
{
    data[0] = (uint8_t)(val & 0xFF);
    data[1] = (uint8_t)((val >> 8) & 0xFF);
    data[2] = (uint8_t)((val >> 16) & 0xFF);
    data[3] = (uint8_t)((val >> 24) & 0xFF);
}

/**
 * @输入 data: 8字节原始数据
 * @输出 uint8_t: 校验和
 * @说明 前 7 字节累加取低 8 位
 */
static uint8_t CAN_CalcChecksum(uint8_t *data)
{
    uint8_t sum = 0;
    uint8_t i;

    for (i = 0; i < 7; i++)
    {
        sum += data[i];
    }
    return sum;
}

/* ==== 调试输出已迁移至 RTT（rtt_dbg 模块）==== */

/* ==== 接口实现 ==== */

/**
 * @输入 无
 * @输出 无
 * @说明 CAN 协议模块初始化
 */
void USR_CAN_Init(void)
{
    /* TODO: 初始化电机控制相关变量 */
}

/**
 * @输入 无
 * @输出 无
 * @说明 主循环调用，从队列取命令并解析执行
 */
void USR_CAN_Process(void)
{
    uint8_t *cmd_data;
    CAN_CMD_T cmd;

    if (QUEUE_IsEmpty(&g_queue_st))
    {
        return;
    }

    cmd_data = (uint8_t *)QUEUE_First(&g_queue_st);
    if (NULL == cmd_data)
    {
        return;
    }

    /* 解析命令（中断中已完成校验） */
    cmd.value    = CAN_BytesToInt32(&cmd_data[0]);
    cmd.cmd      = cmd_data[4];
    cmd.motor    = cmd_data[5];
    cmd.param    = cmd_data[6];
    cmd.checksum = cmd_data[7];

    /* 出队 */
    QUEUE_Delete(&g_queue_st);

    /* 命令分发 */
    switch (cmd.cmd)
    {
    case CMD_ABS_POS:
    {
        int32_t dev = USR_MOTOR_GetEncoderPosition(cmd.motor);
        uint8_t status = USR_MOTOR_GetStatus(cmd.motor);
        uint8_t stage = USR_MOTOR_GetStage(cmd.motor);

        USR_MOTOR_ApplyProfile(cmd.motor, cmd.param);
        USR_MOTOR_MoveTo(cmd.motor, cmd.value);
        USR_CAN_SendMotionFeedback(cmd.motor, dev, status, stage);
        break;
    }

    case CMD_REL_CW:
    {
        int32_t dev = USR_MOTOR_GetEncoderPosition(cmd.motor);
        uint8_t status = USR_MOTOR_GetStatus(cmd.motor);
        uint8_t stage = USR_MOTOR_GetStage(cmd.motor);

        USR_MOTOR_ApplyProfile(cmd.motor, cmd.param);
        USR_MOTOR_MoveBy(cmd.motor, cmd.value);
        USR_CAN_SendMotionFeedback(cmd.motor, dev, status, stage);
        break;
    }

    case CMD_REL_CCW:
    {
        int32_t dev = USR_MOTOR_GetEncoderPosition(cmd.motor);
        uint8_t status = USR_MOTOR_GetStatus(cmd.motor);
        uint8_t stage = USR_MOTOR_GetStage(cmd.motor);

        USR_MOTOR_ApplyProfile(cmd.motor, cmd.param);
        USR_MOTOR_MoveBy(cmd.motor, -cmd.value);
        USR_CAN_SendMotionFeedback(cmd.motor, dev, status, stage);
        break;
    }

    case CMD_VELOCITY:
    {
        int32_t dev = USR_MOTOR_GetEncoderPosition(cmd.motor);
        uint8_t status = USR_MOTOR_GetStatus(cmd.motor);
        uint8_t stage = USR_MOTOR_GetStage(cmd.motor);

        USR_MOTOR_ApplyProfile(cmd.motor, cmd.param);
        USR_MOTOR_SetVelocity(cmd.motor, cmd.value);
        USR_CAN_SendMotionFeedback(cmd.motor, dev, status, stage);
        break;
    }

    case CMD_STOP:
    {
        int32_t dev = USR_MOTOR_GetEncoderPosition(cmd.motor);
        uint8_t status = USR_MOTOR_GetStatus(cmd.motor);

        USR_MOTOR_Stop(cmd.motor);
        USR_CAN_SendMotionFeedback(cmd.motor, dev, status, 0);
        break;
    }

    case CMD_PID_ADJUST:
        /* PID 调参（暂未实现） */
        break;

    case CMD_CL_ENABLE:
        USR_CLOSEDLOOP_Enable(cmd.motor);
        USR_CAN_SendMotionFeedback(cmd.motor, 0, 0, 0);
        break;

    case CMD_CL_DISABLE:
        USR_CLOSEDLOOP_Disable(cmd.motor);
        USR_CAN_SendMotionFeedback(cmd.motor, 0, 0, 0);
        break;

    default:
        break;
    }
}

/**
 * @输入 motor: 电机选择; pos: 编码器实际位姿(X_ENC); status: 状态标志; stage: 运动阶段(已废弃,恒0)
 * @输出 0=成功, 1=发送失败
 * @说明 发送运动反馈帧 (ID: 0x1AA55F43)；byte[6] 保护状态:
 *        bit0=OTPW, bit1=OT, bit2=drv_err(GSTAT), bit3=S2GA, bit4=S2GB,
 *        bit5=S2VSA, bit6=S2VSB, bit7=失步(ENC_STATUS.deviation_warn)
 */
uint8_t USR_CAN_SendMotionFeedback(uint8_t motor, int32_t pos,
                                   uint8_t status, uint8_t stage)
{
    uint8_t tx_data[8];
    uint8_t protect_flags = 0;
    TMC5160_CHIP_T *chip = USR_MOTOR_GetChip(motor);

    (void)stage;
    if (chip != NULL)
    {
        uint32_t drv_status = USR_TMC5160_GetDrvStatus(chip);
        uint32_t gstat = USR_TMC5160_GetGStat(chip);
        if (drv_status & (1u << 26)) protect_flags |= 0x01; /* OTPW  预过温 */
        if (drv_status & (1u << 25)) protect_flags |= 0x02; /* OT    过温关断 */
        if (gstat & (1u << 1))       protect_flags |= 0x04; /* drv_err 驱动错误 */
        if (drv_status & (1u << 27)) protect_flags |= 0x08; /* S2GA  对地短路 A 相 */
        if (drv_status & (1u << 28)) protect_flags |= 0x10; /* S2GB  对地短路 B 相 */
        if (drv_status & (1u << 12)) protect_flags |= 0x20; /* S2VSA 对电源短路 A 相 */
        if (drv_status & (1u << 13)) protect_flags |= 0x40; /* S2VSB 对电源短路 B 相 */
        if (status & 0x02)           protect_flags |= 0x80; /* 失步 (编码器偏差) */
    }

    CAN_Int32ToBytes(pos, &tx_data[0]);
    tx_data[4] = status;
    tx_data[5] = motor;
    tx_data[6] = protect_flags;
    tx_data[7] = CAN_CalcChecksum(tx_data);

    return DRV_CAN_Send(CAN_TX_ID, tx_data);
}

/**
 * @输入 motor: 电机选择; pid_type: PID参数类型; value: 参数值
 * @输出 0=成功, 1=发送失败
 * @说明 发送调参反馈帧 (ID: 0x1AA55F43)
 */
uint8_t USR_CAN_SendPidFeedback(uint8_t motor, uint8_t pid_type, int32_t value)
{
    uint8_t tx_data[8];

    CAN_Int32ToBytes(value, &tx_data[0]);
    tx_data[4] = pid_type;
    tx_data[5] = motor;
    tx_data[6] = CMD_PID_ADJUST;
    tx_data[7] = CAN_CalcChecksum(tx_data);

    return DRV_CAN_Send(CAN_TX_ID, tx_data);
}
