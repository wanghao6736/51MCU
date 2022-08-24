#include <REGX52.h>
#include <INTRINS.h>
#include "LCD1602.h"
#include "Timer0.h"

unsigned int sec, min, hour;

void main(){
	LCD_Init();		// 初始化LCD
	Timer0Init();	// 初始化定时器0
	
	LCD_ShowString(1,1,"Clock:");
	LCD_ShowString(2,1,"  :  :  ");
	
	while(1){		// 显示时间
		LCD_ShowNum(2,1,hour,2);
		LCD_ShowNum(2,4,min,2);
		LCD_ShowNum(2,7,sec,2);
	}
}

void Timer0_Rountine() interrupt 1{		// 定时器T0的中断函数
	static unsigned int Num;
	TL0 = 0x66;		// 重置计数状态
	TH0 = 0xFC;
	Num++;
	if(Num == 1000){	// 1000 ms
		Num = 0;
		sec++;
		if(sec == 60){
			sec = 0;
			min++;
			if(min == 60){
				min = 0;
				hour++;
				if(hour == 24)
					hour = 0;
			}
		}
	}
}