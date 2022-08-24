#ifndef __DS1302_H__
#define __DS1302_H__

extern unsigned char DS_Date[];

void DS1302_Init();
void DS1302_SetTime(unsigned char* _date);
void DS1302_ReadTime(unsigned char* _date);

#endif