#include "ela_eeprom.h"

/*
 * STM32F407 扇区定义 (擦除单位)
 * Sector 0: 0x08000000, 16KB
 * Sector 1: 0x08004000, 16KB
 * Sector 2: 0x08008000, 16KB
 * Sector 3: 0x0800C000, 16KB
 * Sector 4: 0x08010000, 64KB
 * Sector 5: 0x08020000, 128KB
 * Sector 6: 0x08040000, 128KB
 * Sector 7: 0x08060000, 128KB
 */

/* 存储块结构体 */
EEPROM_BLOCK_T g_eeprom_caliblock_st =
    {EEPROM_CALI_ADDR, EEPROM_CALI_SIZE, 1, 0};
EEPROM_BLOCK_T g_eeprom_datablock_st =
    {EEPROM_DATA_ADDR, EEPROM_DATA_SIZE, 1, 0};

//----------------------------------------------------------------------------------
/* eeprom hlp start */
/****
 * @ 输入: unsigned int addr: Flash 地址
 * @ 输出: unsigned int - 扇区编号 (0-7)
 * @ 说明: 根据 Flash 地址获取对应的扇区编号
 ********/
static unsigned int Eeprom_GetSector(unsigned int addr)
{
    unsigned int offset = addr - 0x08000000;

    if (offset < 0x04000) return 0;  // 16KB
    if (offset < 0x08000) return 1;  // 16KB
    if (offset < 0x0C000) return 2;  // 16KB
    if (offset < 0x10000) return 3;  // 16KB
    if (offset < 0x20000) return 4;  // 64KB
    if (offset < 0x40000) return 5;  // 128KB
    if (offset < 0x60000) return 6;  // 128KB
    return 7;                        // 128KB
}

/****
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 *        unsigned int addr: 要设置的写入地址
 * @ 说明: 设置写入地址，
 *        检查写入地址是否在存储块的有效范围内
 ********/
static void Eeprom_WriteSetAddr(EEPROM_BLOCK_T *block,
                                unsigned int addr)
{
    if(addr < block->begin_add)                    return;
    if(addr > block->begin_add + block->area_size) return;
    block->write_addr = addr;
}

/* eeprom hlp end */
//----------------------------------------------------------------------------------
/* eeprom drv start */

/****
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向要擦除的存储块结构体的指针
 * @ 输出: void
 * @ 说明: 擦除指定存储块中的所有扇区，
 *        使用 HAL 库函数进行 Flash 扇区擦除操作
 ********/
void Eeprom_SectorErase(EEPROM_BLOCK_T *block)
{
    unsigned int start = Eeprom_GetSector(block->begin_add);
    unsigned int end   = Eeprom_GetSector(
        block->begin_add + block->area_size - 1);
    unsigned int count = end - start + 1;

    HAL_FLASH_Unlock();

    FLASH_EraseInitTypeDef cfg;
    unsigned int err;
    cfg.TypeErase    = FLASH_TYPEERASE_SECTORS;
    cfg.Sector       = start;
    cfg.NbSectors    = count;
    cfg.VoltageRange = FLASH_VOLTAGE_RANGE_3;

    HAL_FLASHEx_Erase(&cfg, &err);

    HAL_FLASH_Lock();
}

/****
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 * @ 说明: 开始写入数据，
 *        将写地址初始化为存储块的起始地址，并解锁 Flash
 ********/
void Eeprom_WriteBegin(EEPROM_BLOCK_T *block)
{
    HAL_FLASH_Unlock();
    block->write_addr = block->begin_add;
}

/****
 * @ 原型: void Eeprom_WriteEnd(EEPROM_BLOCK_T *block)
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 * @ 说明: 结束写入数据，锁定 Flash
 ********/
void Eeprom_WriteEnd(EEPROM_BLOCK_T *block)
{
    HAL_FLASH_Lock();
}


/****
 * @ 原型: void Eeprom_Write16(EEPROM_BLOCK_T *block,
 *            unsigned short *data, unsigned int num)
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 *        unsigned short *data: 要写入的数据指针
 *        unsigned int num: 要写入的数据数量
 * @ 输出: void
 * @ 说明: 写入16位数据
 ********/
void Eeprom_Write16(EEPROM_BLOCK_T *block,
                    unsigned short *data, unsigned int num)
{
    if(block->write_addr < block->begin_add)
        return;
    if((block->write_addr + num * 2) >
       block->begin_add + block->area_size)
        return;

    for(unsigned int i=0; i<num; i++)
    {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,
               block->write_addr,
               (uint64_t)data[i]) == HAL_OK)
            block->write_addr += 2;
    }
}

/****
 * @ 原型: void Eeprom_Write32(EEPROM_BLOCK_T *block,
 *            unsigned int *data, unsigned int num)
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 *        unsigned int *data: 要写入的数据指针
 *        unsigned int num: 要写入的数据数量
 * @ 输出: void
 * @ 说明: 写入32位数据
 ********/
void Eeprom_Write32(EEPROM_BLOCK_T *block,
                    unsigned int *data, unsigned int num)
{
    if(block->write_addr < block->begin_add)
        return;
    if((block->write_addr + num * 4) >
       block->begin_add + block->area_size)
        return;

    for(unsigned int i=0; i<num; i++)
    {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,
               block->write_addr,
               (unsigned long long)data[i]) == HAL_OK)
            block->write_addr += 4;
    }
}

/****
 * @ 原型: void Eeprom_Write64(EEPROM_BLOCK_T *block,
 *            unsigned long long *data,
 *            unsigned int num)
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 *        unsigned long long *data: 要写入的数据指针
 *        unsigned int num: 要写入的数据数量
 * @ 输出: void
 * @ 说明: 写入64位数据
 ********/
void Eeprom_Write64(EEPROM_BLOCK_T *block,
                    unsigned long long *data,
                    unsigned int num)
{
    if(block->write_addr < block->begin_add)
        return;
    if((block->write_addr + num * 8) >
       block->begin_add + block->area_size)
        return;

    for(unsigned int i=0; i<num; i++)
    {
        if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,
               block->write_addr,
               (unsigned long long)data[i]) == HAL_OK)
            block->write_addr += 8;
    }
}

/* eeprom drv end */
//----------------------------------------------------------------------------------
/* eeprom usr start */

/****
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 *        unsigned int addr:
 *           相对于存储块起始地址的偏移地址
 *        void* data: 读取数据存放地址
 *        unsigned int size: 读取数据大小
 * @ 输出: void
 * @ 说明: 读取指定存储块中从 addr 开始的
 *        size 字节数据到 data 指向的内存区域
 ********/
void Eeprom_Read(EEPROM_BLOCK_T *block, unsigned int addr,
                 void* data, unsigned int size)
{
    if (addr + size > block->area_size) return;

    unsigned char* dst = (unsigned char*)data;
    unsigned int flash_addr = block->begin_add + addr;

    for (unsigned int i = 0; i < size; i++) {
        dst[i] = *((volatile unsigned char*)flash_addr + i);
    }
}


/****
 * @ 原型: void Eeprom_Write(unsigned int addr,
 *            EEPROM_BLOCK_T *block, void* data,
 *            unsigned int size)
 * @ 输入: unsigned int addr:
 *           相对于存储块起始地址的写入偏移
 *        EEPROM_BLOCK_T *block:
 *           指向存储块结构体的指针
 *        void* data: 写入数据存放地址
 *        unsigned int size: 写入数据大小
 * @ 输出: void
 * @ 说明: 将 data 指向的 size 字节数据写入指定存储块
 *        中从 addr 开始的位置
 *        注意: 写入前需要确保目标扇区已被擦除，
 *        调用者应先用 Eeprom_Erase 擦除
 ********/
void Eeprom_Write(unsigned int addr, EEPROM_BLOCK_T *block,
                  void* data, unsigned int size)
{
    if (addr + size > block->area_size) return;

    /* 开始写入 */
    Eeprom_WriteBegin(block);

    /* 设置写地址 */
    Eeprom_WriteSetAddr(block, block->begin_add + addr);

    /* 写入数据（16位对齐） */
    unsigned int halfword_count = (size + 1) / 2;
    Eeprom_Write16(block, (unsigned short*)data,
                   halfword_count);

    /* 结束写入 */
    Eeprom_WriteEnd(block);
}


/****
 * @ 原型: bool Eeprom_Valid(EEPROM_BLOCK_T *block)
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向要检查的存储块结构体的指针
 * @ 输出: bool
 * @ 说明: 检查指定存储块是否有效，
 *        即是否已经写入过数据
 *        通过检查第一个字是否全为0xFF来判断
 *        （空Flash值为0xFFFFFFFF）
 ********/
bool Eeprom_Valid(EEPROM_BLOCK_T *block)
{
    volatile unsigned int* pFirst =
        (volatile unsigned int*)block->begin_add;

    /* 检查第一个字是否全0xFF（空Flash） */
    return (*pFirst != 0xFFFFFFFF);
}


/****
 * @ 原型: void Eeprom_Erase(EEPROM_BLOCK_T *block)
 * @ 输入: EEPROM_BLOCK_T *block:
 *           指向要擦除的存储块结构体的指针
 * @ 输出: void
 * @ 说明: 擦除指定存储块所在的所有扇区
 ********/
void Eeprom_Erase(EEPROM_BLOCK_T *block)
{
    Eeprom_SectorErase(block);
}
/* eeprom usr end */
