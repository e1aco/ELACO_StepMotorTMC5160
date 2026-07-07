#ifndef _ELA_EEPROM_H_
#define _ELA_EEPROM_H_

#include "elaco_main.h"

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
 *   Firmware:   Sectors 0-3   (0x08000000, 64KB)  ← 在.sct中设置
 *   Calibration: Sector 4     (0x08010000, 64KB)
 *   Data:       Sector 5      (0x08020000, 128KB)
 */

/*Flash 存储块结构体 */
typedef struct{
    unsigned int    begin_add;          // 起始地址
    unsigned int    area_size;          // 区域大小
    unsigned int    sector_num;         // 扇区数量
    unsigned int    write_addr;         // 当前写地址
} EEPROM_BLOCK_T;

/* 全局预定义的存储块 */
extern EEPROM_BLOCK_T g_eeprom_caliblock_st; // 校准值 64K (Sector 4)
extern EEPROM_BLOCK_T g_eeprom_datablock_st; // 数据 128K (Sector 5)

/* 地址宏定义 */
#define EEPROM_FIRMWARE_ADDR (0x08000000)
#define EEPROM_FIRMWARE_SIZE (0x00010000)
#define EEPROM_CALI_ADDR     (0x08010000)
#define EEPROM_CALI_SIZE     (0x00010000)
#define EEPROM_DATA_ADDR     (0x08020000)
#define EEPROM_DATA_SIZE     (0x00020000)

/* 用户层函数 */
void  Eeprom_Read(EEPROM_BLOCK_T *block, unsigned int addr,
                  void *data, unsigned int size);
void  Eeprom_Write(unsigned int addr, EEPROM_BLOCK_T *block,
                   void *data, unsigned int size);
bool  Eeprom_Valid(EEPROM_BLOCK_T *block);
void  Eeprom_Erase(EEPROM_BLOCK_T *block);

/* 内部 Flash 操作函数 */
void  Eeprom_SectorErase(EEPROM_BLOCK_T *block);
void  Eeprom_WriteBegin(EEPROM_BLOCK_T *block);
void  Eeprom_WriteEnd(EEPROM_BLOCK_T *block);
void  Eeprom_WriteSetAddr(EEPROM_BLOCK_T *block,
                          unsigned int addr);
void  Eeprom_Write16(EEPROM_BLOCK_T *block,
                     unsigned short *data, unsigned int num);
void  Eeprom_Write32(EEPROM_BLOCK_T *block,
                     unsigned int *data, unsigned int num);
void  Eeprom_Write64(EEPROM_BLOCK_T *block,
                     unsigned long long *data,
                     unsigned int num);

#endif
