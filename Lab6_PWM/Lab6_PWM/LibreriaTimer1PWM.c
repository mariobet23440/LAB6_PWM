/*
 * LibreriaTimer1PWM.c - LIBRERIA PWM CON TIMER1 PARA SERVOMOTORES
 *
 * Created: 11/04/2025 18:32:51
 *  Author: Mario Alejandro Betancourt Franco
 * Descripción: Librería para PWM en TIMER1 con soporte para
 * servomotores. Permite usar OC1A y OC1B con una frecuencia
 * de 50 Hz, con un control del ciclo de trabajo adecuado para
 * servomotores SG90.
 */ 

#include "LibreriaTimer1PWM.h"

void init_timer1(void)
{
	TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11); // Fast PWM, OC1A y OC1B no invertido
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Prescaler de 8, Fast PWM
	ICR1 = 39999;							// Establecer TOP a 39999 (Frecuencia de 50 Hz, 20ms)
	DDRB |= (1 << DDB1) | (1 << DDB2);		// Configurar PB1 como salida (OC1A y OC1B)
}

// Establecer ancho de pulso para PWM1
// La entrada value debe ser un número de 0 a 255
void TIMER1_PWM1_set_servo_PW(uint16_t value)
{
	uint16_t ticks = (4000/256) * value + 1000;	// Función empírica para giro de 180°
	if (ticks > ICR1) ticks = ICR1;			// Truncar ticks a ICR1 si se pasan del valor
	OCR1A = ticks;							// Ajustar el valor de OCR1A
}

void TIMER1_PWM2_set_servo_PW(uint16_t value)
{
	uint16_t ticks = (4000/256) * value + 1000;	// Función empírica para giro de 180°
	if (ticks > ICR1) ticks = ICR1;			// Truncar ticks a ICR1 si se pasan del valor
	OCR1B = ticks;							// Ajustar el valor de OCR1B
}
