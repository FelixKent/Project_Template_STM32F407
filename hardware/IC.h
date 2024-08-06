#ifndef __IC_H
#define __IC_H

#define		IC_TIM						TIM3
#define		IC_TIM_CLK					RCC_APB1Periph_TIM3
#define		IC_TIM_CHANNEL				TIM_Channel_1
#define		IC_TIM_IQR					TIM3_IRQn
#define		IC_TIM_IRQHandler			TIM3_IRQHandler

#define		IC_GPIO_PIN					GPIO_Pin_6
#define		IC_GPIO_PORT				GPIOC
#define		IC_GPIO_CLK					RCC_AHB1Periph_GPIOC
#define		IC_AF_PINSOURCE				GPIO_PinSource6
#define		IC_GPIO_AF_Selection		GPIO_AF_TIM3

void IC_Init(void);
uint32_t IC_GetFreq(void);

#endif
