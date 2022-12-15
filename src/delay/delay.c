#include "AT89X52.H"

#define uchar unsigned char

extern uchar autoNum;

/// @brief  延时:i>=12 ,i的最小延时单12 us
/// @param i 延时的时间长度，单位纳秒
void delay_nus(unsigned int i)
{
	i = i / 10;
	while (--i)
		;
}
/// @brief 延时n ms
/// @param n 延时时间长度，单位毫秒
void delay_nms(unsigned int n)
{
	n = n + 1;
	while (--n)
		delay_nus(900); // 延时 1ms,同时进行补偿
}

void timer1() interrupt 3
{
	autoNum++;
	TH1 = 0x24;
	TL1 = 0xFA;	
}

void Init50ms()
{
	EA = 0;
	ET1 = 0;
	TR1 = 0;
	TMOD = 0x10;
	TH1 = 0x24;
	TL1 = 0xFA;
	EA = 1;
	ET1 = 1;
	TR1 = 1;
}

void Stop50ms()
{
	EA = 0;
	ET1 = 0;
	TR1 = 0;
}