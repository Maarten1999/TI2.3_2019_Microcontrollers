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
	PORTC &= ~(1<<LCD_RS); 
	PORTC |= 0x01; //clear display
	lcd_write_string("How are you today?");
	
	set_cursor(0x40);
	
	lcd_write_string("Hello");
    while (1) 
    {
		//lcd_strobe_lcd();
    }
}

void set_cursor(unsigned int posHex){
	unsigned int byte = 0x80 + posHex; //set DDRAM address
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd();
}

void lcd_strobe_lcd(void)
{
	PORTC |= (1<<LCD_E);
	_delay_ms(1);
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);
}

void init(void)
{
	DDRC = 0xFF;
	
	PORTC &= ~(1<<LCD_RS);
	
	//Return home
	PORTC = 0x00;
	lcd_strobe_lcd();
	PORTC = 0x20;
	lcd_strobe_lcd();
	
	//Set 4 bits mode:
	PORTC = 0x20;
	lcd_strobe_lcd();
	PORTC = 0x80;
	lcd_strobe_lcd();
	
	//Display: on, cursor off, blinking  0x0c
	PORTC = 0x00;
	lcd_strobe_lcd();
	PORTC = 0xC0;
	lcd_strobe_lcd();
	
	//entry modeL cursor to right, no shift 0x06
	PORTC = 0x00;
	lcd_strobe_lcd();
	PORTC = 0x60;
	lcd_strobe_lcd();
	
	// RAM adress : 0, first position, line 1
	PORTC = 0x80;
	lcd_strobe_lcd();
	PORTC = 0x00;
	lcd_strobe_lcd();
}

void lcd_write_string(char *string){
	for (;*string;string++)
	{
		lcd_write_data(*string);
	}
}

void lcd_write_data(unsigned char byte){
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS); //set RS to character mode
	lcd_strobe_lcd();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd();
}

