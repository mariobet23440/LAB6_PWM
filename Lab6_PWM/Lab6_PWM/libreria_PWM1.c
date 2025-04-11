/*
 * libreria_PWM1.c
 *
 * Created: 10/04/2025 23:18:58
 *  Author: mario
 */ 

#include <avr/io.h>
#include "libreria_PWM1.h"

// INICIALIZAR TIMER1 (Lo usaremos por precisión)
void initTimer1(void)
{
	TCCR1A |= (1 << COM1A0) | (1 << WGM11); // No invertido, Fast-PWM (TOP en ICR1)
	TCCR0B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler de 11
	ICR1 = 39999; // TOP = 39999 ? 50 Hz (20 ms)
}

void PWM1_set_pulse_ms(uint16_t pulse_us)
{
	if (pulse_us < 1000) pulse_us = 1000;
	if (pulse_us > 2000) pulse_us = 2000;

	OCR1A = pulse_us * 2; // 1 tick = 0.5us (prescaler 8)
}

