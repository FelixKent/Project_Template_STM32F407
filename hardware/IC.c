#include "stm32f4xx.h"                  // Device header
#include "IC.h"

/**
  * 函    数：输入捕获初始化
  * 参    数：无
  * 返 回 值：无
  */
void IC_Init(void)
{
	
	/*设置中断*/
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	NVIC_InitStructure.NVIC_IRQChannel = IC_TIM_IQR;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
	
	
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(IC_TIM_CLK, ENABLE);			//开启TIM的时钟
	RCC_AHB1PeriphClockCmd(IC_GPIO_CLK, ENABLE);		//开启GPIO的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = IC_GPIO_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IC_GPIO_PORT, &GPIO_InitStructure);							//将IC_PIN引脚初始化为上拉输入
	
	GPIO_PinAFConfig(IC_GPIO_PORT,IC_AF_PINSOURCE,IC_GPIO_AF_Selection);
	
	/*配置时钟源*/
	TIM_InternalClockConfig(IC_TIM);		//选择 IC_TIM 为内部时钟，若不调用此函数，TIM默认也为内部时钟，默认 CLK 为 84MHz
	
	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               //计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 84 - 1;               //预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(IC_TIM, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM的时基单元
	
	/*输入捕获初始化*/
	TIM_ICInitTypeDef TIM_ICInitStructure;							//定义结构体变量
	TIM_ICInitStructure.TIM_Channel = IC_TIM_CHANNEL;				//选择配置定时器通道1
	TIM_ICInitStructure.TIM_ICFilter = 0x0F;							//输入滤波器参数，可以过滤信号抖动
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//极性，选择为上升沿触发捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//捕获预分频，选择不分频，每次信号都触发捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//输入信号交叉，选择直通，不交叉
	TIM_PWMIConfig(IC_TIM, &TIM_ICInitStructure);							//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
	

//	TIM_ITConfig(IC_TIM, TIM_IT_CC1, ENABLE);
//	TIM_ClearFlag(IC_TIM, TIM_IT_CC1);	
	
	TIM_SelectInputTrigger(IC_TIM, TIM_TS_TI1FP1);		
	/* 选择从模式: 复位模式 */
	TIM_SelectSlaveMode(IC_TIM, TIM_SlaveMode_Reset);
	
	/*TIM使能*/
	TIM_Cmd(IC_TIM, ENABLE);			//使能TIM，定时器开始运行
}

/**
  * 函    数：获取输入捕获的频率
  * 参    数：无
  * 返 回 值：捕获得到的频率
  */
uint32_t IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1(IC_TIM) + 1);		//测周法得到频率fx = fc / N，这里不执行+1的操作也可,1MHz 来自PSC之后的频率
}