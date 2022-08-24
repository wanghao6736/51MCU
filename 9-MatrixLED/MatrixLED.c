#include <REGX52.H>
#include "Delay.h"

#define LED P0

sbit RCK = P3^5;	// RCLK 存储寄存器时钟输入
sbit SCK = P3^6;	// SRCLK 移位寄存器时钟输入
sbit SER = P3^4;	// SER 串行数据输入

void MatrixLED_Init(){
	SCK = 0;	// 设置时钟初始状态
	RCK = 0;
}

/**
   * @brief 74HC595 写入一个字节数据
   * @param byte 要写入的数据
   * @retval 无
   */
void _74HC595_WriteByte(unsigned char byte){	// 串行读入，并行输出
	unsigned char ibit;
	for(ibit = 0; ibit < 8; ibit++){
		SER = byte & (0x80 >> ibit);	// 按位进行串行数据读入
		SCK = 1;	// 给高电平，输入位数据并移位
		SCK = 0;	// 重置为低电平
	}
	RCK = 1;	// 给高电平，输入字节数据并移位
	RCK = 0;	// 重置为低电平
}

/**
   * @brief LED 点阵屏显示一列数据
   * @param col 要显示的列，0-7（右）
   * @param Data 要显示的数据，高位在上，1-亮
   * @retval 无
   */
void MatrixLED_ShowCol(unsigned char col, Data){
	_74HC595_WriteByte(Data);
	LED = ~(0x80 >> col);	// 选择列
	Delay(1);
	LED = 0xFF;	// 段码清零
}