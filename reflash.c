#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "IO8155.h"
#include "ADC0808.h"
#include "DAC0832.h"
#include "voltCalc.h"
#include "delay.h"
int num;//用于自动模式下统计读取数据次数
static uchar tmport;//用于判断端口切换
void reflash()
{
	//若为自动模式，则在一个端口读取50次数据进行一次端口切换
	if (flagAuto == 1)
	{
		num++;
		if (num > 50)
		{
			num = 0;
			port++;
			if (port > 7)
			{
				port = 0;
			}
		}
	}
	else
	{
		num = 0;
		port = P1;
		port = port & 0x0F;
	}
	//数据刷新
	pushPort();
	if (tmport =! port)//判断端口切换，切换后初始数据直接读取，避免限幅滤波失效
	{
		delay_nms(100);
		volt = getVolt();
		tmport = port;
	}
	else
	{
		volt = filtFuns[port+4]();//滤波功能函数指针数组，功能号见下
	}
	pushVolt();
	reflash0832();
}
/*
| 序号 | 功能         | 函数名               |
| ---- | ------------ | -------------------- |
| 0    | 平均值滤波   | uchar avgFilt()      |
| 1    | 滑动平均滤波 | uchar slideavgFilt() |
| 2    | 限速滤波     | uchar speedFilt()    |
| 3    | 限幅滤波     | uchar amplimtFilt()  |
| 4    | 中位数滤波   | uchar midFilt()      |
| 5    | 中位平均滤波 | uchar midavgFilt()   |
| 6    | 限幅平均滤波 | uchar limtvgFilt()   |
| 7    | 一阶滞后滤波 | uchar onlastFilt()   |
| 8    | 加权递推     | uchar weislidFlit()  |
| 9    | 消抖滤波     | uchar debFilt()      |
| 10   | 限幅消抖滤波 | uchar debavgFilt()   |
*/