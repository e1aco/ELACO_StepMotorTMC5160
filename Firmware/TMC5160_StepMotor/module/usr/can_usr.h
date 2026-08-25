/*****************************************************************************
 * @文件: can_usr.h
 * @作者: cl
 * @日期: 2026-08-05
 * @版本: v2.0
 * @说明: CAN 协议解析层（命令解析 + 反馈组装）
 * @依赖: drv/can_drv
 ****************************************************************************/
#ifndef CAN_USR_H
#define CAN_USR_H

#include <stdint.h>

/* ==== 位宏 ==== */
#define BIT(n)          (1UL << (n))

/* ==== 命令码 ==== */
#define CMD_ABS_POS     0x01
#define CMD_REL_CW      0x02
#define CMD_REL_CCW     0x03
#define CMD_VELOCITY    0x04
#define CMD_STOP        0x05
#define CMD_PID_ADJUST  0x06
#define CMD_CL_ENABLE   0x07
#define CMD_CL_DISABLE  0x08

/* ==== PID 参数类型 (命令 0x06 byte[6]) ==== */
#define CAN_PID_KP          0x01
#define CAN_PID_KI          0x02
#define CAN_PID_KD          0x03
#define CAN_PID_OUT_MAX     0x04
#define CAN_PID_OUT_MIN     0x05
#define CAN_PID_INT_MAX     0x06

/* ==== 状态标志位 ==== */
#define STATUS_DONE     BIT(0)
#define STATUS_STALL    BIT(1)
#define STATUS_OTW      BIT(2)
#define STATUS_DRV_ERR  BIT(3)
#define STATUS_SPI_ERR  BIT(4)

/* ==== 运动阶段标志 ==== */
#define STAGE_ACCEL     BIT(0)
#define STAGE_CRUISE    BIT(1)
#define STAGE_DECEL     BIT(2)
#define STAGE_HOME_WAIT BIT(3)
#define STAGE_LOCKED    BIT(4)

/* ==== 类型定义 ==== */
typedef struct {
    int32_t  value;
    uint8_t  cmd;
    uint8_t  motor;
    uint8_t  param;
    uint8_t  checksum;
} CAN_CMD_T;

/* ==== 接口 ==== */
void    USR_CAN_Init(void);
void    USR_CAN_Process(void);
uint8_t USR_CAN_SendMotionFeedback(uint8_t motor, int32_t pos,
                                   uint8_t status, uint8_t stage);
uint8_t USR_CAN_SendPidFeedback(uint8_t motor, uint8_t pid_type, int32_t value);

#endif /* CAN_USR_H */
