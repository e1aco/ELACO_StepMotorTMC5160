#include "test_encoder.h"

/* ================================================================
 * 编码器测试 — 位置模式 (RAMPMODE=0)
 * 芯片自动处理加减速和精确定位, 无需手动轮询编码器来停机.
 * 流程: 配置斜坡参数 → 设定 XTARGET → 等待到位 → 对比 X_ENC
 * fCLK = 14MHz, 速度换算: VMAX_real = VMAX * 14e6 / 8388608
 * ================================================================ */

/* ---- 测试芯片选择: 1=CHIP1, 2=CHIP2, 0=两个都测 ---- */
#define ENC_CHIP_NUM        2

/* ---- 电机电流 ---- */
#define ENC_IRUN            15
#define ENC_IHOLD           8
#define ENC_IHOLDDELAY      5

/* ---- 位置模式斜坡参数 ---- */
#define ENC_VSTART          0
#define ENC_VSTOP           10
#define ENC_V1              500
#define ENC_VMAX            30676   /* ≈1rps @14MHz (51200/1.669) */
#define ENC_A1              200
#define ENC_AMAX            500
#define ENC_D1              400
#define ENC_DMAX            800

/* ---- 运动量: 51200 µsteps = 1 圈 (256µstep × 200全步) ---- */
#define ENC_TARGET_STEPS    51200
#define ENC_EXPECTED_ENC    51200   /* X_ENC 期望变化量 (µsteps) */
#define ENC_TOLERANCE       512     /* 1% 容差 */

/* ---- 超时 (毫秒) ---- */
#define ENC_TIMEOUT_MS      5000

/* ---- LED 闪烁周期 ---- */
#define LED_MS              100

/* 全局调试变量 (Keil Watch: g_enc_dbg) */
typedef struct {
    int32_t  x_enc_start;
    int32_t  x_enc_end;
    int32_t  x_enc_delta;
    int32_t  x_actual_start;
    int32_t  x_actual_end;
    int32_t  x_actual_delta;
    int32_t  error;
    unsigned int  ramp_stat;
    unsigned char fault;
} ENC_DBG_T;

ENC_DBG_T g_enc_dbg = {0};

/* test_encoder hlp start */

/****
 * @ 输入: delta: X_ENC变化量; expected: 期望变化量
 * @ 输出: 0=在容差内, 1=超出容差
 * @ 说明: 纯计算, 判断编码器偏差是否在容差范围内
 ********/
static unsigned char Encoder_CheckDelta(int32_t delta,
                                         int32_t expected)
{
    int32_t diff;

    diff = (delta > expected) ? (delta - expected)
                              : (expected - delta);
    if (diff <= ENC_TOLERANCE) {
        return 0;
    }
    return 1;
}

/* test_encoder hlp end */
//----------------------------------------------------------------------------------
/* test_encoder drv start */

/****
 * @ 输入: CHIP_T: 芯片结构体指针
 * @ 输出: void
 * @ 说明: 配置编码器接口
 *        ENCMODE=0: 基本编码器读取, 不使用闭环控制
 *        ENC_CONST=0x000CCCCD: 4000PPR + 1.8°步距角 + 256微步
 *        计算公式: (51200/4000) × 65536 = 838860.8 ≈ 838861
 ********/
static void Encoder_Config(TMC5160_T *CHIP_T)
{
    Tmc5160_WriteReg(CHIP_T, TMC5160_ENCMODE, 0x00000000);
    Tmc5160_WriteReg(CHIP_T, TMC5160_ENC_CONST, 0x000CCCCD);
}

/****
 * @ 输入: CHIP_T: 芯片结构体指针
 * @ 输出: void
 * @ 说明: 配置位置模式全部斜坡参数
 *        速度曲线: VSTART →(A1)→ V1 →(AMAX)→ VMAX
 *                          ←(D1)←      ←(DMAX)← VSTOP
 ********/
static void Encoder_ConfigRamp(TMC5160_T *CHIP_T)
{
    Tmc5160_WriteReg(CHIP_T, TMC5160_RAMPMODE, 0);
    Tmc5160_WriteReg(CHIP_T, TMC5160_VSTART, ENC_VSTART);
    Tmc5160_WriteReg(CHIP_T, TMC5160_VSTOP, ENC_VSTOP);
    Tmc5160_WriteReg(CHIP_T, TMC5160_V1, ENC_V1);
    Tmc5160_WriteReg(CHIP_T, TMC5160_VMAX, ENC_VMAX);
    Tmc5160_WriteReg(CHIP_T, TMC5160_A1, ENC_A1);
    Tmc5160_WriteReg(CHIP_T, TMC5160_AMAX, ENC_AMAX);
    Tmc5160_WriteReg(CHIP_T, TMC5160_D1, ENC_D1);
    Tmc5160_WriteReg(CHIP_T, TMC5160_DMAX, ENC_DMAX);
}

/****
 * @ 输入: CHIP_T: 芯片结构体指针; timeout_ms: 超时时间(毫秒)
 * @ 输出: 0=已到位, 1=超时, 2=SPI通信异常
 * @ 说明: 轮询 RAMP_STAT bit9 (position_reached), 等待定位完成
 ********/
static unsigned char Encoder_WaitPosition(TMC5160_T *CHIP_T,
                                           unsigned int timeout_ms)
{
    unsigned int ramp;
    unsigned int elapsed = 0;

    while (elapsed < timeout_ms) {
        ramp = Tmc5160_ReadReg(CHIP_T, TMC5160_RAMP_STAT);
        if (0xFFFFFFFF == ramp || 0 == ramp) {
            return 2;
        }
        if (ramp & (1 << 9)) {
            g_enc_dbg.ramp_stat = ramp;
            return 0;
        }
        HAL_Delay(10);
        elapsed += 10;
    }

    return 1;
}

/****
 * @ 输入: CHIP_T: 芯片结构体指针
 * @ 输出: 0=正常, 1=SPI通信异常, 2=GSTAT错误
 * @ 说明: 检查芯片SPI通信和错误状态
 ********/
static unsigned char Encoder_CheckError(TMC5160_T *CHIP_T)
{
    unsigned int val;

    val = Tmc5160_ReadReg(CHIP_T, TMC5160_IOIN);
    if (0 == val || 0xFFFFFFFF == val) {
        return 1;
    }

    val = Tmc5160_ReadReg(CHIP_T, TMC5160_GSTAT);
    if (val & 0x06) {
        return 2;
    }

    return 0;
}

/* test_encoder drv end */
//----------------------------------------------------------------------------------
/* test_encoder usr start */

/****
 * @ 输入: CHIP_T: 芯片结构体指针
 * @ 输出: 0=通过, 1=超时, 2=SPI异常, 3=偏差过大
 * @ 说明: 单芯片完整编码器测试:
 *        基础配置 → 编码器配置 → 斜坡配置 →
 *        记录起始位置 → 设定XTARGET(自动运动) →
 *        等待到位 → 记录终点位置 → 对比偏差
 ********/
static unsigned char Encoder_TestChip(TMC5160_T *CHIP_T)
{
    unsigned char ret;
    unsigned char chip = CHIP_T->chip_number;
    int32_t target;

    /* 强制 DRV_ENN = LOW (驱动使能, 低有效) */
    if (1 == chip) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
    }

    /* 清除残留错误 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_GSTAT, 0x07);

    /* === 第一步: 基础与斩波器配置 === */
    Tmc5160_WriteReg(CHIP_T, TMC5160_GCONF, 0x00000004);
    /* CHOPCONF: TOFF=5, TBL=%01, HSTRT=4, HEND=0, MRES=0 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_CHOPCONF, 0x000101C5);
    Tmc5160_WriteReg(CHIP_T, TMC5160_IHOLD_IRUN,
                     (ENC_IHOLDDELAY << 16) |
                     (ENC_IRUN << 8)       |
                     ENC_IHOLD);

    /* === 第二步: 编码器配置 === */
    Encoder_Config(CHIP_T);

    /* === 第三步: 位置模式斜坡参数 === */
    Encoder_ConfigRamp(CHIP_T);

    /* === 第四步: 记录起始位置 === */
    g_enc_dbg.x_enc_start = (int32_t)Tmc5160_ReadReg(
        CHIP_T, TMC5160_X_ENC);
    g_enc_dbg.x_actual_start = (int32_t)Tmc5160_ReadReg(
        CHIP_T, TMC5160_XACTUAL);

    /* === 第五步: 设定目标位置 (相对当前位置移动1圈) === */
    target = g_enc_dbg.x_actual_start + ENC_TARGET_STEPS;
    Tmc5160_WriteReg(CHIP_T, TMC5160_XTARGET, (unsigned int)target);

    /* === 第六步: 等待芯片自动完成定位 === */
    ret = Encoder_WaitPosition(CHIP_T, ENC_TIMEOUT_MS);
    if (0 != ret) {
        g_enc_dbg.fault = ret;
        return ret;
    }

    /* === 第七步: 记录终点位置 === */
    g_enc_dbg.x_enc_end = (int32_t)Tmc5160_ReadReg(
        CHIP_T, TMC5160_X_ENC);
    g_enc_dbg.x_actual_end = (int32_t)Tmc5160_ReadReg(
        CHIP_T, TMC5160_XACTUAL);

    /* === 第八步: 计算偏差 (取绝对值) === */
    g_enc_dbg.x_enc_delta =
        g_enc_dbg.x_enc_end - g_enc_dbg.x_enc_start;
    if (g_enc_dbg.x_enc_delta < 0) {
        g_enc_dbg.x_enc_delta = -g_enc_dbg.x_enc_delta;
    }

    g_enc_dbg.x_actual_delta =
        g_enc_dbg.x_actual_end - g_enc_dbg.x_actual_start;
    if (g_enc_dbg.x_actual_delta < 0) {
        g_enc_dbg.x_actual_delta = -g_enc_dbg.x_actual_delta;
    }

    g_enc_dbg.error = g_enc_dbg.x_enc_delta - ENC_EXPECTED_ENC;

    /* === 第九步: 判断偏差是否在容差内 === */
    if (0 != Encoder_CheckDelta(g_enc_dbg.x_enc_delta,
                                 ENC_EXPECTED_ENC)) {
        g_enc_dbg.fault = 3;
        return 3;
    }

    g_enc_dbg.fault = 0;
    return 0;
}

/****
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 编码器验证测试入口
 *        位置模式运动1圈, 对比X_ENC变化量判定通过/失败.
 *        LED匀速闪烁=通过, 快闪4次=故障.
 ********/
void Test_Encoder(void)
{
    unsigned char ret = 0;

    Tmc5160_Init();

    if (1 == ENC_CHIP_NUM || 0 == ENC_CHIP_NUM) {
        g_tmc5160_chip1_st.mode = 1;
        Tmc5160_Mode(&g_tmc5160_chip1_st);
        ret = Encoder_TestChip(&g_tmc5160_chip1_st);
    }

    if (2 == ENC_CHIP_NUM || 0 == ENC_CHIP_NUM) {
        g_tmc5160_chip2_st.mode = 1;
        Tmc5160_Mode(&g_tmc5160_chip2_st);
        ret = Encoder_TestChip(&g_tmc5160_chip2_st);
    }

    if (0 == ret) {
        /* 通过: LED 匀速闪烁 */
        while (1) {
            HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin);
            HAL_Delay(500);
        }
    } else {
        /* 故障: LED 快闪 4 次后停顿 */
        g_enc_dbg.fault = ret;
        while (1) {
            for (int i = 0; i < 4; i++) {
                HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                                  GPIO_PIN_RESET);
                HAL_Delay(LED_MS);
                HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                                  GPIO_PIN_SET);
                HAL_Delay(LED_MS);
            }
            HAL_Delay(1000);
        }
    }
}

/* test_encoder usr end */
