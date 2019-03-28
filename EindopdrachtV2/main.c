/*
 * EindopdrachtV2.c
 *
 * Created: 28-3-2019 20:23:18
 * Author : Ralph Rouwen
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "lcd.h"

void checkInterrupt(void);

int interruptState = 0;
int pulse = 0;

ISR(INT4_vect)
{
	checkInterrupt();
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


void checkInterrupt(void)
{
	if(interruptState == 0) 
	{
		TCCR1B |= (1 << CS11);
		interruptState = 1;
	} else
	{
		TCCR1B = 0;
		pulse = TCNT1;
		TCNT1 = 0;
		interruptState = 0;
	}
}

void sendPulse(void) 
{
	PORTE &= ~(1 << 6);
	_delay_us(5);
	PORTE |= (1 << 6);
	_delay_us(15);
	PORTE &= (~(1 << 6));
}
	
	
int main(void)
{
	// LCD init
	init();
	
	DDRE = 0b01000000;
	
	// Interrupt
	EICRB |= 0b00000001;
	EIMSK |= 0b00010000;
	
	TIMSK = (1 << TOIE1);
	
	//TCCR1B |= ((1 << CS10));
	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		sendPulse();
		int16_t distance = 0;
		distance = pulse / 58;
		
		char str[10];
		
		itoa(distance, str, 10);
		
		clear_display();
		lcd_write_string(str);
		
		wait(100);
    }
}

