#include "headfile.h"
//L3闪烁还是有点问题
extern bit func_flag;
extern uchar key_num;
extern uchar key_num2;
extern uchar hour,min,sec;
uint temp = 0;//三位数 23.4 234

uchar jm = 1;//3种界面 1-温度 2-时间 3-参数
uchar mode = 1;//2种工作模式 1-温度控制 2-时间控制
uint wendu_can = 230;//23度
uchar hour10=0,min10=0,sec10=0;//十进制

bit jidian_flag1 = 0;
extern bit L1_mode;
bit led3_flag = 0;//L3 0.1秒闪烁标志位
extern bit led3_mode;


void main()
{
	all_init();
	timer1_init();
	timer0_init();
	ds1302_init(0x23,0x59,0x50);//上电为23时25分
	while(1)
	{
		if(func_flag == 1){
			key_scanf();
			ds1302_read();
			temp = temp_read();
			
			func_flag = 0;
		}
		
		if(P0==0x10){
			led3_flag = 1;
		}
		else if(P0!=0x10){
			led3_flag = 0;
		}
		if(led3_mode == 1){led_light(3);}
		else if(led3_mode == 0){led_unlight(3);}

		
		hour10 = hour/16*10+hour%16;
		min10 = min/16*10+min%16;
		sec10 = sec/16*10+sec%16;	
		
		if(key_num == 12){//界面控制
			key_num = 0;
			jm++;
			if(jm>3)jm=1;
		}
		if(key_num == 13){//模式控制
			key_num = 0;
			if(mode == 1)	mode = 2;
			else if(mode == 2) mode = 1;
		}
	///======界面===========
		if(jm == 1){//温度显示
			smg_d(25,1,16,16,16,temp/100,temp%100/10+32,temp%10);
		}
		if(jm == 2){//时间显示
			smg_d(25,2,16,hour/16,hour%16,17,min/16,min%16);
			if(key_num2 == 17){
				smg_d(25,2,16,min/16,min%16,17,sec/16,sec%16);
			}
		}
		if(jm == 3){//参数设置
			if(key_num == 16){//温度加1
				key_num = 0;
				wendu_can+=10;
				if(wendu_can>990){
					wendu_can = 100;
				}
			}
			if(key_num == 17){//温度减1
				key_num = 0;
				wendu_can-=10;
				if(wendu_can<100){
					wendu_can = 990;
				}
			}
			smg_d(25,3,16,16,16,16,wendu_can/100,wendu_can%100/10);
		}
	//===========
		
		//==控制
		if(mode == 1){//温度控制
//			Y5;P0=0x00;Y0;///
			if(temp>wendu_can){
				Y5;
				P0 = 0x10;
				Y0;
			}
			else {
				Y5;
				P0 = 0x00;
				Y0;
			}
		}
		if(mode == 2){//时间显示
//			Y5;P0=0x00;Y0;///
			if((min10==0) && (sec10==0)){//整点
				jidian_flag1 = 1;//整点继电器吸合5秒后断开
			}
			if(L1_mode==1){Y5;P0=0x10;Y0;led_light(1);}
			if(L1_mode==0){Y5;P0=0x00;Y0;led_unlight(1);}		
		}
		//====L2====
		if(mode == 1){
			led_light(2);
		}
		else {
			led_unlight(2);
		}
		//======L3===
//		if(P0==0x10){
//			led3_flag = 1;
//		}
//		if(P0!=0x10){
//			led3_flag = 0;
//		}
		
//		if(led3_mode == 1){led_light(3);}
//		if(led3_mode == 0){led_unlight(3);}

		
	}
}