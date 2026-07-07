//
// Created by electronic on 2026/5/28.
//
#include "tmc5160.h"

TMC5160_T TMC5160_Chip1; // 定义TMC5160芯片1的实例
TMC5160_T TMC5160_Chip2; // 定义TMC5160芯片2的实例

/****
 * @ 原型: unsigned char tmc5160_mode(unsigned char chip_number,unsigned char mode)
 * @ 输入: chip_number:芯片号 ; mode:模式
 * @ 输出: TRUE(0):正常输出 ; FALSE(1):输入错误
 * @ 说明: 设置TMC5160芯片的运行模式
 *   MODE    SD_MODE   SPI_MODE       运行状态
 *    1         0         1          位置式步进
 *    2         1         1      S斜坡运动步进+方向控制
 *    3         1         0        简单步进+方向控制
********/
unsigned char tmc5160_mode(TMC5160_T* CHIP_T){
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
                break;
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
                break;
        }
    }
    return TRUE;
}

/****
 * @ 原型: void tmc5160_init(void)
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 初始化TMC5160芯片结构体，设置芯片号和模式,使能芯片的电机驱动
********/
void tmc5160_init(void) {
    TMC5160_Chip1.chip_number = 1; // 设置芯片1的芯片号
    TMC5160_Chip1.mode = 1;        // 设置芯片1
    TMC5160_Chip2.chip_number = 2; // 设置芯片2的芯片号
    TMC5160_Chip2.mode = 2;        // 设置芯片2的模式

    CHIP1_DRV_ENN_SET; // 使能芯片1的电机驱动
    CHIP2_DRV_ENN_SET; // 使能芯片2的电机驱动
}

/****
 * @ 原型: unsigned char tmc5160_write_reg(TMC5160_T *CHIP_T, unsigned char reg_addr, unsigned int data)
 * @ 输入: CHIP_T:芯片结构体指针 ; reg_addr:寄存器地址 ; data:要写入的32位数据
 * @ 输出: TRUE(0):正常输出 ; FALSE(1):输入错误
 * @ 说明: 通过SPI向TMC5160的指定寄存器写入32位数据
 *          SPI协议格式(数据手册4.1.1节): 40位数据帧(5字节)
 *            Byte0: bit7=1(写标志), bits6-0=寄存器地址
 *            Byte1: 数据[31:24]
 *            Byte2: 数据[23:16]
 *            Byte3: 数据[15:8]
 *            Byte4: 数据[7:0]
 ********/
unsigned char tmc5160_write_reg(TMC5160_T *CHIP_T, unsigned char reg_addr, unsigned int data) {
    unsigned char tx_buf[5];
    unsigned char status;

    /* 构建SPI发送数据帧: bit7=1写标志 + 7位寄存器地址 */
    tx_buf[0] = reg_addr | 0x80;              // 写命令: 0x80 | 寄存器地址
    tx_buf[1] = (data >> 24) & 0xFF;          // 数据高字节
    tx_buf[2] = (data >> 16) & 0xFF;
    tx_buf[3] = (data >> 8) & 0xFF;
    tx_buf[4] = data & 0xFF;                  // 数据低字节

    /* 根据芯片号选择对应的片选引脚 */
    if (CHIP_T->chip_number == 1) {
        CHIP1_CS_RESET;                        // 片选拉低，选中芯片1
        status = HAL_SPI_Transmit(&hspi1, tx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;                          // 片选拉高，释放芯片1
    }
    else if (CHIP_T->chip_number == 2) {
        CHIP2_CS_RESET;                        // 片选拉低，选中芯片2
        status = HAL_SPI_Transmit(&hspi1, tx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;                          // 片选拉高，释放芯片2
    }
    else {
        return FALSE;                          // 芯片号错误
    }

    if (status != HAL_OK) {
        return FALSE;                          // SPI传输失败
    }

    return TRUE;
}

/****
 * @ 原型: unsigned int tmc5160_read_reg(TMC5160_T *CHIP_T, unsigned char reg_addr)
 * @ 输入: CHIP_T:芯片结构体指针 ; reg_addr:寄存器地址
 * @ 输出: 返回读取到的32位寄存器数据 ; 0xFFFFFFFF表示读取失败
 * @ 说明: 通过SPI从TMC5160的指定寄存器读取32位数据
 *          TMC5160读操作需要连续两次SPI通信(数据手册4.1.1节):
 *            第一次: 发送读命令(地址|读标志)，获取的数据是上一次通信的返回值(无效)
 *            第二次: 再次发送读命令，获取第一次请求的寄存器数据
 ********/
unsigned int tmc5160_read_reg(TMC5160_T *CHIP_T, unsigned char reg_addr) {
    unsigned char tx_buf[5];
    unsigned char rx_buf[5];
    unsigned int reg_value;
    unsigned char status;

    /* 构建读命令数据帧: bit7=0读标志 + 7位寄存器地址 */
    tx_buf[0] = reg_addr & 0x7F;              // 读命令: 0x7F & 寄存器地址
    tx_buf[1] = 0x00;                               // 发送空数据
    tx_buf[2] = 0x00;
    tx_buf[3] = 0x00;
    tx_buf[4] = 0x00;

    /* 根据芯片号选择对应的片选引脚 */
    if (CHIP_T->chip_number == 1) {
        /* 第一次读: 发送读命令(发送读请求，接收上一次的数据) */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }

        /* 第二次读: 再次发送读命令，获取实际寄存器数据 */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }
    }
    else if (CHIP_T->chip_number == 2) {
        /* 第一次读: 发送读命令 */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }

        /* 第二次读: 获取实际寄存器数据 */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi1, tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (status != HAL_OK) {
            return 0xFFFFFFFF;
        }
    }
    else {
        return 0xFFFFFFFF;                         // 芯片号错误
    }

    /* 解析返回数据: rx_buf[0]为状态字节，rx_buf[1]~rx_buf[4]为寄存器数据 */
    reg_value = ((unsigned int)rx_buf[1] << 24) |
                ((unsigned int)rx_buf[2] << 16) |
                ((unsigned int)rx_buf[3] << 8)  |
                (unsigned int)rx_buf[4];

    return reg_value;
}

/****
 * @ 使用示例:
 *
 * // 1. 在 main.c 中初始化结构体
 * tmc5160_struct_init();                           // 设置芯片号和默认模式
 *
 * // 2. 设置硬件接口模式(必须先设置模式再操作寄存器)
 * tmc5160_mode(&TMC5160_Chip1);                    // Mode1=位置式步进(全部SPI寄存器控制)
 *
 * // 3. 设置芯片内部斜坡模式为定位模式
 * //    (RAMPMODE=0:定位模式, 1:速度正转, 2:速度反转)
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 0);
 *
 * // ───────────────────────────────
 * // ▼  方案A: 定位模式(走到指定位置后停止)
 * // ───────────────────────────────
 * // 4. 配置芯片1基本参数
 * //    4a. 设置保持电流和运行电流(IHOLD_IRUN寄存器, 地址0x10)
 * //        位域分配: [7:0]=IHOLD保持电流, [15:8]=IRUN运行电流, [19:16]=IHOLDDELAY
 * //        CS值范围0~31(共32级),实际电流 = CS/32 × 额定最大电流
 * //        额定最大电流由硬件决定(取决于驱动板上的Sense电阻Rsense):
 * //          Vfs是满量程检测电压(TMC5160内部固定为0.325V)
 * //          峰值电流: I_peak = Vfs / Rsense
 * //          RMS有效值电流: I_RMS = I_peak / √2 = Vfs / (Rsense × 1.414)
 * //          Datasheet中标注的是RMS电流
 * //          例如: Rsense=0.1Ω时, I_RMS=0.325/(0.1×1.414)≈2.3A
 * //                Rsense=0.05Ω时, I_RMS=0.325/(0.05×1.414)≈4.6A(与datasheet的4.7A基本一致)
 * //
 * //        所以最终电机电流 = CS/32 × I_RMS
 * //        0x00001808 解析:
 * //          IHOLD = 0x08 = 8  →  8/32 = 25% × I_RMS (停止时保持力矩)
 * //          IRUN  = 0x18 = 24 → 24/32 = 75% × I_RMS (运行时力矩)
 * //          IHOLDDELAY = 0    → 停止后立刻降为保持电流
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_IHOLD_IRUN, 0x00001808);
 *
 * //    4b. 配置斩波驱动参数
 * //        这里使用推荐值, 使能stealthChop静音模式
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_CHOPCONF, 0x00000101);
 *
 * //    4c. 设置最大速度和加速度(位置模式·RAMPMODE=0)
 * //        VMAX = 速度上限(运动过程中不会超过这个速度)
 * //        AMAX = 加速度上限(加减速过程的快慢)
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX,  500000);  // 速度上限500000
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_AMAX,   10000);  // 加速度10000
 *
 * //    4d. 设置目标位置(电机将以S曲线运动到指定位置)
 * //        写入XTARGET后电机开始运动，到位置后自动停止
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XTARGET, 20000); // 目标位置20000步
 *
 * //    4e. 读取芯片1实际位置
 * unsigned int pos = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_XACTUAL);
 *
 * // ───────────────────────────────
 * // ▼  方案B: 速度模式(持续正转/反转)
 * // ───────────────────────────────
 * //      (仍在Mode1-SPI模式下,不需要切模式2,改RAMPMODE寄存器就行)
 * // 5. 切换为速度模式
 * //    RAMPMODE=1(速度正转), RAMPMODE=2(速度反转)
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 1);
 *
 * // 6. 设定速度(单位: μsteps/s)
 * //    注: 这里的VMAX和方案A中的4c的VMAX含义不同!
 * //        · 方案A定位模式(4c): VMAX是速度上限,电机走XTARGET时不超过这个速度
 * //        · 方案B速度模式(6):  VMAX就是目标速度(正转或反转)
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX, 200000);  // 以200000μsteps/s正转
 *
 * // 7. 停止电机(速度设为0)
 * tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX, 0);       // 速度归零
 *
 * // 8. 读取驱动状态(检查错误)
 * unsigned int status = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_DRVSTATUS);
 ********/
