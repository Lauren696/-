#include "ds1302.h"  									

uchar hour=0,min=0,sec=0;

sbit SCK = P1^7;		
sbit SDA = P2^3;		
sbit RST = P1^3; 

//д�ֽ�
void Write_Ds1302(unsigned  char temp) 
{
	unsigned char i;
	for (i=0;i<8;i++)     	
	{ 
		SCK = 0;
		SDA = temp&0x01;
		temp>>=1; 
		SCK=1;
	}
}   

//��DS1302�Ĵ���д������
void Write_Ds1302_Byte( unsigned char address,unsigned char dat )     
{
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1; 	_nop_();  
 	Write_Ds1302(address);	
 	Write_Ds1302(dat);		
 	RST=0; 
}

//��DS1302�Ĵ�����������
unsigned char Read_Ds1302_Byte ( unsigned char address )
{
 	unsigned char i,temp=0x00;
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
 	RST=1;	_nop_();
 	Write_Ds1302(address);
 	for (i=0;i<8;i++) 	
 	{		
		SCK=0;
		temp>>=1;	
 		if(SDA)
 		temp|=0x80;	
 		SCK=1;
	} 
 	RST=0;	_nop_();
 	SCK=0;	_nop_();
	SCK=1;	_nop_();
	SDA=0;	_nop_();
	SDA=1;	_nop_();
	return (temp);			
}

void ds1302_init(uchar h,m,s)
{
	Write_Ds1302_Byte(0x84,h);
	Write_Ds1302_Byte(0x82,m);
	Write_Ds1302_Byte(0x80,s);	
}

void ds1302_read()
{
	hour = Read_Ds1302_Byte (0x85);
	min = Read_Ds1302_Byte (0x83);
	sec = Read_Ds1302_Byte (0x81);
}
