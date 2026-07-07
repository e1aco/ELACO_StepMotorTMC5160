//
// Created by electronic on 2026/5/28.
//
#ifndef _TMC5160_H_
#define _TMC5160_H_

#include "main.h"
#include "spi.h"

#define FALSE 1 // 定义一个特殊的FALSE值，表示操作失败
#define TRUE 0 // 定义一个特殊的TRUE值，表示操作成功

/* 定义TMC5160结构体 */
typedef struct TMC5160
{
    unsigned char chip_number; // 芯片号
    unsigned char mode;        // 模式
} TMC5160_T;

extern TMC5160_T TMC5160_Chip1; // 定义TMC5160芯片1的实例
extern TMC5160_T TMC5160_Chip2; // 定义TMC5160芯片2的实例

/* -1- 添加 TMC5160的芯片模式选择引脚 */
/* SD_MODE    SPI_MODE        运行状态
 *    0          1          位置式步进
 *    1          1      S斜坡运动步进+方向控制
 *    1          0        简单步进+方向控制
 */
//CHIP1
#define CHIP1_SD_SET      HAL_GPIO_WritePin(U1_SD_MODE_GPIO_Port, U1_SD_MODE_Pin, GPIO_PIN_SET);
#define CHIP1_SD_RESET    HAL_GPIO_WritePin(U1_SD_MODE_GPIO_Port, U1_SD_MODE_Pin, GPIO_PIN_RESET);
#define CHIP1_SPI_SET      HAL_GPIO_WritePin(U1_SPI_MODE_GPIO_Port, U1_SPI_MODE_Pin, GPIO_PIN_SET);
#define CHIP1_SPI_RESET    HAL_GPIO_WritePin(U1_SPI_MODE_GPIO_Port, U1_SPI_MODE_Pin, GPIO_PIN_RESET);
//CHIP2
#define CHIP2_SD_SET      HAL_GPIO_WritePin(U2_SD_MODE_GPIO_Port, U2_SD_MODE_Pin, GPIO_PIN_SET);
#define CHIP2_SD_RESET    HAL_GPIO_WritePin(U2_SD_MODE_GPIO_Port, U2_SD_MODE_Pin, GPIO_PIN_RESET);
#define CHIP2_SPI_SET      HAL_GPIO_WritePin(U2_SPI_MODE_GPIO_Port, U2_SPI_MODE_Pin, GPIO_PIN_SET);
#define CHIP2_SPI_RESET    HAL_GPIO_WritePin(U2_SPI_MODE_GPIO_Port, U2_SPI_MODE_Pin, GPIO_PIN_RESET);

/* -1- 结束 TMC5160芯片模式选择引脚的添加 */

/* -2- 添加 TMC5160的SPI片选引脚控制 */
//CHIP1
#define CHIP1_CS_SET       HAL_GPIO_WritePin(U1_CS_GPIO_Port, U1_CS_Pin, GPIO_PIN_SET);
#define CHIP1_CS_RESET     HAL_GPIO_WritePin(U1_CS_GPIO_Port, U1_CS_Pin, GPIO_PIN_RESET);
//CHIP2
#define CHIP2_CS_SET       HAL_GPIO_WritePin(U2_CS_GPIO_Port, U2_CS_Pin, GPIO_PIN_SET);
#define CHIP2_CS_RESET     HAL_GPIO_WritePin(U2_CS_GPIO_Port, U2_CS_Pin, GPIO_PIN_RESET);
/* -2- 结束 TMC5160的SPI片选引脚控制 */

/* -3- 添加 TMC5160的电机使能引脚控制 */
//CHIP1
#define CHIP1_DRV_ENN_SET       HAL_GPIO_WritePin(U1_DRV_ENN_GPIO_Port, U1_DRV_ENN_Pin, GPIO_PIN_SET);
#define CHIP1_DRV_ENN_RESET     HAL_GPIO_WritePin(U1_DRV_ENN_GPIO_Port, U1_DRV_ENN_Pin, GPIO_PIN_RESET);
//CHIP2
#define CHIP2_DRV_ENN_SET       HAL_GPIO_WritePin(U2_DRV_ENN_GPIO_Port, U2_DRV_ENN_Pin, GPIO_PIN_SET);
#define CHIP2_DRV_ENN_RESET     HAL_GPIO_WritePin(U2_DRV_ENN_GPIO_Port, U2_DRV_ENN_Pin, GPIO_PIN_RESET);
/* -3- 结束 TMC5160的电机使能引脚控制 */


/* -4- 添加 TMC5160常用寄存器地址定义 */
/* --- 通用配置寄存器 (0x00-0x0C) --- */
#define TMC5160_GCONF          0x00    // 全局配置(校准、PWM模式、方向、DIAG功能选择等)
#define TMC5160_GSTAT          0x01    // 全局状态(复位标志、驱动错误、电荷泵欠压)[写1清除]
#define TMC5160_IFCNT          0x02    // 接口传输计数(UART写入递增,用于检错)
#define TMC5160_SLAVECONF      0x03    // UART从机地址配置(地址+发送延迟)
#define TMC5160_IOIN           0x04    // 输入引脚状态读取(含版本号)
#define TMC5160_X_COMPARE      0x05    // 位置比较寄存器(XACTUAL==X_COMPARE时输出位置脉冲)
#define TMC5160_OTP_PROG       0x06    // OTP一次编程寄存器
#define TMC5160_OTP_READ       0x07    // OTP读取寄存器
#define TMC5160_FACTORY_CONF   0x08    // 工厂配置(内部时钟微调)
#define TMC5160_SHORT_CONF     0x09    // 短路保护检测配置(电平+滤波+延迟)
#define TMC5160_DRV_CONF       0x0A    // 驱动配置(BBM时间、过温阈值、驱动电流、感测滤波)
#define TMC5160_GLOBAL_SCALER  0x0B    // 全局电流缩放系数(32~255: 32/256~255/256)
#define TMC5160_OFFSET_READ    0x0C    // ADC偏移校准结果(只读)

/* --- 速度控制相关寄存器 (0x10-0x15) --- */
#define TMC5160_IHOLD_IRUN     0x10    // 保持电流/运行电流/保持延迟时间
#define TMC5160_TPOWERDOWN     0x11    // 掉电延时(停止后多久降低到IHOLD)
#define TMC5160_TSTEP          0x12    // 实际测得的步进间隔时间(只读,用于速度测量)
#define TMC5160_TPWMTHRS       0x13    // StealthChop PWM上限阈值(低于此使用PWM模式)
#define TMC5160_TCOOLTHRS      0x14    // CoolStep/StallGuard2下限阈值(高于此使能)
#define TMC5160_THIGH          0x15    // 高速切换阈值(高于此切换fullstep或chm模式)

/* --- 运动控制核心寄存器 (0x20-0x2D) --- */
#define TMC5160_RAMPMODE       0x20    // 斜坡模式选择(0:定位, 1:速度正转, 2:速度反转, 3:保持)
#define TMC5160_XACTUAL        0x21    // 实际位置(有符号32位,回零时修改)
#define TMC5160_VACTUAL        0x22    // 实际速度(有符号24位,只读,负号表示反向)
#define TMC5160_VSTART         0x23    // 启动速度(建议VSTOP<=VSTART)
#define TMC5160_A1             0x24    // 第一段加速度(VSTART到V1)
#define TMC5160_V1             0x25    // 第一段加速目标速度(0=跳过A1/D1段)
#define TMC5160_AMAX           0x26    // 最大加速度(V1到VMAX,速度模式下的加减速值)
#define TMC5160_VMAX           0x27    // 最大速度(定位模式/速度模式的目标速度)
#define TMC5160_DMAX           0x28    // 最大减速度(VMAX到V1)
#define TMC5160_D1             0x2A    // 第一段减速度(V1到VSTOP,定位模式勿设为0)
#define TMC5160_VSTOP          0x2B    // 停止速度(定位模式勿设为0,最小值10)
#define TMC5160_TZEROWAIT      0x2C    // 归零等待时间(减速到0后等待,防止反向过冲)
#define TMC5160_XTARGET        0x2D    // 目标位置(RAMPMODE=0时写入以触发定位运动)

/* --- 斜坡/参考开关/DcStep配置寄存器 (0x33-0x36) --- */
/* 这些寄存器在闭环控制和回零操作中非常重要 */
#define TMC5160_VDCMIN         0x33    // DcStep使能速度阈值(高于此启用自动换向)
#define TMC5160_SW_MODE        0x34    // 参考开关&StallGuard2事件配置(限位停止,位置锁存)
#define TMC5160_RAMP_STAT      0x35    // 斜坡状态&参考开关事件状态(含到位标志、失速标志)
#define TMC5160_XLATCH         0x36    // 斜坡位置锁存(开关事件时锁定XACTUAL)

/* --- 编码器接口寄存器 (0x38-0x3D) --- */
/* 闭环位置控制的核心寄存器组 */
#define TMC5160_ENCMODE        0x38    // 编码器模式配置(N事件触发、极性、清零模式)
#define TMC5160_X_ENC          0x39    // 编码器实际位置(有符号32位)
#define TMC5160_ENC_CONST      0x3A    // 编码器累积常数(16位整数+16位小数,匹配分辨率)
#define TMC5160_ENC_STATUS     0x3B    // 编码器状态(N事件标志、偏差警告)[写1清除]
#define TMC5160_ENC_LATCH      0x3C    // 编码器锁存位置(N事件时锁存X_ENC,只读)
#define TMC5160_ENC_DEVIATION  0x3D    // 编码器位置偏差阈值(电机位置与编码器最大允许偏差)

/* --- 微步表寄存器 (0x60-0x6B) --- */
#define TMC5160_MSLUT0         0x60    // 微步查找表 第0段(32位差分编码)
#define TMC5160_MSLUT1         0x61    // 微步查找表 第1段
#define TMC5160_MSLUT2         0x62    // 微步查找表 第2段
#define TMC5160_MSLUT3         0x63    // 微步查找表 第3段
#define TMC5160_MSLUT4         0x64    // 微步查找表 第4段
#define TMC5160_MSLUT5         0x65    // 微步查找表 第5段
#define TMC5160_MSLUT6         0x66    // 微步查找表 第6段
#define TMC5160_MSLUT7         0x67    // 微步查找表 第7段
#define TMC5160_MSLUTSEL       0x68    // 微步表段选择(4段宽度控制,定义每段解析度)
#define TMC5160_MSLUTSTART     0x69    // 微步表起始值(START_SIN+START_SIN90)
#define TMC5160_MSCNT          0x6A    // 实际微步计数器位置(只读,0=正弦波零点)
#define TMC5160_MSCURACT       0x6B    // 实际微步电流值CUR_A/CUR_B(只读)

/* --- 驱动配置寄存器 (0x6C-0x73) --- */
#define TMC5160_CHOPCONF       0x6C    // 斩波配置(微步分辨率、blank time、chopper模式等)
#define TMC5160_COOLCONF       0x6D    // CoolStep/StallGuard2配置(电流自适应阈值)
#define TMC5160_DCCTRL         0x6E    // DcStep自动换向配置(DC_TIME+DC_SG)
#define TMC5160_DRVSTATUS      0x6F    // 驱动状态(StallGuard值+错误标志,只读)

/* --- PWM/StealthChop静音模式配置 (0x70-0x73) --- */
#define TMC5160_PWMCONF        0x70    // PWM配置(振幅、渐变、频率、自动调节)
#define TMC5160_PWMSCALE       0x71    // PWM实际占空比+PWM自动调节偏移量(只读)
#define TMC5160_PWM_AUTO       0x72    // PWM自动调节结果(offset+gradient,只读)
#define TMC5160_LOST_STEPS     0x73    // DcStep模式下丢失的步数(只读,SD_MODE=1时)
/* -4- 结束 TMC5160常用寄存器地址定义 */


/* -5- 添加 函数原型 */
unsigned char tmc5160_mode(TMC5160_T *CHIP_T);
void tmc5160_init(void);
unsigned char tmc5160_write_reg(TMC5160_T *CHIP_T, unsigned char reg_addr, unsigned int data);
unsigned int tmc5160_read_reg(TMC5160_T *CHIP_T, unsigned char reg_addr);
/* -5- 结束 函数原型 */

#endif //_TMC5160_H_
