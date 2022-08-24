#include<REGX52.H>
#include"Nixie.h"

void main(){ // 数码管显示
	int idx = 1;
	while(1){
		Nixie(idx, idx); // 在数码管的第1位置显示1
		idx = idx % 8 + 1;
	}
}