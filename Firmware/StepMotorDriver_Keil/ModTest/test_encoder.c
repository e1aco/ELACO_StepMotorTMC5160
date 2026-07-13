#include "test_encoder.h"

/* 直接从 Test_Speed_Mode 复制, 只加编码器 3 行 */

#define TEST_CHIP_NUM       2
#define TEST_VMAX           30676
#define TEST_AMAX           500
#define TEST_IRUN           15
#define TEST_IHOLD          8
#define MOVE_TIME_MS        1200
#define TOLERANCE_COUNT     512     /* 51200 × 1% */
#define LED_MS              100

typedef struct {
    int32_t  x_enc_init;
    int32_t  x_enc_final;
    int32_t  x_enc_delta;
    int32_t  expected;
    int32_t  error;
    unsigned char fault;
} ENC_DBG_T;

ENC_DBG_T g_enc_dbg = {0};

static void Encoder_SingleChip(TMC5160_T *CHIP_T)
{
    unsigned char chip = CHIP_T->chip_number;

    /* 同 SpeedMode_SingleChip 完全一致 */
    if (chip == 1) {
        HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
    } else {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
    }

    Tmc5160_WriteReg(CHIP_T, TMC5160_GSTAT, 0x07);
    Tmc5160_WriteReg(CHIP_T, TMC5160_CHOPCONF, 0x000100C3);
    Tmc5160_WriteReg(CHIP_T, TMC5160_IHOLD_IRUN,
                     (5 << 16) | (TEST_IRUN << 8) | TEST_IHOLD);
    Tmc5160_WriteReg(CHIP_T, TMC5160_GCONF, 0x00000004);
    Tmc5160_WriteReg(CHIP_T, TMC5160_AMAX, TEST_AMAX);
    Tmc5160_WriteReg(CHIP_T, TMC5160_VMAX, TEST_VMAX);

    /* ★ 编码器 3 行 ★ */
    Tmc5160_WriteReg(CHIP_T, TMC5160_ENCMODE, 0x00000000);
    Tmc5160_WriteReg(CHIP_T, TMC5160_ENC_CONST, 0x00033333);//编码器是4000PPR，步距角是1.8°，微步是256微步
    g_enc_dbg.x_enc_init = Tmc5160_ReadReg(CHIP_T, TMC5160_X_ENC);

    /* 速度模式正转, X_ENC单位是usteps, 1圈=51200, 等编码器变化>=51200后停 */
    Tmc5160_WriteReg(CHIP_T, TMC5160_RAMPMODE, 1);
    {
        int32_t cur, diff;
        unsigned int timeout = 0;
        while (1) {
            cur = Tmc5160_ReadReg(CHIP_T, TMC5160_X_ENC);
            diff = cur - g_enc_dbg.x_enc_init;
            if (diff < 0) diff = -diff;
            if (diff >= 16000) break;       /* 1圈 = 51200 usteps */
            if (++timeout > 10000) break;
            HAL_Delay(1);
        }
    }
    Tmc5160_WriteReg(CHIP_T, TMC5160_VMAX, 0);
    HAL_Delay(500);

    g_enc_dbg.x_enc_final = Tmc5160_ReadReg(CHIP_T, TMC5160_X_ENC);
}

void Test_Encoder(void)
{
    TMC5160_T *chip;
    int32_t delta, error_abs;

    /* 完全同 Test_Speed_Mode 框架 */
    Tmc5160_Init();

    if (TEST_CHIP_NUM == 1 || TEST_CHIP_NUM == 0) {
        g_tmc5160_chip1_st.mode = 1;
        Tmc5160_Mode(&g_tmc5160_chip1_st);
        Encoder_SingleChip(&g_tmc5160_chip1_st);
    }

    if (TEST_CHIP_NUM == 2 || TEST_CHIP_NUM == 0) {
        g_tmc5160_chip2_st.mode = 1;
        Tmc5160_Mode(&g_tmc5160_chip2_st);
        Encoder_SingleChip(&g_tmc5160_chip2_st);
    }

    chip = (TEST_CHIP_NUM == 1) ? &g_tmc5160_chip1_st
                                : &g_tmc5160_chip2_st;
    /* (x_enc 值已由 Encoder_SingleChip 填入 g_enc_dbg) */

    delta = g_enc_dbg.x_enc_final - g_enc_dbg.x_enc_init;
    if (delta < 0) delta = -delta;
    g_enc_dbg.x_enc_delta = delta;
    g_enc_dbg.expected     = 16000;   /* 1圈 = 51200 µsteps in X_ENC */
    g_enc_dbg.error        = delta - 16000;
    error_abs = (delta > 16000) ? (delta - 16000) : (16000 - delta);

    if (error_abs <= TOLERANCE_COUNT) {
        g_enc_dbg.fault = 0;
        while (1) {
            HAL_GPIO_TogglePin(MCU_LED_GPIO_Port, MCU_LED_Pin);
            HAL_Delay(500);
        }
    } else {
        g_enc_dbg.fault = 1;
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
