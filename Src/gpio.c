#include "gpio.h"

void initLed(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); // Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); // Enable clock for GPIO Port B
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // Enable clock for GPIO Port C

	// PC0 Input
	GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins
	GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
	GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_OUT; // Set as input
	GPIO_InitStructAll.GPIO_OType = GPIO_OType_PP; // Set as Push-Pull
	GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_2MHz; // Set speed to 2 MHz

	// PB4 Output
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin B4
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PC7 Output
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_7; // Set so the configuration is on pin C7
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PA9 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_9; // Set so the configuration is on pin A9
	GPIO_Init(GPIOA, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen
}

void setLed(uint8_t colour)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_4, ((colour >> 2U) & 1U));
	GPIO_WriteBit(GPIOC, GPIO_Pin_7, ((colour >> 1U) & 1U));
	GPIO_WriteBit(GPIOA, GPIO_Pin_9, ((colour >> 0U) & 1U));
}

void initJoystick(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE); // Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE); // Enable clock for GPIO Port B
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE); // Enable clock for GPIO Port C

	// PC0 Input
	GPIO_InitTypeDef GPIO_InitStructAll; // Define typedef struct for setting pins
	GPIO_StructInit(&GPIO_InitStructAll); // Initialize GPIO struct
	GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_IN; // Set as input
	GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_DOWN; // Set as pull down
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin C0
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PA4 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_4; // Set so the configuration is on pin A4
	GPIO_Init(GPIOA, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PB5 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_5; // Set so the configuration is on pin B5
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PC1 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_1; // Set so the configuration is on pin A4
	GPIO_Init(GPIOC, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen

	// PB0 Input
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0; // Set so the configuration is on pin A4
	GPIO_Init(GPIOB, &GPIO_InitStructAll); // Setup of GPIO with the settings chosen
}

uint8_t readJoystick(void)
{
	uint8_t up     = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
	uint8_t down   = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
	uint8_t left   = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1);
	uint8_t right  = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0);
	uint8_t centre = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5);

	uint8_t joystickBits = 0U;

	joystickBits |= up     << 0U;
	joystickBits |= down   << 1U;
	joystickBits |= left   << 2U;
	joystickBits |= right  << 3U;
	joystickBits |= centre << 4U;

	return joystickBits;
}

void GPIO_set_AF_PA0(void)
{
	GPIO_InitTypeDef GPIO_InitStructAll;
	GPIO_StructInit(&GPIO_InitStructAll);

	// Configure Pin PA0 to Alternate Function Mode
	GPIO_InitStructAll.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructAll.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructAll.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructAll.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStructAll);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_1); //Sets pin 0 at port A to alternative function 1
}
