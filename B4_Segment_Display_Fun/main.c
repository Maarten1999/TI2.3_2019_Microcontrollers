#define F_CPU 8e6

/*
 * B3_Segment_Display.c
 *
 * Created: 6-2-2019 12:14:55
 * Author : Gerben
 */ 

#include <avr/io.h>
#include <util/delay.h>

const unsigned char Segments[10] =
{
	0b00000001, //0
	0b00000010, //1
	0b00000011, //2
	0b00000110,	//3
	0b00001100, //4
	0b00011000,
	0b00110000,
	0b01100000,
	0b11000000,
	0b11111111
};

int currentSegment = 0;

int main(void)
{
	DDRA = 0xff;

    while (1) 
    {
		display(currentSegment);
		if(currentSegment < 11) {
			currentSegment++;
		}
		else {
			currentSegment = 0;
		}
		wait(1000);	// library function (max 30 ms at 8MHz)
    }
}

void display(int digit)
{
	PORTA = Segments[digit];
}
