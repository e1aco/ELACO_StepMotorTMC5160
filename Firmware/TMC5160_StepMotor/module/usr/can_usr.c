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

/* ==== 调试文本构建（"CAN 当串口用"，ID: 0x1AA55F44）==== */

/**
 * @输入 buf: 目标缓冲区; len: 已写长度指针; val: 有符号十进制数
 * @输出 无
 * @说明 追加有符号十进制到缓冲区
 */
static void CAN_DbgAppendDec(char *buf, uint16_t *len, int32_t val)
{
    char tmp[12];
    uint8_t i = 0;
    uint8_t j;
    uint32_t abs_val;

    if (0 > val)
    {
        buf[(*len)++] = '-';
        abs_val = (uint32_t)(-val);
    }
    else
    {
        abs_val = (uint32_t)val;
    }

    do
    {
        tmp[i++] = (char)('0' + (abs_val % 10));
        abs_val /= 10;
    } while (0 != abs_val);

    for (j = i; 0 != j; j--)
    {
        buf[(*len)++] = tmp[j - 1];
    }
}

/**
 * @输入 buf: 目标缓冲区; len: 已写长度指针; val: 十六进制值; n: 显示位数(1/2/4/8)
 * @输出 无
 * @说明 追加十六进制(大写)到缓冲区，不足位补 0
 */
static void CAN_DbgAppendHex(char *buf, uint16_t *len, uint32_t val, uint8_t n)
{
    static const char HEX_TAB[] = "0123456789ABCDEF";
    int8_t i;

    for (i = (int8_t)n - 1; 0 <= i; i--)
    {
        buf[(*len)++] = HEX_TAB[(val >> (i * 4)) & 0x0F];
    }
}

/**
 * @输入 buf: 目标缓冲区; len: 已写长度指针; str: 源字符串
 * @输出 无
 * @说明 追加字符串到缓冲区
 */
static void CAN_DbgAppendStr(char *buf, uint16_t *len, const char *str)
{
    while (0 != *str)
    {
        buf[(*len)++] = *str++;
    }
}

/**
 * @输入 str: 待发送文本
 * @输出 无
 * @说明 把文本按 8 字节切帧发送到 CAN_DBG_TX_ID，末帧用空格补齐
 */
static void CAN_DebugSendStr(const char *str)
{
    uint8_t tx_data[CAN_DATA_LEN];
    uint8_t i;
    uint16_t pos = 0;

    while (0 != str[pos])
    {
        for (i = 0; i < CAN_DATA_LEN; i++)
        {
            tx_data[i] = (uint8_t)str[pos + i];
            if (0 == str[pos + i])
            {
                break;
            }
        }
        /* 末帧剩余字节补空格，监控端按序拼接还原文本 */
        /* 末帧剩余字节补空格，监控端按序拼接还原文本 */
        while (i < CAN_DATA_LEN)
        {
            tx_data[i++] = ' ';
        }

        /* 连续多帧：等待邮箱空闲再发，避免非阻塞 AddTxMessage 丢帧 */
        DRV_CAN_SendWait(CAN_DBG_TX_ID, tx_data);
        pos += CAN_DATA_LEN;
    }
}

/**
 * @输入 buf: 目标缓冲区; len: 已写长度指针; drv_status: DRV_STATUS 寄存器值
 * @输出 无
 * @说明 追加 DRV_STATUS 报警源文本解码（仅追加置位项，无报警追加 "-"）
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p056.md: DRV_STATUS
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p033.md: GSTAT
 */
static void CAN_DbgAppendAlarm(char *buf, uint16_t *len,
                               uint32_t drv_status, uint32_t gstat)
{
    uint8_t any = 0;

    /* DRV_STATUS 报警位 */
    if (drv_status & (1UL << 26)) { CAN_DbgAppendStr(buf, len, "OTPW,"); any = 1; }  /* 过温预警 120°C */
    if (drv_status & (1UL << 25)) { CAN_DbgAppendStr(buf, len, "OT,");   any = 1; }  /* 过温关断 136/143/150°C */
    if (drv_status & (1UL << 27)) { CAN_DbgAppendStr(buf, len, "S2GA,"); any = 1; } /* 对地短路 A 相 */
    if (drv_status & (1UL << 28)) { CAN_DbgAppendStr(buf, len, "S2GB,"); any = 1; } /* 对地短路 B 相 */
    if (drv_status & (1UL << 12)) { CAN_DbgAppendStr(buf, len, "S2VSA,"); any = 1; }/* 对电源短路 A 相 */
    if (drv_status & (1UL << 13)) { CAN_DbgAppendStr(buf, len, "S2VSB,"); any = 1; }/* 对电源短路 B 相 */
    if (drv_status & (1UL << 29)) { CAN_DbgAppendStr(buf, len, "OLA,");  any = 1; } /* 开路 A 相(仅供参考) */
    if (drv_status & (1UL << 30)) { CAN_DbgAppendStr(buf, len, "OLB,");  any = 1; } /* 开路 B 相(仅供参考) */
    /* GSTAT 报警位 */
    if (gstat & (1UL << 1)) { CAN_DbgAppendStr(buf, len, "DRVERR,"); any = 1; }    /* 驱动错误(过温或短路) */
    if (gstat & (1UL << 2)) { CAN_DbgAppendStr(buf, len, "UVCP,");    any = 1; }    /* 电荷泵欠压 */
    if (gstat & (1UL << 0)) { CAN_DbgAppendStr(buf, len, "RESET,");   any = 1; }    /* 芯片复位 */

    if (0 == any)
    {
        CAN_DbgAppendStr(buf, len, "-");
    }
}

/**
 * @输入 无
 * @输出 无
 * @说明 周期调试遥测：发送 U1/U2 位置/编码器/状态/阶段/DRV_STATUS/GSTAT+报警源文本帧
 *        主循环每 ~500ms 调用一次（HAL_GetTick 节流）
 */
void USR_CAN_DebugTick(void)
{
    char buf[128];
    uint16_t len = 0;
    uint8_t idx;

    for (idx = 0; idx < 2; idx++)
    {
        uint8_t motor = (0 == idx) ? MOTOR_CTRL_U1 : MOTOR_CTRL_U2;
        TMC5160_CHIP_T *chip = USR_MOTOR_GetChip(motor);
        uint32_t drv_status = USR_TMC5160_GetDrvStatus(chip);
        uint32_t gstat = USR_TMC5160_GetGStat(chip);

        CAN_DbgAppendStr(buf, &len, "U");
        buf[len++] = (char)('1' + idx);
        CAN_DbgAppendStr(buf, &len, " X=");
        CAN_DbgAppendDec(buf, &len, USR_MOTOR_GetPosition(motor));
        CAN_DbgAppendStr(buf, &len, " E=");
        CAN_DbgAppendDec(buf, &len, USR_MOTOR_GetEncoderPosition(motor));
        CAN_DbgAppendStr(buf, &len, " S=");
        CAN_DbgAppendHex(buf, &len, USR_MOTOR_GetStatus(motor), 2);
        CAN_DbgAppendStr(buf, &len, " P=");
        CAN_DbgAppendHex(buf, &len, USR_MOTOR_GetStage(motor), 2);
        CAN_DbgAppendStr(buf, &len, " D=");
        CAN_DbgAppendHex(buf, &len, drv_status, 8);
        CAN_DbgAppendStr(buf, &len, " G=");
        CAN_DbgAppendHex(buf, &len, gstat, 8);
        CAN_DbgAppendStr(buf, &len, " A=");
        CAN_DbgAppendAlarm(buf, &len, drv_status, gstat);
        CAN_DbgAppendStr(buf, &len, "  ");
    }
    CAN_DbgAppendStr(buf, &len, "\r\n");
    buf[len] = '\0';   /* CAN_DebugSendStr 按 '\0' 定界，缺此会把栈残留字节当下一帧发出（帧拼接污染） */

    CAN_DebugSendStr(buf);
}

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
 * @输入 motor: 电机选择; pos: 编码器实际位姿(X_ENC); status: 状态标志; stage: 运动阶段
 * @输出 0=成功, 1=发送失败
 * @说明 发送运动反馈帧 (ID: 0x1AA55F43)
 */
uint8_t USR_CAN_SendMotionFeedback(uint8_t motor, int32_t pos,
                                   uint8_t status, uint8_t stage)
{
    uint8_t tx_data[8];

    CAN_Int32ToBytes(pos, &tx_data[0]);
    tx_data[4] = status;
    tx_data[5] = motor;
    tx_data[6] = stage;
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
