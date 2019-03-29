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
#include <stdbool.h>

int overflow_count = 0;
int set_high = false;

//ISR (TIMER2_COMPA_vect){
	//
//}
//ISR (TIMER2_COMPB_vect){
	//
//}
//
ISR(TIMER0_OVF_vect){
	overflow_count++;
	if(6 == overflow_count){
		set_high = true;
		overflow_count = 0;
		TIFR=0x01;
		TCNT0 = 0x00;
	}
}

int main(void)
{
	//DDRD = 0x00; //set PORTD as input
	////TCCR2 = 0x0F; //0b00001101
	//
	//TCNT1 = 0;	//inital value of timer counter
	//
	//TCCR2A |= 0x02;	
	//TCCR2B |= (1 << 3) | (1 << 2) | (1 << 0); //init timer 2
	//
	//OCR2A = 3750; // 15 ms
	//OCR2B = 6250; // 25 ms
	//
	//TIMSK2 |= (1 << 1) | (1 << 2);	//set timer interrupts A,B for timer 2
	//
	DDRD=0xff;
	TCNT0 = 0x00;
	TCCR0 = 0b00000101;
	TIMSK = 0x01;

	sei();
	PORTD ^= (1 << 4);
    while (1) 
    {
		if(true == set_high){
			PORTD ^= (1 << 4);
			set_high = false;
			
		}

		 //while ((TIFR & 0x01) == 0);
		 //TCNT0 = 0x00;
		 //TIFR=0x01; //clear timer1 overflow flag
		 //overflow_count++;
		 //if (overflow_count>=6)
		 //{
			 //PORTD ^= (0x01 << 4);
			 //overflow_count=0;
		 //}
    }
}
