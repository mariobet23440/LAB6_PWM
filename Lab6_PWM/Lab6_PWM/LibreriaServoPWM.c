/*
 * LibreriaServoPWM.c
 *
 * Created: 11/04/2025 13:12:41
 *  Author: mario
 */ 

#include "LibreriaServoPWM.h"

void init_timer1(void)
{
	TCCR1A |= (1 << COM1A1) | (1 << WGM11); // Fast PWM, OC1A no invertido
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Prescaler de 8, Fast PWM
	ICR1 = 39999;							// Establecer TOP a 39999 (Frecuencia de 50 Hz, 20ms)
	DDRB |= (1 << DDB0);					// Configurar PB1 como salida (OC1A)
}

// Establecer ancho de pulso para PWM1
// La entrada value debe ser un número de 0 a 255
void PWM1_set_pulse_width(uint16_t value)
{
	uint16_t ticks = (3800/256) * value + 1000;	// Función empírica para giro de 180°
	if (ticks > ICR1) ticks = ICR1;			// Truncar ticks a ICR1 si se pasan del valor
	OCR1A = ticks;							// Ajustar el valor de OCR1A
}