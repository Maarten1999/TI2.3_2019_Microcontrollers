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
#include "buzzer.h"
#include "ultrasonic.h"

#define MIN_CRASHED_DISTANCE 5

//method to wait before code is runned
void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

//sets the 5 leds on portA on the basis of distance
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
	//LCD init
	init_lcd();

	//Buzzer init
	init_buzzer();

	//Ultrasonic init
	init_ultrasonic();
	
	DDRA = 0b11111111;			// All pins PORTB are set to output, for external Leds
		
	sei();

    while (1) 
    {
		update_ultrasonic();
		clear_display();
		
		int i;
		for (i = 0; i < 2; i++)
		{
			int distance = get_distance(i);
			char str[10];
			sprintf(str, "US%d: %d", (i + 1), distance);
			set_cursor(i * 0x40); // line 1 or 2
			lcd_write_string(str);	
		}

		uint16_t smallest_distance = get_smallest_distance();
		if(0 != smallest_distance)
		{
			setExternalLed(smallest_distance);
			set_buzzer_values(1000 - smallest_distance, smallest_distance / 4);
			
			if(MIN_CRASHED_DISTANCE > smallest_distance) play_song();
		}
		wait(250);
    }
	
}
