#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdio.h"
#include "inttypes.h"

/* SYMBOLIC CONSTANTS */
#define CLK_FREQ	  64000000U
#define TIM_PRESCALER 63U
#define TIM_FREQ	  CLK_FREQ / (TIM_PRESCALER + 1)
#define NUM_SAMPLES	  10U

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

/* TYPE DEFINITIONS */
typedef struct
{
	uint8_t size;
	uint32_t sampleArray[NUM_SAMPLES];
} SampleBuffer_S;

/* GLOBAL VARIABLES */
volatile uint32_t ICValue1 = 0; // Period
volatile uint32_t ICValue2 = 0;	// Duty Cycle
volatile uint8_t  ICValid = 0;

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

/* FUNCTION DEFINITIONS */
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

void TIM2_IRQHandler(void) {
	// Clear Capture/Compare Interrupt Bit
	TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
	setLed(CYAN);

	ICValue1 = TIM_GetCapture1(TIM2); // Period - Counts between rising edges
	ICValue2 = TIM_GetCapture2(TIM2); // Duty/Width - Counts with input channel HI between rising edges
	ICValid = 1;
}

uint64_t updateBufferAndGetOutput(SampleBuffer_S* buffer, uint32_t newSample)
{
	uint8_t bufferSize = buffer->size;

	if (bufferSize < NUM_SAMPLES)
	{
		buffer->sampleArray[bufferSize] = newSample;
		buffer->size++;
	}
	else
	{
		for (int i = 0; i < NUM_SAMPLES - 1; i++)
		{
			buffer->sampleArray[i] = buffer->sampleArray[i+1];
		}

		buffer->sampleArray[NUM_SAMPLES] = newSample;
	}

	uint32_t sum = 0;
	for (int i = 0; i < buffer->size; i++)
	{
		sum += buffer->sampleArray[i];
	}

	return sum / buffer->size;
}

int main(void)
{
	uart_init( 9600 ); // Initialize USB serial at 9600 baud
	GPIO_set_AF_PA0();
	initTIM2();
	initJoystick();
	initLed();

	uint32_t inputFreq; // Input PWM frequency in Hz
	uint32_t dutyCycle; // Input PWM duty cycle in %

	uint8_t measurementEnabled = 1U;

	SampleBuffer_S freqBuffer = {0, {}};
	SampleBuffer_S dutyCycleBuffer = {0, {}};
	uint32_t avgInputFreq;
	uint32_t avgDutyCycle;

	uint8_t lastJoystickState = 0U;

	while(1)
	{
		uint8_t joystickState = readJoystick();
		if (joystickState != lastJoystickState)
		{
			lastJoystickState = joystickState;

			if (joystickState == CENTRE)
			{
				if (measurementEnabled == 1)
				{
					measurementEnabled = 0;
				}
				else
				{
					measurementEnabled = 1;
				}
			}
			else if (joystickState == DOWN)
			{
				printf("Resetting Sample Buffers\n");
				memset(freqBuffer.sampleArray, 0, sizeof(freqBuffer.sampleArray));
				freqBuffer.size = 0;
				memset(dutyCycleBuffer.sampleArray, 0, sizeof(dutyCycleBuffer.sampleArray));
				dutyCycleBuffer.size = 0;
			}
		}

		if (measurementEnabled == 1)
		{
			setLed(GREEN);

			if (ICValid == 1)
			{
				if (ICValue1 > 0)
				{
					inputFreq = TIM_FREQ / ICValue1;
					dutyCycle = (100 * ICValue2) / ICValue1;
				}
				else
				{
					inputFreq = 0;
					dutyCycle = 0;
				}

				printf("Signal Frequency: %ld Hz\nDuty Cycle = %ld %%\n",
					   (unsigned long) inputFreq,
					   (unsigned long) dutyCycle);

				avgInputFreq = updateBufferAndGetOutput(&freqBuffer, inputFreq);
				avgDutyCycle = updateBufferAndGetOutput(&dutyCycleBuffer, dutyCycle);
				ICValid = 0;

				printf("Avg Signal Frequency: %ld Hz\nAvg Duty Cycle = %ld %%\n",
								   (unsigned long) avgInputFreq,
								   (unsigned long) avgDutyCycle);

			}
		}
		else
		{
			setLed(RED);
		}
	}
}
