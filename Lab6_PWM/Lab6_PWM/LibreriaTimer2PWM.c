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

// Inicialización de TIMER2 - PWM Manual
void init_timer2_manualpwm(void)
{
	// Modo Normal, TOP = 255
	TCCR2B |= (1 << CS21); // Prescaler de 8
	
	// Habilitación de interrupciones por overflow de timer y output compare match
	TIMSK2 |= (1 << OCIE2A) | (1 << TOIE2);
	
	DDRD |= (1 << manual_pwm_pin); // Salida de PWM
}

// Establecer ancho de pulso en TIMER2
void timer2_set_PW(uint8_t value)
{
	OCR2A = 255 - value;
}



