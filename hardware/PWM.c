#include "stm32f4xx.h"                  // Device header
#include "PWM.h"

/**
  * 函    数：PWM初始化
  * 参    数：无
  * 返 回 值：无
  */
void PWM_Init(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(PWM_TIM_CLK, ENABLE);			//开启TIM的时钟
	RCC_AHB1PeriphClockCmd(PWM_OUT_GPIO_CLK, ENABLE);		//开启GPIO的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = PWM_OUT_PIN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PWM_OUT_GPIO_PORT, &GPIO_InitStructure);				//将PA1引脚初始化为复用推挽输出	
																	//受外设控制的引脚，均需要配置为复用模式
	
	GPIO_PinAFConfig(PWM_OUT_GPIO_PORT,PWM_OUT_PINSOURCE,PWM_OUT_GPIO_AF_Selection);
	/*配置时钟源*/
	TIM_InternalClockConfig(PWM_TIM);		//选择TIM为内部时钟，若不调用此函数，TIM默认也为内部时钟
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = PWM_TIM_ARR - 1;				//计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84 - 1;				//预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(PWM_TIM, &TIM_TimeBaseInitStructure);          //将结构体变量交给TIM_TimeBaseInit，配置TIM的时基单元
	
	/*输出比较初始化*/ 
	TIM_OCInitTypeDef TIM_OCInitStructure;							//定义结构体变量
	TIM_OCStructInit(&TIM_OCInitStructure);                         //结构体初始化，若结构体没有完整赋值
	                                                                //则最好执行此函数，给结构体所有成员都赋一个默认值
	                                                                //避免结构体初值不确定的问题
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;               //输出比较模式，选择PWM模式1,此处需要额外修改
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;       //输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;								//初始的CCR值
	TIM_OC1Init(PWM_TIM, &TIM_OCInitStructure);                     //将结构体变量交给TIM_OC1Init，配置TIM的输出比较通道1
	
	
	TIM_OC1PreloadConfig(PWM_TIM, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(PWM_TIM, ENABLE);
	
	/*TIM使能*/
	TIM_Cmd(PWM_TIM, ENABLE);			//使能TIM，定时器开始运行
}

/**
  * 函    数：PWM设置CCR
  * 参    数：Compare 要写入的CCR的值，范围：0~100
  * 返 回 值：无
  * 注意事项：CCR和ARR共同决定占空比，此函数仅设置CCR的值，并不直接是占空比
  *           占空比Duty = CCR / (ARR + 1)
  */
void PWM_SetCompare1(unsigned short int Compare)
{
	TIM_SetCompare1(PWM_TIM, Compare);		//设置CCR1的值
}
