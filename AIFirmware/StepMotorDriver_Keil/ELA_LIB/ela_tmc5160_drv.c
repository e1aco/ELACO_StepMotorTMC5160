/****
 * @ 文件: ela_tmc5160_drv.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.0.0
 * @ 说明: TMC5160 硬件驱动层，SPI/GPIO 原语
 ********/
#include "ela_tmc5160_drv.h"
#include "main.h"
#include "spi.h"

//----------------------------------------------------------------------------------
/* tmc5160_drv start */

/* ---- 芯片选择 ---- */

/****
 * @ 输入: chip: 芯片编号 (TMC5160_CHIP_1 / TMC5160_CHIP_2)
 * @ 输出: 无
 * @ 说明: 拉低对应芯片的 SPI 片选引脚
 ********/
void tmc5160_drv_select_chip(uint8_t chip)
{
    if (TMC5160_CHIP_1 == chip)
    {
        HAL_GPIO_WritePin(U1_SPI1_SCN_GPIO_Port,
                          U1_SPI1_SCN_Pin,
                          GPIO_PIN_RESET);
    }
    else if (TMC5160_CHIP_2 == chip)
    {
        HAL_GPIO_WritePin(U2_SPI1_SCN_GPIO_Port,
                          U2_SPI1_SCN_Pin,
                          GPIO_PIN_RESET);
    }
}

/****
 * @ 输入: chip: 芯片编号
 * @ 输出: 无
 * @ 说明: 拉高对应芯片的 SPI 片选引脚
 ********/
void tmc5160_drv_deselect_chip(uint8_t chip)
{
    if (TMC5160_CHIP_1 == chip)
    {
        HAL_GPIO_WritePin(U1_SPI1_SCN_GPIO_Port,
                          U1_SPI1_SCN_Pin,
                          GPIO_PIN_SET);
    }
    else if (TMC5160_CHIP_2 == chip)
    {
        HAL_GPIO_WritePin(U2_SPI1_SCN_GPIO_Port,
                          U2_SPI1_SCN_Pin,
                          GPIO_PIN_SET);
    }
}

/* ---- GPIO 模式控制 ---- */

/****
 * @ 输入: chip: 芯片编号
 *        mode: 模式 (1/2/3)
 * @ 输出: 无
 * @ 说明: 设置 SD_MODE + SPI_MODE 引脚电平
 *   Mode 1: SD=0, SPI=1 → 定位步进
 *   Mode 2: SD=1, SPI=1 → S斜坡步进+方向
 *   Mode 3: SD=1, SPI=0 → 简单步进+方向
 ********/
void tmc5160_drv_set_mode(uint8_t chip, uint8_t mode)
{
    GPIO_PinState sd_pin, spi_pin;

    if (TMC5160_MODE_POSITION == mode)
    {
        sd_pin = GPIO_PIN_RESET;
        spi_pin = GPIO_PIN_SET;
    }
    else if (TMC5160_MODE_RAMP == mode)
    {
        sd_pin = GPIO_PIN_SET;
        spi_pin = GPIO_PIN_SET;
    }
    else if (TMC5160_MODE_STEP == mode)
    {
        sd_pin = GPIO_PIN_SET;
        spi_pin = GPIO_PIN_RESET;
    }
    else
    {
        return;
    }

    if (TMC5160_CHIP_1 == chip)
    {
        HAL_GPIO_WritePin(U1_SD_MODE_GPIO_Port,
                          U1_SD_MODE_Pin, sd_pin);
        HAL_GPIO_WritePin(U1_SPI_MODE_GPIO_Port,
                          U1_SPI_MODE_Pin, spi_pin);
    }
    else if (TMC5160_CHIP_2 == chip)
    {
        HAL_GPIO_WritePin(U2_SD_MODE_GPIO_Port,
                          U2_SD_MODE_Pin, sd_pin);
        HAL_GPIO_WritePin(U2_SPI_MODE_GPIO_Port,
                          U2_SPI_MODE_Pin, spi_pin);
    }
}

/* ---- 电机使能 ---- */

/****
 * @ 输入: chip: 芯片编号
 * @ 输出: 无
 * @ 说明: 拉低 DRV_ENN 使能电机驱动
 ********/
void tmc5160_drv_enable(uint8_t chip)
{
    if (TMC5160_CHIP_1 == chip)
    {
        HAL_GPIO_WritePin(U1_DRV_ENN_GPIO_Port,
                          U1_DRV_ENN_Pin,
                          GPIO_PIN_RESET);
    }
    else if (TMC5160_CHIP_2 == chip)
    {
        HAL_GPIO_WritePin(U2_DRV_ENN_GPIO_Port,
                          U2_DRV_ENN_Pin,
                          GPIO_PIN_RESET);
    }
}

/****
 * @ 输入: chip: 芯片编号
 * @ 输出: 无
 * @ 说明: 拉高 DRV_ENN 禁用电机驱动
 ********/
void tmc5160_drv_disable(uint8_t chip)
{
    if (TMC5160_CHIP_1 == chip)
    {
        HAL_GPIO_WritePin(U1_DRV_ENN_GPIO_Port,
                          U1_DRV_ENN_Pin,
                          GPIO_PIN_SET);
    }
    else if (TMC5160_CHIP_2 == chip)
    {
        HAL_GPIO_WritePin(U2_DRV_ENN_GPIO_Port,
                          U2_DRV_ENN_Pin,
                          GPIO_PIN_SET);
    }
}

/* ---- 延时 ---- */

/****
 * @ 输入: ms: 毫秒数
 * @ 输出: 无
 * @ 说明: 毫秒延时 (HAL_Delay 封装)
 ********/
void tmc5160_drv_delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

/* ---- SPI 读写原语 ---- */

/****
 * @ 输入: chip: 芯片编号
 *        reg_addr: 寄存器地址 (7位)
 *        data: 要写入的32位数据
 * @ 输出: TMC5160_OK / TMC5160_ERR
 * @ 说明: 通过 SPI 向 TMC5160 写入 32 位寄存器
 *   SPI 数据帧 (40-bit, 5字节):
 *     Byte0: bit7=1(写) + bits6-0=地址
 *     Byte1-4: 数据 [31:0]
 * @ 注意: 使用 TransmitReceive 避免 OVR 标志
 ********/
uint8_t tmc5160_drv_write_reg(uint8_t chip,
                               uint8_t reg_addr,
                               uint32_t data)
{
    static uint8_t tx_buf[5];
    static uint8_t rx_buf[5];
    HAL_StatusTypeDef status;

    tx_buf[0] = reg_addr | 0x80;
    tx_buf[1] = (data >> 24) & 0xFF;
    tx_buf[2] = (data >> 16) & 0xFF;
    tx_buf[3] = (data >> 8) & 0xFF;
    tx_buf[4] = data & 0xFF;

    tmc5160_drv_select_chip(chip);
    status = HAL_SPI_TransmitReceive(&hspi3,
                                     tx_buf, rx_buf,
                                     5, HAL_MAX_DELAY);
    tmc5160_drv_deselect_chip(chip);

    return (HAL_OK == status) ? TMC5160_OK : TMC5160_ERR;
}

/****
 * @ 输入: chip: 芯片编号
 *        reg_addr: 寄存器地址 (7位)
 * @ 输出: 32位寄存器值，失败返回 0xFFFFFFFF
 * @ 说明: 通过 SPI 从 TMC5160 读取 32 位寄存器
 *   需要两报: 第一报丢弃旧数据，第二报获取新数据
 * @ 注意: 两报之间 CS 拉高需满足 t_CHH
 ********/
uint32_t tmc5160_drv_read_reg(uint8_t chip,
                               uint8_t reg_addr)
{
    static uint8_t tx_buf[5];
    static uint8_t rx_buf[5];
    HAL_StatusTypeDef status;

    tx_buf[0] = reg_addr & 0x7F;
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    /* 第一报: 丢弃旧数据 */
    tmc5160_drv_select_chip(chip);
    status = HAL_SPI_TransmitReceive(&hspi3,
                                     tx_buf, rx_buf,
                                     5, HAL_MAX_DELAY);
    tmc5160_drv_deselect_chip(chip);
    if (HAL_OK != status)
    {
        return 0xFFFFFFFF;
    }

    /* CS 高电平间隙 */
    HAL_Delay(1);

    /* 第二报: 获取本次数据 */
    tmc5160_drv_select_chip(chip);
    status = HAL_SPI_TransmitReceive(&hspi3,
                                     tx_buf, rx_buf,
                                     5, HAL_MAX_DELAY);
    tmc5160_drv_deselect_chip(chip);
    if (HAL_OK != status)
    {
        return 0xFFFFFFFF;
    }

    return ((uint32_t)rx_buf[1] << 24) |
           ((uint32_t)rx_buf[2] << 16) |
           ((uint32_t)rx_buf[3] << 8) |
           (uint32_t)rx_buf[4];
}

/* tmc5160_drv end */
