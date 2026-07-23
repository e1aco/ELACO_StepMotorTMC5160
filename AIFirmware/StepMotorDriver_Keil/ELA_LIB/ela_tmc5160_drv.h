/****
 * @ 文件: ela_tmc5160_drv.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.0.0
 * @ 说明: TMC5160 硬件驱动层，SPI/GPIO 原语
 ********/
#ifndef ELA_TMC5160_DRV_H
#define ELA_TMC5160_DRV_H

#include <stdint.h>

/* TMC5160 芯片编号 */
#define TMC5160_CHIP_1  1
#define TMC5160_CHIP_2  2

/* SPI 读写返回值 */
#define TMC5160_OK      0
#define TMC5160_ERR     1

/* GPIO 模式引脚: SD_MODE + SPI_MODE
 * Mode 1: SD=0, SPI=1 → 定位步进
 * Mode 2: SD=1, SPI=1 → S斜坡步进+方向
 * Mode 3: SD=1, SPI=0 → 简单步进+方向
 */
#define TMC5160_MODE_POSITION  1
#define TMC5160_MODE_RAMP      2
#define TMC5160_MODE_STEP      3

/* ---- 芯片选择 ---- */
void tmc5160_drv_select_chip(uint8_t chip);
void tmc5160_drv_deselect_chip(uint8_t chip);

/* ---- GPIO 模式控制 ---- */
void tmc5160_drv_set_mode(uint8_t chip, uint8_t mode);

/* ---- 电机使能 ---- */
void tmc5160_drv_enable(uint8_t chip);
void tmc5160_drv_disable(uint8_t chip);

/* ---- 延时 ---- */
void tmc5160_drv_delay_ms(uint32_t ms);

/* ---- SPI 读写原语 ---- */
uint8_t tmc5160_drv_write_reg(uint8_t chip,
                               uint8_t reg_addr,
                               uint32_t data);
uint32_t tmc5160_drv_read_reg(uint8_t chip,
                               uint8_t reg_addr);

#endif
