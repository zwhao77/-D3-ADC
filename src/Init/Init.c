#include <AT89X52.h>
#include <absacc.h>
#include "IO8155.h"
#include "ADC0808.h"
#include "DAC0832.h"
#define uchar unsigned char
#define ioSet PBYTE[0x00] // 8155的命令字寄存器
#define ioA PBYTE[0x01]	  // 8155的A端口
#define ioC PBYTE[0x03]	  // 8155的C端口

#define ioB PBYTE[0x02] // debug:8155的B端口

uchar port = 0x01; // 待转换端口
uchar volt = 0x08; // 得到的模拟量
uchar filt = 0x07; // debug:用于切换滤波方式

extern uchar slidV[5]; // 滑动平均

/// @brief 依次进行三个元件的初始化，为后续功能预留
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
