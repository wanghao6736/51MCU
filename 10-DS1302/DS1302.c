#include <REGX52.H>

// 寄存器写入地址/指令定义
#define DS1302_SEC		0x80
#define DS1302_MIN		0x82
#define DS1302_HOUR		0x84
#define DS1302_DATE		0x86
#define DS1302_MONTH	0x88
#define DS1302_DAY		0x8A	// 星期几
#define DS1302_YEAR		0x8C
#define DS1302_WP		0x8E	// 写保护

// 引脚定义
sbit DS1302_SCK = P3^6;			// 时钟寄存器脉冲
sbit DS1302_CE  = P3^5;			// 芯片使能
sbit DS1302_IO  = P3^4;			// 输入/输出

unsigned char DS_Date[] = {99,12,31,23,59,55}; //Year,Mon,Date,Hour,Min,Sec;

/**
   * @brief     将BCD编码的十进制数转换为十六进制，反之亦然
   * @param D2H 标识符，1: 10->16，0: 16->10
   * @param num 要转换的数字
   * @retval    转换后的值
   * Example:
   *    BCD_Convert(1, 11) => 17
   *    BCD_Convert(0, a1) => 101
   */
unsigned char BCD_Convert(unsigned char D2H, unsigned char num){
	unsigned char base   = D2H? 10 : 16;
	unsigned char factor = D2H? 16 : 10;
	return num / base * factor + num % base;
}

/**
   * @brief  初始化时钟
   * @param  无
   * @retval 无
   */
void DS1302_Init(){
	DS1302_CE  = 0;
	DS1302_SCK = 0;
}

/**
   * @brief      向DS1302写入一个字节数据
   * @param cmd  写入操作命令 - 一字节
   * @param Data 要写入的数据 - 一字节
   * @retval     无
   */
void DS1302_WriteByte(unsigned char cmd, Data){
	unsigned char idx;	// 按位索引
	DS1302_CE = 1;		// 芯片使能
	for(idx = 0; idx < 8; idx++){	// 写入命令
		DS1302_IO = cmd & (0x01 << idx);
		DS1302_SCK = 1;	// 执行写入操作
		DS1302_SCK = 0;
	}
	
	for(idx = 0; idx < 8; idx++){	// 写入数据
		DS1302_IO = Data & (0x01 << idx);
		DS1302_SCK = 1;
		DS1302_SCK = 0;
	}
	DS1302_CE = 0;	// 置零
}

/**
   * @brief     从DS1302中读取一个字节数据
   * @param cmd 读取操作命令
   * @retval    读取到的数据
   */
unsigned char DS1302_ReadByte(unsigned char cmd){
	unsigned char idx, Data = 0x00;
	DS1302_CE = 1;
	cmd |= 0x01;	// 将指令转换为读指令，省略读取指令的宏定义
	for(idx = 0; idx < 8; idx++){	// 读取命令
		DS1302_IO = cmd & (0x01 << idx);
		DS1302_SCK = 0;	// 调整时序，注意与写入操作的区别
		DS1302_SCK = 1;
	}
	
	for(idx = 0; idx < 8; idx++){
		DS1302_SCK = 1;
		DS1302_SCK = 0;
		if(DS1302_IO)
			Data |= (0x01 << idx);
	}
	DS1302_CE = 0;
	DS1302_IO = 0;	// 读取后将IO设置为0，否则读出的数据会出错
	return Data;
}

/**
   * @brief       设置DS1302的日期和时间
   * @param _date 保存了时间信息的数组，格式为：{Year,Mon,Date,Hour,Min,Sec}
   * @retval      无
   */
void DS1302_SetTime(unsigned char* _date){
	DS1302_WriteByte(DS1302_WP   , 0x00);	// 关闭写保护
	DS1302_WriteByte(DS1302_YEAR , BCD_Convert(1, _date[0]));
	DS1302_WriteByte(DS1302_MONTH, BCD_Convert(1, _date[1]));
	DS1302_WriteByte(DS1302_DATE , BCD_Convert(1, _date[2]));
	DS1302_WriteByte(DS1302_HOUR , BCD_Convert(1, _date[3]));
	DS1302_WriteByte(DS1302_MIN  , BCD_Convert(1, _date[4]));
	DS1302_WriteByte(DS1302_SEC  , BCD_Convert(1, _date[5]));
	DS1302_WriteByte(DS1302_WP   , 0x80);	// 打开写保护
}

/**
   * @brief       读取DS1302的日期和时间
   * @param _date 用来保存时间信息的数组，格式为：{Year,Mon,Date,Hour,Min,Sec}
   * @retval      无
   */
void DS1302_ReadTime(unsigned char* _date){
	_date[0] = BCD_Convert(0, DS1302_ReadByte(DS1302_YEAR ));
	_date[1] = BCD_Convert(0, DS1302_ReadByte(DS1302_MONTH));
	_date[2] = BCD_Convert(0, DS1302_ReadByte(DS1302_DATE ));
	_date[3] = BCD_Convert(0, DS1302_ReadByte(DS1302_HOUR ));
	_date[4] = BCD_Convert(0, DS1302_ReadByte(DS1302_MIN  ));
	_date[5] = BCD_Convert(0, DS1302_ReadByte(DS1302_SEC  ));
}