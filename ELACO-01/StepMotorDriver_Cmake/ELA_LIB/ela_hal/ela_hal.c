/* ============================================================
 *  ELA HAL 抽象层 - STM32F4 实现
 *  本文件实现了 ela_hal.h 中声明的抽象接口，
 *  通过 STM32 HAL 库完成底层操作。
 *  移植到其他芯片时，只需要重写本文件即可。
 * ============================================================ */

#include "ela_hal.h"

/* ---------- 芯片相关头文件 ---------- */
#include "stm32f4xx_hal.h"      // HAL库
#include "can.h"                // CAN句柄 + HAL_CAN_GetRxMessage
#include "spi.h"                // hspi1
#include "tim.h"                // htim2, htim4
#include "iwdg.h"               // hiwdg
#include "cmd_queue.h"          // 命令队列(CAN接收用)
#include "main.h"               // 引脚宏定义（U1_SD_MODE_Pin等）

/* ---------- 外部变量声明 ---------- */
extern volatile unsigned char Receive_Count;

/* ---------- 引脚映射表 ---------- */
/* 将 ELA_PinId_t 抽象引脚ID 映射到 STM32 的具体端口和引脚号 */
typedef struct {
    GPIO_TypeDef *port;
    uint16_t      pin;
} PinMap_t;

static const PinMap_t s_pin_map[ELA_PIN_NUM] = {
    /* ELA_PIN_U1_SD_MODE  */  { U1_SD_MODE_GPIO_Port,  U1_SD_MODE_Pin  },
    /* ELA_PIN_U1_SPI_MODE */  { U1_SPI_MODE_GPIO_Port, U1_SPI_MODE_Pin },
    /* ELA_PIN_U1_DRV_ENN  */  { U1_DRV_ENN_GPIO_Port,  U1_DRV_ENN_Pin  },
    /* ELA_PIN_U1_CS       */  { U1_CS_GPIO_Port,       U1_CS_Pin       },
    /* ELA_PIN_U2_SD_MODE  */  { U2_SD_MODE_GPIO_Port,  U2_SD_MODE_Pin  },
    /* ELA_PIN_U2_SPI_MODE */  { U2_SPI_MODE_GPIO_Port, U2_SPI_MODE_Pin },
    /* ELA_PIN_U2_DRV_ENN  */  { U2_DRV_ENN_GPIO_Port,  U2_DRV_ENN_Pin  },
    /* ELA_PIN_U2_CS       */  { U2_CS_GPIO_Port,       U2_CS_Pin       },
    /* ELA_PIN_BTN1        */  { GPIOB,                 GPIO_PIN_12     },
    /* ELA_PIN_BTN2        */  { GPIOB,                 GPIO_PIN_2      },
};

/* ============================================================
 *  GPIO 操作
 * ============================================================ */
void ELA_GPIO_WritePin(ELA_PinId_t pin_id, uint8_t state)
{
    if (pin_id >= ELA_PIN_NUM) return;
    HAL_GPIO_WritePin(s_pin_map[pin_id].port,
                      s_pin_map[pin_id].pin,
                      (state) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

uint8_t ELA_GPIO_ReadPin(ELA_PinId_t pin_id)
{
    if (pin_id >= ELA_PIN_NUM) return 0;
    return (HAL_GPIO_ReadPin(s_pin_map[pin_id].port,
                             s_pin_map[pin_id].pin) == GPIO_PIN_SET)
           ? ELA_PIN_SET : ELA_PIN_RESET;
}

/* ============================================================
 *  SPI 操作 (TMC5160 专用)
 * ============================================================ */
uint8_t ELA_SPI_Transmit(const uint8_t *tx_data, uint16_t size)
{
    return (HAL_SPI_Transmit(&hspi1, (uint8_t *)tx_data, size, HAL_MAX_DELAY) == HAL_OK)
           ? ELA_OK : ELA_ERROR;
}

uint8_t ELA_SPI_TransmitReceive(const uint8_t *tx_data, uint8_t *rx_data, uint16_t size)
{
    return (HAL_SPI_TransmitReceive(&hspi1, (uint8_t *)tx_data, rx_data, size, HAL_MAX_DELAY) == HAL_OK)
           ? ELA_OK : ELA_ERROR;
}

/* ============================================================
 *  定时器 PWM 操作
 * ============================================================ */
static TIM_HandleTypeDef *s_tim_map[ELA_TIM_CH_NUM];
static uint32_t           s_tim_ch_map[ELA_TIM_CH_NUM];

/* 初始化定时器映射(在系统初始化完成后调用) */
void ELA_TIM_Mapping_Init(void)
{
    s_tim_map[ELA_TIM_CH_LED]     = &htim2;
    s_tim_ch_map[ELA_TIM_CH_LED]  = TIM_CHANNEL_2;

    s_tim_map[ELA_TIM_CH_TMC_CLK] = &htim4;
    s_tim_ch_map[ELA_TIM_CH_TMC_CLK] = TIM_CHANNEL_1;
}

void ELA_TIM_PWM_SetCompare(ELA_TimPwmCh_t ch, uint32_t value)
{
    if (ch >= ELA_TIM_CH_NUM) return;
    __HAL_TIM_SetCompare(s_tim_map[ch], s_tim_ch_map[ch], value);
}

void ELA_TIM_PWM_Start(ELA_TimPwmCh_t ch)
{
    if (ch >= ELA_TIM_CH_NUM) return;
    HAL_TIM_PWM_Start(s_tim_map[ch], s_tim_ch_map[ch]);
}

/* ============================================================
 *  独立看门狗
 * ============================================================ */
void ELA_IWDG_Refresh(void)
{
    HAL_IWDG_Refresh(&hiwdg);
}

/* ============================================================
 *  CAN 发送 (扩展帧, 29位ID)
 * ============================================================ */
uint8_t ELA_CAN_Send_EXT(uint32_t id, const uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef tx_header;
    uint32_t tx_mailbox;

    tx_header.StdId = 0;
    tx_header.ExtId = id;
    tx_header.RTR   = CAN_RTR_DATA;
    tx_header.IDE   = CAN_ID_EXT;
    tx_header.DLC   = len;
    tx_header.TransmitGlobalTime = DISABLE;

    return (HAL_CAN_AddTxMessage(&hcan1, &tx_header, (uint8_t *)data, &tx_mailbox) == HAL_OK)
           ? ELA_OK : ELA_ERROR;
}

/* ============================================================
 *  系统滴答
 * ============================================================ */
uint32_t ELA_GetTick(void)
{
    return HAL_GetTick();
}

/* ============================================================
 *  CAN 接收中断回调
 *  由 HAL_CAN_RxFifo0MsgPendingCallback() 调用
 *  移植到新平台时根据新平台的CAN中断回调方式修改
 * ============================================================ */
void ELA_CAN_RxCallback(void)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[CMD_LENGTH];
    uint8_t ret;

    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK)
    {
        ret = CmdQueue_insert(&CmdQueue, rx_data);
        if (ret == TRUE)
        {
            Receive_Count++;
        }
    }
}

/* ============================================================
 *  HAL 回调函数 (与 STM32 HAL 框架绑定的桥梁函数)
 *  移植到新平台时，根据新平台的框架修改这些函数
 * ============================================================ */

/* CAN 接收中断回调 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    ELA_CAN_RxCallback();
}

/* SPI 传输完成回调 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI1) {
        // SPI传输完成后的处理逻辑
    }
}
