#include "DAC0832.h"
/// @brief 初始化DAC0832芯片
void Init0832()
{
	XFER_0832 = 0;
	CS_0832 = 0;
	ioA = volt;//给出电压
	PBYTE[0xFF] = 0;//虚写启动转换，单缓冲
	CS_0832 = 1;
}
/// @brief 对DAC0832芯片进行状态更新
void reflash0832()
{
	CS_0832 = 0;
	PBYTE[0xFF] = 0;//虚写启动转换，单缓冲
	CS_0832 = 1;
}