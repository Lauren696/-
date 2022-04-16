#ifndef __DS1302_H
#define __DS1302_H

#include "config.h"

//sbit SCK = P1^7;		
//sbit SDA = P2^3;		
//sbit RST = P1^3; 

void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte( unsigned char address );


void ds1302_init(uchar h,m,s);
void ds1302_read();

#endif
