#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"
#include "IO8155.h"
/// @brief 初始化8155芯片
void Init8155()
{
	CS_8155 = 0;
	IOM_8155 = 1;
	ioSet = 0x8F;//设置为三口均输出，定时器停止工作，禁用中断
	ioA = volt;
	ioC = port;//初始值送出
	CS_8155 = 1;
}
/// @brief 向A口输出转换后电压的数字量
void pushVolt()
{
	CS_8155 = 0;
	ioA = volt;
	CS_8155 = 1;
}
/// @brief 向C口输出待转换端口
void pushPort()
{
	CS_8155 = 0;
	ioC = port;
	CS_8155 = 1;
}