#include <AT89X52.h>
#include <absacc.h>
#include "IO8155.h"
#include "ADC0808.h"
#include "DAC0832.h"
#define uchar unsigned char
#define ioSet PBYTE[0x00]
#define ioA PBYTE[0x01]
#define ioC PBYTE[0x03]
uchar port = 0x01;
uchar volt = 0x08;
bit flagAuto = 0;


void Init()
{
	port = P1;
	port = port & 0x0F;
	P2_5 = 1;
	flagAuto = P2_5;
	Init8155();
	Init0808();
	Init0832();
}
