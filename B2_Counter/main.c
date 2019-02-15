/*
 * B2_Counter.c
 *
 * Created: 13-2-2019 10:40:08
 * Author : Maarten
 */  
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#define LCD_E	3
#define LCD_RS	2

int main(void)
{
	DDRD = 0x00;
	TCCR2 = 0x07; //0b00000111
	init();
	clear_display();
	lcd_write_string("H?");
	
	set_cursor(0x40);
	
	lcd_write_string("Hello");
    while (1) 
    {
		clear_display();
		char string[10];
		itoa(TCNT2, string, 10);
		//sprintf(string, "%d", TCNT2); // is beide mogelijk
		lcd_write_string(string);
		_delay_ms(1000);
    }
}



