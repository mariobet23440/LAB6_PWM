/*
 * LibreriaADC.h
 *
 * Created: 11/04/2025 10:14:34
 *  Author: mario
 */ 


#ifndef LIBRERIAADC_H_
#define LIBRERIAADC_H_

#include <avr/io.h>

// Prototipos de funciones
void setup_adc(void);
void adc_set_channel(unsigned char channel);


#endif /* LIBRERIAADC_H_ */