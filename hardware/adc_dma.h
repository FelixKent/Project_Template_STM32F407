#ifndef __ADC_DMA_H
#define __ADC_DMA_H

#include "stm32f4xx.h"

#define ADC_NOFCHANEL      3

/*=====================通道1 IO ======================*/

// PB0 通过调帽接电位器
// ADC IO宏定义

#define ADC_GPIO_PORT_1    	GPIOB
#define ADC_GPIO_PIN_1     	GPIO_Pin_0
#define ADC_GPIO_CLK_1     	RCC_AHB1Periph_GPIOB
#define ADC_CHANNEL_1      	ADC_Channel_8

/*=====================通道2 IO ======================*/

// PB1 通过调帽接光敏电阻
// ADC IO宏定义

#define ADC_GPIO_PORT_2    	GPIOB
#define ADC_GPIO_PIN_2     	GPIO_Pin_1
#define ADC_GPIO_CLK_2     	RCC_AHB1Periph_GPIOB
#define ADC_CHANNEL_2      	ADC_Channel_9

/*=====================通道3 IO ======================*/

// PA6 悬空，可用杜邦线接3V3或者GND来实验
// ADC IO宏定义

#define ADC_GPIO_PORT_3    	GPIOA
#define ADC_GPIO_PIN_3     	GPIO_Pin_6

#define ADC_GPIO_CLK_3		RCC_AHB1Periph_GPIOA
#define ADC_CHANNEL_3		ADC_Channel_6

// ADC 序号宏定义
#define ADC_NO				ADC1
#define ADC_CLK				RCC_APB2Periph_ADC1
// ADC DR寄存器宏定义，ADC转换后的数字值则存放在这里
#define ADC_DR_ADDR    		((u32)ADC1+0x4c)


// ADC DMA 通道宏定义，这里我们使用DMA传输
#define ADC_DMA_CLK			RCC_AHB1Periph_DMA2
#define ADC_DMA_CHANNEL  	DMA_Channel_0
#define ADC_DMA_STREAM   	DMA2_Stream0



void ADC_DMA_Init(void);

#endif /* __ADC_DMA_H */

