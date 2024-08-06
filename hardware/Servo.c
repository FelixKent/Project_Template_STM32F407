#include "stm32f4xx.h"                  // Device header
#include "PWM.h"
#include "Servo.h"

/**
  * 函    数：舵机初始化
  * 参    数：无
  * 返 回 值：无
  */
void Servo_Init(void)
{
	PWM_Init();									//初始化舵机的底层PWM
}

/**
  * 函    数：舵机设置角度
  * 参    数：Angle 要设置的舵机角度，范围：0~180
  * 返 回 值：无
  */
void Servo_SetAngle(float Angle)
{
	PWM_SetCompare1(Angle / 180 * 2000);	//设置占空比
												//将角度线性变换，对应到舵机要求的占空比范围上
}


/**
  * @Name    Servo_SetDuty
  * @brief   设置舵机驱动 PWM 波空占比
  * @param   Duty: [输入/出] 
  * @retval  None
  * @author  Felix JIA
  * @Data    2024-08-05
  * <description> :
 **/
void Servo_SetDuty(float Duty)			// 需要按照 Channel 修改代码
{
	PWM_SetCompare1( Duty * PWM_TIM_ARR);
}
