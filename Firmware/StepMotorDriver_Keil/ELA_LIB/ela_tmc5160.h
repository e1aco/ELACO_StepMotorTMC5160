#ifndef _ELA_TMC5160_H_
#define _ELA_TMC5160_H_

#include "elaco_main.h"


#define FALSE 1 // 操作失败
#define TRUE 0  // 操作成功

/* 定义TMC5160结构体 */
typedef struct TMC5160
{
    unsigned char chip_number; // 芯片号
    unsigned char mode;        // 模式
    unsigned char move_pending; // 0=空闲, 1=运动到位反馈待发送
} TMC5160_T;

extern TMC5160_T g_tmc5160_chip1_st;
extern TMC5160_T g_tmc5160_chip2_st;

/* -1- TMC5160芯片模式选择引脚 */
/* SD_MODE    SPI_MODE        运行状态
 *    0          1          位置式步进
 *    1          1      S斜坡运动步进+方向控制
 *    1          0        简单步进+方向控制
 */
//CHIP1
#define CHIP1_SD_SET \
    HAL_GPIO_WritePin(U1_SD_MODE_GPIO_Port, \
                      U1_SD_MODE_Pin, GPIO_PIN_SET);
#define CHIP1_SD_RESET \
    HAL_GPIO_WritePin(U1_SD_MODE_GPIO_Port, \
                      U1_SD_MODE_Pin, GPIO_PIN_RESET);
#define CHIP1_SPI_SET \
    HAL_GPIO_WritePin(U1_SPI_MODE_GPIO_Port, \
                      U1_SPI_MODE_Pin, GPIO_PIN_SET);
#define CHIP1_SPI_RESET \
    HAL_GPIO_WritePin(U1_SPI_MODE_GPIO_Port, \
                      U1_SPI_MODE_Pin, GPIO_PIN_RESET);
//CHIP2
#define CHIP2_SD_SET \
    HAL_GPIO_WritePin(U2_SD_MODE_GPIO_Port, \
                      U2_SD_MODE_Pin, GPIO_PIN_SET);
#define CHIP2_SD_RESET \
    HAL_GPIO_WritePin(U2_SD_MODE_GPIO_Port, \
                      U2_SD_MODE_Pin, GPIO_PIN_RESET);
#define CHIP2_SPI_SET \
    HAL_GPIO_WritePin(U2_SPI_MODE_GPIO_Port, \
                      U2_SPI_MODE_Pin, GPIO_PIN_SET);
#define CHIP2_SPI_RESET \
    HAL_GPIO_WritePin(U2_SPI_MODE_GPIO_Port, \
                      U2_SPI_MODE_Pin, GPIO_PIN_RESET);
/* -1- 结束 */

/* -2- TMC5160的SPI片选引脚控制 */
//CHIP1
#define CHIP1_CS_SET \
    HAL_GPIO_WritePin(U1_SPI1_SCN_GPIO_Port, \
                      U1_SPI1_SCN_Pin, GPIO_PIN_SET);
#define CHIP1_CS_RESET \
    HAL_GPIO_WritePin(U1_SPI1_SCN_GPIO_Port, \
                      U1_SPI1_SCN_Pin, GPIO_PIN_RESET);
//CHIP2
#define CHIP2_CS_SET \
    HAL_GPIO_WritePin(U2_SPI1_SCN_GPIO_Port, \
                      U2_SPI1_SCN_Pin, GPIO_PIN_SET);
#define CHIP2_CS_RESET \
    HAL_GPIO_WritePin(U2_SPI1_SCN_GPIO_Port, \
                      U2_SPI1_SCN_Pin, GPIO_PIN_RESET);
/* -2- 结束 */

/* -3- TMC5160的电机使能引脚控制 */
//CHIP1
#define CHIP1_DRV_ENN_SET \
    HAL_GPIO_WritePin(U1_DRV_ENN_GPIO_Port, \
                      U1_DRV_ENN_Pin, GPIO_PIN_SET);
#define CHIP1_DRV_ENN_RESET \
    HAL_GPIO_WritePin(U1_DRV_ENN_GPIO_Port, \
                      U1_DRV_ENN_Pin, GPIO_PIN_RESET);
//CHIP2
#define CHIP2_DRV_ENN_SET \
    HAL_GPIO_WritePin(U2_DRV_ENN_GPIO_Port, \
                      U2_DRV_ENN_Pin, GPIO_PIN_SET);
#define CHIP2_DRV_ENN_RESET \
    HAL_GPIO_WritePin(U2_DRV_ENN_GPIO_Port, \
                      U2_DRV_ENN_Pin, GPIO_PIN_RESET);
/* -3- 结束 */


/* -4- TMC5160常用寄存器地址定义 */
/* --- 通用配置寄存器 (0x00-0x0C) --- */
#define TMC5160_GCONF          0x00
#define TMC5160_GSTAT          0x01
#define TMC5160_IFCNT          0x02
#define TMC5160_SLAVECONF      0x03
#define TMC5160_IOIN           0x04
#define TMC5160_X_COMPARE      0x05
#define TMC5160_OTP_PROG       0x06
#define TMC5160_OTP_READ       0x07
#define TMC5160_FACTORY_CONF   0x08
#define TMC5160_SHORT_CONF     0x09
#define TMC5160_DRV_CONF       0x0A
#define TMC5160_GLOBAL_SCALER  0x0B
#define TMC5160_OFFSET_READ    0x0C

/* --- 速度控制相关寄存器 (0x10-0x15) --- */
#define TMC5160_IHOLD_IRUN     0x10
#define TMC5160_TPOWERDOWN     0x11
#define TMC5160_TSTEP          0x12
#define TMC5160_TPWMTHRS       0x13
#define TMC5160_TCOOLTHRS      0x14
#define TMC5160_THIGH          0x15

/* --- 运动控制核心寄存器 (0x20-0x2D) --- */
#define TMC5160_RAMPMODE       0x20
#define TMC5160_XACTUAL        0x21
#define TMC5160_VACTUAL        0x22
#define TMC5160_VSTART         0x23
#define TMC5160_A1             0x24
#define TMC5160_V1             0x25
#define TMC5160_AMAX           0x26
#define TMC5160_VMAX           0x27
#define TMC5160_DMAX           0x28
#define TMC5160_D1             0x2A
#define TMC5160_VSTOP          0x2B
#define TMC5160_TZEROWAIT      0x2C
#define TMC5160_XTARGET        0x2D

/* --- 斜坡/参考开关/DcStep配置 (0x33-0x36) --- */
#define TMC5160_VDCMIN         0x33
#define TMC5160_SW_MODE        0x34
#define TMC5160_RAMP_STAT      0x35
#define TMC5160_XLATCH         0x36

/* --- 编码器接口寄存器 (0x38-0x3D) --- */
#define TMC5160_ENCMODE        0x38
#define TMC5160_X_ENC          0x39
#define TMC5160_ENC_CONST      0x3A
#define TMC5160_ENC_STATUS     0x3B
#define TMC5160_ENC_LATCH      0x3C
#define TMC5160_ENC_DEVIATION  0x3D

/* --- 微步表寄存器 (0x60-0x6B) --- */
#define TMC5160_MSLUT0         0x60
#define TMC5160_MSLUT1         0x61
#define TMC5160_MSLUT2         0x62
#define TMC5160_MSLUT3         0x63
#define TMC5160_MSLUT4         0x64
#define TMC5160_MSLUT5         0x65
#define TMC5160_MSLUT6         0x66
#define TMC5160_MSLUT7         0x67
#define TMC5160_MSLUTSEL       0x68
#define TMC5160_MSLUTSTART     0x69
#define TMC5160_MSCNT          0x6A
#define TMC5160_MSCURACT       0x6B

/* --- 驱动配置寄存器 (0x6C-0x73) --- */
#define TMC5160_CHOPCONF       0x6C
#define TMC5160_COOLCONF       0x6D
#define TMC5160_DCCTRL         0x6E
#define TMC5160_DRVSTATUS      0x6F

/* --- PWM/StealthChop静音模式配置 (0x70-0x73) --- */
#define TMC5160_PWMCONF        0x70
#define TMC5160_PWMSCALE       0x71
#define TMC5160_PWM_AUTO       0x72
#define TMC5160_LOST_STEPS     0x73
/* -4- 结束 */

/* -5- 运动参数组结构体 */
typedef struct {
    unsigned int vstart;
    unsigned int vstop;
    unsigned int v1;
    unsigned int a1;
    unsigned int amax;
    unsigned int vmax;
    unsigned int d1;
    unsigned int dmax;
    unsigned int tzerowait;
} TMC5160_MotionProfile_T;

#define TMC5160_PROFILE_COUNT  4 // 4组运动参数
/* -5- 结束 */

/* -6- 编码器验证结果 */
#define TMC5160_ENC_TOLERANCE      256  /* 偏差容差: 256步≈0.5° */
#define TMC5160_MOVE_TIMEOUT_MS    5000 /* 运动超时(ms) */
#define TMC5160_MAX_RETRY          3    /* 最大重试次数 */

typedef enum {
    MOVE_OK = 0,
    MOVE_TIMEOUT,
    MOVE_DEVIATION,
    MOVE_SPI_ERROR
} TMC5160_MoveResult_T;

/* -7- 函数原型 */
unsigned char Tmc5160_Mode(TMC5160_T *CHIP_T);
void         Tmc5160_Init(void);
unsigned char Tmc5160_WriteReg(TMC5160_T *CHIP_T,
                                unsigned char reg_addr,
                                unsigned int data);
unsigned int  Tmc5160_ReadReg(TMC5160_T *CHIP_T,
                               unsigned char reg_addr);
void         Tmc5160_ApplyProfile(TMC5160_T *chip,
                                   unsigned char profile_id);
void         Tmc5160_MoveTo(TMC5160_T *chip, int target);
void         Tmc5160_MoveBy(TMC5160_T *chip, int offset);
void         Tmc5160_SetVelocity(TMC5160_T *chip,
                                  int velocity);
void         Tmc5160_StopMotor(TMC5160_T *chip);
int          Tmc5160_GetPosition(TMC5160_T *chip);
unsigned int Tmc5160_GetRampStat(TMC5160_T *chip);
unsigned int Tmc5160_GetDrvStatus(TMC5160_T *chip);
unsigned char Tmc5160_GetStatusFlags(TMC5160_T *chip);
unsigned char Tmc5160_GetMotionPhase(TMC5160_T *chip);

/* 编码器相关 */
void         Tmc5160_ConfigEncoder(TMC5160_T *chip);
int          Tmc5160_GetEncoderPosition(TMC5160_T *chip);
unsigned int Tmc5160_GetEncoderStatus(TMC5160_T *chip);
int          Tmc5160_GetEncoderDeviation(TMC5160_T *chip);
unsigned char Tmc5160_CheckPosition(TMC5160_T *chip,
                                     int expected_steps);

/* 带验证的运动控制 */
TMC5160_MoveResult_T Tmc5160_WaitPosition(
    TMC5160_T *chip, unsigned int timeout_ms);
TMC5160_MoveResult_T Tmc5160_MoveToWithVerify(
    TMC5160_T *chip, int target);
/* -7- 结束 */

#endif
