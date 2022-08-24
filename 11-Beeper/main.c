#include <REGX52.H>
#include "key.h"
#include "Buzzer.h"

unsigned char keyN;

void main(){
	while(1){
		keyN = key();
		if(keyN){
			Buzzer_Beep(100);
		}
	}
}