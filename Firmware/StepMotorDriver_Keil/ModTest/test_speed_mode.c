#include "test_speed_mode.h"

/* ================================================================
 * 速度模式 — 配置顺序: GCONF→CHOPCONF→IHOLD_IRUN→AMAX→VMAX→RAMPMODE
 * 写完后持续监控运行状态, LED匀速闪烁表示正常运行.
 * fCLK = 14MHz, 速度换算: VMAX_real = VMAX * 14e6 / 8388608
 * ================================================================ */

/* ---- 电机电流 ---- */
#define SPEED_IHOLD         125
#define SPEED_IRUN          30
#define SPEED_IHOLDDELAY    5

/* ---- 加速度 ---- */
#define SPEED_AMAX          500

/* ---- 目标速度 (14MHz时钟: 1圈/秒 = 51200/1.669 ≈ 30676) ---- */
#define SPEED_VMAX          30676

/* ---- 芯片选择 ---- */
#define SPEED_CHIP_NUM      2

/* ---- 方向: 1=正转, 2=反转 ---- */
#define SPEED_DIRECTION     2

/* ================================================================ */

#define LED_MS              100
#define MONITOR_MS          200

/* 全局限时监控变量 (Keil Watch: g_speed_dbg) */
typedef struct {
    unsigned int  ioin_val;
    unsigned int  gstat;
    unsigned int  drv_status;
    unsigned int  ramp_stat;
    unsigned int  vactual;
    unsigned int  xactual;
    unsigned char fault;          /* 0=正常, 1=SPI死, 2=GSTAT错误 */
} SPEED_DBG_T;

SPEED_DBG_T g_speed_dbg = {0};

/* test_speed_mode hlp start */

/****
 * 对照推荐步骤:
 * 第一步: GCONF → CHOPCONF → IHOLD_IRUN
 * 第二步: AMAX → VMAX
 * 第三步: RAMPMODE (启动)
 ********/
static void SpeedMode_SingleChip(TMC5160_T *CHIP_T)
{
    unsigned char chip = CHIP_T->chip_number;

    /* 强制 DRV_ENN = LOW */
    if (chip == 1) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
    }

    /* 清除残留错误 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_GSTAT, 0x07);

    /* === 第一步: 基础与斩波器配置 === */

    /* 1. GCONF: en_pwm_mode=1, 使能StealthChop */
    Tmc5160_WriteReg(CHIP_T, TMC5160_GCONF, 0x00000004);

    /* 2. CHOPCONF: TOFF=3 (必须>0才能输出) */
    Tmc5160_WriteReg(CHIP_T, TMC5160_CHOPCONF, 0x000100C3);

    /* 3. IHOLD_IRUN: 电机电流 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_IHOLD_IRUN,
                     (SPEED_IHOLDDELAY << 16) |
                     (SPEED_IRUN << 8)       |
                     SPEED_IHOLD);

    /* === 第二步: 速度模式参数 === */

    /* 4. AMAX: 最大加速度 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_AMAX, SPEED_AMAX);

    /* 5. VMAX: 目标速度 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_VMAX, SPEED_VMAX);

    /* === 第三步: 启动速度模式 === */

    /* 6. RAMPMODE: 1=正转, 2=反转 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_RAMPMODE, SPEED_DIRECTION);
}

/****
 * 持续监控运行状态, 写入 g_speed_dbg
 * 返回: 0=正常, 1=SPI故障, 2=GSTAT错误
 ********/
static unsigned char Monitor_Chip(TMC5160_T *CHIP_T)
{
    unsigned int val;

    /* SPI 存活检测 */
    val = Tmc5160_ReadReg(CHIP_T, TMC5160_IOIN);
    if (val == 0 || val == 0xFFFFFFFF) return 1;

    /* GSTAT 错误检测 */
    val = Tmc5160_ReadReg(CHIP_T, TMC5160_GSTAT);
    g_speed_dbg.gstat = val;
    if (val & 0x06) {
        g_speed_dbg.drv_status = Tmc5160_ReadReg(CHIP_T,
                                                  TMC5160_DRVSTATUS);
        return 2;
    }

    /* 正常: 刷新状态 */
    g_speed_dbg.ioin_val   = val;  /* 实际是之前读的gstat, 覆盖 */
    g_speed_dbg.ioin_val   = Tmc5160_ReadReg(CHIP_T, TMC5160_IOIN);
    g_speed_dbg.drv_status = Tmc5160_ReadReg(CHIP_T, TMC5160_DRVSTATUS);
    g_speed_dbg.ramp_stat  = Tmc5160_ReadReg(CHIP_T, TMC5160_RAMP_STAT);
    g_speed_dbg.vactual    = Tmc5160_ReadReg(CHIP_T, TMC5160_VACTUAL);
    g_speed_dbg.xactual    = Tmc5160_ReadReg(CHIP_T, TMC5160_XACTUAL);
    return 0;
}

/* test_speed_mode hlp end */
//----------------------------------------------------------------------------------
/* test_speed_mode usr start */

void Test_Speed_Mode(void)
{
    TMC5160_T *chip;
    unsigned char fault;

    Tmc5160_Init();

    /* 选择测试芯片 */
    if (SPEED_CHIP_NUM == 1 || SPEED_CHIP_NUM == 0) {
        g_tmc5160_chip1_st.mode = 1;
        Tmc5160_Mode(&g_tmc5160_chip1_st);
        SpeedMode_SingleChip(&g_tmc5160_chip1_st);
    }

    if (SPEED_CHIP_NUM == 2 || SPEED_CHIP_NUM == 0) {
        g_tmc5160_chip2_st.mode = 1;
        Tmc5160_Mode(&g_tmc5160_chip2_st);
        SpeedMode_SingleChip(&g_tmc5160_chip2_st);
    }

    chip = (SPEED_CHIP_NUM == 1) ? &g_tmc5160_chip1_st : &g_tmc5160_chip2_st;

    /* 持续监控运行状态 */
    while (1) {
        fault = Monitor_Chip(chip);

        if (fault == 0) {
            /* 正常: LED 匀速闪烁, 在Watch窗口看 g_speed_dbg */
            HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin);
        } else if (fault == 1) {
            /* SPI 故障: 快闪2次 */
            for (int i = 0; i < 2; i++) {
                HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                                  GPIO_PIN_RESET);
                HAL_Delay(LED_MS);
                HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                                  GPIO_PIN_SET);
                HAL_Delay(LED_MS);
            }
        } else {
            /* GSTAT 错误: 快闪4次 */
            for (int i = 0; i < 4; i++) {
                HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                                  GPIO_PIN_RESET);
                HAL_Delay(LED_MS);
                HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin,
                                  GPIO_PIN_SET);
                HAL_Delay(LED_MS);
            }
        }

        g_speed_dbg.fault = fault;
        HAL_Delay(MONITOR_MS);
    }
}

/* test_speed_mode usr end */
