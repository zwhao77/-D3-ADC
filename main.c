#include <AT89X52.h>
#include "Init.h"
#include "delay.h"
#include "reflash.h"

void main()
{
	int num = 0;
	Init();
	while (1)
	{
		reflash();
		delay_nms(50);
	}
}