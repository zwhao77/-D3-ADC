#ifndef _ADC0808_H
#define _ADC0808_H

#define unEN_0808 P2_7
#define EOC P3_0

#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"

void Init0808();
unsigned char getVolt();

#endif