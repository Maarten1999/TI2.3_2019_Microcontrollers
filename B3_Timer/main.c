/*
 * B3_Timer.c
 *
 * Created: 13-2-2019 10:40:41
 * Author : Maarten
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.>h
#include <stdio.h>
#include <stdlib.h>

ISR (TIMER2_COMPA_vect){
	
}
ISR (TIMER2_COMPB_vect){
	
}

int main(void)
{
	DDRD = 0x00; //set PORTD as input
	//TCCR2 = 0x0F; //0b00001101
	
	TCNT1 = 0;	//inital value of timer counter
	
	TCCR2A |= 0x02;	
	TCCR2B |= (1 << 3) | (1 << 2) | (1 << 0); //init timer 2
	
	OCR2A = 3750; // 15 ms
	OCR2B = 6250; // 25 ms
	
	TIMSK2 |= (1 << 1) | (1 << 2);	//set timer interrupts A,B for timer 2
	
	sei();
	
    while (1) 
    {
    }
}
