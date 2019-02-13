/*
 * B2_Counter.c
 *
 * Created: 13-2-2019 10:40:08
 * Author : Maarten
 */ 
/*
 * B1_LCD.c
 *
 * Created: 13-2-2019 10:39:44
 * Author : Maarten
 */ 
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#define LCD_E	3
#define LCD_RS	2

int main(void)
{
	init();
	clear_display();
	lcd_write_string("H?");
	
	set_cursor(0x40);
	
	lcd_write_string("Hello");
    while (1) 
    {
		//lcd_strobe_lcd();
    }
}

