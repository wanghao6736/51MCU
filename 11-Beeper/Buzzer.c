#include <REGX52.H>
#include <INTRINS.H>

// 绑定蜂鸣器端口
sbit Buzzer = P1^5;

/**
   * @brief  延时500微秒
   * @param  无
   * @retval 无
   */
void Buzzer_Delay500us(){	// @11.0592MHz
	unsigned char i;
	_nop_();
	i = 227;
	while (--i);
}

/**
   * @brief     以1000Hz的频率蜂鸣
   * @param xms 蜂鸣的时长
   * @retval    无
   */
void Buzzer_Beep(unsigned int xms){
	unsigned int t;
	for(t = 0; t < xms; t++){
		Buzzer = !Buzzer;
		Buzzer_Delay500us();	// 延时500us，周期为1ms，频率为1000Hz
	}
}