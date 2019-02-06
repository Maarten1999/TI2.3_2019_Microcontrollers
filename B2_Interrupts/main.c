/*
 * B2_Interrupts.c
 *
 * Created: 6-2-2019 12:06:43
 * Author : Maarten
 */ 
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int i;

ISR(INT1_vect)
{
	if(i == 0) i = 7;
	else i--;
	
	PORTA = (1 << i);
}

ISR(INT2_vect)
{
	if(i == 7) i = 0;
	else i++;
	
	PORTA = (1 << i);
}

int main(void)
{
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input
	DDRA = 0xFF;			// All pins of PORTA are set to output for loop light
	
	// Init Interrupt hardware
	EICRA |= 0x2C;			// INT2 falling edge, INT1 rising edge
	EIMSK |= 0x06;			// Enable INT2 & INT1
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

