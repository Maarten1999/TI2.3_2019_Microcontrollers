///*
 //* lcd.c
 //*
 //* Created: 13-2-2019 16:05:16
 //*  Author: Maarten
 //*/ 
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#define LCD_E	3
#define LCD_RS	2

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
	PORTC |= (1<<LCD_RS); //set RS to character mode
	PORTC = byte;
	lcd_strobe_lcd();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd();
}

void clear_display(){
	PORTC &= ~(1<<LCD_RS); //set RS to instruction mode
	PORTC = 0x00;
	lcd_strobe_lcd();

	// Second nibble
	PORTC = 0x10;
	PORTC &= ~(1<<LCD_RS); //set RS to instruction mode
	lcd_strobe_lcd();
}
