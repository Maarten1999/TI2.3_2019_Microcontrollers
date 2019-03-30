/*
 * buzzer.h
 *
 * Created: 30-3-2019 10:16:49
 *  Author: Maarten
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

//notes for the song
#define C6  661
#define D6  588
#define E6  524
#define F6  495
#define G6  441
#define A6  393
#define B6  350
#define C7  330

#define VERY_SHORT_PAUSE 1
#define VERY_LONG_PAUSE 20
#define SHORT_PAUSE 5
#define LONG_PAUSE 10

enum Buzzer{PLAYING_SONG, ON, OFF};

void init_buzzer(void);
void set_sound_buzzer_off(void);
void toggle_buzzer(void);
void set_buzzer_values(int f, int new_max_overflow);
void play_song(void);

#endif /* BUZZER_H_ */