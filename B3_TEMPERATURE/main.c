/*
 * B3_TEMPERATURE.c
 *
 * Created: 20-2-2019 10:32:05
 * Author : Maarten
 */ 

#define F_CPU 8e6
#define LCD_E	3
#define LCD_RS	2
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

void clear_display(){
	PORTC &= ~(1<<LCD_RS); //set RS to instruction mode
	PORTC = 0x00;
	lcd_strobe_lcd();

	// Second nibble
	PORTC = 0x10;
	PORTC &= ~(1<<LCD_RS); //set RS to instruction mode
	lcd_strobe_lcd();
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

void lcd_write_string(char *string){
	for (;*string;string++)
	{
		lcd_write_data(*string);
	}
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
