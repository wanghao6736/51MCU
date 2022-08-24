#include <REG51.H>
#include <INTRINS.H>

void Delay(int ms){ // @11.0592MHz, 延时指定毫秒
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

void main(){ // LED流水灯
	int idx = 0x01;  // 控制点亮的LED位置
	while(1){
		P2 = ~idx;   // 亮灯位置置低电平
		if(idx == 0x80) // 到达最高位，重置亮灯位置
			idx = 0x01;
		else
			idx <<= 1;  // 左移一位，点亮下一颗LED
		Delay(1000);    // 延时1秒
	}
}
