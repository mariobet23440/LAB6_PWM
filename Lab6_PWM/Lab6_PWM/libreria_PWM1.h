/*
 * libreria_PWM1.h
 *
 * Created: 10/04/2025 22:31:39
 *  Author: mario
 */ 


#ifndef LIBRERIA_PWM1_H_
#define LIBRERIA_PWM1_H_

// INICIALIZAR TIMER1 (Lo usaremos por precisión)
void initTimer1(void);
void PWM1_set_pulse_ms(uint16_t pulse_us)
#include "libreria_PWM1.c"

#endif /* LIBRERIA_PWM1_H_ */