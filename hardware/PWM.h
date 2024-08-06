#ifndef __PWM_H
#define __PWM_H

// 该例程配置为 PA1 接口输出 PWM 波，使用的定时器为 TIM2
#define		PWM_TIM							TIM2
#define		PWM_TIM_CLK						RCC_APB1Periph_TIM2
#define		PWM_OUT_GPIO_AF_Selection		GPIO_AF_TIM2

#define		PWM_OUT_PIN			GPIO_Pin_5
#define		PWM_OUT_GPIO_PORT	GPIOA
#define		PWM_OUT_GPIO_CLK	RCC_AHB1Periph_GPIOA
#define		PWM_OUT_PINSOURCE	GPIO_PinSource5

#define		PWM_TIM_ARR			20000

void PWM_Init(void);
void PWM_SetCompare1(unsigned short int Compare);

#endif
