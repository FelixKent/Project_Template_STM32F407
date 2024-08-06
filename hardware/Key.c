#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "Key.h"

/**
  * 函    数：按键初始化
  * 参    数：无
  * 返 回 值：无
  */
void Key_Init(void)
{
	/*开启时钟*/
	RCC_AHB1PeriphClockCmd(KEY1_GPIO_CLK | KEY2_GPIO_CLK, ENABLE); //开启 GPIOA 和 GPIOC 的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = KEY2_PIN;
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
}

/**
  * 函    数：按键获取键码
  * 参    数：无
  * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
  * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
  */
uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;		//定义变量，默认键码值为0
	
	if (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_PIN) == 1)	//读KEY1输入寄存器的状态，如果为1，则代表按键1按下
	{
		while (GPIO_ReadInputDataBit(KEY1_GPIO_PORT, KEY1_PIN) == 1);	//等待按键松手
		KeyNum = 1;												//置键码为1
	}
	
	if (GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_PIN) == 1)			//读PB11输入寄存器的状态，如果为1，则代表按键2按下
	{
		while (GPIO_ReadInputDataBit(KEY2_GPIO_PORT, KEY2_PIN) == 1);	//等待按键松手
		KeyNum = 2;												//置键码为2
	}
	
	return KeyNum;			//返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
}
