
/*
 * ultrasonic.h
 *
 * Created: 27-3-2019 13:11:36
 *  Author: Ralph Rouwen
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

void US_SendPulse(void);
void US_InterruptUpdate(void);
int16_t US_GetDistance(void);
