#include <avr/io.h>
#include <avr/interrupt.h>

void setup_adc(void)
{
	ADMUX |= (1 << ADLAR) | (1 << REFS0);  // Ajuste a la izquierda (ADLAR), Referencia AVCC (REFS0)
	ADCSRA |= (1 << ADEN) | (1 << ADIE);    // Habilitar ADC y habilitar interrupción ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1);  // Prescaler de 64
	ADCSRA |= (1 << ADSC);                  // Iniciar conversión
}

void adc_set_channel(unsigned char channel)
{
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);  // Limpiar bits de canal y asignar nuevo canal
}

void init_timer1(void)
{
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);  // Fast PWM, OC1A no invertido
	TCCR1B |= (1 << WGM13) | (1 << WGM12) | (1 << CS11);  // Prescaler de 8, Fast PWM
	ICR1 = 39999;  // Establecer TOP a 39999 (Frecuencia de 50 Hz, 20ms)
	DDRB |= (1 << DDB0);  // Configurar PB0 como salida (OC1A)
}

void PWM1_set_pulse_width(uint16_t value)
{
	uint16_t ticks = value * 40;  // Escalar el valor de 0-1023 a 0-39999
	if (ticks > ICR1) ticks = ICR1;
	OCR1A = ticks;  // Ajustar el valor de OCR1A
}

ISR(ADC_vect)
{
	uint16_t adc_value = ADC;  // Leer el valor del ADC (10 bits)
	PWM1_set_pulse_width(adc_value);  // Ajustar el ancho de pulso basado en el valor del ADC
	ADCSRA |= (1 << ADSC);  // Iniciar una nueva conversión
}

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
