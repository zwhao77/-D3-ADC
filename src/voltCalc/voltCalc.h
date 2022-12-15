#ifndef _voltCalc_H
#define _voltCalc_H

#ifndef uchar
#define  uchar unsigned char
#endif

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

#endif