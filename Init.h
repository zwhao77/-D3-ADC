#ifndef _INIT_H
#define _INIT_H
//泛用宏定义、声明用头文件
#define uchar unsigned char
#define ioSet PBYTE[0x00]//8155的命令字寄存器
#define ioA PBYTE[0x01]//8155的A端口
#define ioC PBYTE[0x03]//8155的C端口

#define ioB PBYTE[0x02]//debug:8155的B端口

#define flagAuto P2_5//控制是否自动切换端口
extern uchar port;//待转换端口
extern uchar volt;//得到的模拟量
extern uchar filt;//debug:滤波方式

void Init();

#endif