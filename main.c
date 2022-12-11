#include <AT89X52.h>
#include "Init.h"
#include "delay.h"
#include "reflash.h"
#define uchar unsigned char

extern uchar port;
extern bit flagAuto;

void main()
{
	int num = 0;
	Init();
	while (1)
	{
		P2_5 = 1;
		flagAuto = P2_5;
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
		reflash();
		delay_nms(50);
	}
}