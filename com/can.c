#include "can.h"

uint32_t RxID;
uint8_t RxLength;
uint8_t RxData[8];   // 按照数据包大小修改函数

void CAN_GPIO_Config(void){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	// 打开 GPIO 时钟
	RCC_AHB1PeriphClockCmd(CAN_TX_GPIO_CLK|CAN_RX_GPIO_CLK, ENABLE);
	
	// 设置引脚复用
	GPIO_PinAFConfig(CAN_TX_GPIO_PORT, CAN_RX_AF_PINSOURCE, CAN_GPIO_AF_Selection);
	GPIO_PinAFConfig(CAN_RX_GPIO_PORT, CAN_TX_AF_PINSOURCE, CAN_GPIO_AF_Selection); 
	
	// 配置 CAN TX 引脚
	GPIO_InitStructure.GPIO_Pin = CAN_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(CAN_TX_GPIO_PORT, &GPIO_InitStructure);
	
	// 配置 CAN RX 引脚
	GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(CAN_RX_GPIO_PORT, &GPIO_InitStructure);
	
}


void CAN_NVIC_Config(void){
	
	NVIC_InitTypeDef NVIC_InitStructure;
    // 设置权限组
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*中断设置*/
    NVIC_InitStructure.NVIC_IRQChannel = CAN_RX_IRQ;	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
	
}

void CAN_Mode_Config(void){
	
	CAN_InitTypeDef CAN_InitStructure;
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);

	/*CAN寄存器初始化*/
	CAN_DeInit(CAN_COM);
	CAN_StructInit(&CAN_InitStructure);

	/*CAN单元初始化*/
	CAN_InitStructure.CAN_TTCM = DISABLE;			   	//MCR-TTCM  关闭时间触发通信模式使能
	CAN_InitStructure.CAN_ABOM = ENABLE;			   	//MCR-ABOM  自动离线管理 
	CAN_InitStructure.CAN_AWUM = ENABLE;			   	//MCR-AWUM  使用自动唤醒模式
	CAN_InitStructure.CAN_NART = DISABLE;			   	//MCR-NART  禁止报文自动重传	  DISABLE-自动重传
	CAN_InitStructure.CAN_RFLM = DISABLE;			   	//MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文  
	CAN_InitStructure.CAN_TXFP = DISABLE;			   	//MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符 
	CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;  	//回环工作模式
	CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;		   	//BTR-SJW 重新同步跳跃宽度 2个时间单元
	 
	/* ss=1 bs1=4 bs2=2 位时间宽度为(1+4+2) 波特率即为时钟周期tq*(1+4+2)  */
	CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;		   	//BTR-TS1 时间段1 占用了4个时间单元
	CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;		   	//BTR-TS1 时间段2 占用了2个时间单元	
	
	/* CAN Baudrate = 1 MBps (1MBps已为stm32的CAN最高速率) (CAN 时钟频率为 APB 1 = 42 MHz) */
	// 波特率计算方法：时钟频率/（分频数 * Tq 总数）
	CAN_InitStructure.CAN_Prescaler = 6;		   		//BTR-BRP 波特率分频器  定义了时间单元的时间长度 42/(1+4+2)/6=1 Mbps
	CAN_Init(CAN_COM, &CAN_InitStructure);
}

void CAN_Filter_Config(void){
	
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;

	/*CAN筛选器初始化*/
	CAN_FilterInitStructure.CAN_FilterNumber = 14;						//筛选器组14
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;		//工作在掩码模式
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;	//筛选器位宽为单个32位。
	
	/* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */

	CAN_FilterInitStructure.CAN_FilterIdHigh = ((((u32)0x1314 << 3)|CAN_ID_EXT|CAN_RTR_DATA) & 0xFFFF0000) >> 16;	//要筛选的ID高位 
	CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)0x1314 << 3)|CAN_ID_EXT|CAN_RTR_DATA) & 0xFFFF; 				//要筛选的ID低位 
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh= 0xFFFF;			//筛选器高16位每位必须匹配
	CAN_FilterInitStructure.CAN_FilterMaskIdLow= 0xFFFF;			//筛选器低16位每位必须匹配
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;				//筛选器被关联到FIFO0
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//使能筛选器
	CAN_FilterInit(&CAN_FilterInitStructure);
	
	/*CAN通信中断使能*/
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

