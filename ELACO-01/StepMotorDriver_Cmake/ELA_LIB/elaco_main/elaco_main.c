#include "elaco_main.h"


volatile unsigned char Receive_Count = 0;            // CAN报文接收计数
LIGHT_CANS_T CAN_COL={0};   // 初始化全局的灯光和CAN数据结构实例

/* -1- START 主循环函数 */

/****
 * @ 原型: static void Process_CAN_Commands(void)
 * @ 输入: void
 * @ 输出: static void
 * @ 说明: 处理CAN命令的函数，从命令队列中取出命令进行处理
********/
static void Process_CAN_Commands(void) {
    if (Receive_Count > 0)
    {
        // 从命令队列中取出第一个命令进行处理
        unsigned char *cmd = CmdQueue_first(&CmdQueue);
        unsigned char verify = 0;

        CmdQueue_delete(&CmdQueue);
        Receive_Count--; // 处理完一个命令后，接收计数减1
        for (int i = 0; i < CMD_LENGTH - 1; i++)
        {
            verify += cmd[i];
        }
        if (verify == cmd[CMD_LENGTH - 1])
        {
            switch (cmd[0])
            {
                case CHANGE_LIGHT:
                {
                    // 关闭常亮模式
                    CAN_COL.Constant_Light_Flag = 0; // 关闭常亮模式
                    // 更新灯光状态，并设置改变标志
                    if(CAN_COL.Rx_Lights[0] != cmd[1] || CAN_COL.Rx_Lights[1] != cmd[2] || CAN_COL.Rx_Lights[2] != cmd[3] || CAN_COL.Rx_Lights[3] != cmd[4])
                    {
                        CAN_COL.Light_Changed_Flag = 1; // 灯光状态改变标志
                        CAN_COL.Rx_Lights[0] = cmd[1];
                        CAN_COL.Rx_Lights[1] = cmd[2];
                        CAN_COL.Rx_Lights[2] = cmd[3];
                        CAN_COL.Rx_Lights[3] = cmd[4];
                    }


                    // 回复控制器亮度修改成功
                    CAN_COL.Tx_CAN_Buffer[0] = 0x01; // 回复命令类型
                    CAN_COL.Tx_CAN_Buffer[1] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[2] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[3] = 0x01;
                    if (HAL_OK == CAN_SendMessage_EXT(RX_CAN_ID, (uint8_t *)CAN_COL.Tx_CAN_Buffer, RX_LENGTH)) // 亮度修改成功，回复控制器
                    {
                    }
                }
                    break;
                case CHANGE_CONSTANT_LIGHT:
                {
                    // 开启常亮模式，保持当前灯光状态不变
                    CAN_COL.Constant_Light_Flag = 1; // 开启常亮模式
                    // 更新灯光状态，并设置改变标志
                    if(CAN_COL.Rx_Lights[0] != cmd[1] || CAN_COL.Rx_Lights[1] != cmd[2] || CAN_COL.Rx_Lights[2] != cmd[3] || CAN_COL.Rx_Lights[3] != cmd[4])
                    {
                        CAN_COL.Light_Changed_Flag = 1; // 灯光状态改变标志
                        CAN_COL.Rx_Lights[0] = cmd[1];
                        CAN_COL.Rx_Lights[1] = cmd[2];
                        CAN_COL.Rx_Lights[2] = cmd[3];
                        CAN_COL.Rx_Lights[3] = cmd[4];
                    }
                    // 回复控制器常亮模式已开启
                    CAN_COL.Tx_CAN_Buffer[0] = 0x01; // 回复命令类型
                    CAN_COL.Tx_CAN_Buffer[1] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[2] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[3] = 0x01;
                    if (HAL_OK == CAN_SendMessage_EXT(RX_CAN_ID, (uint8_t *)CAN_COL.Tx_CAN_Buffer, RX_LENGTH)) // 常亮模式开启成功，回复控制器
                    {
                    }
                }
                    break;
                case CAN_TEST:
                {
                    CAN_COL.Tx_CAN_Buffer[0] = 0x08; // 回复命令类型
                    CAN_COL.Tx_CAN_Buffer[1] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[2] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[3] = 0x08;
                    if (HAL_OK == CAN_SendMessage_EXT(RX_CAN_ID, (uint8_t *)CAN_COL.Tx_CAN_Buffer, RX_LENGTH)) // CAN 通讯测试成功，回复控制器
                    {
                    }
                }
                    break;
                default:
                {
                    CAN_COL.Tx_CAN_Buffer[0] = 0x0E; // 回复命令类型
                    CAN_COL.Tx_CAN_Buffer[1] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[2] = 0x00;
                    CAN_COL.Tx_CAN_Buffer[3] = 0x0E;
                    if (HAL_OK == CAN_SendMessage_EXT(RX_CAN_ID, (uint8_t *)CAN_COL.Tx_CAN_Buffer, RX_LENGTH)) // 命令无效，回复控制器
                    {
                    }
                }
                    break;
            }
        }
        else
        {
            CAN_COL.Tx_CAN_Buffer[0] = 0x0D; // 回复命令类型
            CAN_COL.Tx_CAN_Buffer[1] = 0x00;
            CAN_COL.Tx_CAN_Buffer[2] = 0x00;
            CAN_COL.Tx_CAN_Buffer[3] = 0x0D;
            if (HAL_OK == CAN_SendMessage_EXT(RX_CAN_ID, (uint8_t *)CAN_COL.Tx_CAN_Buffer, RX_LENGTH)) // 校验失败，回复控制器
            {
            }
        }
    }
}

/****
 * @ 原型: void elaco_main_proc(void)
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 主循环函数，将所有任务集中在该函数实现，减少对HAL库的依赖
********/
void elaco_main_proc(void)
{
    CmdQueueInit(&CmdQueue); // 初始化命令队列

    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 5000); // LED闪烁
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // 启动TIM2的PWM功能

    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_1, 3); // 给TMC5160芯片时钟频率
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); // 启动TIM4的PWM功能

    tmc5160_init(); // 初始化TMC5160芯片，设置芯片号和默认模式,使能芯片的电机驱动

    tmc5160_mode(&TMC5160_Chip1); // 设置TMC5160芯片1为位置式步进
    tmc5160_mode(&TMC5160_Chip2); // 设置TMC5160芯片2为位置式步进

    while(1)
    {
        Process_CAN_Commands(); // 处理CAN命令
        HAL_IWDG_Refresh(&hiwdg); // 喂狗
    }


}
/* -1- END 主循环函数 */

/* -2- START 中断回调函数 */

/****
 * @ 原型: void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
 * @ 输入: CAN_HandleTypeDef *hcan : 指向CAN句柄的指针，用于访问CAN外设的相关信息和状态
 * @ 输出: void
 * @ 说明: CAN接收中断回调函数，当CAN接收到消息时被调用，从CAN接收FIFO0中读取消息并将数据放入命令队列中，增加接收计数
********/
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[CMD_LENGTH];
    uint8_t ret = FALSE;

    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data) == HAL_OK)
    {
        ret=CmdQueue_insert(&CmdQueue,rx_data);
        if(ret == TRUE)
        {
            Receive_Count++;
        }
        else
        {
            // 队列已满，处理溢出情况
        }
    }
}

/****
 * @ 原型: void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
 * @ 输入: SPI_HandleTypeDef *hspi : 指向SPI句柄的指针，用于访问SPI外设的相关信息和状态
 * @ 输出: void
 * @ 说明: SPI传输完成回调函数，当SPI传输完成时被调用
********/
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
    if (hspi->Instance == SPI1) {
        // SPI传输完成后的处理逻辑
    }
}
