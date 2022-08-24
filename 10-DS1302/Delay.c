/**
   * @brief 延时函数
   * @param xms 要延时的时间，单位为毫秒
   * @retval 无
   */
void Delay(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}