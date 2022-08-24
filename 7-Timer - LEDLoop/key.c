#include <REGX52.H>
#include "Delay.h"

unsigned int key(){
	unsigned int keyNum = 0;
	
	if(P3_1 == 0){Delay(20); while(P3_1 == 0); Delay(20); keyNum = 1;}
	
	return keyNum;
}