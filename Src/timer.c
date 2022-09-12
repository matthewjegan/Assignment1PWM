#include "timer.h"

void initTIM2(void)
{
	// Timer
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_TimeBaseStructInit(&TIM_InitStructure);
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStructure.TIM_Prescaler = 63; // Scale counter freq to 1 MHz
	TIM_InitStructure.TIM_Period = 0xFFFFFFFF; // Set auto-reload to maximum value
	TIM_TimeBaseInit(TIM2,&TIM_InitStructure);

	TIM_ICInitTypeDef TIM_ICInitStruct;
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_PWMIConfig(TIM2, &TIM_ICInitStruct);

	TIM_ITConfig(TIM2, TIM_IT_CC1,ENABLE);
	TIM_Cmd(TIM2,ENABLE);

	// NVIC for timer
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_SetPriority(TIM2_IRQn, 0); // Set interrupt priority interrupts
	NVIC_EnableIRQ(TIM2_IRQn); // Enable interrupt
}
