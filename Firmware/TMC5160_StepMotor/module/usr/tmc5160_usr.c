/*****************************************************************************
 * @文件: tmc5160_usr.c
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v2.0
 * @说明: TMC5160 业务逻辑层（运动控制/编码器/状态/配置持久化）
 * @依赖: drv/tmc5160_drv, drv/eeprom
 ****************************************************************************/
#include "usr/tmc5160_usr.h"
#include "drv/tmc5160_drv.h"
#include "drv/eeprom.h"

/* ==== TMC5160 寄存器地址（usr 层只读常量） ==== */
/* 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md: 寄存器映射 */
#define REG_GCONF          0x00
#define REG_GSTAT          0x01
#define REG_IHOLD_IRUN     0x10
#define REG_TPOWERDOWN     0x11
#define REG_TPWMTHRS       0x13
#define REG_SHORT_CONF     0x09
#define REG_TCOOLTHRS      0x14
#define REG_COOLCONF       0x6D
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
#define REG_DRV_CONF       0x0A
#define REG_DRVSTATUS      0x6F
#define REG_PWMCONF        0x70

/* ==== 内部工具 ==== */

/**
 * @输入 reg_value: 读取到的寄存器值
 * @输出 0=有效, 1=无效
 * @说明 0xFFFFFFFF 视为 SPI 读失败哨兵值
 */
static uint8_t TMC5160_RegValid(uint32_t reg_value)
{
    if (0xFFFFFFFF == reg_value)
    {
        return 1;
    }
    return 0;
}

/* ==== 全局实例 ==== */
TMC5160_CHIP_T g_tmc5160_chip1_st;
TMC5160_CHIP_T g_tmc5160_chip2_st;

/* 编码器零位偏移：上电时 X_ENC 的初始值，后续读数减去此值归零 */
static int32_t s_enc_offset[2];
static uint8_t s_chip_dirty;

/* ==== Flash 配置持久化 ==== */

/**
 * @输入 无
 * @输出 无
 * @说明 置脏标记，主循环检测并写入 Flash
 */
void USR_TMC5160_SetDirty(void)
{
    s_chip_dirty = 1;
}

/**
 * @输入 chip: 芯片指针; idx: 芯片在 Flash 中的偏移索引(0/1)
 * @输出 无
 * @说明 从 Flash 加载芯片配置（无效则用默认值）
 * @注意 不可在 ISR 中调用
 */
static void TMC5160_CfgLoad(TMC5160_CHIP_T *chip, uint8_t idx)
{
    TMC5160_CFG_T cfg;
    uint32_t offset = idx * sizeof(TMC5160_CFG_T);
    uint16_t expected;

    USR_EEPROM_Read(&g_eeprom_caliblock_st, offset, &cfg, sizeof(TMC5160_CFG_T));

    expected = (uint16_t)(cfg.magic + cfg.mode + cfg.closed_loop);

    if (TMC5160_CFG_MAGIC == cfg.magic && expected == cfg.checksum)
    {
        chip->mode = cfg.mode;
        chip->closed_loop = cfg.closed_loop;
    }
    else
    {
        chip->mode = TMC5160_MODE_POSITION;
        chip->closed_loop = 0;
    }
}

/**
 * @输入 无
 * @输出 无
 * @说明 将两芯片配置写入 Flash（有变化才擦写）
 * @注意 不可在 ISR 中调用
 */
static void TMC5160_CfgSave(void)
{
    TMC5160_CHIP_T *chips[2] = { &g_tmc5160_chip1_st, &g_tmc5160_chip2_st };
    TMC5160_CFG_T old, new_cfg;
    uint8_t changed = 0;
    uint8_t i;

    /* 比对是否有变化 */
    for (i = 0; i < 2; i++)
    {
        uint32_t offset = i * sizeof(TMC5160_CFG_T);
        USR_EEPROM_Read(&g_eeprom_caliblock_st, offset, &old, sizeof(TMC5160_CFG_T));

        if (old.mode != chips[i]->mode ||
            old.closed_loop != chips[i]->closed_loop)
        {
            changed = 1;
            break;
        }
    }

    if (!changed) return;

    /* 擦除后逐个写入 */
    USR_EEPROM_Erase(&g_eeprom_caliblock_st);

    for (i = 0; i < 2; i++)
    {
        uint32_t offset = i * sizeof(TMC5160_CFG_T);
        new_cfg.magic = TMC5160_CFG_MAGIC;
        new_cfg.mode = chips[i]->mode;
        new_cfg.closed_loop = chips[i]->closed_loop;
        new_cfg.checksum = (uint16_t)(new_cfg.magic + new_cfg.mode +
                                      new_cfg.closed_loop);

        USR_EEPROM_Write(offset, &g_eeprom_caliblock_st,
                         &new_cfg, sizeof(TMC5160_CFG_T));
    }
}

/**
 * @输入 无
 * @输出 无
 * @说明 检测脏标记，有变化则写入 Flash
 * @注意 不可在 ISR 中调用
 */
void USR_TMC5160_SaveConfig(void)
{
    if (!s_chip_dirty) return;
    s_chip_dirty = 0;
    TMC5160_CfgSave();
}

/* ==== 初始化 ==== */

/**
 * @输入 无
 * @输出 无
 * @说明 初始化两片 TMC5160：模式引脚/使能/清错/基础寄存器/编码器/电流
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md: GCONF
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p048.md: CHOPCONF
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p038.md: IHOLD_IRUN/TPOWERDOWN
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p045.md: ENCMODE/ENC_CONST
 */
void USR_TMC5160_Init(void)
{
    uint8_t i;
    uint32_t gstat;
    TMC5160_CHIP_T *chips[2] = { &g_tmc5160_chip1_st, &g_tmc5160_chip2_st };

    /* 等待 TMC5160 上电稳定后再操作 SPI */
    DRV_TMC5160_DelayMs(50);

    for (i = 0; i < 2; i++)
    {
        TMC5160_CHIP_T *chip = chips[i];
        chip->chip_number = i + 1;

        /* 从 Flash 加载配置（首次上电用默认值） */
        TMC5160_CfgLoad(chip, i);

        /* 设置模式引脚 */
        DRV_TMC5160_SetMode(chip->chip_number, chip->mode);

        /* 保持 DRV_ENN 高电平(禁用), 上电默认寄存器尚未配置, 此时使能会瞬时过流
         * 依据 .cl/datasheet/TMC5160A_Datasheet_Rev1.14_ch06_p006.. 使能时序:
         *   上电→保持使能脚上拉(禁用)→写入电机配置→延时→拉低使能→延时 */

        /* 清除 Power-on 残留错误，同时验证 SPI 通信 */
        USR_TMC5160_WriteReg(chip, REG_GSTAT, 0x07);
        DRV_TMC5160_DelayMs(1);
        gstat = USR_TMC5160_ReadReg(chip, REG_GSTAT);
        if (0xFFFFFFFF == gstat)
        {
            /* SPI 通信异常，重试一次 */
            DRV_TMC5160_DelayMs(10);
            USR_TMC5160_WriteReg(chip, REG_GSTAT, 0x07);
            DRV_TMC5160_DelayMs(1);
            gstat = USR_TMC5160_ReadReg(chip, REG_GSTAT);
        }

        /* 斩波模式: 全程 SpreadCycle（非静音）
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p032.md: GCONF.en_pwm_mode
         * GCONF=0x00: en_pwm_mode=0 → SpreadCycle 全程启用（高速段扭矩足，可到 50rev/s）
         * 背景: 原 StealthChop(GCONF=0x04) 高速扭矩不足/丢步。08-05 全程 SpreadCycle 试验已证
         *       解决高速丢步（仅噪声大）。用户 2026-08-18 明确允许非静音模式。 */
        USR_TMC5160_WriteReg(chip, REG_GCONF, 0x00);

        /* CHOPCONF: TOFF=5, TBL=%11(54clk 最长死区), HSTRT/HEND=StealthChop忽略, MRES=%0000(256微步)
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p051/p052.md: CHOPCONF
         * 说明: StealthChop 模式下 TOFF 仅用于使能电机驱动(ch07), MRES=0=256微步配合内部运动控制器。
         *       TBL 2026-08-14 由 %10(36clk) 加长至 %11(54clk): 实测 U1 双机运行时在 4A 全电流加速段
         *       方向相关 S2GA 对地短路误触发(T=51200 移动途中 XACTUAL≈977 处, 高温后复现), 加长
         *       比较器死区以抑制切换瞬态误触发。其余斩波参数由 PWMCONF 决定。 */
        USR_TMC5160_WriteReg(chip, REG_CHOPCONF, 0x000181C5);

        /* DRV_CONF: DRVSTRENGTH=00(weak), 降低栅极驱动电流以减缓 MOS 开关斜率
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch03.p017.md: 表3.3 MOSFET Miller Charge VS DRVSTRENGTH
         * 推导: 外接 MOS AOD4126 Qgd=10nC(typ) ∈ 10~20nC → DRVSTRENGTH=0 或 1, 取最小 0(weak)。
         *       复位缺省 %10(medium) 栅极驱动过强 → 开关振铃/额外发热(温升报警根因之一)。
         *       依据 .cl/memory/hardware_corrections.md 2026-08-10 推导。
         * 只写寄存器无法读回, 其余字段按复位缺省: BBMTIME=0, BBMCLKS=4, OTSELECT=0, FILT_ISENSE=0 */
        USR_TMC5160_WriteReg(chip, REG_DRV_CONF, 0x00000400);

        /* SHORT_CONF: 短路检测灵敏度调至最低(S2VS_LEVEL=15, S2G_LEVEL=15),
         * 滤波最强(SHORTFILTER=3µs), 延迟最长(shortdelay=1500ns)
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p035.md: SHORT_CONF
         * 目的: 大步偶发 S2GA/S2GB 短路误检测(驱动保护关断放开电机)，OTP 默认灵敏度(6/12)
         *       在 4A 大步 + StealthChop 高 dv/dt 下误触发，降至最低灵敏度消除误检测。
         * 值: 0x7030F = shortdelay(bit18)=1 | SHORTFILTER(bit17:16)=3 | S2G_LEVEL(bit11:8)=15 | S2VS_LEVEL(bit3:0)=15 */
        USR_TMC5160_WriteReg(chip, REG_SHORT_CONF, 0x0007030F);

        /* PWMCONF: StealthChop 斩波频率 = %01 → fPWM=2/683×14MHz=41.0kHz
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch07.p060.md: 表7.1 表7.1 PWM 频率选择
         * 推导: fCLK=14MHz(TIM4_CH1), 复位 %00=2/1024×14MHz=27.3kHz 偏低(铁损发热/近可听频段)。
         *       %01=41.0kHz 落 36~48kHz 推荐区间。其余位保持复位默认 0xC40C001E:
         *       pwm_autoscale=1/pwm_autograd=1 自动调校, PWM_OFS=30, PWM_GRAD=12, PWM_LIM=12。
         *       依据 .cl/memory/hardware_corrections.md 2026-08-10 推导。 */
        USR_TMC5160_WriteReg(chip, REG_PWMCONF, 0xC40D001E);

        /* 编码器配置 */
        USR_TMC5160_ConfigEncoder(chip);

        /* 电机电流: IHOLD=8, IRUN=20, IHOLDDELAY=6
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch09.p074.md: 公式 IRMS=(CS+1)/32×VFS/RSENSE/√2
         * 推导: RSENSE=0.05Ω, VFS(VSRT)=0.325V → IRUN=20 → (20+1)/32×0.325/0.05/√2 ≈ 3.02A RMS
         *       IHOLD=8 → (8+1)/32×0.325/0.05/√2 ≈ 1.20A RMS(保持力矩 1.3N.m 充足, 静止降热)
         * 2026-08-14: IRUN 27(4A)→20(3A). 实测双机持续满电流运行至 OTPW(120°C) 后 S2 短路比较器
         *   热漂移误触发(S2GA/S2GB), TBL 加长仅推迟触发(~5.6min)未根除. 降流热功率降~44%, 待验证
         *   3A 下 VMAX=50000 加速段是否仍无丢步(见 .cl/memory/hardware_corrections.md)。
         * 静止约 873ms(TPOWERDOWN=40) 后自动降至 IHOLD */
        USR_TMC5160_WriteReg(chip, REG_IHOLD_IRUN, (8 << 16) | (20 << 8) | 6);

        /* 静止降流延迟: 2^18 tCLK 单位, 40 → 约 873ms
         * 需 >=2 保证 StealthChop PWM 自动调校正常 */
        USR_TMC5160_WriteReg(chip, REG_TPOWERDOWN, 40);

        /* CoolStep 关闭: 保持全速段 StealthChop 静音 */
        USR_TMC5160_WriteReg(chip, REG_COOLCONF, 0x0000);

        /* CoolStep 速度窗口: 0 = 关闭 */
        USR_TMC5160_WriteReg(chip, REG_TCOOLTHRS, 0);

        /* TPWMTHRS: 试验发现高速切 SpreadCycle 在当前斩波参数下反复切换导致抖动,
         * 回退 0 并改用全程 SpreadCycle(见 GCONF/CHOPCONF) */

        /* 温升排查历史：曾删除 U2 特判的 IHOLD=0+freewheel 块，恢复两片统一配置。
         * 现电流值按 2026-08-10 推导（IHOLD=8/IRUN=27，匹配电机额定 4A）见上。
         * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p038.md: IHOLD_IRUN/TPOWERDOWN */

        /* 使能时序: 配置写完后延时稳定, 再拉低 DRV_ENN 使能, 随后延时等待校准
         * 避免上电瞬时过流(当前/斩波参数已就绪时才导通功率级) */
        DRV_TMC5160_DelayMs(10);
        DRV_TMC5160_Enable(chip->chip_number);
        DRV_TMC5160_DelayMs(10);
    }

    /* 等待 StealthChop PWM 校准稳定 */
    DRV_TMC5160_DelayMs(100);

    /* 记录编码器上电初始值，后续读数减去此偏移归零 */
    s_enc_offset[0] = (int32_t)USR_TMC5160_ReadReg(&g_tmc5160_chip1_st, REG_X_ENC);
    s_enc_offset[1] = (int32_t)USR_TMC5160_ReadReg(&g_tmc5160_chip2_st, REG_X_ENC);
}

/* ==== 寄存器读写 ==== */

/**
 * @输入 chip: 芯片指针; reg_addr: 寄存器地址; data: 数据
 * @输出 TMC5160_SUCCESS / TMC5160_FAIL
 * @说明 写寄存器（转发 drv 层）
 */
uint8_t USR_TMC5160_WriteReg(TMC5160_CHIP_T *chip, uint8_t reg_addr, uint32_t data)
{
    return DRV_TMC5160_WriteReg(chip->chip_number, reg_addr, data);
}

/**
 * @输入 chip: 芯片指针; reg_addr: 寄存器地址
 * @输出 寄存器值，失败 0xFFFFFFFF
 * @说明 读寄存器（转发 drv 层）
 */
uint32_t USR_TMC5160_ReadReg(TMC5160_CHIP_T *chip, uint8_t reg_addr)
{
    return DRV_TMC5160_ReadReg(chip->chip_number, reg_addr);
}

/* ==== 运动参数组 ==== */

static const TMC5160_PROFILE_T s_profiles[TMC5160_PROFILE_COUNT] = {
    {0, 10, 0, 0, 1000, 5000, 1000, 1000, 10},
    {0, 10, 0, 0, 5000, 20000, 5000, 5000, 10},
    {0, 10, 0, 0, 10000, 50000, 10000, 10000, 10},
    {0, 10, 0, 0, 20000, 100000, 20000, 20000, 10},
    /* 组5 超高速: VMAX=3067834=50rev/s, AMAX/DMAX=40000(加速3.57M µsteps/s², 0.72s达2.56M)
     * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p040.md:
     *   VMAX[µsteps/t] t=2^24/fCLK → 50×51200×2^24/14e6=3067834(上限2^23-512=8388608 OK)
     *   AMAX[µsteps/ta²] ta²=2^41/fCLK² → 40000→3.57M µsteps/s² */
    {0, 10, 0, 0, 40000, 3067834, 40000, 40000, 10},
};

/**
 * @输入 chip: 芯片指针; profile_id: 运动参数组 ID(1~4)
 * @输出 无
 * @说明 按预配置运动参数组设置斜坡寄存器
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p040.md: VSTART/A1/V1/AMAX/VMAX/DMAX/D1
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p041.md: VSTOP/TZEROWAIT
 */
void USR_TMC5160_ApplyProfile(TMC5160_CHIP_T *chip, uint8_t profile_id)
{
    const TMC5160_PROFILE_T *p;

    if (0 == profile_id || TMC5160_PROFILE_COUNT < profile_id)
    {
        profile_id = 1;
    }
    p = &s_profiles[profile_id - 1];

    USR_TMC5160_WriteReg(chip, REG_VSTART, p->vstart);
    USR_TMC5160_WriteReg(chip, REG_VSTOP, p->vstop);
    USR_TMC5160_WriteReg(chip, REG_V1, p->v1);
    USR_TMC5160_WriteReg(chip, REG_A1, p->a1);
    USR_TMC5160_WriteReg(chip, REG_AMAX, p->amax);
    USR_TMC5160_WriteReg(chip, REG_VMAX, p->vmax);
    USR_TMC5160_WriteReg(chip, REG_DMAX, p->dmax);
    USR_TMC5160_WriteReg(chip, REG_D1, p->d1);
    USR_TMC5160_WriteReg(chip, REG_TZEROWAIT, p->tzerowait);
}

/* ==== 运动控制 ==== */

/**
 * @输入 chip: 芯片指针; target: 目标绝对位置
 * @输出 无
 * @说明 绝对定位，RAMPMODE=0 位置模式
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p040.md: RAMPMODE
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p041.md: XTARGET
 */
void USR_TMC5160_MoveTo(TMC5160_CHIP_T *chip, int32_t target)
{
    USR_TMC5160_WriteReg(chip, REG_RAMPMODE, 0);
    USR_TMC5160_WriteReg(chip, REG_XTARGET, (uint32_t)target);
}

/**
 * @输入 chip: 芯片指针; offset: 相对偏移量(+正转, -反转)
 * @输出 无
 * @说明 从当前位置运动指定偏移量
 */
void USR_TMC5160_MoveBy(TMC5160_CHIP_T *chip, int32_t offset)
{
    int32_t current = USR_TMC5160_GetPosition(chip);

    USR_TMC5160_MoveTo(chip, current + offset);
}

/**
 * @输入 chip: 芯片指针; velocity: 目标速度(+正转, -反转)
 * @输出 无
 * @说明 速度模式持续旋转
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p040.md: RAMPMODE 速度模式
 */
void USR_TMC5160_SetVelocity(TMC5160_CHIP_T *chip, int32_t velocity)
{
    if (0 <= velocity)
    {
        USR_TMC5160_WriteReg(chip, REG_RAMPMODE, 1);
        USR_TMC5160_WriteReg(chip, REG_VMAX, (uint32_t)velocity);
    }
    else
    {
        USR_TMC5160_WriteReg(chip, REG_RAMPMODE, 2);
        USR_TMC5160_WriteReg(chip, REG_VMAX, (uint32_t)(-velocity));
    }
}

/**
 * @输入 chip: 芯片指针
 * @输出 无
 * @说明 立即停止，切回定位模式保持锁轴
 */
void USR_TMC5160_Stop(TMC5160_CHIP_T *chip)
{
    USR_TMC5160_WriteReg(chip, REG_VMAX, 0);
    USR_TMC5160_WriteReg(chip, REG_RAMPMODE, 0);
}

/* ==== 位置读取 ==== */

/**
 * @输入 chip: 芯片指针
 * @输出 int32_t: 当前位置(XACTUAL)
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p040.md: XACTUAL
 */
int32_t USR_TMC5160_GetPosition(TMC5160_CHIP_T *chip)
{
    return (int32_t)USR_TMC5160_ReadReg(chip, REG_XACTUAL);
}

/**
 * @输入 chip: 芯片指针
 * @输出 uint32_t: RAMP_STAT 寄存器值
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p042.md: RAMP_STAT
 */
uint32_t USR_TMC5160_GetRampStat(TMC5160_CHIP_T *chip)
{
    return USR_TMC5160_ReadReg(chip, REG_RAMP_STAT);
}

/**
 * @输入 chip: 芯片指针
 * @输出 uint32_t: DRV_STATUS 寄存器值
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p033.md: DRV_STATUS
 */
uint32_t USR_TMC5160_GetDrvStatus(TMC5160_CHIP_T *chip)
{
    return USR_TMC5160_ReadReg(chip, REG_DRVSTATUS);
}

/**
 * @输入 chip: 芯片指针
 * @输出 uint32_t: GSTAT 寄存器值（reset/drv_err/uv_cp）
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p033.md: GSTAT
 */
uint32_t USR_TMC5160_GetGStat(TMC5160_CHIP_T *chip)
{
    return USR_TMC5160_ReadReg(chip, REG_GSTAT);
}

/* ==== 状态标志 ==== */

/**
 * @输入 chip: 芯片指针
 * @输出 uint8_t 状态标志位
 *   bit0=到位, bit1=失步, bit2=过温, bit3=驱动错误, bit4=SPI通讯异常
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p042.md: RAMP_STAT
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p045.md: ENC_STATUS
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p033.md: GSTAT/DRV_STATUS
 */
uint8_t USR_TMC5160_GetStatusFlags(TMC5160_CHIP_T *chip)
{
    uint32_t ramp_stat, drv_status, gstat, enc_stat;
    uint8_t flags = 0;

    ramp_stat = USR_TMC5160_ReadReg(chip, REG_RAMP_STAT);
    drv_status = USR_TMC5160_ReadReg(chip, REG_DRVSTATUS);
    gstat = USR_TMC5160_ReadReg(chip, REG_GSTAT);
    enc_stat = USR_TMC5160_ReadReg(chip, REG_ENC_STATUS);

    /* SPI 通讯异常检测 */
    if (TMC5160_RegValid(ramp_stat) ||
        TMC5160_RegValid(drv_status) ||
        TMC5160_RegValid(gstat))
    {
        flags |= 0x10;
        return flags;
    }

    /* bit0: 到位 - RAMP_STAT.bit9 */
    if (ramp_stat & (1UL << 9))
    {
        flags |= 0x01;
        USR_TMC5160_WriteReg(chip, REG_RAMP_STAT, (1UL << 9));
    }
    /* bit1: 失步 - ENC_STATUS.bit1 (deviation_warn) */
    if (enc_stat & (1UL << 1))
    {
        flags |= 0x02;
        USR_TMC5160_WriteReg(chip, REG_ENC_STATUS, (1UL << 1));
    }
    /* bit2: 过温 - DRV_STATUS.bit26/25 */
    if (drv_status & (3UL << 25))
    {
        flags |= 0x04;
    }
    /* bit3: 驱动错误 - GSTAT.bit1 (drv_err) */
    if (gstat & 0x02)
    {
        flags |= 0x08;
        USR_TMC5160_WriteReg(chip, REG_GSTAT, 0x02);
    }

    return flags;
}

/**
 * @输入 chip: 芯片指针
 * @输出 uint8_t: 运动阶段标志
 *   bit0=加速, bit1=匀速, bit2=减速, bit3=归零等待, bit4=静止锁轴
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p042.md: RAMP_STAT
 */
uint8_t USR_TMC5160_GetMotionPhase(TMC5160_CHIP_T *chip)
{
    uint32_t ramp_stat;
    uint8_t phase = 0;

    ramp_stat = USR_TMC5160_ReadReg(chip, REG_RAMP_STAT);

    if (ramp_stat & (1UL << 5))
    {
        phase |= 0x01;    /* 加速 */
    }
    if (ramp_stat & (1UL << 6))
    {
        phase |= 0x02;    /* 匀速 */
    }
    if (ramp_stat & (1UL << 7))
    {
        phase |= 0x04;    /* 减速 */
    }
    if (ramp_stat & (1UL << 10))
    {
        phase |= 0x08;    /* 归零等待 */
    }
    if (ramp_stat & (1UL << 0))
    {
        phase |= 0x10;    /* 静止锁轴 */
    }

    return phase;
}

/* ==== 编码器 ==== */

/**
 * @输入 chip: 芯片指针
 * @输出 无
 * @说明 配置编码器接口
 * 依据 .cl/datasheet/pages/TMC5160A_Datasheet_Rev1.14.ch06.p045.md: ENCMODE/ENC_CONST/ENC_DEVIATION
 */
void USR_TMC5160_ConfigEncoder(TMC5160_CHIP_T *chip)
{
    USR_TMC5160_WriteReg(chip, REG_ENCMODE, 0x00);
    USR_TMC5160_WriteReg(chip, REG_ENC_CONST, 0xFFF33333);
    USR_TMC5160_WriteReg(chip, REG_ENC_DEVIATION, TMC5160_ENC_TOLERANCE);
}

/**
 * @输入 chip: 芯片指针
 * @输出 int32_t: 编码器当前位姿(X_ENC 归零后)
 */
int32_t USR_TMC5160_GetEncoderPosition(TMC5160_CHIP_T *chip)
{
    int32_t raw = (int32_t)USR_TMC5160_ReadReg(chip, REG_X_ENC);
    int32_t idx = (TMC5160_CHIP_1 == chip->chip_number) ? 0 : 1;
    return raw - s_enc_offset[idx];
}

/**
 * @输入 chip: 芯片指针
 * @输出 uint32_t: ENC_STATUS 寄存器值
 */
uint32_t USR_TMC5160_GetEncoderStatus(TMC5160_CHIP_T *chip)
{
    return USR_TMC5160_ReadReg(chip, REG_ENC_STATUS);
}

/**
 * @输入 chip: 芯片指针
 * @输出 int32_t: 编码器偏差绝对值 (X_ENC - XACTUAL)
 */
int32_t USR_TMC5160_GetEncoderDeviation(TMC5160_CHIP_T *chip)
{
    int32_t enc_pos = USR_TMC5160_GetEncoderPosition(chip);
    int32_t x_actual = USR_TMC5160_GetPosition(chip);
    int32_t diff = enc_pos - x_actual;

    if (diff < 0)
    {
        diff = -diff;
    }
    return diff;
}

/**
 * @输入 chip: 芯片指针; expected_steps: 期望运动步数
 * @输出 0=在容差内, 1=超出容差
 * @说明 验证编码器实际运动量是否符合预期
 */
uint8_t USR_TMC5160_CheckPosition(TMC5160_CHIP_T *chip, int32_t expected_steps)
{
    int32_t enc_before, enc_after;
    int32_t actual_delta, error;

    enc_before = USR_TMC5160_GetEncoderPosition(chip);
    DRV_TMC5160_DelayMs(10);
    enc_after = USR_TMC5160_GetEncoderPosition(chip);

    actual_delta = enc_after - enc_before;
    error = actual_delta - expected_steps;
    if (error < 0)
    {
        error = -error;
    }

    return (error <= TMC5160_ENC_TOLERANCE) ? 0 : 1;
}

/* ==== 带验证的运动 ==== */

/**
 * @输入 chip: 芯片指针; timeout_ms: 超时(ms)
 * @输出 TMC5160_MOVE_RESULT_T
 * @说明 等待芯片完成定位，检查 RAMP_STAT.bit9(position_reached)
 */
TMC5160_MOVE_RESULT_T USR_TMC5160_WaitPosition(TMC5160_CHIP_T *chip, uint32_t timeout_ms)
{
    uint32_t elapsed = 0;
    uint32_t ramp_stat;

    while (elapsed < timeout_ms)
    {
        ramp_stat = USR_TMC5160_GetRampStat(chip);

        if (0xFFFFFFFF == ramp_stat || 0 == ramp_stat)
        {
            return TMC5160_MOVE_SPI_ERROR;
        }

        if (ramp_stat & (1UL << 9))
        {
            return TMC5160_MOVE_OK;
        }

        DRV_TMC5160_DelayMs(5);
        elapsed += 5;
    }

    return TMC5160_MOVE_TIMEOUT;
}

/**
 * @输入 chip: 芯片指针; target: 目标绝对位置
 * @输出 TMC5160_MOVE_RESULT_T
 * @说明 执行位置运动并验证编码器精度，偏差超限自动重试
 */
TMC5160_MOVE_RESULT_T USR_TMC5160_MoveToWithVerify(TMC5160_CHIP_T *chip, int32_t target)
{
    TMC5160_MOVE_RESULT_T result;
    int32_t current_pos, move_delta;
    int32_t enc_before, enc_after;
    int32_t deviation;
    uint8_t retry;

    current_pos = USR_TMC5160_GetPosition(chip);
    move_delta = target - current_pos;

    for (retry = 0; retry < TMC5160_MAX_RETRY; retry++)
    {
        /* 清除残留错误 */
        USR_TMC5160_WriteReg(chip, REG_GSTAT, 0x07);

        enc_before = USR_TMC5160_GetEncoderPosition(chip);

        USR_TMC5160_MoveTo(chip, target);

        result = USR_TMC5160_WaitPosition(chip, TMC5160_MOVE_TIMEOUT_MS);
        if (TMC5160_MOVE_OK != result)
        {
            return result;
        }

        enc_after = USR_TMC5160_GetEncoderPosition(chip);

        deviation = (enc_after - enc_before) - move_delta;
        if (deviation < 0)
        {
            deviation = -deviation;
        }

        if (deviation <= TMC5160_ENC_TOLERANCE)
        {
            return TMC5160_MOVE_OK;
        }

        /* 偏差超限，以编码器为基准修正 */
        current_pos = USR_TMC5160_GetEncoderPosition(chip);
        target = current_pos + move_delta;
    }

    return TMC5160_MOVE_DEVIATION;
}
