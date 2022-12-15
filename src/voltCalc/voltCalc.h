#ifndef _voltCalc_H
#define _voltCalc_H

#include <AT89X52.h>
#include <math.h>
#include "Init.h"
#include "ADC0808.h"
#include "delay.h"

#define  uchar unsigned char

#define DV 5
#define LV 50
#define LASTA 0.3
#define MAXDEB 5

uchar avgFilt();
uchar slideavgFilt();
uchar speedFilt();
uchar amplimtFilt();
uchar midFilt();
uchar midavgFilt();
uchar limtvgFilt();
uchar onlastFilt();
uchar weislidFlit();
uchar debFilt();
uchar debavgFilt();

extern uchar (*filtFuns[11]) ();

extern uchar slidV[5];
extern uchar weight[5];
extern uchar debnum;

#endif