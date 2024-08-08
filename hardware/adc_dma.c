#include "adc_dma.h"

volatile uint16_t ADC_ConvertedValue[ADC_NOFCHANEL]={0};

static void ADC_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*=====================ͨ��1======================*/	
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(ADC_GPIO_CLK_1,ENABLE);		
	// ���� IO
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	//������������	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(ADC_GPIO_PORT_1, &GPIO_InitStructure);

	/*=====================ͨ��2======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(ADC_GPIO_CLK_2,ENABLE);		
	// ���� IO
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	//������������	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(ADC_GPIO_PORT_2, &GPIO_InitStructure);	

	/*=====================ͨ��3=======================*/
	// ʹ�� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(ADC_GPIO_CLK_3,ENABLE);		
	// ���� IO
	GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	//������������	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(ADC_GPIO_PORT_3, &GPIO_InitStructure);
	
}

static void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	
	// ADC1ʹ��DMA2��������0��ͨ��0��������ֲ�̶�����
	// ����DMAʱ��
	RCC_AHB1PeriphClockCmd(ADC_DMA_CLK, ENABLE); 
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_DR_ADDR;
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC_ConvertedValue;  
	// ���ݴ��䷽��Ϊ���赽�洢��	
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	// ��������СΪ��ָһ�δ����������
	DMA_InitStructure.DMA_BufferSize = ADC_NOFCHANEL;	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	// �洢����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	// �������ݴ�СΪ���֣��������ֽ� 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; 
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;	
	// ѭ������ģʽ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	// ��ֹDMA FIFO	��ʹ��ֱ��ģʽ
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;  
	// FIFO ��С��FIFOģʽ��ֹʱ�������������	
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
	// ѡ�� DMA ͨ����ͨ������������
	DMA_InitStructure.DMA_Channel = ADC_DMA_CHANNEL; 
	//��ʼ��DMA�������൱��һ����Ĺܵ����ܵ������кܶ�ͨ��
	DMA_Init(ADC_DMA_STREAM, &DMA_InitStructure);
	// ʹ��DMA��
	DMA_Cmd(ADC_DMA_STREAM, ENABLE);
	
	// ����ADCʱ��
	RCC_APB2PeriphClockCmd(ADC_CLK , ENABLE);
	
	// ����ADCģʽ
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	// ʱ��Ϊfpclk x��Ƶ	
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
	// ��ֹDMAֱ�ӷ���ģʽ	
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
	// ����ʱ����	
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;  
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_StructInit(&ADC_InitStructure);
	// ADC �ֱ���
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	// ɨ��ģʽ����ͨ���ɼ���Ҫ	
	ADC_InitStructure.ADC_ScanConvMode = ENABLE; 
	// ����ת��
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
	//��ֹ�ⲿ���ش���
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	//�ⲿ����ͨ����������ʹ�������������ֵ��㸳ֵ����
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	//�����Ҷ���	
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	//ת��ͨ�� 1��
	ADC_InitStructure.ADC_NbrOfConversion = ADC_NOFCHANEL;                                    
	ADC_Init(ADC_NO, &ADC_InitStructure);
		
	// ���� ADC ͨ��ת��˳��Ͳ���ʱ������
	ADC_RegularChannelConfig(ADC_NO, ADC_CHANNEL_1, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC_NO, ADC_CHANNEL_2, 2, ADC_SampleTime_3Cycles); 
	ADC_RegularChannelConfig(ADC_NO, ADC_CHANNEL_3, 3, ADC_SampleTime_3Cycles); 

	// ʹ��DMA���� after last transfer (Single-ADC mode)
	ADC_DMARequestAfterLastTransferCmd(ADC_NO, ENABLE);
	// ʹ��ADC DMA
	ADC_DMACmd(ADC_NO, ENABLE);
		
	// ʹ��ADC
	ADC_Cmd(ADC_NO, ENABLE);  
	//��ʼadcת�����������
	ADC_SoftwareStartConv(ADC_NO);
}

void ADC_DMA_Init(void){
	ADC_GPIO_Config();
	ADC_Mode_Config();
}
