/*
 * B1_ADC_LED.c
 *
 * Created: 20-2-2019 10:22:11
 * Author : Maarten
 */ 

#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

void adcInit(void)
{

    // 7 en 6 bits AREF = VCC : 01
    // 5 ADLAR enabled : 1
    // 4 3 2 1 0 channels alleen 0 enabled
    ADMUX = 0b01100001;

    // 6 en 7  bits enable and start hoog
    // 5 bit free running aan
    // 4 en 3 interrupt disabled
    // 2 en 1 en 0 prescaler is 64: 110
    ADCSRA = 0b11100110;
}

int main(void)
{
    //PORTF op input
    DDRF = 0x00;
    // DDRA en DDRB op output 
    DDRA = 0xFF;
    DDRB = 0xFF;
    adcInit();
    
    while (1) 
    {
        PORTB = ADCL;
        PORTA = ADCH;
        wait(100);
    }
}
