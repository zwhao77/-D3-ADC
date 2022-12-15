#include "reflash.h"

static uchar autoNum;		 // 用于自动模式下统计读取数据次数
static uchar tmport;		 // 用于判断端口切换
static bit lastFlag; // 记录上一次的autoflag状态

void timer1() interrupt 3
{
	autoNum++;
	TH1 = 0x24;
	TL1 = 0xFA;	
}

void reflash()
{
	uchar i;
	// 若为自动模式，则在50*20=1000ms后切换
	if (flagAuto == 1)
	{
		if (lastFlag != flagAuto)
		{
			Init50ms();
		}
		if (autoNum > (2 * 20))
		{
			autoNum = 0;
			port++;
			if (port > 7)
			{
				port = 0;
			}
		}
	}
	else
	{
		Stop50ms();
		autoNum = 0;
		port = P1;
		port = port & 0x0F;
	}
	lastFlag = flagAuto;
	// debug:读取滤波方式
	filt = P1;
	filt = filt & 0xF0;
	filt = filt >> 4;
	if (filt > 10)
	{
		filt = 10;
	}
	pushFilt();
	// 数据刷新
	pushPort();
	if (tmport != port) // 判断端口切换，切换后初始数据直接读取，避免限幅滤波失效
	{
		delay_nms(100);
		volt = getVolt();
		for (i = 0; i < 5; i++)
		{
			slidV[i] = volt;
		}
		tmport = port;
	}
	else
	{
		volt = filtFuns[filt](); // 滤波功能函数指针数组，功能号见下
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