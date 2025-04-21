/*
 * LibreriaTimer2PWM.h
 *
 * Created: 11/04/2025 18:44:07
 *  Author: mario
 */ 


#ifndef LIBRERIATIMER2PWM_H_
#define LIBRERIATIMER2PWM_H_

#include <avr/io.h>
void init_timer2(void);

// Establecer duty cycle para OC2A (PWM1), valor de 0 a 255
void TIMER2_PWM1_set_duty(uint8_t value);

// Establecer duty cycle para OC2B (PWM2), valor de 0 a 255
void TIMER2_PWM2_set_duty(uint8_t value);


#endif /* LIBRERIATIMER2PWM_H_ */