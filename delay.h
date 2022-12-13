#ifndef _DELAY_H
#define _DELAY_H

void delay_nus(unsigned int i);  //延时:i>=12 ,i的最小延时单12 us
void delay_nms(unsigned int n);  //延时n ms
void Init50ms();//初始化50ms定时器
void Stop50ms();

#endif
