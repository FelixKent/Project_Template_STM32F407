#ifndef __USART_H
#define __USART_H

#include "main.h" 




/*串口的初始化，这里初始化了PA9，PA10*/
void Serial_Init(void);

/*发送单个字节*/
void Serial_SendByte(uint8_t Byte);

/*接收单个字节*/
uint8_t Serial_GetRxData(void);

/*打印*/
void Serial_Printf(char *format, ...);

/*发送数组*/
void Serial_SendArray(int16_t *Array, uint16_t Length);

/*发送字符串*/
void Serial_SendString(char *String);

/*发送数字*/
void Serial_SendNumber(int32_t Number, uint8_t Length);



#endif
