/*
 * buzzer.c
 *
 * Created: 30-3-2019 10:16:33
 *  Author: Maarten
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "buzzer.h"

void set_frequency_buzzer(int f);
void handle_interval_interrupt(void);

//variables for buzzer
const float sec_per_overflow = 0.032768;
int overflow_count = 0;	//number of overflows
int max_overflow = 100; //initial value
enum Buzzer buzzer_state = OFF;
int current_chord = 0;

//Hardcoded song
const int song[][2] = {
	{G6,LONG_PAUSE}, {G6,LONG_PAUSE},// {G6,LONG_PAUSE}, {G6,LONG_PAUSE},// {G6,LONG_PAUSE},
	{G6,LONG_PAUSE}, {G6,LONG_PAUSE}, {G6,LONG_PAUSE}, {G6,SHORT_PAUSE},{G6,SHORT_PAUSE},
	{G6,VERY_LONG_PAUSE}, {G6,LONG_PAUSE}, {G6,LONG_PAUSE},{A6,VERY_LONG_PAUSE},{B6, VERY_LONG_PAUSE},
	{20000, LONG_PAUSE},
	{G6,LONG_PAUSE}, {G6,LONG_PAUSE}, {G6,LONG_PAUSE}, {G6,LONG_PAUSE}, {G6,LONG_PAUSE},
	{G6,SHORT_PAUSE}, {G6,SHORT_PAUSE}, {G6,VERY_LONG_PAUSE},{G6,LONG_PAUSE},//{G6,LONG_PAUSE},
	{G6,LONG_PAUSE}, {E6,LONG_PAUSE}, {D6,LONG_PAUSE}, {E6,VERY_LONG_PAUSE}, {G6,VERY_LONG_PAUSE},
	{0, 0}
};

//Interrupt for the interval of the tone
ISR(TIMER0_OVF_vect){
	overflow_count++;
	if(max_overflow <= overflow_count){
		handle_interval_interrupt();
	}
}

//Initializes the buzzer
void init_buzzer(void){
	//init timer3 for PWM signal
	DDRE |= ( 1 << PE3)	;		//set output pin for buzzer
	TCCR3A = 0b10000010;	//set compare on OC3A
	TCCR3B = 0b00011000;	//Fast PWM, top=ICR1
	TCCR3B |= (1 << CS31);	//start timer with prescaling 8

	//Initialize Timer0 for buzzer interval
	TCNT0 = 0x00;
	TCCR0 = 0b00000111; // set prescaler on 1024 to achieve latest overflow interrupt possible

	//TIMER set overflow enabled for timers0 and 1
	TIMSK = (1 << TOIE1) | (1 << TOIE0);

}

//Set the buzzer off
void set_sound_buzzer_off(void){
	TCCR3B &= ~(1 << CS31);	//stops the timer
}

//Toggle the state of the buzzer on/off
void toggle_buzzer(void){
	TCNT3 = 0;
	TCCR3B ^= (1 << CS31);	//Toggle on/off the prescaler 8 and start/stop the timer
}

//change buzzer variables: frequency and time out
void set_buzzer_values(int f, int new_max_overflow)
{
	if (PLAYING_SONG != buzzer_state)
	{
		max_overflow = new_max_overflow;
		set_frequency_buzzer(f);
	}
}

//To initialize the song
void play_song(void)
{
	if(PLAYING_SONG != buzzer_state) 	current_chord = 0;
		buzzer_state = PLAYING_SONG;
}

//this method set the frequency of the buzzer tone
void set_frequency_buzzer(int f){
	int ms = (int)(1.0 / f * 1000000.0); //convert frequency in Hz to time in ms
	OCR3A = ms / 2;
	ICR3 = ms;
}

//This method handles the interrupt
void handle_interval_interrupt(void)
{
	overflow_count = 0;
	TCNT0 = 0x00;
	switch(buzzer_state)
	{
		case PLAYING_SONG:
			if(0 != song[current_chord][0])
			{
				set_sound_buzzer_off();
				max_overflow = song[current_chord][1];
				set_frequency_buzzer(song[current_chord][0]);
				current_chord++;
				toggle_buzzer();
			}
			else buzzer_state = ON;
			break;
		case ON:
			set_sound_buzzer_off();
			buzzer_state = OFF;
			break;
		case OFF:
			toggle_buzzer();
			buzzer_state = ON;
			break;
	}	
}
