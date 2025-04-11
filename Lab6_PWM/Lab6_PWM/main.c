#include <avr/io.h>
#include <avr/interrupt.h>
#include "LibreriaServoPWM.h"
#include "LibreriaADC.h"

int main(void)
{
	DDRB |= (1 << DDB1);  // Configurar PB0 como salida
	setup_adc();  // Configurar ADC
	init_timer1();  // Inicializar Timer1 en modo Fast PWM
	sei();  // Habilitar interrupciones globales

	while (1)
	{
		// La ISR del ADC se encargará de actualizar el PWM
	}

	return 0;
}

ISR(ADC_vect)
{
	uint16_t adc_value = ADCH;				// Leer el valor del ADC (10 bits)
	PWM1_set_pulse_width(adc_value);		// Ajustar el ancho de pulso basado en el valor del ADC
	ADCSRA |= (1 << ADSC);					// Iniciar una nueva conversión
}
