#include <REGX52.H>
#include "Key.h"
#include "Timer0.h"
#include "DS1302.h"
#include "LCD1602.h"

unsigned char keyN, MODE, selectTime, selectTimeFlag;

void ShowTime(unsigned char* date){
	unsigned char idx, col, start;
	if(selectTime < 6)
		LCD_ShowString(1, 10, "SET ");	// 此条件为设置时间的显示
	else{
		LCD_ShowString(1, 10, "SHOW");	// 此条件为读取时间的显示
		DS1302_ReadTime(date);
	}
	for(idx = 0; idx < 6; idx++){	// 根据idx索引确定显示位置
		col = idx/3 + 1;	// 显示在第几列
		start = 1 + (idx%3) * 3;	// 显示起始位置
		if(idx != selectTime)		// 显示未被selectTime标记的时间位
			LCD_ShowNum(col, start, date[idx], 2);
		else	// 控制被selectTime标记的时间位闪烁
			selectTimeFlag? LCD_ShowString(col, start, "  ") : LCD_ShowNum(col, start, date[idx], 2);
	}
}

void SetTime(unsigned char* date){
	unsigned char date2 = 0;
	if(keyN == 2){	// 按键2按下，选择修改内容（Year,Mon,Date,Hour,Min,Sec）
		selectTime++;
		selectTime %= 6;
	}
	if(keyN == 3){	// 按键3按下，加1
		date[selectTime]++;
		date[0] %= 100;	// 年 0~99（2000~2099）
		date[1] = (date[1] % 13) ? (date[1] % 13) : 1;	//月 1~12
		date[3] %= 24;	// 时 0~23
		date[4] %= 60;	// 分 0~59
		date[5] %= 60;	// 秒 0~59
		switch(date[1]){	// 天数检查
			case 1: 
			case 3: 
			case 5: 
			case 7: 
			case 8: 
			case 10: 
			case 12: date2 = 32; break;	// 大月 1~31
			case 4: 
			case 6: 
			case 9: 
			case 11: date2 = 31; break;	// 小月 1~30
			case 2:  date2 = (date[0] % 4) ? 29 : 30; break;	// 平/闰月 1~28/29
		}
		date[2] = (date[2] % date2) ? (date[2] % date2) : 1;	//日
	}
	if(keyN == 4){	// 按键4按下，减1
		date[selectTime]--;
		date[0] = date[0] <= 99? date[0] : 99;	// 无符号数，不会小于零
		date[1] = date[1] ? date[1] : 12;
		date[3] = date[3] <= 23? date[3] : 23;
		date[4] = date[4] <= 59? date[4] : 59;
		date[5] = date[5] <= 59? date[5] : 59;
		switch(date[1]){	// 天数检查
			case 1: 
			case 3: 
			case 5: 
			case 7: 
			case 8: 
			case 10: 
			case 12: date2 = 31; break;	// 大月
			case 4: 
			case 6: 
			case 9: 
			case 11: date2 = 30; break;	// 小月
			case 2:  date2 = (date[0] % 4) ? 28 : 29; break;	// 平/闰月
		}
		date[2] = (date[2] % date2) ? (date[2] % date2) : date2; // 日
	}
}

void Timer0_Rountine() interrupt 1{	// 定时器控制修改位闪烁标志
	static unsigned int sec;
	TL0 = 0x66;		// 重置计数状态
	TH0 = 0xFC;
	sec++;
	if(sec == 500){	// 500毫秒闪烁一次
		selectTimeFlag = !selectTimeFlag;
		sec = 0;
	}
}

void main(){
	LCD_Init();
	Timer0Init();
	DS1302_Init();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	DS1302_SetTime(DS_Date);
	
	while(1){
		keyN = key();
		if(keyN == 1){	// 按键1按下，切换功能
			if(MODE) 	// 若MODE为1，则按键按下时将时间写入DS1302，然后切换为显示模式
				DS1302_SetTime(DS_Date);
			MODE = !MODE;
		}
		if(MODE)	// 设置时间
			SetTime(DS_Date);
		else		// 读取时间
			selectTime += 6;	// 记录当前selectTime值，并保证读取时不闪烁，即ShowTime()中的idx != selectTime
		ShowTime(DS_Date);		// 显示时间
		selectTime %= 6;		// 执行读取操作后恢复selectTime的值
	}
}