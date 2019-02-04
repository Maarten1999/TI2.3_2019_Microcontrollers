/*
 * Microcontrollers2.3.c
 *
 * Created: 30-1-2019 10:55:25
 * Author : Maarten
 */ 
#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

void OpdrachtB2();
void OpdrachtB3();
void OpdrachtB4();
void OpdrachtB4_V2();
void OpdrachtB5();
void OpdrachtB6();
void OpdrachtB7();

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
	while(1){
		OpdrachtB7();
	}
	return 1;
	
}

void OpdrachtB2()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	
	PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
	wait(500);				// Wait 500miliseconds
	PORTD = 0b00100000;		// Set all leds to 0 except LED of port 6
	wait(500);				// Wait 500miliseconds
	
}

void OpdrachtB3()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b00000000;			// All pins PORTC are set to input
	
	
	if(PINC & (1<< PINC0)){
		PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
		wait(500);				// Wait 500 miliseconds
		PORTD = 0b00000000;		// Set all leds to 0
		wait(500);				// Wait 500 miliseconds
	}
	
}

// Lichtloop van 8 leds dmv shiften 1
void OpdrachtB4()
{
	DDRD = 0b11111111;		
	static int value = 0b0000001;

	PORTD = value;
	value = value << 1;
		
	if(value == 0b100000000){
		value = 0b0000001;	
	}
	wait(250);
	
}


void OpdrachtB4_V2(){
	DDRA = 0b11111111;				// All pins PORTA are set to output
	static int value = 0b00000001;	// Initial value of loop light.
	static int turn = 1;			// Boolean to save the direction

	PORTA = value;
	if(turn)
		value = (value << 1);		//Bitshift to the left
	else
		value = (value >> 1);		//Bitshift to the right
	if(value == 0b10000000)			//End of the row
		turn = 0;					//Switch direction
	else if(value == 0b00000001)	//Start of the row
		turn = 1;					//Switch direction
	wait(250);						//Wait 250 milliseconds
	
}

//void OpdrachtB.5 Light effect
typedef struct {					//Struct that holds the value of the row and the delay
	unsigned char data;
	unsigned int delay ;
} LIGHTEFFECT_STRUCT;

//Array with the values of the light pattern
LIGHTEFFECT_STRUCT lighteffect[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x00, 100},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0xAA,  50}, {0x55,  50},
	{0x00, 100},
	{0x81, 100}, {0x42, 100}, {0x24, 100}, {0x18, 100}, {0x0F, 200}, {0xF0, 200}, {0x0F, 200}, {0xF0, 200},
	{0x00, 0x00}
};

void OpdrachtB5(){
	DDRA = 0b11111111;			// All pins PORTA are set to output
	
	int index = 0;
	//loops through the array until the value is 0
	while(lighteffect[index].delay != 0){	
		// sets the pins of PORTA to the first value in the struct
		PORTA = lighteffect[index].data;
		// waits the second value of the struct in milliseconds	
		wait(lighteffect[index].delay);		
		index++;
	}
}

void OpdrachtB6()
{
	DDRD = 0b11111111;			// All pins PORTD are set to output
	DDRC = 0b00000000;			// All pins PORTC are set to input
	
	static int PRESSED, prev_state = 0;
	static int MILLISECONDS = 500;

	const int pushed = PINC & (1 << PINC0);
	if(pushed && prev_state == 0)			// Checks if port C0 is pressed = 0;
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
		prev_state = 1;
	}
	else if(!pushed)		
		prev_state = 0;
		
	PORTD = 0b01000000;		// Set all leds to 0 except LED of port 7
	wait(MILLISECONDS);		// Wait x miliseconds
	PORTD = 0b00000000;		// Set all leds to 0
	wait(MILLISECONDS);		// Wait x miliseconds
	
}

void OpdrachtB7() {
		setCharliePlexingLed(1);
		wait(500);
		setCharliePlexingLed(2);
		wait(500);
		setCharliePlexingLed(3);
		wait(500);
		setCharliePlexingLed(4);
		wait(500);
		setCharliePlexingLed(5);
		wait(500);
		setCharliePlexingLed(6);
		wait(500);
}

void setCharliePlexingLed(int lednr)
{
	//pin 1 = A1
	//pin 2 = B1
	//pin 3 = C1
	
	switch(lednr)
	{
		case 1: //led1
		DDRA = 0b11111011;			// All pins PORTD are set to output except 3 (input)
		//values:
		PORTA = 0b00000001;			// Set all leds to 0 except 1
		break;
		case 2: //led2
		DDRA = 0b11111011;
		//values:
		PORTA = 0b00000010;
		break;
		case 3: //led3
		DDRA = 0b11111110;
		//values:
		PORTA = 0b00000010;
		break;
		case 4: //led4
		DDRA = 0b11111110;
		//values:
		PORTA = 0b00000100;
		break;
		case 5: //led5
		DDRA = 0b11111101;
		//values:
		PORTA = 0b00000100;
		break;
		case 6: //led2
		DDRA = 0b11111101;
		//values:
		PORTA = 0b00000001;
		break;
	}
}