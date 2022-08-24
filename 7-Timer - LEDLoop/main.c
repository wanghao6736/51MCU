#include <REGX52.h>
#include <INTRINS.h>
#include "Key.h"
#include "LCD1602.h"
#include "Timer0.h"

int mode;

void main(){
	unsigned int num = 0;
	// LCD_Init();
	Timer0Init();
	
	// LCD_ShowString(1,1,"Clock:");
	P2 = 0xFE;
	while(1){
		num = key();
		if(num){
			mode++;
			mode %= 2;
		}
	}
}

void Timer0_Rountine() interrupt 1{
	static unsigned int sec;
	TL0 = 0x66;		// 重置计数状态
	TH0 = 0xFC;
	sec++;
	if(sec == 500){
		if(mode){	// 向左流动
			P2 = _cror_(P2,1);
		}else{		// 向右流动
			P2 = _crol_(P2,1);
		}
		sec = 0;
	}
}