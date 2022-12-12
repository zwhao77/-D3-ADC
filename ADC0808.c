#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "ADC0808.h"
/// @brief ADC0808的初始化函数
void Init0808()
{
	unEN_0808 = 0;
	port = P1;
	port = port & 0x0F;
	ioC = port;//第一次读取并设置端口
	unEN_0808 = 1;
}
/// @brief 获取当前端口指向的模拟量
/// @return 得到的模拟量
uchar getVolt()
{
	uchar tmp;
	unEN_0808 = 0;
	PBYTE[0xFF] = 0;//虚写启动，后续读取类似，地址均为虚拟
	while (EOC == 1);//由于滤波过程中没有其他任务，故采用等待的方法
	tmp = PBYTE[0xFF];
	unEN_0808 = 1;
	return tmp;
}