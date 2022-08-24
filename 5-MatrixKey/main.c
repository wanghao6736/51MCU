#include <REGX52.h>
#include "Delay.h"
#include "LCD1602.h"
#include "MatrixKey.h"

unsigned char Num;
void main()
{
	unsigned int pwd = 0;
	int count = 0;
	LCD_Init();
	LCD_ShowString(1,1,"Password:");
	while(1){
		// Num = MatrixKey_old();
        Num = MatrixKey();
		if(Num > 0 && Num < 11 && count < 4){	// 输入4位密码
			pwd *= 10;	// 密码左移一位
			pwd += Num % 10;	// 加入新输入的数字，数字0由10 % 10表示
			LCD_ShowNum(2,1,pwd,4);
			count++;	// 更新输入位数
		}
		if(Num == 11){	// 按下确认键
			if(pwd == 4578)
				LCD_ShowString(1,13,"OK! ");
			else
				LCD_ShowString(1,13,"ERR!");
			pwd = 0;	// 重置输入状态
			count = 0;
			LCD_ShowNum(2,1,pwd,4);
		}
		if(Num == 12){	// 按下取消键
			pwd = 0;
			count = 0;
			LCD_ShowNum(2,1,pwd,4);
		}
		if(Num == 13){	// 按下退格键
			pwd /= 10;
			if(count > 0)
				count--;
			LCD_ShowNum(2,1,pwd,4);
		}
	}
}