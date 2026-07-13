#ifndef _TEST_ENCODER_H_
#define _TEST_ENCODER_H_

#include "elaco_main.h"

/****
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 编码器验证测试 (位置模式)
 *        配置编码器接口 → 位置模式运动1圈 →
 *        等待自动定位完成 → 对比X_ENC变化量.
 *        芯片自动处理加减速和定位, 无需手动轮询.
 *        LED匀速闪烁=通过, 快闪4次=故障.
 ********/
void Test_Encoder(void);

#endif
