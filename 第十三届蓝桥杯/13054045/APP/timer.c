#include "timer.h"

uchar x=0;
extern uchar d[];
bit func_flag = 0;

extern bit jidian_flag1;//�̵�������5�� ��־λ 5000ms
uint tt = 0;
uint tt2 = 0;
bit L1_mode = 0;
extern bit led3_flag;
bit led3_mode = 0;


void timer0_init(void)		//5����@12.000MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0x78;		//���ö�ʱ��ֵ
	TH0 = 0xEC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	EA = 1;
	ET0 = 1;
}

void timer1_init(void)		//1����@12.000MHz
{
	AUXR &= 0xBF;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0x18;		//���ö�ʱ��ֵ
	TH1 = 0xFC;		//���ö�ʱ��ֵ
	TF1 = 0;		//���TF1��־
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
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
	
	if(led3_flag == 1){//0.1������˸ 100ms 0.1s = 
		tt2++;
		if(tt2<10){led3_mode = 0;}
		else if(tt2>=10){tt2=0;led3_mode = 1;}
	}
	
	
	
	func_flag = 1;
}
