#include <REGX52.H>
#include <INTRINS.H>

//数码管段码表-[0~9]（数码管LED高电平点亮）
unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void Delay(int ms){		//@11.0592MHz, 延时指定毫秒
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

//数码管显示子函数
void Nixie(unsigned char Location,Number)
{
//	switch(Location)	//位码输出
//	{	//com端给低电平时数码管显示
//		case 1: P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
//		case 2: P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
//		case 3: P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
//		case 4: P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
//		case 5: P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
//		case 6: P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
//		case 7: P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
//		case 8: P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
//	}
    unsigned char index = (0x08 - Location) << 2;   // 0x000x xx00，根据位选信息设置 P2_4~P2_2 的值
    P2 &= 0xE3;     // 0x1110 0011，将 P2_4, P2_3, P2_2 置零
    P2 |= index;    // 将 index 赋值给 P2
	P0 = NixieTable[Number];	//段码输出
	Delay(1);				//显示一段时间
	P0 = 0x00;				//段码清0，消影
}
