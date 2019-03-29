/*
 * Eindopdracht.c
 *
 * Created: 20-3-2019 09:41:59
 * Author : Ralph Rouwen
 */ 

#define F_CPU 8e6

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#include "lcd.h"

int interruptState = 0;

char string[20];
int timerTick = 0;
int teller = 0;

//ISR(INT6_vect){
	//teller++;
	//if(0 == interruptState){
		//TCNT1 = 0;
		//interruptState = 1;
	//} else if(1 == interruptState) {
		//timerTick = TCNT1;
	//}
//}

int main(void)
{
	// init lcd 
	init();
	
	// trigger(0) output en echo(1) input
	DDRE = 0b00000001;
	
	// Interrupt 
	//EICRB = 0b00000001;
	//EIMSK |= 0b00100000;	
		
	//TCCR1A = 0x00; // alles nu
	TCCR1B |= 0x02; //prescaler van 8 
	//TCCR1C = 0x00; //NULLLLLL
	
	
	// Timer eerst rising edge want echo wordt high
	// echo heel de tijd high
	// wachten voor echo, echo wordt low
	// Timer faling edge 0b00000110
	
	//1 stuur hoog signaal naar trigger
		// write low on trigger
		// wait 5 ms
		// write high on trigger
		// wait 10ms 
		// terug zetten op low
	//2 timer starten
	//3 echo ontvangen
	//4 timer stoppen en tijd meten 
	
	sei();
	
    while (1) 
    {
		//teller++;
		//lcd_write_string("JOEJOE");
					
		//
			//PORTE &= ~(1 << 0);
			//_delay_us(5);
			PORTE |= (1 << 0);
			_delay_us(20);
			PORTE &= (~(1 << 0));	
			//interruptState = 0;
		
		
		
		//int sensorDistance = (((timerTick / 1000000) * 346) * 100) / 2;
		//itoa(sensorDistance, string, 10);
		//lcd_write_string(string);
		int i;
		for(i = 0; i< 1;i++){
		
			_delay_ms(20);
		}
	}
}