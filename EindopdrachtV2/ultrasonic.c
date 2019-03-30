
/*
 * ultrasonic.c
 *
 * Created: 28-3-2019 20:36:45
 *  Author: Ralph Rouwen
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

void check_interrupt(void);
void send_pulse(int pin);

//variabels for ultrasonic sensors
int currentUS = 0; // 0 or 1;
int interruptState = 0;
int pulse[] = { 0,0 };
int issending = 0; //0 or 1
uint16_t smallest_distance = 0xFFFF;

//echo		: port E4 & port E5
//trigger	: port E0 & port E1

//Interrupt for first ultrasonic
ISR(INT4_vect)
{
	check_interrupt();
}

//Interrupt for second ultrasonic
ISR(INT5_vect)
{
	check_interrupt();
}

void init_ultrasonic(void)
{
	DDRE |= 0b00000011;			//trigger pins on output, the rest on input
	
	// Interrupts
	EICRB |= 0b00000101;		//set both interupts on any logical change
	EIMSK |= 0b00110000;		//enable int4 and int5
}

int get_distance(int us)
{
	int distance = pulse[us] / 58;
	return (0 < distance) ? distance : 0;
}

int get_smallest_distance(void)
{
	return smallest_distance;
}

void update_ultrasonic(void)
{
	if(0 == issending) {
		currentUS = (1 == currentUS) ? 0 : 1;
		send_pulse(currentUS);
	}
	
	smallest_distance = 0xFFFF;
	
	int i;
	for (i = 0; i < 2;i++)
	{
		int distance = get_distance(i);
		if(smallest_distance > distance) smallest_distance = distance;
	}
}

//method to handle interrupts of both ultrasonics
void check_interrupt(void)
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
void send_pulse(int pin)
{
	issending = 1;
	PORTE &= ~(1 << pin);
	_delay_us(5);
	PORTE |= (1 << pin);
	_delay_us(15);
	PORTE &= (~(1 << pin));
}