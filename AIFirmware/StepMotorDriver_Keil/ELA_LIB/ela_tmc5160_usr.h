/****
 * @ 文件: ela_tmc5160_usr.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.0.0
 * @ 说明: TMC5160 业务逻辑层，运动控制/编码器/状态
 ********/
#ifndef ELA_TMC5160_USR_H
#define ELA_TMC5160_USR_H

#include <stdint.h>

/* ---- 错误码 ---- */
#define TMC5160_SUCCESS     0
#define TMC5160_FAIL        1

/* ---- 运动结果 ---- */
typedef enum {
    MOVE_OK = 0,
    MOVE_TIMEOUT,
    MOVE_DEVIATION,
    MOVE_SPI_ERROR
} TMC5160_MOVE_RESULT_T;

/* ---- Flash 配置 ---- */
#define CHIP_CONFIG_MAGIC    0x454C4143  /* "ELAC" */

typedef struct {
    uint32_t magic;
    uint8_t  mode;
    uint8_t  closed_loop;
    uint16_t checksum;
} CHIP_CONFIG_T;

/* ---- 芯片状态 ---- */
typedef struct {
    uint8_t chip_number;
    uint8_t mode;
    uint8_t closed_loop;
} TMC5160_CHIP_T;

/* ---- 运动参数组 ---- */
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
} TMC5160_MOTION_PROFILE_T;

#define TMC5160_PROFILE_COUNT  4

/* ---- 常量 ---- */
#define TMC5160_ENC_TOLERANCE    256
#define TMC5160_MOVE_TIMEOUT_MS  5000
#define TMC5160_MAX_RETRY        3

/* ---- 全局实例 ---- */
extern TMC5160_CHIP_T g_tmc5160_chip1_st;
extern TMC5160_CHIP_T g_tmc5160_chip2_st;

/* ---- 初始化 ---- */
void ela_tmc5160_init(void);

/* ---- 寄存器读写 ---- */
uint8_t ela_tmc5160_write_reg(TMC5160_CHIP_T *chip,
                               uint8_t reg_addr,
                               uint32_t data);
uint32_t ela_tmc5160_read_reg(TMC5160_CHIP_T *chip,
                               uint8_t reg_addr);

/* ---- 运动控制 ---- */
void ela_tmc5160_apply_profile(TMC5160_CHIP_T *chip,
                                uint8_t profile_id);
void ela_tmc5160_move_to(TMC5160_CHIP_T *chip,
                          int32_t target);
void ela_tmc5160_move_by(TMC5160_CHIP_T *chip,
                          int32_t offset);
void ela_tmc5160_set_velocity(TMC5160_CHIP_T *chip,
                               int32_t velocity);
void ela_tmc5160_stop(TMC5160_CHIP_T *chip);

/* ---- 位置读取 ---- */
int32_t ela_tmc5160_get_position(TMC5160_CHIP_T *chip);
uint32_t ela_tmc5160_get_ramp_stat(TMC5160_CHIP_T *chip);
uint32_t ela_tmc5160_get_drv_status(TMC5160_CHIP_T *chip);

/* ---- 状态标志 ---- */
uint8_t ela_tmc5160_get_status_flags(TMC5160_CHIP_T *chip);
uint8_t ela_tmc5160_get_motion_phase(TMC5160_CHIP_T *chip);

/* ---- 编码器 ---- */
void ela_tmc5160_config_encoder(TMC5160_CHIP_T *chip);
int32_t ela_tmc5160_get_encoder_position(TMC5160_CHIP_T *chip);
uint32_t ela_tmc5160_get_encoder_status(TMC5160_CHIP_T *chip);
int32_t ela_tmc5160_get_encoder_deviation(TMC5160_CHIP_T *chip);
uint8_t ela_tmc5160_check_position(TMC5160_CHIP_T *chip,
                                    int32_t expected_steps);

/* ---- 带验证的运动 ---- */
TMC5160_MOVE_RESULT_T ela_tmc5160_wait_position(
    TMC5160_CHIP_T *chip, uint32_t timeout_ms);
TMC5160_MOVE_RESULT_T ela_tmc5160_move_to_with_verify(
    TMC5160_CHIP_T *chip, int32_t target);

/* ---- 配置持久化 ---- */
void ela_tmc5160_set_dirty(void);
void ela_tmc5160_save_config(void);

#endif
