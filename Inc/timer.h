#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdio.h"

#define CLK_FREQ	  64000000U
#define TIM_PRESCALER 63U
#define TIM_FREQ	  CLK_FREQ / (TIM_PRESCALER + 1)

void initTIM2(void);

#endif /* _TIMER_H */
