#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "IO8155.h"
void Init8155()
{
	CS_8155 = 0;
	IOM_8155 = 1;
	ioSet = 0x8F;
	ioA = volt;
	ioC = port;
	CS_8155 = 1;
}

void pushVolt()
{
	CS_8155 = 0;
	ioA = volt;
	CS_8155 = 1;
}

void pushPort()
{
	CS_8155 = 0;
	ioC = port;
	CS_8155 = 1;
}