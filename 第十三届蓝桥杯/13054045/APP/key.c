#include "key.h"

uchar key_num = 0;
uchar key_num2 = 0;


void key_scanf()
{
	static uchar key_state=0,hang=0;
	switch(key_state){
		case 0:{
			P32=1;P33=1;P35=0;P34=0;
			if(P32!=1||P33!=1){
				key_state = 1;
			}
		}break;
		case 1:{
			P32=1;P33=1;P35=0;P34=0;
			if(P32!=1||P33!=1){
				if(P32==0)hang=3;
				if(P33==0)hang=4;		
				switch(hang){
					case 3:{
						P32=0;P33=0;P35=1;P34=1;
						if(P35==0){key_num=13;key_state=2;}
						if(P34==0){key_num=17;key_num2=17;key_state=2;}
					}break;
					case 4:{
						P32=0;P33=0;P35=1;P34=1;
						if(P35==0){key_num=12;key_state=2;}
						if(P34==0){key_num=16;key_state=2;}						
					}break;
				}
			}		
			else {
				key_state = 0;
			}
		}break;
		case 2:{
			P32=1;P33=1;P35=0;P34=0;
			if(P32==1&&P33==1){
				key_state = 0;
				key_num2 = 0;//³¤°´
			}
		}break;
	}
}