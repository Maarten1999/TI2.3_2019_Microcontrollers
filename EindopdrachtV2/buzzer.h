/*
 * buzzer.h
 *
 * Created: 30-3-2019 10:16:49
 *  Author: Maarten
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

void init_buzzer(void);
void set_frequency_buzzer(int f);
void set_sound_buzzer_off(void);
void toggle_buzzer(void);

#endif /* BUZZER_H_ */