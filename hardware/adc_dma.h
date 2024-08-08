#ifndef __ADC_DMA_H
#define __ADC_DMA_H

#include "stm32f4xx.h"

#define ADC_NOFCHANEL      3

/*=====================ͨ��1 IO ======================*/

// PB0 ͨ����ñ�ӵ�λ��
// ADC IO�궨��

#define ADC_GPIO_PORT_1    	GPIOB
#define ADC_GPIO_PIN_1     	GPIO_Pin_0
#define ADC_GPIO_CLK_1     	RCC_AHB1Periph_GPIOB
#define ADC_CHANNEL_1      	ADC_Channel_8

/*=====================ͨ��2 IO ======================*/

// PB1 ͨ����ñ�ӹ�������
// ADC IO�궨��

#define ADC_GPIO_PORT_2    	GPIOB
#define ADC_GPIO_PIN_2     	GPIO_Pin_1
#define ADC_GPIO_CLK_2     	RCC_AHB1Periph_GPIOB
#define ADC_CHANNEL_2      	ADC_Channel_9

/*=====================ͨ��3 IO ======================*/

// PA6 ���գ����öŰ��߽�3V3����GND��ʵ��
// ADC IO�궨��

#define ADC_GPIO_PORT_3    	GPIOA
#define ADC_GPIO_PIN_3     	GPIO_Pin_6

#define ADC_GPIO_CLK_3		RCC_AHB1Periph_GPIOA
#define ADC_CHANNEL_3		ADC_Channel_6

// ADC ��ź궨��
#define ADC_NO				ADC1
#define ADC_CLK				RCC_APB2Periph_ADC1
// ADC DR�Ĵ����궨�壬ADCת���������ֵ����������
#define ADC_DR_ADDR    		((u32)ADC1+0x4c)


// ADC DMA ͨ���궨�壬��������ʹ��DMA����
#define ADC_DMA_CLK			RCC_AHB1Periph_DMA2
#define ADC_DMA_CHANNEL  	DMA_Channel_0
#define ADC_DMA_STREAM   	DMA2_Stream0



void ADC_DMA_Init(void);

#endif /* __ADC_DMA_H */

