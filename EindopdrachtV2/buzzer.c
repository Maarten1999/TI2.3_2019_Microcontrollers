/*
 * buzzer.c
 *
 * Created: 30-3-2019 10:16:33
 *  Author: Maarten
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "buzzer.h"

void init_buzzer(void){
	//init timer3 for PWM signal
	DDRE |= ( 1 << PE3)	;		//set output pin for buzzer
	TCCR3A = 0b10000010;	//
	TCCR3B = 0b00011000;	//fast pwm, top=ICR1
	TCCR3B |= (1 << CS31);
	//set_frequency_buzzer(1000);
}

void set_frequency_buzzer(int f){
	int ms = (int)(1.0 / f * 1000000.0); //convert frequency in Hz to time in ms
	
	

	//TCNT3 = 0;
	OCR3A = ms / 2;
	ICR3 = ms;
}

void set_sound_buzzer_off(void){
	TCCR3B &= ~(1 << CS31);	//stops the timer
}

void toggle_buzzer(void){
	TCNT3 = 0;
	TCCR3B ^= (1 << CS31);	//Toggle on/off the prescaler 8 and start/stop the timer
}
