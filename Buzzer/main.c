/*
 * Buzzer.c
 *
 * Created: 30-3-2019 11:26:25
 * Author : Maarten
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void BuzzerInit()
{
	DDRE = 0xFF;
	TCCR3A = 0b10000010;		// compare output at OC1A  (=PB5)
	TCCR3B = 0b00011000;		// fast PWM, TOP=ICR1
}

void BuzzerSetFrequency(float frequency)
{
	int ms = (int)(1.0 / frequency * 1000000.0); // Convert hertz to microseconds
	
	TCCR3B |= (1 << CS31);		// Turn on the 8 times prescaler (which starts the timer)
	TCNT3 = 0;
	ICR3	= ms;				// TOP value for counter
	OCR3A	= ms / 2;			// compare value in between
}

void BuzzerPwmOff()
{
	TCCR3B &= ~(1 << CS31);		// Turn off the prescaler (which stops the timer)
}

int main(void)
{
	BuzzerInit();
    /* Replace with your application code */
	int counter = 1000;
    while (1) 
    {
		counter -= 10;
		BuzzerSetFrequency(counter);
		wait(2000);
		BuzzerPwmOff();
		wait(1000);
    }
}

