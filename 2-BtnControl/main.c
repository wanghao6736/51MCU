#include <REGX52.H>
#include <INTRINS.H>

void Delay(int ms){	// @11.0592MHz, 延时指定毫秒
	unsigned char i, j;
	while(ms--){
		_nop_();
		i = 2;
		j = 199;
		do{
			while (--j);
		} while (--i);
	}
}

void showBinary(){	// LED显示二进制
	int idx = 0x01;
	while(1){
		if(P3_1==0)			// 如果K1按键按下
		{
			Delay(20);		// 延时消抖
			while(P3_1==0);	// 松手检测
			Delay(20);		// 延时消抖
			
			P2=~idx;		// 设置LED
			if(idx == 0xFF)
				idx = 0x01;
			else
				idx++;
		}
	}
}

void ledOffset(){	// 按键控制LED偏移
	int idx = 0x01;
	P2 = ~idx;
	while(1){
		if(P3_1==0)			// 如果K1按键按下
		{
			Delay(20);		// 延时消抖
			while(P3_1 == 0);	// 松手检测
			Delay(20);		// 延时消抖
			
			if(idx == 0x01)
				idx = 0x80;
			else
				idx = idx >> 1;
			P2 = ~idx;		// LED取反
		}
		if(P3_0 == 0)		// 如果K2按键按下
		{
			Delay(20);		// 延时消抖
			while(P3_0 == 0);	// 松手检测
			Delay(20);		// 延时消抖
			
			if(idx == 0x80)
				idx = 0x01;
			else
				idx = idx << 1;
			P2 = ~idx;		// LED取反
		}
	}
}

void main(){
	ledOffset();
}