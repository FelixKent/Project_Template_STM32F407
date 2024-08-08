#ifndef __CAN_H
#define __CAN_H

#include "stm32f4xx.h"

/* 
	该例程使用前需使用挑帽连接 J40：3V3-CAN/485_3V3，启动板载 CAN 收发器供电
	CANH 与 CANL 接口位于 J13
	数据接收接口为 PB12 ，数据发送接口为 PB13
*/

#define CAN_COM						CAN2
#define CAN_CLK						RCC_APB1Periph_CAN1 |RCC_APB1Periph_CAN2
#define CAN_RX_IRQ					CAN2_RX0_IRQn
#define CAN_RX_IRQHandler			CAN2_RX0_IRQHandler

#define CAN_RX_PIN					GPIO_Pin_12
#define CAN_TX_PIN 					GPIO_Pin_13
#define CAN_TX_GPIO_PORT			GPIOB
#define CAN_RX_GPIO_PORT			GPIOB
#define CAN_TX_GPIO_CLK				RCC_AHB1Periph_GPIOB
#define CAN_RX_GPIO_CLK				RCC_AHB1Periph_GPIOB
#define CAN_GPIO_AF_Selection		GPIO_AF_CAN2
#define CAN_RX_AF_PINSOURCE			GPIO_PinSource12
#define CAN_TX_AF_PINSOURCE			GPIO_PinSource13 

void CAN_GPIO_Config(void);
void CAN_NVIC_Config(void);
void CAN_Mode_Config(void);
void CAN_Filter_Config(void);
void CAN_COM_Init(void);
void CAN_COM_Transmit(uint32_t ID, uint8_t Length, uint8_t *Data);
void CAN_COM_Receive(uint32_t *ID, uint8_t *Length, uint8_t *Data);
uint8_t CAN_COM_ReceiveFlag(void);
void CAN_RX_IRQHandler(void);
#endif
