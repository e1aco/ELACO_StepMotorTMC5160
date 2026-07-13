#ifndef _TEST_ENCODER_H_
#define _TEST_ENCODER_H_

#include "elaco_main.h"

/****
 * @ 输入: void
 * @ 输出: void
 * @ 说明: 编码器验证测试
 *        配置编码器接口 → 运动固定步数 → 对比X_ENC变化
 *        LED匀速闪烁=测试通过, 快闪4次=偏差过大.
 ********/
void Test_Encoder(void);

#endif
