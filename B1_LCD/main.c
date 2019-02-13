/*
 * B1_LCD.c
 *
 * Created: 13-2-2019 10:39:44
 * Author : Maarten
 */ 
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#define LCD_E	3
#define LCD_RS	2

void init(void);
void display_test(void);
void lcd_strobe_lcd(void);

int main(void)
{
	DDRD = 0xFF;
	init();
	display_test();
	
    while (1) 
    {
    }
}

void display_test(void)
{
	// First nibble.
	PORTC = 0x40;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd();

	// Second nibble
	PORTC = 0x60;
	PORTC |= (1<<LCD_RS);
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
	PORTC = 0x00;
	
	//Return home
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
	PORTC = 0xF0;
	lcd_strobe_lcd();
	
	//entry modeL cursor to right, no shift 0x06
	PORTC = 0x00;
	lcd_strobe_lcd();
	PORTC = 0x60;
	lcd_strobe_lcd();
}

