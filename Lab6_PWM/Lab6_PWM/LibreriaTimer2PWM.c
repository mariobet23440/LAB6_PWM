/*
 * LibreriaTimer2PWM.c - LIBRERIA PWM CON TIMER2
 *
 * Created: 11/04/2025 18:44:56
 *  Author: Mario Alejandro Betancourt Franco
 * Descripción: Librería para PWM en TIMER2. Permite usar OC2A y OC2B 
 * con una frecuencia de 50 Hz, con un control del ciclo de trabajo adecuado 
 * para hacer luces con dimmer.
 */ 

#include "LibreriaTimer2PWM.h"

void init_timer2(void)
{
	// Modo Fast PWM, TOP = 255, salida no invertida en OC2A y OC2B
	TCCR2A |= (1 << COM2A1) | (1 << COM2B1) | (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << CS21); // Prescaler de 8

	DDRB |= (1 << DDB3); // PB3 como salida (OC2A)
	DDRD |= (1 << DDD3); // PD3 como salida (OC2B)
}

// Establecer duty cycle para OC2A (PWM1), valor de 0 a 255
void TIMER2_PWM1_set_duty(uint8_t value)
{
	OCR2A = value;
}

// Establecer duty cycle para OC2B (PWM2), valor de 0 a 255
void TIMER2_PWM2_set_duty(uint8_t value)
{
	OCR2B = value;
}




