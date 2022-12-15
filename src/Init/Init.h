#ifndef _INIT_H
#define _INIT_H
//泛用宏定义、声明用头文件
#include <AT89X52.h>
#include "IO8155.h"
#include "ADC0808.h"
#include "DAC0832.h"

#define  uchar unsigned char

#define flagAuto P2_5//控制是否自动切换端口
extern uchar port;//待转换端口
extern uchar volt;//得到的模拟量
extern uchar filt;//debug:滤波方式

void Init();

#endif