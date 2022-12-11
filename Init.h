#ifndef _INIT_H
#define _INIT_H

#define uchar unsigned char
#define ioSet PBYTE[0x00]
#define ioA PBYTE[0x01]
#define ioC PBYTE[0x03]
#define flagAuto P2_5
extern uchar port;
extern uchar volt;

void Init();

#endif