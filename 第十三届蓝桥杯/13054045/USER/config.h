#ifndef _CONFIG_H
#define _CONFIG_H

#include <STC15F2K60S2.H>
#include "intrins.h"

typedef unsigned char uchar;
typedef unsigned int uint;

#define Y4 P2=(P2&0x1f)|0x80
#define Y5 P2=(P2&0x1f)|0xa0
#define Y6 P2=(P2&0x1f)|0xc0
#define Y7 P2=(P2&0x1f)|0xe0
#define Y0 P2=(P2&0x1f)




#endif