#include <REGX52.H>

/**
   * @brief 串口初始化
   * @param 无
   * @retval 无
   */
void UartInit()		// 9600bps@11.0592MHz
{
	PCON &= 0x7F;	// 波特率不倍速
	SCON = 0x50;	// 8位数据,可变波特率
	TMOD &= 0x0F;	// 设置定时器模式
	TMOD |= 0x20;	// 设置定时器模式
	TL1 = 0xFD;		// 设置定时初始值
	TH1 = 0xFD;		// 设置定时重载值
	ET1 = 0;		// 禁止定时器1中断
	TR1 = 1;		// 定时器1开始计时
	EA = 1;
	ES = 1;
}

/**
   * @brief 发送一个字节数据
   * @param byte 要发送的数据
   * @retval 无
   */
void UartSendByte(unsigned char byte)
{
	SBUF = byte;
	while(!TI);
	TI = 0;			// 发送标志位清零
}

/* 串口中断模板函数
void UartRoutine() interrupt 4{
	if(RI == 1){
		P2 = SBUF;
		UartSendByte(SBUF);
		RI = 0;
	}
}
*/