#include "myTim.h"

void myTIM_Init(void)
{
    // 初始化TIM2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_InternalClockConfig(TIM2);
    TIM_TimeBaseInitTypeDef tim2_initstruct;
    tim2_initstruct.TIM_Prescaler = 7200 - 1;
    tim2_initstruct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim2_initstruct.TIM_CounterMode = TIM_CounterMode_Up;
    tim2_initstruct.TIM_Period = 10- 1;
    TIM_TimeBaseInit(TIM2, &tim2_initstruct);

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	 TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd(TIM2, ENABLE);
}
