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
unsigned char Tmc5160_Mode(TMC5160_T *CHIP_T)
{
    if (CHIP_T->chip_number == 1)
    {
        switch (CHIP_T->mode)
        {
        case 1: // 01
            CHIP1_SD_RESET;
            CHIP1_SPI_SET;
            break;
        case 2: // 11
            CHIP1_SD_SET;
            CHIP1_SPI_SET;
            break;
        case 3: // 10
            CHIP1_SD_SET;
            CHIP1_SPI_RESET;
            break;
        default:
            // Handle invalid mode
            return FALSE;
        }
    }
    else if (CHIP_T->chip_number == 2)
    {
        switch (CHIP_T->mode)
        {
        case 1: // 01
            CHIP2_SD_RESET;
            CHIP2_SPI_SET;
            break;
        case 2: // 11
            CHIP2_SD_SET;
            CHIP2_SPI_SET;
            break;
        case 3: // 10
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
                               unsigned int data)
{
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
    if (CHIP_T->chip_number == 1)
    {
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                                         tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
    }
    else if (CHIP_T->chip_number == 2)
    {
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                                         tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
    }
    else
    {
        return FALSE; // 芯片号错误
    }

    if (HAL_OK != status)
    {
        return FALSE; // SPI传输失败
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
                             unsigned char reg_addr)
{
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
    if (CHIP_T->chip_number == 1)
    {
        /* 第一报: 发送读命令, 接收的是上一次通信的数据(丢弃) */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                                         tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (HAL_OK != status)
        {
            return 0xFFFFFFFF;
        }
        /* CS高电平间隙(满足t_CHH最小时间) */
        HAL_Delay(1);
        /* 第二报: 再次发送读命令, 接收本次请求的寄存器数据 */
        CHIP1_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                                         tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP1_CS_SET;
        if (HAL_OK != status)
        {
            return 0xFFFFFFFF;
        }
    }
    else if (CHIP_T->chip_number == 2)
    {
        /* 第一报: 发送读命令, 接收的是上一次通信的数据(丢弃) */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                                         tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (HAL_OK != status)
        {
            return 0xFFFFFFFF;
        }
        /* CS高电平间隙(满足t_CHH最小时间) */
        HAL_Delay(1);
        /* 第二报: 再次发送读命令, 接收本次请求的寄存器数据 */
        CHIP2_CS_RESET;
        status = HAL_SPI_TransmitReceive(&hspi3,
                                         tx_buf, rx_buf, 5, HAL_MAX_DELAY);
        CHIP2_CS_SET;
        if (HAL_OK != status)
        {
            return 0xFFFFFFFF;
        }
    }
    else
    {
        return 0xFFFFFFFF; // 芯片号错误
    }

    /* 解析返回数据:
       rx_buf[0]为状态字节，rx_buf[1]~rx_buf[4]为寄存器数据 */
    reg_value = ((unsigned int)rx_buf[1] << 24) |
                ((unsigned int)rx_buf[2] << 16) |
                ((unsigned int)rx_buf[3] << 8) |
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
void Tmc5160_Init(void)
{
    unsigned char i;
    TMC5160_T *chips[2] = {&g_tmc5160_chip1_st,
                           &g_tmc5160_chip2_st};

    for (i = 0; i < 2; i++)
    {
        TMC5160_T *chip = chips[i];
        chip->chip_number = i + 1;
        chip->mode = 1;
        chip->move_pending = 0;

        Tmc5160_Mode(chip); // 设置 SD_MODE/SPI_MODE 引脚

        /* 使能电机驱动 */
        if (i == 0)
        {
            CHIP1_DRV_ENN_RESET;
        }
        else
        {
            CHIP2_DRV_ENN_RESET;
        }
        /* 清除 Power-on 残留错误标志 */
        // 清除复位，驱动错误，电荷泵异常问题
        Tmc5160_WriteReg(chip, TMC5160_GSTAT, 0x07);

        /* 基础配置 */
        // 开机设置为静音模式
        Tmc5160_WriteReg(chip, TMC5160_GCONF, 0x00000004);
        /* CHOPCONF 推荐值:
         * TOFF=5(稳定), TBL=%01(24时钟),
         * HSTRT=4, HEND=0, MRES=0(256微步) */
        // 000 10 0 00 0 0011 100 0101
        Tmc5160_WriteReg(chip, TMC5160_CHOPCONF, 0x000101C5);

        /* 编码器配置 */
        Tmc5160_ConfigEncoder(chip);

        /* 电机电流配置
         * IHOLD_IRUN 寄存器 (0x10) 布局:
         *   Bits [4:0]   = IHOLD     (5位, 0~31)  保持电流
         *   Bits [12:8]  = IRUN      (5位, 0~31)  运行电流
         *   Bits [19:16] = IHOLDDELAY (4位, 0~15) 保持延迟
         *
         * 电流计算公式 (TMC5160 数据手册):
         *   I_run = (IRUN / 31) × (0.325V / (32 × RS))
         *
         *  RS=0.05R
         *   I_full = 0.325V / (32 × 0.05Ω) ≈ 203mA
         *
         * 电机 57CME13 MS31 额定电流 = 1.0A
         * 需要 IRUN ≈ 24 (77%) 才能达到额定电流
         *
         * 设置值: IHOLD=6, IRUN=16, IHOLDDELAY=6
         *   保持电流 = 6/31 × 203mA ≈ 35mA (省电降温)
         *   运行电流 = 16/31 × 203mA ≈ 104.7mA
         *   延迟时间 ≈ 6 × 16 × tclk ≈ 500ms
         */
        Tmc5160_WriteReg(chip, TMC5160_IHOLD_IRUN,
                         (6 << 16) | (16 << 8) | 6);
    }
}

/* 运动参数组定义 */
static const TMC5160_MotionProfile_T
    g_tmc5160_profiles_st[TMC5160_PROFILE_COUNT] = {
        {0, 10, 0, 0, 1000, 5000, 1000, 1000, 10},
        {0, 10, 0, 0, 5000, 20000, 5000, 5000, 10},
        {0, 10, 0, 0, 10000, 50000, 10000, 10000, 10},
        {0, 10, 0, 0, 20000, 100000, 20000, 20000, 10},
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
        TMC5160_PROFILE_COUNT < profile_id)
    {
        profile_id = 1;
    }
    p = &g_tmc5160_profiles_st[profile_id - 1];

    Tmc5160_WriteReg(chip, TMC5160_VSTART, p->vstart);
    Tmc5160_WriteReg(chip, TMC5160_VSTOP, p->vstop);
    Tmc5160_WriteReg(chip, TMC5160_V1, p->v1);
    Tmc5160_WriteReg(chip, TMC5160_A1, p->a1);

    Tmc5160_WriteReg(chip, TMC5160_AMAX, p->amax);
    Tmc5160_WriteReg(chip, TMC5160_VMAX, p->vmax);
    Tmc5160_WriteReg(chip, TMC5160_DMAX, p->dmax);
    Tmc5160_WriteReg(chip, TMC5160_D1, p->d1);

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
    if (0 <= velocity)
    {
        Tmc5160_WriteReg(chip, TMC5160_RAMPMODE, 1);
        Tmc5160_WriteReg(chip, TMC5160_VMAX,
                         (unsigned int)velocity);
    }
    else
    {
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
 *        bit0=到位, bit1=失步, bit2=过温,
 *        bit3=驱动错误, bit4=SPI通讯异常
 ********/
unsigned char Tmc5160_GetStatusFlags(TMC5160_T *chip)
{
    unsigned int ramp_stat, drv_status, gstat, enc_stat;
    unsigned char flags = 0;

    ramp_stat = Tmc5160_ReadReg(chip,
                                TMC5160_RAMP_STAT);
    drv_status = Tmc5160_ReadReg(chip,
                                 TMC5160_DRVSTATUS);
    gstat = Tmc5160_ReadReg(chip,
                            TMC5160_GSTAT);
    enc_stat = Tmc5160_ReadReg(chip,
                               TMC5160_ENC_STATUS);

    /* SPI通讯异常检测: 任一寄存器返回全F说明SPI通讯失败 */
    if (0xFFFFFFFF == ramp_stat ||
        0xFFFFFFFF == drv_status ||
        0xFFFFFFFF == gstat)
    {
        flags |= 0x10; // bit4 = SPI通讯异常
        return flags;  // 寄存器数据无效，不解析其他位
    }

    /* bit0: 到位 - RAMP_STAT.bit9 = position_reached */
    if (ramp_stat & (1 << 9))
    {
        flags |= 0x01;
    }
    /* bit1: 失步 - ENC_STATUS.bit1 = deviation_warn (编码器偏差) */
    if (enc_stat & (1 << 1))
    {
        flags |= 0x02;
        Tmc5160_WriteReg(chip, TMC5160_ENC_STATUS, (1 << 1));
    }
    /* bit2: 过温 - DRV_STATUS.bit26=otpw + bit25=ot */
    if (drv_status & (3 << 25))
    {
        flags |= 0x04;
    }
    /* bit3: 驱动错误 - GSTAT.bit1 = drv_err */
    if (gstat & 0x02)
    {
        flags |= 0x08;
        Tmc5160_WriteReg(chip, TMC5160_GSTAT, (1 << 1));
    }

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

    if (ramp_stat & (1 << 5))
    {
        phase |= 0x01;
    }
    if (ramp_stat & (1 << 6))
    {
        phase |= 0x02;
    }
    if (ramp_stat & (1 << 7))
    {
        phase |= 0x04;
    }
    if (ramp_stat & (1 << 10))
    {
        phase |= 0x08;
    }
    if (ramp_stat & (1 << 0))
    {
        phase |= 0x10;
    }

    return phase;
}

/* tmc5160 usr end */
//----------------------------------------------------------------------------------
/* tmc5160 enc start */

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: void
 * @ 说明: 配置编码器接口
 *        ENCMODE=0x00000000: 基本编码器读取(和测试代码一致)
 *        ENC_CONST=0x000CCCCD: 4000PPR编码器常数
 *        ENC_DEVIATION=256: 偏差报警阈值(0.5°)
 ********/
void Tmc5160_ConfigEncoder(TMC5160_T *chip)
{
    /* ENCMODE: 基本编码器读取 */
    Tmc5160_WriteReg(chip, TMC5160_ENCMODE, 0x00000000);
    /* ENC_CONST: 4000PPR, 1.8°电机, 256微步
     * (51200/4000) × 65536 ≈ 838861 = 0x000CCCCD */
    // 设置一圈的编码器值（硬件规定）
    Tmc5160_WriteReg(chip, TMC5160_ENC_CONST, 0x000CCCCD);
    /* ENC_DEVIATION: 偏差阈值 */
    Tmc5160_WriteReg(chip, TMC5160_ENC_DEVIATION,
                     TMC5160_ENC_TOLERANCE);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: int:编码器当前位置(X_ENC)
 * @ 说明: 读取编码器位置寄存器X_ENC(0x39)
 ********/
int Tmc5160_GetEncoderPosition(TMC5160_T *chip)
{
    return (int)Tmc5160_ReadReg(chip, TMC5160_X_ENC);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: unsigned int:ENC_STATUS寄存器值
 * @ 说明: 读取编码器状态寄存器ENC_STATUS(0x3B)
 *        bit0=n_event, bit1=deviation_warn
 ********/
unsigned int Tmc5160_GetEncoderStatus(TMC5160_T *chip)
{
    return Tmc5160_ReadReg(chip, TMC5160_ENC_STATUS);
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 * @ 输出: int:编码器偏差值(绝对值)
 * @ 说明: 计算编码器位置与期望运动量的偏差
 ********/
int Tmc5160_GetEncoderDeviation(TMC5160_T *chip)
{
    int enc_pos = Tmc5160_GetEncoderPosition(chip);
    int x_actual = Tmc5160_GetPosition(chip);

    /* 返回编码器与芯片内部位置的差值(绝对值) */
    int diff = enc_pos - x_actual;
    if (diff < 0)
        diff = -diff;
    return diff;
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        expected_steps:期望运动步数
 * @ 输出: 0=在容差内, 1=超出容差
 * @ 说明: 验证编码器实际运动量是否符合预期
 ********/
unsigned char Tmc5160_CheckPosition(TMC5160_T *chip,
                                    int expected_steps)
{
    int enc_before, enc_after;
    int actual_delta, error;

    enc_before = Tmc5160_GetEncoderPosition(chip);
    /* 等待编码器稳定 */
    HAL_Delay(10);
    enc_after = Tmc5160_GetEncoderPosition(chip);

    actual_delta = enc_after - enc_before;
    error = actual_delta - expected_steps;
    if (error < 0)
        error = -error;

    if (error <= TMC5160_ENC_TOLERANCE)
    {
        return 0; /* 在容差内 */
    }
    return 1; /* 超出容差 */
}

/* tmc5160 enc end */
//----------------------------------------------------------------------------------
/* tmc5160 verify start */

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        timeout_ms:超时时间(毫秒)
 * @ 输出: TMC5160_MoveResult_T:运动结果
 * @ 说明: 等待芯片完成定位,检测RAMP_STAT.bit9
 ********/
TMC5160_MoveResult_T Tmc5160_WaitPosition(
    TMC5160_T *chip, unsigned int timeout_ms)
{
    unsigned int elapsed = 0;
    unsigned int ramp_stat;

    while (elapsed < timeout_ms)
    {
        ramp_stat = Tmc5160_GetRampStat(chip);

        /* SPI通信异常检测 */
        if (0xFFFFFFFF == ramp_stat || 0 == ramp_stat)
        {
            return MOVE_SPI_ERROR;
        }

        /* 到位检测: RAMP_STAT bit9 = position_reached */
        if (ramp_stat & (1 << 9))
        {
            return MOVE_OK;
        }

        HAL_Delay(5);
        elapsed += 5;
    }

    return MOVE_TIMEOUT;
}

/****
 * @ 输入: chip:TMC5160_T结构体指针
 *        target:目标绝对位置
 * @ 输出: TMC5160_MoveResult_T:运动结果
 * @ 说明: 执行位置运动并验证编码器精度
 *        偏差超限时自动重试
 ********/
TMC5160_MoveResult_T Tmc5160_MoveToWithVerify(
    TMC5160_T *chip, int target)
{
    TMC5160_MoveResult_T result;
    int current_pos;
    int move_delta;
    int enc_before, enc_after;
    int deviation;
    unsigned char retry;

    current_pos = Tmc5160_GetPosition(chip);
    move_delta = target - current_pos;

    for (retry = 0; retry < TMC5160_MAX_RETRY; retry++)
    {
        /* 清除残留错误 */
        Tmc5160_WriteReg(chip, TMC5160_GSTAT, 0x07);

        /* 记录编码器起始位置 */
        enc_before = Tmc5160_GetEncoderPosition(chip);

        /* 执行运动 */
        Tmc5160_MoveTo(chip, target);

        /* 等待到位 */
        result = Tmc5160_WaitPosition(
            chip, TMC5160_MOVE_TIMEOUT_MS);
        if (MOVE_OK != result)
        {
            return result;
        }

        /* 稳定后读取编码器 */
        HAL_Delay(10);
        enc_after = Tmc5160_GetEncoderPosition(chip);

        /* 验证偏差 */
        deviation = (enc_after - enc_before) - move_delta;
        if (deviation < 0)
            deviation = -deviation;

        if (deviation <= TMC5160_ENC_TOLERANCE)
        {
            return MOVE_OK; /* 精度合格 */
        }

        /* 偏差超限,以编码器为基准修正目标 */
        current_pos = Tmc5160_GetEncoderPosition(chip);
        target = current_pos + move_delta;

        HAL_Delay(50);
    }

    return MOVE_DEVIATION; /* 重试耗尽 */
}

/* tmc5160 verify end */
