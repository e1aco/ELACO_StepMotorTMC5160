#include "test_freemodbus.h"

void test_freemodbus(void)
{
    eMBInit(MB_RTU, 0x01, 0, 115200, MB_PAR_NONE); // Modbus RTU 初始化
    eMBEnable(); // 启用 Modbus RTU	
	  while (1)
    {
        HAL_IWDG_Refresh(&hiwdg);   // 喂狗，防止 IWDG 超时复位
        eMBPoll(); // Modbus RTU 主循环
    }
}
