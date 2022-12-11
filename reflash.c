#include <AT89X52.h>
#include <absacc.h>
#define uchar unsigned char
#define CS_8155 P2_0
#define IOM_8155 P2_1
#define CS_0832 P2_3
#define WR_0832 P3_6
#define XFER_0832 P2_4
#define unEN_0808 P2_7
#define ioSet PBYTE[0x00]
#define ioA PBYTE[0x01]
#define ioC PBYTE[0x03]
#define Vadd PBYTE[0xFF]
extern uchar port;
extern uchar volt;
extern bit flagAuto;

void reflash()
{
	CS_8155 = 0;
	ioC = port;
	CS_8155 = 1;
	unEN_0808 = 0;
	ioC = port;
	while (P3_0 == 1);
	volt = ioA;
	unEN_0808 = 1;
	CS_8155 = 0;
	ioA = volt;
	CS_8155 = 1;
	CS_0832 = 0;
	Vadd = 0;
	CS_0832 = 1;
	
}
