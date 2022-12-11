#include <AT89X52.h>
#include <absacc.h>
#define uchar unsigned char
#define CS_8155 P2_0
#define IOM_8155 P2_1
#define CS_0832 P2_2
#define XFER_0832 P2_4
#define unEN_0808 P2_7
#define ioSet PBYTE[0x00]
#define ioA PBYTE[0x01]
#define ioC PBYTE[0x03]
uchar port = 0x01;
uchar volt = 0x08;
bit flagAuto = 0;

void getVolt() interrupt 4
{
	EA = 0;
	volt = P0;
	ioA = volt;
	RI = 0;
	EA = 1;
}

void Init8155()
{
	CS_8155 = 0;
	IOM_8155 = 1;
	ioSet = 0x8F;
	ioA = volt;
	ioC = port;
	CS_8155 = 1;
}

void Init0832()
{
	XFER_0832 = 0;
	CS_0832 = 0;
	ioA = volt;
	CS_0832 = 1;
}

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
