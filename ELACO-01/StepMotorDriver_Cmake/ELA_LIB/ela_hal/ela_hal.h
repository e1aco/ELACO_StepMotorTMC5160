#ifndef _ELA_HAL_H_
#define _ELA_HAL_H_

#include <stdint.h>

/* ============================================================
 *  ELA HAL 抽象层
 *  作用: 隔离 ELA_LIB 业务代码与具体芯片 HAL 的依赖
 *  移植到其他芯片时, 只需要重新实现 ela_hal.c 即可
 * ============================================================ */

/* ---------- 返回状态定义 ---------- */
#define ELA_OK      0
#define ELA_ERROR   1

/* ---------- GPIO 引脚抽象ID ---------- */
/* 每个引脚对应一个枚举值, 在 ela_hal.c 中映射到具体芯片的端口/引脚 */
typedef enum {
    ELA_PIN_U1_SD_MODE,      // TMC5160 芯片1 模式选择 SD
    ELA_PIN_U1_SPI_MODE,     // TMC5160 芯片1 模式选择 SPI
    ELA_PIN_U1_DRV_ENN,      // TMC5160 芯片1 电机使能
    ELA_PIN_U1_CS,           // TMC5160 芯片1 SPI 片选
    ELA_PIN_U2_SD_MODE,      // TMC5160 芯片2 模式选择 SD
    ELA_PIN_U2_SPI_MODE,     // TMC5160 芯片2 模式选择 SPI
    ELA_PIN_U2_DRV_ENN,      // TMC5160 芯片2 电机使能
    ELA_PIN_U2_CS,           // TMC5160 芯片2 SPI 片选
    ELA_PIN_BTN1,            // 按键1
    ELA_PIN_BTN2,            // 按键2
    ELA_PIN_NUM              // 引脚总数(内部使用)
} ELA_PinId_t;

/* ---------- GPIO 电平定义 ---------- */
#define ELA_PIN_SET     1
#define ELA_PIN_RESET   0

/* ---------- 定时器PWM通道抽象ID ---------- */
typedef enum {
    ELA_TIM_CH_LED,          // TIM2_CH2: LED 指示灯 PWM
    ELA_TIM_CH_TMC_CLK,      // TIM4_CH1: TMC5160 时钟 PWM
    ELA_TIM_CH_NUM           // 通道总数(内部使用)
} ELA_TimPwmCh_t;

/* ---------- 功能函数原型 ---------- */

/* --- GPIO --- */
void    ELA_GPIO_WritePin(ELA_PinId_t pin_id, uint8_t state);
uint8_t ELA_GPIO_ReadPin(ELA_PinId_t pin_id);

/* --- SPI (TMC5160 专用, 5字节固定长度) --- */
uint8_t ELA_SPI_Transmit(const uint8_t *tx_data, uint16_t size);
uint8_t ELA_SPI_TransmitReceive(const uint8_t *tx_data, uint8_t *rx_data, uint16_t size);

/* --- 定时器 PWM --- */
void ELA_TIM_Mapping_Init(void);     // 初始化定时器映射(在系统定时器初始化完成后调用)
void ELA_TIM_PWM_SetCompare(ELA_TimPwmCh_t ch, uint32_t value);
void ELA_TIM_PWM_Start(ELA_TimPwmCh_t ch);

/* --- 独立看门狗 --- */
void ELA_IWDG_Refresh(void);

/* --- CAN 发送(扩展帧, 29位ID) --- */
uint8_t ELA_CAN_Send_EXT(uint32_t id, const uint8_t *data, uint8_t len);

/* --- 系统滴答(毫秒) --- */
uint32_t ELA_GetTick(void);

/* --- CAN接收中断回调(由HAL中断框架调用, 业务处理在ela_hal内部完成) --- */
/*     注意: 这个函数依然和HAL框架绑定, 是HAL→ELA的桥梁 */
/*     在 irq_handler 中由 HAL_CAN_IRQHandler → HAL_CAN_RxFifo0MsgPendingCallback 触发 */
/*     移植时需要根据新平台的CAN中断回调方式修改实现 */
void ELA_CAN_RxCallback(void);

#endif /* _ELA_HAL_H_ */
