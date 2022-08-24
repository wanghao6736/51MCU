#include <REGX52.H>

void Timer0Init(){	// 1毫秒@11.0592MHz
	TMOD &= 0xF0;	// 设置定时器模式
	TMOD |= 0x01;	// 设置定时器模式
	TL0 = 0x66;		// 设置定时初始值-低位
	TH0 = 0xFC;		// 设置定时初始值-高位
	TF0 = 0;		// 清除TF0标志
	TR0 = 1;		// 定时器0开始计时
	EA = 1;			// 允许中断
	ET0 = 1;		// 允许T0中断
}

/*
void Timer0_Rountine() interrupt 1{
	static unsigned int sec;
	TL0 = 0x66;		// 重置计数状态
	TH0 = 0xFC;
	sec++;
	if(sec == 500){
		
	}
}
*/