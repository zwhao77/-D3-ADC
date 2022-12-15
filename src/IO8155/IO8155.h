#ifndef _IO8155_H
#define _IO8155_H

#define CS_8155 P2_0
#define IOM_8155 P2_1

#include <AT89X52.h>
#include <absacc.h>
#include "Init.h"

#define ioSet PBYTE[0x00]//8155的命令字寄存器
#define ioA PBYTE[0x01]//8155的A端口
#define ioC PBYTE[0x03]//8155的C端口

#define ioB PBYTE[0x02]//debug:8155的B端口

void Init8155();
void pushVolt();
void pushPort();
void pushFilt();//debug
#endif