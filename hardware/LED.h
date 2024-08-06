#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"                  // Device header

/* LED Òý½Å¶¨Òå */
// LED_RED
#define	LED_RED_PIN					GPIO_Pin_6
#define LED_RED_GPIO_PORT			GPIOF	
#define LED_RED_GPIO_CLK			RCC_AHB1Periph_GPIOF

// LED_GREEN
#define LED_GREEN_PIN				GPIO_Pin_7
#define LED_GREEN_GPIO_PORT			GPIOF
#define LED_GREEN_GPIO_CLK			RCC_AHB1Periph_GPIOF

// LED_BLUE
#define LED_BLUE_PIN                GPIO_Pin_8
#define LED_BLUE_GPIO_PORT          GPIOF
#define LED_BLUE_GPIO_CLK           RCC_AHB1Periph_GPIOF

/* ¿ØÖÆ LED ¿ª¹Ø*/
#define ON 0
#define OFF 1

#define LED_RED_SET(flag) if(flag)	\
							GPIO_SetBits(LED_RED_GPIO_PORT,LED_RED_PIN);	\
						else		\
							GPIO_ResetBits(LED_RED_GPIO_PORT,LED_RED_PIN)
#define LED_GREEN_SET(flag) if(flag)	\
							GPIO_SetBits(LED_GREEN_GPIO_PORT,LED_GREEN_PIN);	\
						else		\
							GPIO_ResetBits(LED_GREEN_GPIO_PORT,LED_GREEN_PIN)
#define LED_BLUE_SET(flag) if(flag)	\
							GPIO_SetBits(LED_BLUE_GPIO_PORT,LED_BLUE_PIN);	\
						else		\
							GPIO_ResetBits(LED_BLUE_GPIO_PORT,LED_BLUE_PIN)
#define	LED_RED_TURN	if(GPIO_ReadOutputDataBit(LED_RED_GPIO_PORT, LED_RED_PIN) == 0) \
							GPIO_SetBits(LED_RED_GPIO_PORT, LED_RED_PIN); \
						else	\
							GPIO_ResetBits(LED_RED_GPIO_PORT, LED_RED_PIN) 
#define	LED_GREEN_TURN	if(GPIO_ReadOutputDataBit(LED_GREEN_GPIO_PORT, LED_GREEN_PIN) == 0) \
							GPIO_SetBits(LED_GREEN_GPIO_PORT, LED_GREEN_PIN); \
						else	\
							GPIO_ResetBits(LED_GREEN_GPIO_PORT, LED_GREEN_PIN) 
#define	LED_BLUE_TURN	if(GPIO_ReadOutputDataBit(LED_BLUE_GPIO_PORT, LED_BLUE_PIN) == 0) \
							GPIO_SetBits(LED_BLUE_GPIO_PORT, LED_BLUE_PIN); \
						else	\
							GPIO_ResetBits(LED_BLUE_GPIO_PORT, LED_BLUE_PIN) 
						
//ºì
#define LED_RED  \
					LED_RED_SET(ON);\
					LED_GREEN_SET(OFF);\
					LED_BLUE_SET(OFF)

//ÂÌ
#define LED_GREEN		\
					LED_RED_SET(OFF);\
					LED_GREEN_SET(ON);\
					LED_BLUE_SET(OFF)

//À¶
#define LED_BLUE	\
					LED_RED_SET(OFF);\
					LED_GREEN_SET(OFF);\
					LED_BLUE_SET(ON)

					
//»Æ(ºì+ÂÌ)					
#define LED_YELLOW	\
					LED_RED_SET(ON);\
					LED_GREEN_SET(ON);\
					LED_BLUE_SET(OFF)
//×Ï(ºì+À¶)
#define LED_PURPLE	\
					LED_RED_SET(ON);\
					LED_GREEN_SET(OFF);\
					LED_BLUE_SET(ON)

//Çà(ÂÌ+À¶)
#define LED_CYAN \
					LED_RED_SET(OFF);\
					LED_GREEN_SET(ON);\
					LED_BLUE_SET(ON)
					
//°×(ºì+ÂÌ+À¶)
#define LED_WHITE	\
					LED_RED_SET(ON);\
					LED_GREEN_SET(ON);\
					LED_BLUE_SET(ON)
					
//ºÚ(È«²¿¹Ø±Õ)
#define LED_RGB_OFF	\
					LED_RED_SET(OFF);\
					LED_GREEN_SET(OFF);\
					LED_BLUE_SET(OFF)	



void LED_Init(void);

#endif
