/****
 * @ 文件: ela_eeprom.h
 * @ 作者: ELACO
 * @ 日期: 2026-07-24
 * @ 版本: 1.0.0
 * @ 说明: STM32F4 内部 Flash EEPROM 模拟
 ********/
#ifndef ELA_EEPROM_H
#define ELA_EEPROM_H

#include <stdint.h>
#include <stdbool.h>

/* STM32F407ZET6 Flash 扇区布局 (512KB):
 * Sector 0: 0x08000000, 16KB
 * Sector 1: 0x08004000, 16KB
 * Sector 2: 0x08008000, 16KB
 * Sector 3: 0x0800C000, 16KB
 * Sector 4: 0x08010000, 64KB
 * Sector 5: 0x08020000, 128KB
 * Sector 6: 0x08040000, 128KB
 * Sector 7: 0x08060000, 128KB
 *
 * 分配方案:
 *   Firmware:   Sectors 0-3   (0x08000000, 64KB)
 *   Config:     Sector 4      (0x08010000, 64KB)
 *   Data:       Sector 5      (0x08020000, 128KB)
 */

/* Flash 存储块结构体 */
typedef struct {
    uint32_t begin_add;
    uint32_t area_size;
    uint32_t sector_num;
    uint32_t write_addr;
} EEPROM_BLOCK_T;

/* 地址宏定义 */
#define EEPROM_FIRMWARE_ADDR  (0x08000000)
#define EEPROM_FIRMWARE_SIZE  (0x00010000)
#define EEPROM_CALI_ADDR      (0x08010000)
#define EEPROM_CALI_SIZE      (0x00010000)
#define EEPROM_DATA_ADDR      (0x08020000)
#define EEPROM_DATA_SIZE      (0x00020000)

/* 全局预定义的存储块 */
extern EEPROM_BLOCK_T g_eeprom_caliblock_st;
extern EEPROM_BLOCK_T g_eeprom_datablock_st;

/* 用户层函数 */
void ela_eeprom_read(EEPROM_BLOCK_T *block, uint32_t addr,
                     void *data, uint32_t size);
void ela_eeprom_write(uint32_t addr, EEPROM_BLOCK_T *block,
                      void *data, uint32_t size);
bool ela_eeprom_valid(EEPROM_BLOCK_T *block);
void ela_eeprom_erase(EEPROM_BLOCK_T *block);

#endif
