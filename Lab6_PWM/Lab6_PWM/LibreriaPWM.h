/*
 * LibreriaPWM.h
 *
 * Created: 11/04/2025 10:49:07
 *  Author: mario
 */ 


#ifndef LIBRERIAPWM_H_
#define LIBRERIAPWM_H_

#include <avr/io.h>
void init_timer1(void);
void PWM1_set_pulse_width(unsigned int value);



#endif /* LIBRERIAPWM_H_ */