#define F_CPU 8e6

/*
 * B3_Segment_Display.c
 *
 * Created: 6-2-2019 12:14:55
 * Author : Gerben
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const unsigned char Numbers[15] =
{
	//dPgfe dcba
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111,	//3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111,	//9 (element)//10
	
	//Hexadecimal value's
	//	dPgfe dcba
	0b01110111,	//A
	0b01111100,	//B
	0b00111001,	//C
	0b01011110, //D
	0b01111001	//E for error 
};

int currentDigit = 0;

ISR(INT0_vect) //PD0 = poort 0 
{
	//up
	currentDigit++;
	display(currentDigit);
	if(currentDigit > 15)
	{	
		currentDigit = 0;
		display(currentDigit);
	}
}

ISR(INT1_vect)
{
	//down
	if(currentDigit > 0) {
		currentDigit--;
		display(currentDigit);	
	}
}

int main(void)
{
	DDRD = 0xf0; //11110000 0-3 input 4-7 output 
	DDRA = 0xff;
	
	EICRA |= 0x0f;
	EIMSK |= 0x03;
	
	sei();
	display(0);

    /* Replace with your application code */
    while (1) 
    {
		
		
    }
}

void display(int digit)
{
	printf("CurrentDigit: %d", currentDigit);
	if(digit < 15)
	{
		PORTA = Numbers[digit];
	}
}
