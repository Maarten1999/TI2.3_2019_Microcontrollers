
/*
 * ultrasonic.c
 *
 * Created: 27-3-2019 13:10:27
 *  Author: Ralph Rouwen
 */ 

#define F_CPU 8e6
#include "ultrasonic.h"

#define TRIGGER_PIN PINE6
#define ECHO_PIN	PINE4

volatile int timerOverflow = 0;
volatile int flag = 0;
volatile int pulse = 0;

void US_InterruptUpdate(void)
{
	// Low to high
	if (flag == 0)
	{
		TCCR1B |=  (1 << CS11);
		flag = 1;
	}
	// High to low
	else
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		flag = 0;
	}
}
void US_SendPulse(void)
{
	PORTE &= ~(1 << TRIGGER_PIN);
	_delay_us(5);
	PORTE |= (1 << TRIGGER_PIN);
	_delay_us(15);
	PORTE &= (~(1 << TRIGGER_PIN));
}

int16_t US_GetDistance(void)
{
	return pulse /58;
}