/*
 * B3_TEMPERATURE.c
 *
 * Created: 20-2-2019 10:32:05
 * Author : Maarten
 */ 

#define F_CPU 8e6
#define LCD_E	3
#define LCD_RS	2
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>


void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void adcInit(void)
{

	// 7 en 6 bits AREF = 2.56 : 11
	// 5 ADLAR enabled : 1
	// 4 3 2 1 0 channels alleen 0 enabled
	ADMUX = 0b11100001;

	// 6 en 7  bits enable and start hoog
	// 5 bit free running aan
	// 4 en 3 interrupt disabled
	// 2 en 1 en 0 prescaler is 64: 110
	ADCSRA = 0b11100110;
}

int main(void)
{
	//PORTF op input
	DDRF = 0x00;
	// DDRA en DDRB op output
	DDRA = 0xFF;
	adcInit();
	lcd_strobe_lcd();
	init();
	
	while (1)
	{
		clear_display();
		char string[10];
		itoa((ADCH<<1), string, 10);
		lcd_write_string(string);
		PORTA = ADCH;
		wait(100);
	}
}
