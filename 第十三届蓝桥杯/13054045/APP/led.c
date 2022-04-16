#include "led.h"

uchar led_wei = 0xff;
uchar led_d[9] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,0x00};

void all_init()
{
	Y4;P0=0xff;
	Y5;P0=0x00;
	Y6;P0=0xff;
	Y7;P0=0xff;
	Y0;
}

void led_scan()
{
	Y4;
	P0 = led_wei;
	Y0;
}

void led_light(uchar a)
{
	led_wei &= led_d[a-1];
}

void led_unlight(uchar a)
{
	led_wei |= ~led_d[a-1];
}