/*
 * ultrasonic.h
 *
 * Created: 30-3-2019 13:54:11
 *  Author: Maarten
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

void init_ultrasonic(void);
int get_distance(int us);
int get_smallest_distance(void);
int update_ultrasonic(void);


#endif /* ULTRASONIC_H_ */