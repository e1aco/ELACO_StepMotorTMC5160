/*****************************************************************************
 * @文件: tmc5160_usr.h
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v2.0
 * @说明: TMC5160 业务逻辑层（运动控制/编码器/状态/配置持久化）
 * @依赖: drv/tmc5160_drv, drv/eeprom
 ****************************************************************************/
#ifndef TMC5160_USR_H
#define TMC5160_USR_H

#include <stdint.h>
#include "drv/tmc5160_drv.h"

/* ==== 返回码 ==== */
#define TMC5160_SUCCESS     0
#define TMC5160_FAIL        1

/* ==== 运动结果 ==== */
typedef enum {
    TMC5160_MOVE_OK = 0,
    TMC5160_MOVE_TIMEOUT,
    TMC5160_MOVE_DEVIATION,
    TMC5160_MOVE_SPI_ERROR
} TMC5160_MOVE_RESULT_T;

/* ==== Flash 配置 ==== */
#define TMC5160_CFG_MAGIC    0x454C4143  /* "ELAC" */

typedef struct {
    uint32_t magic;
    uint8_t  mode;
    uint8_t  closed_loop;
    uint16_t checksum;
} TMC5160_CFG_T;

/* ==== 芯片状态 ==== */
typedef struct {
    uint8_t chip_number;
    uint8_t mode;
    uint8_t closed_loop;
} TMC5160_CHIP_T;

/* ==== 运动参数组 ==== */
typedef struct {
    uint32_t vstart;
    uint32_t vstop;
    uint32_t v1;
    uint32_t a1;
    uint32_t amax;
    uint32_t vmax;
    uint32_t d1;
    uint32_t dmax;
    uint32_t tzerowait;
} TMC5160_PROFILE_T;

#define TMC5160_PROFILE_COUNT  4

/* ==== 常量 ==== */
#define TMC5160_ENC_TOLERANCE    256
#define TMC5160_MOVE_TIMEOUT_MS  5000
#define TMC5160_MAX_RETRY        3

/* ==== 全局实例 ==== */
extern TMC5160_CHIP_T g_tmc5160_chip1_st;
extern TMC5160_CHIP_T g_tmc5160_chip2_st;

/* ==== 接口 ==== */
void    USR_TMC5160_Init(void);
uint8_t USR_TMC5160_WriteReg(TMC5160_CHIP_T *chip, uint8_t reg_addr, uint32_t data);
uint32_t USR_TMC5160_ReadReg(TMC5160_CHIP_T *chip, uint8_t reg_addr);

void    USR_TMC5160_ApplyProfile(TMC5160_CHIP_T *chip, uint8_t profile_id);
void    USR_TMC5160_MoveTo(TMC5160_CHIP_T *chip, int32_t target);
void    USR_TMC5160_MoveBy(TMC5160_CHIP_T *chip, int32_t offset);
void    USR_TMC5160_SetVelocity(TMC5160_CHIP_T *chip, int32_t velocity);
void    USR_TMC5160_Stop(TMC5160_CHIP_T *chip);

int32_t USR_TMC5160_GetPosition(TMC5160_CHIP_T *chip);
uint32_t USR_TMC5160_GetRampStat(TMC5160_CHIP_T *chip);
uint32_t USR_TMC5160_GetDrvStatus(TMC5160_CHIP_T *chip);
uint32_t USR_TMC5160_GetGStat(TMC5160_CHIP_T *chip);

uint8_t USR_TMC5160_GetStatusFlags(TMC5160_CHIP_T *chip);
uint8_t USR_TMC5160_GetMotionPhase(TMC5160_CHIP_T *chip);

void    USR_TMC5160_ConfigEncoder(TMC5160_CHIP_T *chip);
int32_t USR_TMC5160_GetEncoderPosition(TMC5160_CHIP_T *chip);
uint32_t USR_TMC5160_GetEncoderStatus(TMC5160_CHIP_T *chip);
int32_t USR_TMC5160_GetEncoderDeviation(TMC5160_CHIP_T *chip);
uint8_t USR_TMC5160_CheckPosition(TMC5160_CHIP_T *chip, int32_t expected_steps);

TMC5160_MOVE_RESULT_T USR_TMC5160_WaitPosition(TMC5160_CHIP_T *chip, uint32_t timeout_ms);
TMC5160_MOVE_RESULT_T USR_TMC5160_MoveToWithVerify(TMC5160_CHIP_T *chip, int32_t target);

void USR_TMC5160_SetDirty(void);
void USR_TMC5160_SaveConfig(void);

#endif /* TMC5160_USR_H */
