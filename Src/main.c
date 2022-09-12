#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" // Input/output library for this course
#include "stdio.h"
#include "string.h"
#include "gpio.h"
#include "timer.h"

/* SYMBOLIC CONSTANTS */
#define NUM_SAMPLES	  10U

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

/* FUNCTION DEFINITIONS */
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
