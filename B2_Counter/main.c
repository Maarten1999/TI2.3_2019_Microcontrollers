/*
 * B2_Counter.c
 *
 * Created: 13-2-2019 10:40:08
 * Author : Maarten
 */  
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#define LCD_E	3
#define LCD_RS	2

void lcd_write_byte(unsigned int byte){
	PORTC |= (1<<LCD_RS); //set RS to character mode
	PORTC = byte;
	lcd_strobe_lcd();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd();
}

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
		lcd_write_byte(TCNT2);
		_delay_ms(1000);
		//lcd_strobe_lcd();
    }
}



