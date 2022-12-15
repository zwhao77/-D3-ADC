#ifndef _DAC0832_H
#define _DAC0832_H

#define CS_0832 P2_3
#define XFER_0832 P2_4

#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"

void Init0832();
void reflash0832();

#endif