#include <avr/io.h>
#include <avr/interrupt.h>
#include "LibreriaServoPWM.h"
#include "LibreriaADC.h"

volatile uint8_t current_channel = 0; // Comenzar en ADC0

// TIMER 0 - Multiplexado
void init_timer0(void)
{
	// Operamos el temporizador en modo NORMAL
	TCCR0B |= (1 << CS01) | (1 << CS00);	// Prescaler de 64
	TCNT0 = 0;
	
	// Habilitar interrupciones por overflow de TIMER0
	TIMSK0 |= (1 << TOIE0);
}

int main(void)
{
	cli();
	DDRB |= (1 << DDB1) | (1 << DDB2);  // Configurar PB0 como salida
	setup_adc();  // Configurar ADC
	init_timer1();  // Inicializar Timer1 en modo Fast PWM
	init_timer0();
	sei();  // Habilitar interrupciones globales

	while (1)
	{
		// La ISR del ADC se encargará de actualizar el PWM
	}

	return 0;
}

// Timer0 Overflow - dispara conversión ADC
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0; // Reiniciar contador
	ADCSRA |= (1 << ADSC); // Iniciar conversión
}

// ADC listo - se ejecuta cuando termina la conversión
ISR(ADC_vect)
{
	uint8_t adc_value = ADCH; // Si usás ADLAR = 1, ADCH ya contiene los 8 bits más significativos

	switch (current_channel)
	{
		case 0:
		PWM1_set_pulse_width(adc_value); // PWM para canal 0 (OC1A)
		current_channel = 1;
		adc_set_channel(1);
		break;

		case 1:
		PWM2_set_pulse_width(adc_value); // PWM para canal 1 (OC1B)
		current_channel = 0;
		adc_set_channel(0);
		break;
	}
}