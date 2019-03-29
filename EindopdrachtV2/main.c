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

//variabels for ultrasonic sensors
int currentUS = 0; // 0 or 1;
int interruptState = 0;
int pulse[] = { 0,0 };
int issending = 0; //0 or 1

//variabels for buzzer
const float sec_per_overflow = 0.032768;
int overflow_count = 0;	//number of 
int max_overflow = 100;

//echo		: port E4 & port E5
//trigger	: port E0 & port E1

//Interrupt for first ultrasonic
ISR(INT4_vect)
{
	checkInterrupt();
}

//Interrupt for second ultrasonic
ISR(INT5_vect)
{
	checkInterrupt();
}

ISR(TIMER0_OVF_vect){
	overflow_count++;
	if(max_overflow <= overflow_count){
		PORTG ^= (1 << 0);
		overflow_count = 0;
		TCNT0 = 0x00;
	}
}

//method to wait before code is runned
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//method to handle interrupts of both ultrasonics
void checkInterrupt(void)
{
	if(interruptState == 0) 
	{
		TCCR1B |= (1 << CS11);
		interruptState = 1;
	} else {
		TCCR1B = 0;
		pulse[currentUS] = TCNT1;
		TCNT1 = 0;	
		interruptState = 0;
		issending = 0;
	}
}

//sends pulse to trigger pin of ultrasonics
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

void setleds(uint16_t distance)
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

void setExternalLed(uint16_t distance)
{	
	if(distance > 150){
		PORTA = 0b00000000;
	} else if(distance > 120){
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
	
	DDRE = 0b00000011;			//trigger pins on input, the rest on output
	DDRG = 0xFF;				// All pins are set to output for buzzer;
	DDRA = 0b11111111;			// All pins PORTB are set to output, for external Leds
	DDRD = 0b11111111;			// All pins PORTD are set to output, for leds
	// Interrupt
	EICRB |= 0b00000101;
	EIMSK |= 0b00110000;

	//Initialize Timer0 for buzzer
	TCNT0 = 0x00;
	TCCR0 = 0b00000111; // set prescaler on 1024 to achieve latest overflow interrupt possible

	//TIMER set overflow enabled for timers0 and 1
	TIMSK = (1 << TOIE1) | (1 << TOIE0);
	
	//TCCR1B |= ((1 << CS10));
		
	sei();
	
    uint16_t distance[2] = {0,0};
	uint16_t smallest_distance;
    while (1) 
    {
		if(0 == issending) {			
			currentUS = (1 == currentUS) ? 0 : 1;
			sendPulse(currentUS);
		}
		
		clear_display();
		
		smallest_distance = 0xFFFF;
		int i;
		for (i = 0; i < 2; i++)
		{
			distance[i] = pulse[i] / 58;
			set_cursor(i * 0x40); // line 1 or 2
			if(distance[i] >= 0) 
			{
				if(smallest_distance > distance[i]) smallest_distance = distance[i];
				char str[10];
				sprintf(str, "US%d: %d", (i + 1), distance[i]);
				lcd_write_string(str);	
			}
			else {
				lcd_write_string("ERROR");
			}
		}
		
		setExternalLed(smallest_distance);
		max_overflow = smallest_distance / 4;
		wait(250);
    }
	
}

//regel 1: 0x00;
//regel 2: 0x40;
