//
// Created by electronic on 2026/5/29.
// TMC5160 SPI控制模式使用示例 (SD=0, SPI=1, 模式1: Full Motion Controller)
// 说明: 逐步学习,每个示例只引入一个新概念
//
#include "tmc5160.h"

/* ==========================================================
 * 【前置知识】SPI控制模式(SD=0, SPI=1)
 *   此模式下,芯片内部斜坡发生器自动处理加减速,
 *   你只需要通过SPI写入目标位置即可.
 *   无需外部STEP脉冲,芯片自己计算每一步.
 *
 *   RAMPMODE决定运动方式:
 *     0 = 定位模式(走到指定位置停)
 *     1 = 速度正转(持续正向转)
 *     2 = 速度反转(持续反向转)
 *
 *   速度曲线: VSTART →(A1)→ V1 →(AMAX)→ VMAX
 *                        ←(D1)←    ←(DMAX)←
 * ========================================================== */

/* ==========================================================
 *  第1步: 初始化
 *  说明: 这是最基本的初始化,只做三件事:
 *        1)结构体赋值  2)设置SD/SPI引脚电平  3)配置电机电流
 *  目标: 让芯片能正常工作,电机保持力矩
 * ========================================================== */
void step1_init(void)
{
    /* ① 结构体初始化: 给 chip_number 和 mode 赋初值 */
    tmc5160_struct_init();

    /* ② 设置芯片1为模式1(SD=0, SPI=1): SPI完全控制 */
    TMC5160_Chip1.mode = 1;
    tmc5160_mode(&TMC5160_Chip1);       // 驱动SD_MODE和SPI_MODE引脚电平

    /* ③ 配置电机电流: IHOLD_IRUN寄存器(0x10)
     *    IHOLD  = 8  → 保持电流 8/32 = 25%
     *    IRUN   = 16 → 运行电流 16/32 = 50%
     *    IHOLDDELAY = 5 → 停止后等约109ms再降为保持电流
     *    寄存器布局: [IHOLDDELAY 19:16] [IRUN 12:8] [IHOLD 4:0]
     */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_IHOLD_IRUN,
                      (5 << 16) | (16 << 8) | 8);
}


/* ==========================================================
 *  第2步: 配置斩波器(驱动核心)
 *  说明: 斩波器决定电机如何换相、微步分辨率、电流控制方式
 *  目标: 理解CHOPCONF每个关键位的作用
 * ==========================================================
 *  CHOPCONF(0x6C) 关键位域:
 *    [27:24] MRES  = 0000(256微步) / 0001(128) / ... / 1000(全步)
 *    [16:15] TBL   = 00(16clk) / 01(24clk) / 10(36clk) / 11(54clk)
 *    [14]   CHM    = 0(SpreadCycle模式) / 1(固定关闭时间模式)
 *    [7:4]  HSTRT  = 斩波滞环开始(通常4~7)
 *    [2:0]  HEND   = 斩波滞环结束(通常0~3)
 *    [17]   -      = 保留,设为0
 *
 *  常用值 0x000101D5:
 *    MRES=0000(256微步), TBL=01(24clk), CHM=0(SpreadCycle)
 *    TOFF=4, HSTRT=5, HEND=3, TPFD=4
 * ========================================================== */
void step2_chopper_config(void)
{
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_CHOPCONF, 0x000101D5);
}

/* ==========================================================
 *  第3步: 定位运动
 *  说明: 设置加减速参数 → 写入目标位置 → 电机自动转到
 *  目标: 实现点到点定位
 *
 *  速度曲线参数:
 *    VSTART  = 启动速度
 *    VSTOP   = 停止速度(建议≤VSTART)
 *    V1      = 第一段加速的目标速度(设0则跳过A1/D1段)
 *    VMAX    = 最终速度
 *    A1      = 第一段加速度(VSTART→V1)
 *    AMAX    = 第二段加速度(V1→VMAX)
 *    D1      = 第一段减速度(V1→VSTOP)
 *    DMAX    = 第二段减速度(VMAX→V1)
 * ========================================================== */
void step3_position_move(void)
{
    /* ① 设为定位模式 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 0);

    /* ② 设置速度曲线参数 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VSTART,  0);      // 启动速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VSTOP,   10);     // 停止速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_V1,      500);    // 第一段目标速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX,    2000);   // 最大速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_A1,      200);    // 第一段加速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_AMAX,    500);    // 最大加速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_D1,      400);    // 第一段减速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_DMAX,    800);    // 最大减速度
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_TZEROWAIT, 10);   // 归零等待

    /* ③ 写入目标位置 → 电机立即开始运动 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XTARGET, 50000);
}


/* ==========================================================
 *  第4步: 检查是否到位
 *  说明: 轮询RAMP_STAT寄存器,判断运动是否完成
 *  目标: 掌握状态读取
 * ==========================================================
 *  RAMP_STAT(0x35) 关键位:
 *    bit9  = position_reached : 1=已到达目标位置
 *    bit8  = velocity_reached : 1=已达到目标速度
 *    bit10 = t_zerowait_active: 1=正在归零等待
 * ========================================================== */
unsigned char step4_wait_for_position(void)
{
    unsigned int status;

    do {
        status = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_RAMP_STAT);
        // 如果读到FFFFFFFF说明SPI通信异常
        if (status == 0xFFFFFFFF) return FALSE;
    } while ((status & (1 << 9)) == 0);   // 等待 position_reached

    return TRUE;
}


/* ==========================================================
 *  第5步: 速度模式(连续旋转)
 *  说明: RAMPMODE=1(正转)或2(反转), VMAX就是目标速度
 *  目标: 理解定位模式和速度模式的区别
 * ==========================================================
 *  注意:
 *    · 定位模式: VMAX是速度上限,目标由XTARGET决定
 *    · 速度模式: VMAX就是目标速度,持续转直到你改RAMPMODE或VMAX=0
 * ========================================================== */
void step5_velocity_mode(void)
{
    /* ① 切为速度正转模式 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 1);

    /* ② VMAX在这里就是目标速度(单位: μsteps/s) */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX, 100000);

    // 让电机转一会儿...
    // HAL_Delay(3000);

    /* ③ 速度归零 = 停止 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX, 0);

    /* ④ 切回定位模式 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 0);
}


/* ==========================================================
 *  第6步: 读取错误状态
 *  说明: 检查GSTAT和DRV_STATUS,判断芯片是否正常
 *  目标: 学会排查驱动故障
 * ==========================================================
 *  GSTAT(0x01):   bit0=复位发生 / bit1=驱动错误 / bit2=电荷泵欠压
 *  DRV_STATUS(0x6F):  bits25:16=StallGuard负载值
 *                      bit31=过温 / bit30=过温预警
 * ========================================================== */
unsigned char step6_check_error(void)
{
    unsigned int gstat = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_GSTAT);

    if (gstat & 0x02) {         // bit1 = drv_err
        // 驱动错误! 需要读DRV_STATUS看具体原因
        unsigned int drv = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_DRVSTATUS);

        if (drv & (1 << 31)) {
            // 过温保护(ot)
        }
        if (drv & (1 << 30)) {
            // 过温预警(otpw)
        }
        if (drv & (1 << 27)) {
            // 短路到GND(s2g)
        }

        // 清除GSTAT错误标志(写1清除)
        tmc5160_write_reg(&TMC5160_Chip1, TMC5160_GSTAT, 0x02);
        return FALSE;
    }

    if (gstat & 0x04) {         // bit2 = uv_cp 电荷泵欠压
        // 检查VM电源电压是否正常
        tmc5160_write_reg(&TMC5160_Chip1, TMC5160_GSTAT, 0x04);
        return FALSE;
    }

    return TRUE;
}


/* ==========================================================
 *  第7步: 用StallGuard2堵转检测来找零位(回零)
 *  说明: 让电机往机械限位块方向转,撞上时StallGuard2
 *        检测到负载突变,停止并设当前位置为零位.
 *
 *  原理: StallGuard2将负载转为0~1023数值
 *        空载高(800~1023), 堵转低(0~300)
 *        设一个中间阈值(如500),低于阈值判定为堵转
 *
 *  适用场景: 上电后找绝对零点、每次开机回零
 *
 *  前置条件(!!!很容易踩坑!!!):
 *    ① TCOOLTHRS必须设,且回零速度必须>TCOOLTHRS
 *       StallGuard2只在高于TCOOLTHRS时才更新
 *    ② CHOPCONF要用SpreadCycle模式(CHM=0)
 *       StallGuard2在SpreadCycle下最准确
 *    ③ 机构上必须有机械硬限位块
 * ==========================================================
 *  TCOOLTHRS(0x14) - StallGuard2使能速度阈值
 *    StallGuard2只在电机速度高于此值时工作
 *    回零时的VMAX必须大于TCOOLTHRS
 *
 *  DRV_STATUS(0x6F) bits[25:16] - StallGuard结果
 *    0=负载最大(堵转)  1023=负载最小(空转)
 *    实际值需实测后确定阈值
 * ========================================================== */

/* 回零参数(需根据实际电机和机构调整) */
#define HOMING_VELOCITY     20000       // 回零速度(μsteps/s),必须>TCOOLTHRS
#define HOMING_THRESHOLD    500         // 堵转判定阈值(SG<此值=堵转),这个要实测
#define HOMING_BACKOFF      2000        // 撞到限位后退回的距离(微步)
#define HOMING_TCOOLTHRS    500         // StallGuard使能阈值(回零VMAX必须大于此值)

void step7_homing_by_stall(void)
{
    unsigned int drv;
    int sg;

    /* ① 清除之前的错误状态 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_GSTAT, 0x07);

    /* ② 确保StallGuard2已使能: 设TCOOLTHRS */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_TCOOLTHRS, HOMING_TCOOLTHRS);

    /* ③ 先检查当前是否已经堵在限位上 */
    drv = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_DRVSTATUS);
    sg = (drv >> 16) & 0x3FF;
    if (sg < HOMING_THRESHOLD) {
        // 已堵在限位上,往反方向退一段再回零
        tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 0);
        tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XACTUAL, 0);
        tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XTARGET, -50000);  // 退一段
        step4_wait_for_position();
    }

    /* ④ 设XACTUAL=0,以当前位置为起始 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XACTUAL, 0);

    /* ⑤ 反转去找限位块(速度不要过快,保护机构) */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 2);         // 速度反转模式
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX, HOMING_VELOCITY);

    /* ⑥ 循环检测StallGuard值,直到判定堵转 */
    while (1) {
        drv = tmc5160_read_reg(&TMC5160_Chip1, TMC5160_DRVSTATUS);
        sg = (drv >> 16) & 0x3FF;

        if (sg < HOMING_THRESHOLD) {
            // 堵转! 立即停止电机
            tmc5160_write_reg(&TMC5160_Chip1, TMC5160_VMAX, 0);
            break;
        }

        // 建议加超时保护,防止无限循环
        // if (超时) break;
    }

    /* ⑦ 设当前位置为零位(撞限位的位置) */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XACTUAL, 0);

    /* ⑧ 退出限位: 往正方向走一段,脱离限位块 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_RAMPMODE, 0);         // 切回定位模式
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XTARGET, HOMING_BACKOFF);
    step4_wait_for_position();

    /* ⑨ 最终零位 = 脱离限位后的位置 */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XACTUAL, 0);
    // 现在 XACTUAL=0 就是机械零位
}


/* ==========================================================
 *  综合示例: 完整上电→回零→运动流程
 *  说明: 前面的流程加上开机回零
 * ========================================================== */
void spi_mode_demo_with_homing(void)
{
    /* ---- 初始化+斩波配置 ---- */
    step1_init();
    step2_chopper_config();

    /* ---- 检查芯片状态 ---- */
    if (step6_check_error() == FALSE) return;

    /* ---- 回零(这是每次开机必须做的) ---- */
    step7_homing_by_stall();

    /* ---- 定位运动(从零位开始走) ---- */
    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XTARGET, 51200);    // 正转1圈
    step4_wait_for_position();

    tmc5160_write_reg(&TMC5160_Chip1, TMC5160_XTARGET, -51200);   // 回到零位
    step4_wait_for_position();

    /* ---- 速度模式 ---- */
    step5_velocity_mode();
}
