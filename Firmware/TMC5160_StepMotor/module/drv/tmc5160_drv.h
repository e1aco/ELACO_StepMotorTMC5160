/*****************************************************************************
 * @文件: tmc5160_drv.h
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v2.0
 * @说明: TMC5160 硬件驱动层（SPI/GPIO 原语）
 * @平台: STM32F407 (SPI3, 模式3, 2.625Mbps)
 * @依赖: HAL_SPI, HAL_GPIO
 ****************************************************************************/
#ifndef TMC5160_DRV_H
#define TMC5160_DRV_H

#include <stdint.h>

/* ==== 芯片编号 ==== */
#define TMC5160_CHIP_1   1
#define TMC5160_CHIP_2   2

/* ==== SPI 读写返回码 ==== */
#define TMC5160_OK       0
#define TMC5160_ERR      1

/* ==== GPIO 模式引脚 (SD_MODE + SPI_MODE) ==== */
#define TMC5160_MODE_POSITION  1   /* SD=0, SPI=1: 位置式步进(SPI 完全控制) */
#define TMC5160_MODE_RAMP      2   /* SD=1, SPI=1: S 斜坡步进+方向 */
#define TMC5160_MODE_STEP      3   /* SD=1, SPI=0: 简单步进+方向 */

/* ==== 接口 ==== */
void     DRV_TMC5160_SelectChip(uint8_t chip);
void     DRV_TMC5160_DeselectChip(uint8_t chip);
void     DRV_TMC5160_SetMode(uint8_t chip, uint8_t mode);
void     DRV_TMC5160_Enable(uint8_t chip);
void     DRV_TMC5160_Disable(uint8_t chip);
void     DRV_TMC5160_DelayMs(uint32_t ms);
uint8_t  DRV_TMC5160_WriteReg(uint8_t chip, uint8_t reg_addr, uint32_t data);
uint32_t DRV_TMC5160_ReadReg(uint8_t chip, uint8_t reg_addr);

#endif /* TMC5160_DRV_H */
