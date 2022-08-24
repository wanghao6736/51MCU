#include <REGX52.H>
#include "UART.h"

void main(){

	UartInit();
	while(1){
		//UartSendByte(sec);	//波特率过快可能导致串口发送的数据接收异常，通过Delay()函数延时后可正常接收
	}
}

void UartRoutine() interrupt 4{
	if(RI == 1){
		P2 = SBUF;
		UartSendByte(SBUF);
		RI = 0;
	}
}