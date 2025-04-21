/*
 * LibreriaServoPWM.h
 *
 * Created: 11/04/2025 13:12:11
 *  Author: mario
 */ 


#ifndef LIBRERIASERVOPWM_H_
#define LIBRERIASERVOPWM_H_

#include <avr/io.h>
void init_timer1(void);
void PWM1_set_pulse_width(uint16_t value);
void PWM2_set_pulse_width(uint16_t value);


#endif /* LIBRERIASERVOPWM_H_ */