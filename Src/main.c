#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course

#define UP     1U
#define DOWN   2U
#define LEFT   4U
#define RIGHT  8U
#define CENTRE 16U

#define RED     0b011
#define GREEN   0b101
#define BLUE    0b110
#define CYAN    0b100
#define YELLOW  0b001
#define MAGENTA 0b010
#define WHITE   0b000

void initInterrupts(void)
{
	// enable interrupts
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5); // sets port B pin 5 to the IRQ
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0); // sets port B pin 0 to the IRQ

	// define and set setting for EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line5; // line 5 see [RM p. 215]
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = EXTI_Line0; // line 5 see [RM p. 215]
	EXTI_Init(&EXTI_InitStructure);

	// setup NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable interrupt
	NVIC_EnableIRQ(EXTI0_IRQn); // Enable interrupt
}

void EXTI9_5_IRQHandler(void){
	if( EXTI_GetITStatus(EXTI_Line5) != RESET ){
		printf("Right : %d | Up : %d | Center : %d | Left : %d | Down : %d\n",
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0),
				GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4),
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5),
				GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1),
				GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));

		GPIO_WriteBit(GPIOB, GPIO_Pin_4, ((CYAN >> 2U) & 1U));
		GPIO_WriteBit(GPIOC, GPIO_Pin_7, ((CYAN >> 1U) & 1U));
		GPIO_WriteBit(GPIOA, GPIO_Pin_9, ((CYAN >> 0U) & 1U));

		EXTI_ClearITPendingBit(EXTI_Line5);

		printf("Interrupt Triggered PB5\n");
	}
}

void EXTI0_IRQHandler(void){
	// Do some important stuff here!...
	printf("line 0 interrupt\n");
	EXTI_ClearITPendingBit(EXTI_Line0);
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

void setLed(uint8_t state)
{
	uint8_t colour = 0U;

	switch (state)
	{
		case (UP):
			colour = RED;
			break;

		case (DOWN):
			colour = GREEN;
			break;

		case (LEFT):
			colour = BLUE;
			break;

		case (RIGHT):
			colour = YELLOW;
			break;

		case (CENTRE):
			colour = MAGENTA;
			break;

		default:
			colour = WHITE;
	}

	GPIO_WriteBit(GPIOB, GPIO_Pin_4, ((colour >> 2U) & 1U));
	GPIO_WriteBit(GPIOC, GPIO_Pin_7, ((colour >> 1U) & 1U));
	GPIO_WriteBit(GPIOA, GPIO_Pin_9, ((colour >> 0U) & 1U));
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

int main(void)
{
	uart_init( 9600 ); // Initialize USB serial at 9600 baud
	initJoystick();
	initLed();
	initInterrupts();

	uint8_t joystickState;

	while(1)
	{
		uint8_t newJoystickState = readJoystick();

		if (newJoystickState != joystickState)
		{
			joystickState = newJoystickState;
			printf("Joystick: %d\n", joystickState);
		}

		setLed(joystickState);
	}
}
