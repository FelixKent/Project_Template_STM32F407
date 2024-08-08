#include "can.h"

uint32_t RxID;
uint8_t RxLength;
uint8_t RxData[8];   // �������ݰ���С�޸ĺ���

void CAN_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	// �� GPIO ʱ��
	RCC_AHB1PeriphClockCmd(CAN_TX_GPIO_CLK|CAN_RX_GPIO_CLK, ENABLE);
	
	// �������Ÿ���
	GPIO_PinAFConfig(CAN_TX_GPIO_PORT, CAN_RX_AF_PINSOURCE, CAN_GPIO_AF_Selection);
	GPIO_PinAFConfig(CAN_RX_GPIO_PORT, CAN_TX_AF_PINSOURCE, CAN_GPIO_AF_Selection); 
	
	// ���� CAN TX ����
	GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���� CAN RX ����
	GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
	
}


void CAN_NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
    // ����Ȩ����
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*�ж�����*/
    NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
}

void CAN_Mode_Config(void){
	
	CAN_InitTypeDef CAN_InitStructure;
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

	/*CAN�Ĵ�����ʼ��*/
	CAN_DeInit(CAN_COM);
	CAN_StructInit(&CAN_InitStructure);

	/*CAN��Ԫ��ʼ��*/
	CAN_InitStructure.CAN_TTCM = DISABLE;			   	//MCR-TTCM  �ر�ʱ�䴥��ͨ��ģʽʹ��
	CAN_InitStructure.CAN_ABOM = ENABLE;			   	//MCR-ABOM  �Զ����߹��� 
	CAN_InitStructure.CAN_AWUM = ENABLE;			   	//MCR-AWUM  ʹ���Զ�����ģʽ
	CAN_InitStructure.CAN_NART = DISABLE;			   	//MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
	CAN_InitStructure.CAN_RFLM = DISABLE;			   	//MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���  
	CAN_InitStructure.CAN_TXFP = DISABLE;			   	//MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ�� 
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;  	//�ػ�����ģʽ
	CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;		   	//BTR-SJW ����ͬ����Ծ��� 2��ʱ�䵥Ԫ
	 
	/* ss=1 bs1=4 bs2=2 λʱ����Ϊ(1+4+2) �����ʼ�Ϊʱ������tq*(1+4+2)  */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;		   	//BTR-TS1 ʱ���1 ռ����4��ʱ�䵥Ԫ
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;		   	//BTR-TS1 ʱ���2 ռ����2��ʱ�䵥Ԫ	
	
	/* CAN Baudrate = 1 MBps (1MBps��Ϊstm32��CAN�������) (CAN ʱ��Ƶ��Ϊ APB 1 = 42 MHz) */
	// �����ʼ��㷽����ʱ��Ƶ��/����Ƶ�� * Tq ������
	CAN_InitStructure.CAN_Prescaler = 6;		   		//BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 42/(1+4+2)/6=1 Mbps
	CAN_Init(CAN_COM, &CAN_InitStructure);
}

void CAN_Filter_Config(void){
	
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/*CANɸѡ����ʼ��*/
	CAN_FilterInitStructure.CAN_FilterNumber = 14;						//ɸѡ����14
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		//����������ģʽ
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	//ɸѡ��λ��Ϊ����32λ��
	
	/* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */

	CAN_FilterInitStructure.CAN_FilterIdHigh = ((((u32)0x1314 << 3)|CAN_ID_EXT|CAN_RTR_DATA) & 0xFFFF0000) >> 16;	//Ҫɸѡ��ID��λ 
	CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)0x1314 << 3)|CAN_ID_EXT|CAN_RTR_DATA) & 0xFFFF; 				//Ҫɸѡ��ID��λ 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xFFFF;			//ɸѡ����16λÿλ����ƥ��
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0xFFFF;			//ɸѡ����16λÿλ����ƥ��
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;				//ɸѡ����������FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//ʹ��ɸѡ��
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/*CANͨ���ж�ʹ��*/
	CAN_ITConfig(CAN_COM, CAN_IT_FMP0, ENABLE);
	
}

void CAN_COM_Init(void){
	
	CAN_GPIO_Config();
	CAN_NVIC_Config();
	CAN_Mode_Config();
	CAN_Filter_Config();
}

void CAN_COM_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data){
	
	CanTxMsg TxMessage;
	// TxMessage.StdId = ID;
	TxMessage.ExtId = ID;
	TxMessage.IDE = CAN_ID_EXT;
	TxMessage.RTR = CAN_RTR_Data;
	TxMessage.DLC = Length;
	for (uint8_t i = 0; i < Length; i ++)
	{
		TxMessage.Data[i] = Data[i];
	}
	uint8_t TransmitMailbox = CAN_Transmit(CAN_COM, &TxMessage);
	
	while (CAN_TransmitStatus(CAN_COM, TransmitMailbox) != CAN_TxStatus_Ok);
}

void CAN_COM_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data){
	
	CanRxMsg RxMessage;
	
	CAN_Receive(CAN_COM, CAN_FIFO0, &RxMessage);
	
	if (RxMessage.IDE == CAN_Id_Standard)
	{
		*ID = RxMessage.StdId;
	}
	else
	{
		*ID = RxMessage.ExtId;
	}
	
	if (RxMessage.RTR == CAN_RTR_Data)
	{
		*Length = RxMessage.DLC;
		for (uint8_t i = 0; i < *Length; i ++)
		{
			Data[i] = RxMessage.Data[i];
		}
	}
	else
	{
		*Length = 0; 
	}
}


void CAN_RX_IRQHandler(void){
	CAN_COM_Receive(&RxID, &RxLength, RxData);
}

