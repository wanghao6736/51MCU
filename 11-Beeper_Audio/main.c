#include <REGX52.H>
#include "Delay.h"
#include "Timer0.h"

//绑定蜂鸣器端口
sbit Buzzer = P1^5;

unsigned char selectFreq, selectNote;
unsigned int Freq2Note[] = {
	63464,63576,63690,63791,63891,63980,64069,64151,64228,64302,64371,64437,
	64498,64556,64611,64663,64712,64758,64802,64843,64882,64918,64953,64986,
	65017,65046,65073,65099,65124,65147,65168,65189,65208,65227,65244,65260
};
unsigned char NotesIndex[] = {
	12, 4,
	12, 4,
	19, 4,
	19, 4,
	21, 4,
	21, 4,
	19, 4 + 4,
	17, 4,
	17, 4,
	16, 4,
	16, 4,
	14, 4,
	14, 4,
	12, 4 + 4
};

void main(){
	Timer0Init();
	while(1){
		selectFreq = NotesIndex[selectNote];
		selectNote++;
		Delay(125 * NotesIndex[selectNote]);
		selectNote++;
		selectNote %= 28;
		TR0 = 0;
		Delay(5);
		TR0 = 1;
	}
}

void Timer0_Rountine() interrupt 1{
	TL0 = Freq2Note[selectFreq] % 256;	// 重置计数状态
	TH0 = Freq2Note[selectFreq] / 256;
	Buzzer = !Buzzer;	// 1ms翻转一次，频率为500Hz
}