#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "DAC0832.h"

void Init0832()
{
	XFER_0832 = 0;
	CS_0832 = 0;
	ioA = volt;
	CS_0832 = 1;
}

void reflash0832()
{
	CS_0832 = 0;
	PBYTE[0xFF] = 0;
	CS_0832 = 1;
}