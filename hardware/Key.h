#ifndef __KEY_H
#define __KEY_H

// 野火开发板 KEY 1 和 KEY 2 GPIO 接口配置
#define KEY1_PIN                  GPIO_Pin_0                 
#define KEY1_GPIO_PORT            GPIOA                      
#define KEY1_GPIO_CLK             RCC_AHB1Periph_GPIOA

#define KEY2_PIN                  GPIO_Pin_13                 
#define KEY2_GPIO_PORT            GPIOC                      
#define KEY2_GPIO_CLK             RCC_AHB1Periph_GPIOC

void Key_Init(void);
uint8_t Key_GetNum(void);

#endif
