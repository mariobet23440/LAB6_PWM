/*
 * LibreriaADC.c
 *
 * Created: 11/04/2025 10:14:16
 *  Author: mario
 */ 


#include "LibreriaADC.h"


// FUNCIONES NO DE INTERRUPCIÓN
// Inicializar ADC
void setup_adc(void)
{
	ADMUX  |= (1 << ADLAR) | (1 << REFS0);	// ADMUX: Ajuste a la izquierda (ADLAR), Referencia AVCC (REFS0), activación de canal 0
	ADCSRA |= (1 << ADEN) | (1 << ADIE);     // Activar ADC e Interrupciones por conversión completa
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);	// Prescaler de 64
	ADCSRA |= (1 << ADSC);					// Iniciar Conversión
}

// Cambiar canal de ADC con número de canal
// Recordemos que MUX3-MUX0 son los bits 3-0 de ADMUX (Los últimos 4)
void adc_set_channel(unsigned char channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
}