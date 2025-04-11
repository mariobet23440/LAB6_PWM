/*
 * LibreriaPWM.c
 *
 * Created: 11/04/2025 10:49:28
 *  Author: mario
 */ 

#include "LibreriaPWM.h"

#include <stdint.h>

// INICIALIZAR TIMER1 (Lo usaremos por precisión)
void init_timer1(void)
{
	TCCR1A |= (1 << COM1A0) | (1 << WGM11); // No invertido, Fast-PWM (TOP en ICR1)
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Prescaler de 8
	ICR1 = 39999;							// TOP = 39999 ? 50 Hz (20 ms)
	TIMSK1 |= (1 << OCIE1A) | (1 << TOIE1); // Habilitar interrupciones por Output Compare Match y Overflow de TIMER1 
	OCR1A  = 0x0050;
}

void PWM1_set_pulse_width(unsigned int value)
{
	unsigned int ticks = value * 2; // 1 tick = 0.5us
	if (ticks > ICR1) ticks = ICR1;
	OCR1A = ticks;
}