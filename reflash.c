#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "IO8155.h"
#include "ADC0808.h"
#include "DAC0832.h"

int num;

void reflash()
{
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
	pushPort();
	getVolt();
	pushVolt();
	reflash0832();
}
