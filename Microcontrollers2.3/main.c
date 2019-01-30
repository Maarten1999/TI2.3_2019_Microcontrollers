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
	//OpdrachtB3();	
	OpdrachtB6();
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
		if(PINC & (1<< PINC0)){		// Checks if port C0 is pressed = 0;
			PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
			wait(500);				// Wait 500 miliseconds
			PORTD = 0b00000000;		// Set all leds to 0
			wait(500);				// Wait 500 miliseconds
		}
	}
}

void OpdrachtB6()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b00000000;			// All pins PORTC are set to input
	
	int PRESSED = 0;
	int MILLISECONDS = 500;
	
	while(1) 
	{
		if(PINC & (1<< PINC0))			// Checks if port C0 is pressed = 0;
		{
			if(PRESSED == 0)			// If value of pressed was 0
			{
				PRESSED = 1;			// Used as a sort of boolean
				MILLISECONDS = 125;		//Set time to wait to 125 miliseconds
			}
			else {						// If PRESSED = 1	
				PRESSED = 0;			//Set PRESSED back to 0
				MILLISECONDS = 500;		//Set time to wait back to 500 miliseconds
			}
		}
		
		PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
		wait(MILLISECONDS);		// Wait x miliseconds
		PORTD = 0b00000000;		// Set all leds to 0
		wait(MILLISECONDS);		// Wait x miliseconds
		
	}
}
