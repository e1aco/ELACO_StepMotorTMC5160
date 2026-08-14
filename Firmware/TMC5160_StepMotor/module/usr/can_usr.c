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

/* 故障快照: FaultMonitor 边沿触发时冻结, DebugTick 上报 FAULT 帧 */
#define REG_VACTUAL        0x22
#define REG_XTARGET        0x2D
#define REG_VMAX           0x27
#define REG_AMAX           0x26
#define REG_GSTAT          0x01

/* 故障自动恢复: 冷却后再尝试清错重使能, 重试超限保持闩存(提示真实硬件故障) */
#define FAULT_RECOVER_DELAY_MS    1000
#define FAULT_RECOVER_MAX_RETRY   3

static volatile uint8_t s_fault_latch[2];
static uint32_t s_fault_drv[2];
static uint32_t s_fault_gstat[2];
static uint32_t s_fault_ramp[2];
static uint32_t s_fault_enc[2];
static int32_t  s_fault_pos[2];
static int32_t  s_fault_encpos[2];
static int32_t  s_fault_xtarget[2];
static uint32_t s_fault_vmax[2];
static uint32_t s_fault_amax[2];
static int32_t  s_fault_vactual[2];

static volatile uint32_t s_fault_recover_tick[2];
static uint8_t  s_fault_retry[2];

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
 * @输入 idx: 电机索引(0=U1, 1=U2)
 * @输出 无
 * @说明 立即发送一次故障快照文本帧（连发 3 次防止 PCAN-View 漏收），
 *        仅由 FaultMonitor 在错误边沿触发时调用。
 */
static void CAN_SendFaultFrame(uint8_t idx)
{
    char buf[160];
    uint16_t len;
    uint8_t rep;

    for (rep = 0; rep < 3; rep++)
    {
        len = 0;
        CAN_DbgAppendStr(buf, &len, "FAULT U");
        buf[len++] = (char)('1' + idx);
        CAN_DbgAppendStr(buf, &len, " D=");
        CAN_DbgAppendHex(buf, &len, s_fault_drv[idx], 8);
        CAN_DbgAppendStr(buf, &len, " G=");
        CAN_DbgAppendHex(buf, &len, s_fault_gstat[idx], 8);
        CAN_DbgAppendStr(buf, &len, " R=");
        CAN_DbgAppendHex(buf, &len, s_fault_ramp[idx], 6);
        CAN_DbgAppendStr(buf, &len, " E=");
        CAN_DbgAppendHex(buf, &len, s_fault_enc[idx], 2);
        CAN_DbgAppendStr(buf, &len, " X=");
        CAN_DbgAppendDec(buf, &len, s_fault_pos[idx]);
        CAN_DbgAppendStr(buf, &len, " XE=");
        CAN_DbgAppendDec(buf, &len, s_fault_encpos[idx]);
        CAN_DbgAppendStr(buf, &len, " V=");
        CAN_DbgAppendDec(buf, &len, s_fault_vactual[idx]);
        CAN_DbgAppendStr(buf, &len, " T=");
        CAN_DbgAppendDec(buf, &len, s_fault_xtarget[idx]);
        CAN_DbgAppendStr(buf, &len, " VMAX=");
        CAN_DbgAppendDec(buf, &len, (int32_t)s_fault_vmax[idx]);
        CAN_DbgAppendStr(buf, &len, " AMAX=");
        CAN_DbgAppendDec(buf, &len, (int32_t)s_fault_amax[idx]);
        CAN_DbgAppendStr(buf, &len, "\r\n");
        buf[len] = '\0';
        CAN_DebugSendStr(buf);
    }
}

/**
 * @输入 无
 * @输出 无
 * @说明 检测 TMC5160 驱动错误边沿（DRV_STATUS 短路/过温位或 GSTAT 错误位 0→1），
 *        触发时立即冻结完整状态快照并发送 FAULT 帧。
 *        已触发且冷却结束后，自动尝试恢复：清 GSTAT + 切换 ENN 重新使能驱动；
 *        复查错误位已清则解除闩存恢复监视，超限重试则保持闩存（提示真实硬件故障）。
 *        主循环每次迭代调用，无需额外节拍定时器。
 * @注意 错误位在驱动关闭后会保持置位（p056: 需 TOFF=0 或 ENN 才清除），
 *        主循环高频轮询可在触发瞬间捕获，快照只发一次（连发3帧防丢）。
 */
void USR_CAN_FaultMonitor(void)
{
    uint8_t idx;

    for (idx = 0; idx < 2; idx++)
    {
        uint8_t motor = (0 == idx) ? MOTOR_CTRL_U1 : MOTOR_CTRL_U2;
        TMC5160_CHIP_T *chip = USR_MOTOR_GetChip(motor);
        uint32_t gstat;
        uint32_t fault_now;

        if ((void *)0 == chip)
        {
            continue;
        }

        if (0 != s_fault_latch[idx])
        {
            /* 已触发过: 冷却结束后尝试自动恢复, 成功才解除闩存 */
            if (HAL_GetTick() >= s_fault_recover_tick[idx])
            {
                s_fault_recover_tick[idx] = HAL_GetTick() + FAULT_RECOVER_DELAY_MS;

                if (s_fault_retry[idx] < FAULT_RECOVER_MAX_RETRY)
                {
                    /* 清 GSTAT 错误标志, 再切换 ENN 清除 DRV_STATUS 闩存位并重新使能 */
                    USR_TMC5160_WriteReg(chip, REG_GSTAT, 0x07);
                    DRV_TMC5160_DelayMs(1);
                    DRV_TMC5160_Disable(chip->chip_number);
                    DRV_TMC5160_DelayMs(1);
                    DRV_TMC5160_Enable(chip->chip_number);
                    DRV_TMC5160_DelayMs(1);
                    s_fault_retry[idx]++;
                }

                /* 复查错误位: 已清则解除闩存, 恢复监视 */
                fault_now = USR_TMC5160_GetDrvStatus(chip);
                fault_now &= ((1UL << 28) | (1UL << 27) | (1UL << 25) |
                              (1UL << 13) | (1UL << 12));
                gstat = USR_TMC5160_GetGStat(chip);
                fault_now |= (gstat & 0x07);        /* GSTAT reset/drv_err/uv_cp */

                if (0 == fault_now)
                {
                    s_fault_latch[idx] = 0;
                    s_fault_retry[idx] = 0;
                }
            }
            continue;
        }

        /* 错误位掩码: DRV_STATUS S2GA/S2GB/S2VSA/S2VSB/OT + GSTAT drv_err/uv_cp/reset
         * (OTPW 仅上报不入闩存, 避免过热时反复 ENN 翻转诱发 S2 误触发) */
        fault_now = USR_TMC5160_GetDrvStatus(chip);
        fault_now &= ((1UL << 28) | (1UL << 27) | (1UL << 25) |
                      (1UL << 13) | (1UL << 12));
        gstat = USR_TMC5160_GetGStat(chip);
        fault_now |= (gstat & 0x07);        /* GSTAT reset/drv_err/uv_cp */

        if (0 != fault_now)
        {
            /* 错误触发：冻结快照（仅首次捕获，保持到清除） */
            s_fault_latch[idx] = 1;
            s_fault_drv[idx] = USR_TMC5160_GetDrvStatus(chip);
            s_fault_gstat[idx] = USR_TMC5160_GetGStat(chip);
            s_fault_ramp[idx] = USR_TMC5160_GetRampStat(chip);
            s_fault_enc[idx] = USR_TMC5160_GetEncoderStatus(chip);
            s_fault_pos[idx] = USR_TMC5160_GetPosition(chip);
            s_fault_encpos[idx] = USR_TMC5160_GetEncoderPosition(chip);
            s_fault_xtarget[idx] = (int32_t)USR_TMC5160_ReadReg(chip, REG_XTARGET);
            s_fault_vmax[idx] = USR_TMC5160_ReadReg(chip, REG_VMAX);
            s_fault_amax[idx] = USR_TMC5160_ReadReg(chip, REG_AMAX);
            s_fault_vactual[idx] = (int32_t)USR_TMC5160_ReadReg(chip, REG_VACTUAL);
            s_fault_recover_tick[idx] = HAL_GetTick() + FAULT_RECOVER_DELAY_MS;
            s_fault_retry[idx] = 0;

            CAN_SendFaultFrame(idx);
        }
    }
}

/**
 * @输入 无
 * @输出 无
 * @说明 CAN 接收中断里调用（stm32f4xx_it.c）。仅读取主循环已冻结的闩存快照，
 *        检测到驱动错误（latch=1）即连发 3 次 FAULT 数据包。
 * @注意 中断上下文内禁止 SPI/Delay：此处只读内存快照并复用 CAN 发送（不依赖 SysTick），
 *        不调用任何 USR_TMC5160_* / HAL_Delay。
 */
void USR_CAN_FaultISR(void)
{
    uint8_t idx;

    for (idx = 0; idx < 2; idx++)
    {
        if (0 != s_fault_latch[idx])
        {
            CAN_SendFaultFrame(idx);
        }
    }
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
