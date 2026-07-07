#include "ela_tmc5160.h"

TMC5160_T g_tmc5160_chip1_st; // 定义TMC5160芯片1的实例
TMC5160_T g_tmc5160_chip2_st; // 定义TMC5160芯片2的实例

/* tmc5160 drv start */

/****
 * @ 原型: unsigned char Tmc5160_Mode(
 *            TMC5160_T* CHIP_T)
 * @ 输入: CHIP_T:芯片号 ; mode:模式
 * @ 输出: TRUE(0):正常输出 ; FALSE(1):输入错误
 * @ 说明: 设置TMC5160芯片的运行模式
 *   MODE    SD_MODE   SPI_MODE       运行状态
 *    1         0         1          位置式步进
 *    2         1         1      S斜坡运动步进+方向控制
 *    3         1         0        简单步进+方向控制
********/
unsigned char Tmc5160_Mode(TMC5160_T* CHIP_T){
    if (CHIP_T->chip_number == 1) {
        switch (CHIP_T->mode) {
            case 1://01
                CHIP1_SD_RESET;
                CHIP1_SPI_SET;
                break;
            case 2://11
                CHIP1_SD_SET;
                CHIP1_SPI_SET;
                break;
            case 3://10
                CHIP1_SD_SET;
                CHIP1_SPI_RESET;
                break;
            default:
                // Handle invalid mode
                return FALSE;
        }
    }
    else if (CHIP_T->chip_number == 2) {
        switch (CHIP_T->mode) {
            case 1://01
                CHIP2_SD_RESET;
                CHIP2_SPI_SET;
                break;
            case 2://11
                CHIP2_SD_SET;
                CHIP2_SPI_SET;
                break;
            case 3://10
                CHIP2_SD_SET;
                CHIP2_SPI_RESET;
                break;
            default:
                // Handle invalid mode
                return FALSE;
        }
    }
    return TRUE;
}

/****
 * @ 原型: unsigned char Tmc5160_WriteReg(
 *            TMC5160_T *CHIP_T,
 *            unsigned char reg_addr,
 *            unsigned int data)
 * @ 输入: CHIP_T:芯片结构体指针
 *        reg_addr:寄存器地址
 *        data:要写入的32位数据
 * @ 输出: TRUE(0):正常输出 ; FALSE(1):输入错误
 * @ 说明: 通过SPI向TMC5160的指定寄存器写入32位数据
 *          SPI协议格式(数据手册4.1.1节):
 *          40位数据帧(5字节)
 *            Byte0: bit7=1(写标志), bits6-0=寄存器地址
 *            Byte1: 数据[31:24]
 *            Byte2: 数据[23:16]
 *            Byte3: 数据[15:8]
 *            Byte4: 数据[7:0]
 ********/
unsigned char Tmc5160_WriteReg(TMC5160_T *CHIP_T,
                                unsigned char reg_addr,
                                unsigned int data) {
    unsigned char tx_buf[5];
    unsigned char status;

    /* 构建SPI发送数据帧: bit7=1写标志 + 7位寄存器地址 */
    tx_buf[0] = reg_addr | 0x80;
    tx_buf[1] = (data >> 24) & 0xFF;
    tx_buf[2] = (data >> 16) & 0xFF;
    tx_buf[3] = (data >> 8) & 0xFF;
    tx_buf[4] = data & 0xFF;

    /* 根据芯片号选择对应的片选引脚 */
    if (CHIP_T->chip_number == 1) {
        CHIP1_CS_RESET;
        status = HAL_SPI_Transmit(&hspi3, tx_buf, 5,
                                  HAL_MAX_DELAY);
        CHIP1_CS_SET;
    }
    else if (CHIP_T->chip_number == 2) {
        CHIP2_CS_RESET;
        status = HAL_SPI_Transmit(&hspi3, tx_buf, 5,
                                  HAL_MAX_DELAY);
        CHIP2_CS_SET;
    }
    else {
        return FALSE;                  // 芯片号错误
    }

    if (status != HAL_OK) {
        return FALSE;                  // SPI传输失败
    }

    return TRUE;
}

/****
 * @ 原型: unsigned int Tmc5160_ReadReg(
 *            TMC5160_T *CHIP_T,
 *            unsigned char reg_addr)
 * @ 输入: CHIP_T:芯片结构体指针
 *        reg_addr:寄存器地址
 * @ 输出: 返回读取到的32位寄存器数据
 *        0xFFFFFFFF表示读取失败
 * @ 说明: 通过SPI从TMC5160的指定寄存器读取32位数据
 *          TMC5160读操作需要连续两次SPI通信
 *          (数据手册4.1.1节):
 *            第一次: 发送读命令(地址|读标志)，
 *              获取的数据是上一次通信的返回值(无效)
 *            第二次: 再次发送读命令，
 *              获取第一次请求的寄存器数据
 ********/
unsigned int Tmc5160_ReadReg(TMC5160_T *CHIP_T,
                              unsigned char reg_addr) {
    unsigned char tx_buf[5];
    unsigned char rx_buf[5];
    unsigned int reg_value;
    unsigned char status;

    /* 构建读命令数据帧: bit7=0读标志 + 7位寄存器地址 */
    tx_buf[0] = reg_addr & 0x7F;
    tx_buf[1] = 0x00;
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    /* 根据芯片号选择对应的片选引脚 */
    if (CHIP_T->chip_number == 1) {
        /* 第一次读: 发送读命令(发送读请求，接收上次数据) */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }

        /* 第二次读: 再次发送读命令，获取实际寄存器数据 */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }
    }
    else if (CHIP_T->chip_number == 2) {
        /* 第一次读: 发送读命令 */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }

        /* 第二次读: 获取实际寄存器数据 */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }
    }
    else {
        return 0xFFFFFFFF;             // 芯片号错误
    }

    /* 解析返回数据:
       rx_buf[0]为状态字节，rx_buf[1]~rx_buf[4]为寄存器数据 */
    reg_value = ((unsigned int)rx_buf[1] << 24) |
                ((unsigned int)rx_buf[2] << 16) |
                ((unsigned int)rx_buf[3] << 8)  |
                (unsigned int)rx_buf[4];

    return reg_value;
}

/* tmc5160 drv end */
//----------------------------------------------------------------------------------
/* tmc5160 usr start */

/****
 * @ 原型: void Tmc5160_Init(void)
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 初始化TMC5160芯片结构体，
 *        设置芯片号和模式,使能芯片的电机驱动
********/
void Tmc5160_Init(void) {
    g_tmc5160_chip1_st.chip_number = 1;
    g_tmc5160_chip1_st.mode = 1;
    g_tmc5160_chip2_st.chip_number = 2;
    g_tmc5160_chip2_st.mode = 1;

    CHIP1_DRV_ENN_SET; // 使能芯片1的电机驱动
    CHIP2_DRV_ENN_SET; // 使能芯片2的电机驱动
}

/* tmc5160 usr end */
