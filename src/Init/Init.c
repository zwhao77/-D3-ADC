#include "Init.h"

extern uchar slidV[5]; // 滑动平均
uchar port = 0x01; // 待转换端口
uchar volt = 0x08; // 得到的模拟量
uchar filt = 0x07; // debug:用于切换滤波方式

/*
 *依次进行三个元件的初始化，为后续功能预留
*/
void Init()
{
	uchar i;
	Init8155();
	Init0808();
	Init0832();
	volt = getVolt();
	for (i = 0; i < 5; i++)
	{
		slidV[i] = volt;
	}
	pushVolt();
}
