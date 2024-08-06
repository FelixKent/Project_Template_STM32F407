#ifndef __PWM_H
#define __PWM_H

// ����������Ϊ PA1 �ӿ���� PWM ����ʹ�õĶ�ʱ��Ϊ TIM2
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
