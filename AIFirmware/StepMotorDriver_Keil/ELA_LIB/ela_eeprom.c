/****
 * @ 文件: ela_eeprom.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-24
 * @ 版本: 1.0.0
 * @ 说明: STM32F4 内部 Flash EEPROM 模拟
 ********/
#include "ela_eeprom.h"
#include "stm32f4xx_hal.h"

/* 扇区偏移边界 */
#define SECTOR_1_OFFSET      0x04000
#define SECTOR_2_OFFSET      0x08000
#define SECTOR_3_OFFSET      0x0C000
#define SECTOR_4_OFFSET      0x10000
#define SECTOR_5_OFFSET      0x20000
#define SECTOR_6_OFFSET      0x40000
#define SECTOR_7_OFFSET      0x60000

//----------------------------------------------------------------------------------
/* eeprom hlp start */

/****
 * @ 输入: uint32_t addr: Flash 地址
 * @ 输出: uint32_t - 扇区编号 (0-7)
 * @ 说明: 根据 Flash 地址获取对应的扇区编号
 ********/
static uint32_t eeprom_get_sector(uint32_t addr)
{
    uint32_t offset = addr - EEPROM_FIRMWARE_ADDR;

    if (offset < SECTOR_1_OFFSET) return 0;
    if (offset < SECTOR_2_OFFSET) return 1;
    if (offset < SECTOR_3_OFFSET) return 2;
    if (offset < SECTOR_4_OFFSET) return 3;
    if (offset < SECTOR_5_OFFSET) return 4;
    if (offset < SECTOR_6_OFFSET) return 5;
    if (offset < SECTOR_7_OFFSET) return 6;
    return 7;
}

/* eeprom hlp end */
//----------------------------------------------------------------------------------
/* eeprom drv start */

EEPROM_BLOCK_T g_eeprom_caliblock_st =
    {EEPROM_CALI_ADDR, EEPROM_CALI_SIZE, 1, 0};
EEPROM_BLOCK_T g_eeprom_datablock_st =
    {EEPROM_DATA_ADDR, EEPROM_DATA_SIZE, 1, 0};

/****
 * @ 输入: EEPROM_BLOCK_T *block: 要擦除的存储块
 * @ 输出: 无
 * @ 说明: 擦除指定存储块中的所有扇区
 * @ 注意: 不可在 ISR 中调用
 ********/
static void eeprom_sector_erase(EEPROM_BLOCK_T *block)
{
    uint32_t start = eeprom_get_sector(block->begin_add);
    uint32_t end   = eeprom_get_sector(
        block->begin_add + block->area_size - 1);
    uint32_t count = end - start + 1;

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef cfg;
    uint32_t err;
    cfg.TypeErase    = FLASH_TYPEERASE_SECTORS;
    cfg.Sector       = start;
    cfg.NbSectors    = count;
    cfg.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    HAL_FLASHEx_Erase(&cfg, &err);

    HAL_FLASH_Lock();
}

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 * @ 输出: 无
 * @ 说明: 开始写入，解锁 Flash
 * @ 注意: 不可在 ISR 中调用
 ********/
static void eeprom_write_begin(EEPROM_BLOCK_T *block)
{
    HAL_FLASH_Unlock();
    block->write_addr = block->begin_add;
}

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 * @ 输出: 无
 * @ 说明: 结束写入，锁定 Flash
 ********/
static void eeprom_write_end(EEPROM_BLOCK_T *block)
{
    HAL_FLASH_Lock();
}

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 *         uint32_t addr: 写入地址
 * @ 输出: 无
 * @ 说明: 设置写入地址
 ********/
static void eeprom_write_set_addr(EEPROM_BLOCK_T *block,
                                  uint32_t addr)
{
    if (addr < block->begin_add) return;
    if (addr >= block->begin_add + block->area_size) return;
    block->write_addr = addr;
}

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 *         uint16_t *data: 数据指针（需 2 字节对齐）
 *         uint32_t num: 数据数量
 * @ 输出: 无
 * @ 说明: 写入 16 位数据，通过 uint8_t 指针避免对齐问题
 ********/
static void eeprom_write16(EEPROM_BLOCK_T *block,
                           uint16_t *data, uint32_t num)
{
    const uint8_t *src = (const uint8_t *)data;
    uint32_t i;

    if (block->write_addr < block->begin_add) return;
    if ((block->write_addr + num * 2) >
        block->begin_add + block->area_size) return;

    for (i = 0; i < num; i++)
    {
        uint16_t val = (uint16_t)src[i * 2] |
                       ((uint16_t)src[i * 2 + 1] << 8);
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,
                block->write_addr,
                (uint64_t)val) == HAL_OK)
            block->write_addr += 2;
    }
}

/* eeprom drv end */
//----------------------------------------------------------------------------------
/* eeprom usr start */

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 *         uint32_t addr: 相对偏移地址
 *         void *data: 读取数据存放地址
 *         uint32_t size: 读取字节数
 * @ 输出: 无
 * @ 说明: 读取指定存储块中的数据
 ********/
void ela_eeprom_read(EEPROM_BLOCK_T *block, uint32_t addr,
                     void *data, uint32_t size)
{
    if (addr + size > block->area_size) return;

    uint8_t *dst = (uint8_t *)data;
    uint32_t flash_addr = block->begin_add + addr;

    for (uint32_t i = 0; i < size; i++)
    {
        dst[i] = *((volatile uint8_t *)flash_addr + i);
    }
}

/****
 * @ 输入: uint32_t addr: 相对偏移地址
 *         EEPROM_BLOCK_T *block: 存储块
 *         void *data: 数据指针
 *         uint32_t size: 字节数
 * @ 输出: 无
 * @ 说明: 写入数据到指定存储块
 * @ 注意: 不可在 ISR 中调用；调用前须先擦除目标扇区
 ********/
void ela_eeprom_write(uint32_t addr, EEPROM_BLOCK_T *block,
                      void *data, uint32_t size)
{
    uint32_t i;
    const uint8_t *src = (const uint8_t *)data;
    uint8_t *dst;

    if (addr + size > block->area_size) return;

    eeprom_write_begin(block);
    eeprom_write_set_addr(block, block->begin_add + addr);

    uint32_t halfword_count = (size + 1) / 2;
    eeprom_write16(block, (uint16_t *)data,
                   halfword_count);

    eeprom_write_end(block);

    /* 回读校验 */
    dst = (uint8_t *)(block->begin_add + addr);
    for (i = 0; i < size; i++)
    {
        if (dst[i] != src[i]) return;
    }
}

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 * @ 输出: bool - 是否有效（已写入过数据）
 * @ 说明: 检查存储块是否有效
 ********/
bool ela_eeprom_valid(EEPROM_BLOCK_T *block)
{
    volatile uint32_t *pFirst =
        (volatile uint32_t *)block->begin_add;

    return (*pFirst != 0xFFFFFFFF);
}

/****
 * @ 输入: EEPROM_BLOCK_T *block: 存储块
 * @ 输出: 无
 * @ 说明: 擦除指定存储块
 * @ 注意: 不可在 ISR 中调用
 ********/
void ela_eeprom_erase(EEPROM_BLOCK_T *block)
{
    eeprom_sector_erase(block);
}

/* eeprom usr end */
