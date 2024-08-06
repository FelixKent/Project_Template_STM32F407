#include "LED.h"

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void LED_Init(void)
{
	/*开启时钟*/
	RCC_AHB1PeriphClockCmd(LED_RED_GPIO_CLK | LED_GREEN_GPIO_CLK | LED_BLUE_GPIO_CLK, ENABLE);		//开启GPIO的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = LED_RED_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED_RED_GPIO_PORT, &GPIO_InitStructure);			
	
	GPIO_InitStructure.GPIO_Pin = LED_GREEN_GPIO_CLK;
	GPIO_Init(LED_GREEN_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_BLUE_PIN;
	GPIO_Init(LED_BLUE_GPIO_PORT, &GPIO_InitStructure);	
	
	/*设置GPIO初始化后的默认电平*/
	LED_RGB_OFF;
}
