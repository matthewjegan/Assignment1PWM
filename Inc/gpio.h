#ifndef _GPIO_H_
#define _GPIO_H_

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdio.h"
#include "inttypes.h"

#define UP     1U
#define DOWN   2U
#define LEFT   4U
#define RIGHT  8U
#define CENTRE 16U

#define OFF		0b111
#define RED     0b011
#define GREEN   0b101
#define BLUE    0b110
#define CYAN    0b100
#define YELLOW  0b001
#define MAGENTA 0b010
#define WHITE   0b000

void initLed(void);
void setLed(uint8_t colour);
void initJoystick(void);
uint8_t readJoystick(void);
void GPIO_set_AF_PA0(void);

#endif /* _GPIO_H_ */
