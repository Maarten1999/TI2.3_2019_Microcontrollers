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

void checkInterrupt(int us);

int currentUS = 0; // 0 or 1;
int interruptState = 0;
int pulse[] = { 0,0 };
int issending = 0; //0 or 1

//echo		: port E4 & port E5
//trigger	: port E0 & port E1

ISR(INT4_vect)
{
	checkInterrupt(0);
}

ISR(INT5_vect)
{
	checkInterrupt(1);
}

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


void checkInterrupt(int us)
{
	if(interruptState == 0) 
	{
		TCCR1B |= (1 << CS11);
		interruptState = 1;
	} else {
		//interruptstate word nooit meer 1;
		TCCR1B = 0;
		pulse[us] = TCNT1;
		TCNT1 = 0;	
		interruptState = 0;
		issending = 0;
	}
}

void sendPulse(int pin) 
{
	issending = 1;
	PORTE &= ~(1 << pin);
	_delay_us(5);
	PORTE |= (1 << pin);
	_delay_us(15);
	PORTE &= (~(1 << pin));
}

void buzzSound(void)
{
	PORTG = 0xFF;
	wait(500);
	PORTG = 0x00;
	wait(100);
}

void setleds(int distance)
{	
	if(distance > 150){
		PORTD = 0b00000000;
	}else if(distance > 130){
		PORTD = 0b00000001;
	} else if(distance > 110){
		PORTD = 0b00000011;
	} else if(distance > 90) {
		PORTD = 0b00000111;
	} else if(distance > 70) {
		PORTD = 0b00001111;
	} else if(distance > 50) {
		PORTD = 0b00011111;
	} else if(distance > 30) {
		PORTD = 0b00111111;
	} else if(distance > 10) {
		PORTD = 0b01111111;
	} else {
		PORTD = 0b11111111;
	}
}

void setExternalLed(int distance)
{	
	if(distance > 120){
		PORTA = 0b00000001;
	} else if(distance > 90){
		PORTA = 0b00000011;
	} else if(distance > 60) {
		PORTA = 0b00000111;
	} else if(distance > 30) {
		PORTA = 0b00001111;
	} else if(distance > 0) {
		PORTA = 0b00011111;
	}
}
	
int main(void)
{
	// LCD init
	init();
	
	DDRE = 0b00000011;
	
	// buzzer output
	DDRG = 0xFF;
	
	// Interrupt
	//EICRB |= 0b00000001;
	//EIMSK |= 0b00010000;
	
	EICRB |= 0b00000101;
	EIMSK |= 0b00110000;

	TIMSK = (1 << TOIE1);
	
	//TCCR1B |= ((1 << CS10));
	
	DDRA = 0b11111111;			// All pins PORTB are set to output, for external Leds
	DDRD = 0b11111111;			// All pins PORTD are set to output, for leds
		
	sei();
	
    /* Replace with your application code */
	
    while (1) 
    {
		if(1 == interruptState) {
			//lcd_write_string("intestate = 1");
		}
		if(0 == issending) {
			clear_display();
			if(1 == currentUS) {
				currentUS = 0;
			}
			else {
				currentUS = 1;
			}
			
			//currentUS = (1 == currentUS) ? 0 : 1;
			sendPulse(currentUS);
			char *str = ((1 == currentUS) ? "CurrentUS: 1" : "CurrentUS: 0");
			//lcd_write_string(str);
		}
		else {
			//clear_display();
			//lcd_write_string("Sending");
		}
		
		//clear_display();
		
		int i;
		for (i = 0; i < 2; i++)
		{
			int16_t distance = 0;
			
			distance = pulse[i] / 58;
			set_cursor(i * 0x40); // line 1 or 2
		
			if(distance >= 0) 
			{
				char str[10];
				//setleds(distance);
				setExternalLed(distance);
				itoa(distance, str, 10);
					
				lcd_write_string(str);	
			}
			else {
				lcd_write_string("ERROR");
			}
		}
		wait(250);
    }
}

//regel 1: 0x00;
//regel 2: 0x40;
