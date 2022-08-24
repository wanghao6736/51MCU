#include <REGX52.h>
#include "MatrixKey.h"
#include "Delay.h"

/**
   * @brief 返回所按键的键码值（教程所附代码）
   * @param None
   * @retval KeyNum 按下键的键码值
   */
unsigned char MatrixKey_old(){
	unsigned char KeyNum = 0;	// 键码值
	
	P1 = 0xFF;	// 将P1置1
	P1_3 = 0;	// 扫描第一列
	if(P1_4 == 0){ Delay(20); while(P1_4 == 0); Delay(20); KeyNum = 13;	}
	if(P1_5 == 0){ Delay(20); while(P1_5 == 0); Delay(20); KeyNum = 9;	}
	if(P1_6 == 0){ Delay(20); while(P1_6 == 0); Delay(20); KeyNum = 5;	}
	if(P1_7 == 0){ Delay(20); while(P1_7 == 0); Delay(20); KeyNum = 1;	}
	
	P1 = 0xFF;
	P1_2 = 0;	// 扫描第二列
	if(P1_4 == 0){ Delay(20); while(P1_4 == 0); Delay(20); KeyNum = 14;	}
	if(P1_5 == 0){ Delay(20); while(P1_5 == 0); Delay(20); KeyNum = 10;	}
	if(P1_6 == 0){ Delay(20); while(P1_6 == 0); Delay(20); KeyNum = 6;	}
	if(P1_7 == 0){ Delay(20); while(P1_7 == 0); Delay(20); KeyNum = 2;	}
	
	P1 = 0xFF;
	P1_1 = 0;	// 扫描第三列
	if(P1_4 == 0){ Delay(20); while(P1_4 == 0); Delay(20); KeyNum = 15;	}
	if(P1_5 == 0){ Delay(20); while(P1_5 == 0); Delay(20); KeyNum = 11;	}
	if(P1_6 == 0){ Delay(20); while(P1_6 == 0); Delay(20); KeyNum = 7;	}
	if(P1_7 == 0){ Delay(20); while(P1_7 == 0); Delay(20); KeyNum = 3;	}
	
	P1 = 0xFF;
	P1_0 = 0;	// 扫描第四列
	if(P1_4 == 0){ Delay(20); while(P1_4 == 0); Delay(20); KeyNum = 16;	}
	if(P1_5 == 0){ Delay(20); while(P1_5 == 0); Delay(20); KeyNum = 12;	}
	if(P1_6 == 0){ Delay(20); while(P1_6 == 0); Delay(20); KeyNum = 8;	}
	if(P1_7 == 0){ Delay(20); while(P1_7 == 0); Delay(20); KeyNum = 4;	}
	
	return KeyNum;
}
/**
   * @brief 返回所按键的键码值（个人优化代码）
   * @param None
   * @retval KeyNum 按下键的键码值
   */
unsigned char MatrixKey(){
    unsigned char KeyNum = 0, temp = 0;
    unsigned char col = 0, row = 0;
    
    for (col=0; col < 4; col++)     // 开始列扫描
    {
        P1 = ~(0x08 >> col);        // 扫描第 col + 1 列，即依次设置 P1_0~P1_3 为零
        for (row=0; row < 4; row++) // 开始扫描行
        {
            temp = ~(0x80 >> row);  // 假设第 row + 1 行为被按下的按键所在行，即依次检测 P1_7~P1_4 是否为零
            if ((P1 & 0xF0) == (temp & 0xF0)){  // 检测 P1 高四位中为零的位，判断假设是否成立
                Delay(20);          // 按下消抖
                while((P1 & 0xF0) == (temp & 0xF0));   // 按下稳定阶段
                Delay(20);          // 松手消抖
                KeyNum = row * 4 + col + 1;     // 设置键码值
            }
        }
    }
    return KeyNum;
}