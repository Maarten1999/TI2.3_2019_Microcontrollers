/*
 * Microcontrollers2.3.c
 *
 * Created: 30-1-2019 10:55:25
 * Author : Maarten
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>




/******************************************************************/
void wait( int ms )
/* 
short:			Busy wait number of millisecs
inputs:			int ms (Number of millisecs to busy wait)
outputs:	
notes:			Busy wait, not very accurate. Make sure (external)
				clock value is set. This is used by _delay_ms inside
				util/delay.h
Version :    	DMK, Initial code
*******************************************************************/
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

/******************************************************************/
int main( void )
/* 
short:			main() loop, entry point of executable
inputs:			
outputs:	
notes:			Looping forever, flipping bits on PORTD
Version :    	DMK, Initial code
*******************************************************************/
{
	//OpdrachtB2();
	OpdrachtB3();	
	return 1;
}

void OpdrachtB2()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	
	while (1)
	{
		PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
		wait(500);				// Wait 500miliseconds
		PORTD = 0b00100000;		// Set all leds to 0 except LED of port 6
		wait(500);				// Wait 500miliseconds
	}
}

void OpdrachtB3()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b00000000;			// All pins PORTC are set to input
	
	while(1)
	{
		if(PINC & (1<< PINC0)){
			PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
			wait(500);				// Wait 500 miliseconds
			PORTD = 0b00000000;		// Set all leds to 0
			wait(500);
		}
		//if(PORTC0 == 0)				// If PortC button is pressed (0) = false
		//{
			//PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
			//wait(500);				// Wait 500 miliseconds
			//PORTD = 0b00000000;		// Set all leds to 0
			//wait(500);				// Wait 500 miliseconds
		//}
	}
}
