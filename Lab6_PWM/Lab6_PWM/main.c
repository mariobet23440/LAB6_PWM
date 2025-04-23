#include <avr/io.h>
#include <avr/interrupt.h>
#include "LibreriaTimer1PWM.h"
#include "LibreriaADC.h"

// VARIABLES GLOBALES
volatile uint8_t current_channel = 0; // Comenzar en ADC0
static uint8_t manual_pwm_pin = DDD3;

// PROTOTIPOS DE FUNCIONES
void init_timer0(void);
void init_timer2_manualpwm(void);
void timer2_set_PW(uint8_t value);

// MAINLOOP
int main(void)
{
	cli();
	DDRB |= (1 << DDB1) | (1 << DDB2) ;  // Configurar PB0 como salida
	setup_adc();  // Configurar ADC
	init_timer0();
	init_timer1();  // Inicializar Timer1 en modo Fast PWM
	init_timer2_manualpwm();
	sei();  // Habilitar interrupciones globales

	while (1)
	{
		// La ISR del ADC se encargará de actualizar el PWM
	}

	return 0;
}

// FUNCIONES NO DE INTERRUPCIÓN
// Inicialización de TIMER 0 - Disparo de conversión
void init_timer0(void)
{
	// Operamos el temporizador en modo NORMAL
	TCCR0B |= (1 << CS01) | (1 << CS00);	// Prescaler de 64
	TCNT0 = 0;
	
	// Habilitar interrupciones por overflow de TIMER0
	TIMSK0 |= (1 << TOIE0);
}

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

// RUTINAS DE INTERRUPCIÓN
// Timer0 Overflow - dispara conversión ADC
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 0; // Reiniciar contador
	ADCSRA |= (1 << ADSC); // Iniciar conversión
}

// ADC listo - se ejecuta cuando termina la conversión
// Multiplexado de canales
ISR(ADC_vect)
{
	uint8_t adc_value = ADCH; // Al usar ADLAR = 1, ADCH ya contiene los 8 bits más significativos

	switch (current_channel)
	{
		case 0:
		TIMER1_PWM1_set_servo_PW(adc_value); // PWM para canal 0 (OC1A)
		current_channel = 1;
		adc_set_channel(1);
		break;

		case 1:
		TIMER1_PWM2_set_servo_PW(adc_value); // PWM para canal 1 (OC1B)
		current_channel = 2;
		adc_set_channel(2);
		break;
		
		case 2:
		timer2_set_PW(adc_value);
		current_channel = 0;
		adc_set_channel(0);
		break;
	}
}

// Cuando ocurra un overflow de TIMER2 - Apagar 
ISR(TIMER2_OVF_vect)
{
	uint8_t temp = PIND;
	temp = temp ^ (1 << manual_pwm_pin); 
	PORTD = temp;
}

// Cuando ocurra un Output Compare Match - Encender
ISR(TIMER2_COMPA_vect)
{
	uint8_t temp = PIND;
	temp |= (1 << manual_pwm_pin);
	PORTD = temp;
}