/****
 * @ 文件: ela_tmc5160_usr.c
 * @ 作者: ELACO
 * @ 日期: 2026-07-22
 * @ 版本: 1.0.0
 * @ 说明: TMC5160 业务逻辑层，运动控制/编码器/状态
 ********/
#include "ela_tmc5160_usr.h"
#include "ela_tmc5160_drv.h"

//----------------------------------------------------------------------------------
/* tmc5160 寄存器地址 (usr 层只读常量) */

#define REG_GCONF          0x00
#define REG_GSTAT          0x01
#define REG_IHOLD_IRUN     0x10
#define REG_TPOWERDOWN     0x11
#define REG_RAMPMODE       0x20
#define REG_XACTUAL        0x21
#define REG_VSTART         0x23
#define REG_A1             0x24
#define REG_V1             0x25
#define REG_AMAX           0x26
#define REG_VMAX           0x27
#define REG_DMAX           0x28
#define REG_D1             0x2A
#define REG_VSTOP          0x2B
#define REG_TZEROWAIT      0x2C
#define REG_XTARGET        0x2D
#define REG_RAMP_STAT      0x35
#define REG_ENCMODE        0x38
#define REG_X_ENC          0x39
#define REG_ENC_CONST      0x3A
#define REG_ENC_STATUS     0x3B
#define REG_ENC_DEVIATION  0x3D
#define REG_CHOPCONF       0x6C
#define REG_DRVSTATUS      0x6F

//----------------------------------------------------------------------------------
/* tmc5160 hlp start */

/****
 * @ 输入: reg_value: 读取到的寄存器值 (0xFFFFFFFF=失败)
 * @ 输出: 0=有效, 1=无效
 * @ 说明: 校验 SPI 读取结果是否有效
 ********/
static uint8_t tmc5160_is_reg_valid(uint32_t reg_value)
{
    return (0xFFFFFFFF != reg_value) ? 0 : 1;
}

/* tmc5160 hlp end */
//----------------------------------------------------------------------------------
/* tmc5160 usr start */

TMC5160_CHIP_T g_tmc5160_chip1_st;
TMC5160_CHIP_T g_tmc5160_chip2_st;

/****
 * @ 输入: 无
 * @ 输出: 无
 * @ 说明: 初始化两片 TMC5160 芯片
 *   1. 设置芯片号和模式
 *   2. 配置引脚 (SD/SPI)
 *   3. 使能驱动
 *   4. 清除错误标志
 *   5. 基础寄存器配置
 *   6. 编码器配置
 *   7. 电机电流配置
 ********/
void ela_tmc5160_init(void)
{
    uint8_t i;
    TMC5160_CHIP_T *chips[2] = {
        &g_tmc5160_chip1_st,
        &g_tmc5160_chip2_st
    };

    for (i = 0; i < 2; i++)
    {
        TMC5160_CHIP_T *chip = chips[i];
        chip->chip_number = i + 1;
        chip->mode = TMC5160_MODE_POSITION;
        chip->move_pending = 0;

        /* 设置模式引脚 */
        tmc5160_drv_set_mode(chip->chip_number,
                             chip->mode);

        /* 使能电机驱动 */
        tmc5160_drv_enable(chip->chip_number);

        /* 清除 Power-on 残留错误 */
        ela_tmc5160_write_reg(chip, REG_GSTAT, 0x07);

        /* 静音模式 (StealthChop) */
        ela_tmc5160_write_reg(chip, REG_GCONF, 0x04);

        /* CHOPCONF: TOFF=5, TBL=01, HSTRT=4,
         * HEND=0, MRES=0(256微步) */
        ela_tmc5160_write_reg(chip, REG_CHOPCONF,
                              0x000101C5);

        /* 编码器配置 */
        ela_tmc5160_config_encoder(chip);

        /* 电机电流: IHOLD=4, IRUN=10, IHOLDDELAY=6
         * RS=0.05R → I_full ≈ 203mA
         * 保持电流 ≈ 26mA, 运行电流 ≈ 65mA */
        ela_tmc5160_write_reg(chip, REG_IHOLD_IRUN,
                              (4 << 16) | (10 << 8) | 6);
    }

    /* 等待 StealthChop PWM 校准稳定 */
    tmc5160_drv_delay_ms(100);
}

/* ---- 寄存器读写 ---- */

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        reg_addr: 寄存器地址
 *        data: 要写入的 32 位数据
 * @ 输出: TMC5160_SUCCESS / TMC5160_FAIL
 * @ 说明: 向 TMC5160 指定寄存器写入 32 位数据
 ********/
uint8_t ela_tmc5160_write_reg(TMC5160_CHIP_T *chip,
                               uint8_t reg_addr,
                               uint32_t data)
{
    return tmc5160_drv_write_reg(chip->chip_number,
                                 reg_addr, data);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        reg_addr: 寄存器地址
 * @ 输出: 32 位寄存器值，失败返回 0xFFFFFFFF
 * @ 说明: 从 TMC5160 指定寄存器读取 32 位数据
 ********/
uint32_t ela_tmc5160_read_reg(TMC5160_CHIP_T *chip,
                               uint8_t reg_addr)
{
    return tmc5160_drv_read_reg(chip->chip_number,
                                reg_addr);
}

/* ---- 运动参数组 ---- */

static const TMC5160_MOTION_PROFILE
    g_profiles[TMC5160_PROFILE_COUNT] = {
        {0, 10, 0, 0, 1000, 5000, 1000, 1000, 10},
        {0, 10, 0, 0, 5000, 20000, 5000, 5000, 10},
        {0, 10, 0, 0, 10000, 50000, 10000, 10000, 10},
        {0, 10, 0, 0, 20000, 100000, 20000, 20000, 10},
};

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        profile_id: 运动参数组 ID (1~4)
 * @ 输出: 无
 * @ 说明: 按预配置的运动参数组设置斜坡寄存器
 ********/
void ela_tmc5160_apply_profile(TMC5160_CHIP_T *chip,
                                uint8_t profile_id)
{
    const TMC5160_MOTION_PROFILE *p;

    if (0 == profile_id ||
        TMC5160_PROFILE_COUNT < profile_id)
    {
        profile_id = 1;
    }
    p = &g_profiles[profile_id - 1];

    ela_tmc5160_write_reg(chip, REG_VSTART, p->vstart);
    ela_tmc5160_write_reg(chip, REG_VSTOP, p->vstop);
    ela_tmc5160_write_reg(chip, REG_V1, p->v1);
    ela_tmc5160_write_reg(chip, REG_A1, p->a1);
    ela_tmc5160_write_reg(chip, REG_AMAX, p->amax);
    ela_tmc5160_write_reg(chip, REG_VMAX, p->vmax);
    ela_tmc5160_write_reg(chip, REG_DMAX, p->dmax);
    ela_tmc5160_write_reg(chip, REG_D1, p->d1);
    ela_tmc5160_write_reg(chip, REG_TZEROWAIT,
                          p->tzerowait);
}

/* ---- 运动控制 ---- */

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        target: 目标绝对位置
 * @ 输出: 无
 * @ 说明: 设置目标位置 (绝对定位), RAMPMODE=0
 ********/
void ela_tmc5160_move_to(TMC5160_CHIP_T *chip,
                          int32_t target)
{
	// 设置为位置模式
    ela_tmc5160_write_reg(chip, REG_RAMPMODE, 0);
	// 写入目标值
    ela_tmc5160_write_reg(chip, REG_XTARGET,
                          (uint32_t)target);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        offset: 相对偏移量 (正=正转, 负=反转)
 * @ 输出: 无
 * @ 说明: 从当前位置运动指定偏移量
 ********/
void ela_tmc5160_move_by(TMC5160_CHIP_T *chip,
                          int32_t offset)
{
    int32_t current = ela_tmc5160_get_position(chip);

    ela_tmc5160_move_to(chip, current + offset);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        velocity: 目标速度 (正=正转, 负=反转)
 * @ 输出: 无
 * @ 说明: 切换速度模式持续旋转
 ********/
void ela_tmc5160_set_velocity(TMC5160_CHIP_T *chip,
                               int32_t velocity)
{
    if (0 <= velocity)
    {
        ela_tmc5160_write_reg(chip, REG_RAMPMODE, 1);
        ela_tmc5160_write_reg(chip, REG_VMAX,
                              (uint32_t)velocity);
    }
    else
    {
        ela_tmc5160_write_reg(chip, REG_RAMPMODE, 2);
        ela_tmc5160_write_reg(chip, REG_VMAX,
                              (uint32_t)(-velocity));
    }
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: 无
 * @ 说明: 立即停止电机, 切回定位模式保持锁轴
 ********/
void ela_tmc5160_stop(TMC5160_CHIP_T *chip)
{
    ela_tmc5160_write_reg(chip, REG_VMAX, 0);
    ela_tmc5160_write_reg(chip, REG_RAMPMODE, 0);
}

/* ---- 位置读取 ---- */

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: int32_t: 当前位置值 (XACTUAL)
 * @ 说明: 读取当前位置寄存器
 ********/
int32_t ela_tmc5160_get_position(TMC5160_CHIP_T *chip)
{
    return (int32_t)ela_tmc5160_read_reg(
        chip, REG_XACTUAL);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: uint32_t: RAMP_STAT 寄存器值
 * @ 说明: 读取斜坡状态寄存器
 ********/
uint32_t ela_tmc5160_get_ramp_stat(TMC5160_CHIP_T *chip)
{
    return ela_tmc5160_read_reg(chip, REG_RAMP_STAT);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: uint32_t: DRV_STATUS 寄存器值
 * @ 说明: 读取驱动状态寄存器
 ********/
uint32_t ela_tmc5160_get_drv_status(TMC5160_CHIP_T *chip)
{
    return ela_tmc5160_read_reg(chip, REG_DRVSTATUS);
}

/* ---- 状态标志 ---- */

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: uint8_t: 状态标志位
 *   bit0=到位, bit1=失步, bit2=过温,
 *   bit3=驱动错误, bit4=SPI通讯异常
 * @ 说明: 读取电机状态并组装为标志位
 ********/
uint8_t ela_tmc5160_get_status_flags(TMC5160_CHIP_T *chip)
{
    uint32_t ramp_stat, drv_status, gstat, enc_stat;
    uint8_t flags = 0;

    ramp_stat = ela_tmc5160_read_reg(chip, REG_RAMP_STAT);
    drv_status = ela_tmc5160_read_reg(chip, REG_DRVSTATUS);
    gstat = ela_tmc5160_read_reg(chip, REG_GSTAT);
	enc_stat = ela_tmc5160_read_reg(chip, REG_ENC_STATUS); // 这个寄存器不是检测失步的

    /* SPI 通讯异常检测 */
    if (0xFFFFFFFF == ramp_stat ||
        0xFFFFFFFF == drv_status ||
        0xFFFFFFFF == gstat)
    {
        flags |= 0x10;
        return flags;
    }

    /* bit0: 到位 - RAMP_STAT.bit9 */
    if (ramp_stat & (1UL << 9))
    {
        flags |= 0x01;
        ela_tmc5160_write_reg(chip, REG_RAMP_STAT,
                              (1UL << 9));
    }
    /* bit1: 失步 - ENC_STATUS.bit1 */
    if (enc_stat & (1UL << 1))
    {
        flags |= 0x02;
        ela_tmc5160_write_reg(chip, REG_ENC_STATUS,
                              (1UL << 1));
    }
    /* bit2: 过温 - DRV_STATUS.bit26/25 */
    if (drv_status & (3UL << 25))
    {
        flags |= 0x04;
    }
    /* bit3: 驱动错误 - GSTAT.bit1 */
    if (gstat & 0x02)
    {
        flags |= 0x08;
        ela_tmc5160_write_reg(chip, REG_GSTAT, 0x02);
    }

    return flags;
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: uint8_t: 运动阶段标志位
 *   bit0=加速, bit1=匀速, bit2=减速,
 *   bit3=归零等待, bit4=静止锁轴
 * @ 说明: 读取 RAMP_STAT 判断当前运动阶段
 ********/
uint8_t ela_tmc5160_get_motion_phase(TMC5160_CHIP_T *chip)
{
    uint32_t ramp_stat;
    uint8_t phase = 0;

    ramp_stat = ela_tmc5160_read_reg(chip, REG_RAMP_STAT);

    if (ramp_stat & (1UL << 5))
    {
        phase |= 0x01;
    }
    if (ramp_stat & (1UL << 6))
    {
        phase |= 0x02;
    }
    if (ramp_stat & (1UL << 7))
    {
        phase |= 0x04;
    }
    if (ramp_stat & (1UL << 10))
    {
        phase |= 0x08;
    }
    if (ramp_stat & (1UL << 0))
    {
        phase |= 0x10;
    }

    return phase;
}

/* ---- 编码器 ---- */

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: 无
 * @ 说明: 配置编码器接口
 *   ENCMODE=0x00: 基本编码器读取
 *   ENC_CONST=0xFFF33333: 4000CPR, 取反补偿编码器方向
 *   ENC_DEVIATION=256: 偏差阈值
 ********/
void ela_tmc5160_config_encoder(TMC5160_CHIP_T *chip)
{
    ela_tmc5160_write_reg(chip, REG_ENCMODE, 0x00);
    ela_tmc5160_write_reg(chip, REG_ENC_CONST,	
                          0xFFF33333);
    ela_tmc5160_write_reg(chip, REG_ENC_DEVIATION,
                          TMC5160_ENC_TOLERANCE);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: int32_t: 编码器当前位置 (X_ENC)
 * @ 说明: 读取编码器位置寄存器
 ********/
int32_t ela_tmc5160_get_encoder_position(
    TMC5160_CHIP_T *chip)
{
    return (int32_t)ela_tmc5160_read_reg(
        chip, REG_X_ENC);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: uint32_t: ENC_STATUS 寄存器值
 * @ 说明: 读取编码器状态
 ********/
uint32_t ela_tmc5160_get_encoder_status(
    TMC5160_CHIP_T *chip)
{
    return ela_tmc5160_read_reg(chip, REG_ENC_STATUS);
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 * @ 输出: int32_t: 编码器偏差值 (绝对值)
 * @ 说明: 计算编码器位置与期望运动量的偏差
 ********/
int32_t ela_tmc5160_get_encoder_deviation(
    TMC5160_CHIP_T *chip)
{
    int32_t enc_pos = ela_tmc5160_get_encoder_position(
        chip);
    int32_t x_actual = ela_tmc5160_get_position(chip);
    int32_t diff = enc_pos - x_actual;

    if (diff < 0)
    {
        diff = -diff;
    }
    return diff;
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        expected_steps: 期望运动步数
 * @ 输出: 0=在容差内, 1=超出容差
 * @ 说明: 验证编码器实际运动量是否符合预期
 ********/
uint8_t ela_tmc5160_check_position(
    TMC5160_CHIP_T *chip, int32_t expected_steps)
{
    int32_t enc_before, enc_after;
    int32_t actual_delta, error;

    enc_before = ela_tmc5160_get_encoder_position(chip);
    tmc5160_drv_delay_ms(10);
    enc_after = ela_tmc5160_get_encoder_position(chip);

    actual_delta = enc_after - enc_before;
    error = actual_delta - expected_steps;
    if (error < 0)
    {
        error = -error;
    }

    return (error <= TMC5160_ENC_TOLERANCE) ? 0 : 1;
}

/* ---- 带验证的运动 ---- */

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        timeout_ms: 超时时间 (毫秒)
 * @ 输出: TMC5160_MOVE_RESULT
 * @ 说明: 等待芯片完成定位, 检测 RAMP_STAT.bit9
 ********/
TMC5160_MOVE_RESULT ela_tmc5160_wait_position(
    TMC5160_CHIP_T *chip, uint32_t timeout_ms)
{
    uint32_t elapsed = 0;
    uint32_t ramp_stat;

    while (elapsed < timeout_ms)
    {
        ramp_stat = ela_tmc5160_get_ramp_stat(chip);

        if (0xFFFFFFFF == ramp_stat || 0 == ramp_stat)
        {
            return MOVE_SPI_ERROR;
        }

        if (ramp_stat & (1UL << 9))
        {
            return MOVE_OK;
        }

        tmc5160_drv_delay_ms(5);
        elapsed += 5;
    }

    return MOVE_TIMEOUT;
}

/****
 * @ 输入: chip: TMC5160_CHIP_T 结构体指针
 *        target: 目标绝对位置
 * @ 输出: TMC5160_MOVE_RESULT
 * @ 说明: 执行位置运动并验证编码器精度,
 *   偏差超限时自动重试
 ********/
TMC5160_MOVE_RESULT ela_tmc5160_move_to_with_verify(
    TMC5160_CHIP_T *chip, int32_t target)
{
    TMC5160_MOVE_RESULT result;
    int32_t current_pos, move_delta;
    int32_t enc_before, enc_after;
    int32_t deviation;
    uint8_t retry;

    current_pos = ela_tmc5160_get_position(chip);
    move_delta = target - current_pos;

    for (retry = 0; retry < TMC5160_MAX_RETRY; retry++)
    {
        /* 清除残留错误 */
        ela_tmc5160_write_reg(chip, REG_GSTAT, 0x07);

        enc_before = ela_tmc5160_get_encoder_position(
            chip);

        ela_tmc5160_move_to(chip, target);

        result = ela_tmc5160_wait_position(
            chip, TMC5160_MOVE_TIMEOUT_MS);
        if (MOVE_OK != result)
        {
            return result;
        }

        enc_after = ela_tmc5160_get_encoder_position(
            chip);

        deviation = (enc_after - enc_before) - move_delta;
        if (deviation < 0)
        {
            deviation = -deviation;
        }

        if (deviation <= TMC5160_ENC_TOLERANCE)
        {
            return MOVE_OK;
        }

        /* 偏差超限, 以编码器为基准修正 */
        current_pos = ela_tmc5160_get_encoder_position(
            chip);
        target = current_pos + move_delta;
    }

    return MOVE_DEVIATION;
}

/* tmc5160 usr end */
