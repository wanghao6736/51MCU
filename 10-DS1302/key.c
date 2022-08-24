#include <REGX52.H>
#include "Delay.h"

/**
   * @brief 获取按下的独立按键键码值
   * @param 无
   * @retval kyeNum 被按下的独立按键序号
   */
unsigned char key(){
	unsigned char keyNum = 0;
	
	if(P3_1 == 0){Delay(20); while(P3_1 == 0); Delay(20); keyNum = 1;}
	if(P3_0 == 0){Delay(20); while(P3_0 == 0); Delay(20); keyNum = 2;}
	if(P3_2 == 0){Delay(20); while(P3_2 == 0); Delay(20); keyNum = 3;}
	if(P3_3 == 0){Delay(20); while(P3_3 == 0); Delay(20); keyNum = 4;}
	
	return keyNum;
}