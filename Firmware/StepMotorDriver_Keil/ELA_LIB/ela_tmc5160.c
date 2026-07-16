#include "ela_tmc5160.h"

/* 定义TMC5160结构体
typedef struct TMC5160
{
    unsigned char chip_number; // 芯片号
    unsigned char mode;        // 模式
} TMC5160_T;
*/

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
 *        SPI协议格式(数据手册4.1.1节):
 *        40位数据帧(5字节)
 *          Byte0: bit7=1(写标志), bits6-0=寄存器地址
 *          Byte1: 数据[31:24]
 *          Byte2: 数据[23:16]
 *          Byte3: 数据[15:8]
 *          Byte4: 数据[7:0]
 * @ 注意: 使用TransmitReceive而非Transmit,
 *        避免SPI OVR标志置位影响后续读操作
 ********/
unsigned char Tmc5160_WriteReg(TMC5160_T *CHIP_T,
                                unsigned char reg_addr,
                                unsigned int data) {
    unsigned char tx_buf[5];
    unsigned char rx_buf[5];
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
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
    }
    else if (CHIP_T->chip_number == 2) {
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
    }
    else {
        return FALSE;                  // 芯片号错误
    }

    if (HAL_OK != status) {
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
 *        TMC5160读操作需要两个完整的数据报
 *        (数据手册§4.1.1, 每报40-bit由CS帧定界):
 *          第一报: 发送读命令→返回上次通信的数据(丢弃)
 *          第二报: 再次发送读命令→返回本次请求的寄存器数据
 * @ 注意: 两报之间CS必须拉高再拉低, 各为一个完整的
 *        SPI数据报; 每报之间的CS高电平时间需≥t_CHH
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
        /* 第一报: 发送读命令, 接收的是上一次通信的数据(丢弃) */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (HAL_OK != status) {
            return 0xFFFFFFFF;
        }
        /* CS高电平间隙(满足t_CHH最小时间) */
        HAL_Delay(1);
        /* 第二报: 再次发送读命令, 接收本次请求的寄存器数据 */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (HAL_OK != status) {
            return 0xFFFFFFFF;
        }
    }
    else if (CHIP_T->chip_number == 2) {
        /* 第一报: 发送读命令, 接收的是上一次通信的数据(丢弃) */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (HAL_OK != status) {
            return 0xFFFFFFFF;
        }
        /* CS高电平间隙(满足t_CHH最小时间) */
        HAL_Delay(1);
        /* 第二报: 再次发送读命令, 接收本次请求的寄存器数据 */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                    tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (HAL_OK != status) {
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
 * @ 说明: 初始化TMC5160芯片结构体，
 *        设置芯片号和模式,配置基础寄存器,使能电机驱动
 ********/
void Tmc5160_Init(void) {
    unsigned char i;
    TMC5160_T *chips[2] = { &g_tmc5160_chip1_st,
                            &g_tmc5160_chip2_st };

    for (i = 0; i < 2; i++) {
        TMC5160_T *chip = chips[i];
        chip->chip_number = i + 1;
        chip->mode = 1;
        chip->move_pending = 0;

        Tmc5160_Mode(chip); // 设置 SD_MODE/SPI_MODE 引脚

        /* 使能电机驱动 */
        if (i == 0) {
            CHIP1_DRV_ENN_RESET;
        } else {
            CHIP2_DRV_ENN_RESET;
        }

        /* 清除 Power-on 残留错误标志 */
        Tmc5160_WriteReg(chip, TMC5160_GSTAT, 0x07);

        /* 基础配置 */
        Tmc5160_WriteReg(chip, TMC5160_GCONF, 0x00000004);
        Tmc5160_WriteReg(chip, TMC5160_CHOPCONF, 0x000100C3);

        /* 电机电流：IHOLD=125, IRUN=30, IHOLDDELAY=5 */
        Tmc5160_WriteReg(chip, TMC5160_IHOLD_IRUN, 0x051E7D);
    }
}

/* 运动参数组定义 */
static const TMC5160_MotionProfile_T
    g_tmc5160_profiles_st[TMC5160_PROFILE_COUNT] = {
    { 0, 10, 0, 0,   1000,   5000,   1000,  1000, 10 },
    { 0, 10, 0, 0,   5000,  20000,   5000,  5000, 10 },
    { 0, 10, 0, 0,  10000,  50000,  10000, 10000, 10 },
    { 0, 10, 0, 0,  20000, 100000,  20000, 20000, 10 },
};

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        profile_id:运动参数组ID(1~4)
 * @ 输出: void
 * @ 说明: 按预配置的运动参数组设置TMC5160的斜坡寄存器
 ********/
void Tmc5160_ApplyProfile(TMC5160_T *chip,
                           unsigned char profile_id)
{
    const TMC5160_MotionProfile_T *p;

    if (0 == profile_id ||
        TMC5160_PROFILE_COUNT < profile_id) {
        profile_id = 1;
    }
    p = &g_tmc5160_profiles_st[profile_id - 1];

    Tmc5160_WriteReg(chip, TMC5160_VSTART, p->vstart);
    Tmc5160_WriteReg(chip, TMC5160_VSTOP,  p->vstop);
    Tmc5160_WriteReg(chip, TMC5160_V1,     p->v1);
    Tmc5160_WriteReg(chip, TMC5160_A1,     p->a1);

    Tmc5160_WriteReg(chip, TMC5160_AMAX,   p->amax);
    Tmc5160_WriteReg(chip, TMC5160_VMAX,   p->vmax);
    Tmc5160_WriteReg(chip, TMC5160_DMAX,   p->dmax);
    Tmc5160_WriteReg(chip, TMC5160_D1,     p->d1);

    Tmc5160_WriteReg(chip, TMC5160_TZEROWAIT,
                     p->tzerowait);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        target:目标绝对位置
 * @ 输出: void
 * @ 说明: 设置目标位置(绝对定位),RAMPMODE=0
 ********/
void Tmc5160_MoveTo(TMC5160_T *chip, int target)
{
    Tmc5160_WriteReg(chip, TMC5160_RAMPMODE, 0);
    Tmc5160_WriteReg(chip, TMC5160_XTARGET,
                     (unsigned int)target);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        offset:相对偏移量(正=正转,负=反转)
 * @ 输出: void
 * @ 说明: 从当前位置运动指定偏移量
 ********/
void Tmc5160_MoveBy(TMC5160_T *chip, int offset)
{
    int current = Tmc5160_GetPosition(chip);

    Tmc5160_MoveTo(chip, current + offset);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        velocity:目标速度(正=正转,负=反转)
 * @ 输出: void
 * @ 说明: 切换速度模式持续旋转,直到收到StopMotor命令
 ********/
void Tmc5160_SetVelocity(TMC5160_T *chip, int velocity)
{
    if (0 <= velocity) {
        Tmc5160_WriteReg(chip, TMC5160_RAMPMODE, 1);
        Tmc5160_WriteReg(chip, TMC5160_VMAX,
                         (unsigned int)velocity);
    } else {
        Tmc5160_WriteReg(chip, TMC5160_RAMPMODE, 2);
        Tmc5160_WriteReg(chip, TMC5160_VMAX,
                         (unsigned int)(-velocity));
    }
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: void
 * @ 说明: 立即停止电机,切回定位模式保持锁轴
 ********/
void Tmc5160_StopMotor(TMC5160_T *chip)
{
    Tmc5160_WriteReg(chip, TMC5160_VMAX, 0);
    Tmc5160_WriteReg(chip, TMC5160_RAMPMODE, 0);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: int:当前位置值(XACTUAL)
 * @ 说明: 读取当前位置寄存器XACTUAL(0x21)
 ********/
int Tmc5160_GetPosition(TMC5160_T *chip)
{
    return (int)Tmc5160_ReadReg(chip, TMC5160_XACTUAL);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: unsigned int:RAMP_STAT寄存器值
 * @ 说明: 读取斜坡状态寄存器RAMP_STAT(0x35)
 ********/
unsigned int Tmc5160_GetRampStat(TMC5160_T *chip)
{
    return Tmc5160_ReadReg(chip, TMC5160_RAMP_STAT);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: unsigned int:DRV_STATUS寄存器值
 * @ 说明: 读取驱动状态寄存器DRV_STATUS(0x6F)
 ********/
unsigned int Tmc5160_GetDrvStatus(TMC5160_T *chip)
{
    return Tmc5160_ReadReg(chip, TMC5160_DRVSTATUS);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: unsigned char:状态标志位
 * @ 说明: 读取电机状态并组装为协议定义的标志位
 *        bit0=到位, bit1=堵转, bit2=过温,
 *        bit3=驱动错误, bit4=SPI通讯异常
 ********/
unsigned char Tmc5160_GetStatusFlags(TMC5160_T *chip)
{
    unsigned int ramp_stat, drv_status, gstat;
    unsigned char flags = 0;

    ramp_stat  = Tmc5160_ReadReg(chip,
                                  TMC5160_RAMP_STAT);
    drv_status = Tmc5160_ReadReg(chip,
                                  TMC5160_DRVSTATUS);
    gstat      = Tmc5160_ReadReg(chip,
                                  TMC5160_GSTAT);

    /* SPI通讯异常检测 */
    if (0xFFFFFFFF == ramp_stat ||
        0xFFFFFFFF == drv_status ||
        0xFFFFFFFF == gstat) {
        flags |= 0x10; // bit4 = SPI通讯异常
        return flags;  // 寄存器数据无效，不解析其他位
    }

    if (ramp_stat & (1 << 9))  { flags |= 0x01; }
    if (gstat & 0x02)          { flags |= 0x02; }
    if (drv_status & (3 << 30)){ flags |= 0x04; }
    if (gstat & 0x04)          { flags |= 0x08; }

    return flags;
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: unsigned char:运动阶段标志位
 * @ 说明: 读取RAMP_STAT判断电机当前运动阶段
 *        bit0=加速, bit1=匀速, bit2=减速,
 *        bit3=归零等待, bit4=静止锁轴,
 *        bit5-7保留
 ********/
unsigned char Tmc5160_GetMotionPhase(TMC5160_T *chip)
{
    unsigned int ramp_stat;
    unsigned char phase = 0;

    ramp_stat = Tmc5160_ReadReg(chip,
                                 TMC5160_RAMP_STAT);

    if (ramp_stat & (1 << 5))  { phase |= 0x01; }
    if (ramp_stat & (1 << 6))  { phase |= 0x02; }
    if (ramp_stat & (1 << 7))  { phase |= 0x04; }
    if (ramp_stat & (1 << 10)) { phase |= 0x08; }
    if (ramp_stat & (1 << 0))  { phase |= 0x10; }

    return phase;
}

/* tmc5160 usr end */
