#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "ADC0808.h"

void Init0808()
{
	unEN_0808 = 0;
	EA = 0;
	//ES = 1;
	port = P1;
	port = port & 0x0F;
	ioC = port;
	//EA = 1;
	unEN_0808 = 1;
}

uchar getVolt()
{
	uchar tmp;
	unEN_0808 = 0;
	PBYTE[0xFF] = 0;
	while (EOC == 1);
	tmp = PBYTE[0xFF];
	unEN_0808 = 1;
	return tmp;
}

/*
void getVolt() interrupt 4
{
	EA = 0;
	volt = P0;
	ioA = volt;
	RI = 0;
	EA = 1;
}
*/