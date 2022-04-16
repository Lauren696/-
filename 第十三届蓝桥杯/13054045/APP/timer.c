#include "timer.h"

uchar x=0;
extern uchar d[];
bit func_flag = 0;

extern bit jidian_flag1;//继电器吸合5秒 标志位 5000ms
uint tt = 0;
uint tt2 = 0;
bit L1_mode = 0;
extern bit led3_flag;
bit led3_mode = 0;


void timer0_init(void)		//5毫秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x78;		//设置定时初值
	TH0 = 0xEC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	EA = 1;
	ET0 = 1;
}

void timer1_init(void)		//1毫秒@12.000MHz
{
	AUXR &= 0xBF;		//定时器时钟12T模式
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0x18;		//设置定时初值
	TH1 = 0xFC;		//设置定时初值
	TF1 = 0;		//清除TF1标志
	TR1 = 1;		//定时器1开始计时
	EA = 1;
	ET1 = 1;
}

void timer0_run() interrupt 1
{
//			if(P0==0x10){
//			led3_flag = 1;
//		}
//		if(P0!=0x10){
//			led3_flag = 0;
//		}

	if(jidian_flag1 == 1){
		tt++;
		L1_mode = 1;
		led_light(1);
	}
		if(tt>1000){
			jidian_flag1 = 0;
			tt=0;
			L1_mode = 0;
		}	
}

void timer1_run() interrupt 3
{
	func_flag = 0;
	
	led_scan();
	smg_scan(x+1,d[x]);
	x++;
	if(x>=8) x=0;
	
	if(led3_flag == 1){//0.1秒间隔闪烁 100ms 0.1s = 
		tt2++;
		if(tt2<10){led3_mode = 0;}
		else if(tt2>=10){tt2=0;led3_mode = 1;}
	}
	
	
	
	func_flag = 1;
}
