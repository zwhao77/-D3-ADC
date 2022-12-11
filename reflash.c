#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "IO8155.h"
#include "ADC0808.h"
#include "DAC0832.h"
#include "voltCalc.h"
int num;
void reflash()
{
	//若为自动模式，则读取50次数据进行一次通道切换
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
	//volt = getVolt();
	volt = filtFuns[7]();
	pushVolt();
	reflash0832();
}
