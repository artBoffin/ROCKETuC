#ifndef __PIN_H_
#define __PIN_H_

#ifdef __MSP430__
#include "pin_msp430.h"
#endif

#define PIN_FUNCTION_INPUT_FLOAT	0x00

#define PIN_FUNCTION_INPUT_PULLUP	0x01

#define PIN_FUNCTION_INPUT_PULLDOWN	0x02

#define PIN_FUNCTION_OUTPUT			0x03

#define PIN_FUNCTION_ANALOG_IN		0x04

#define PIN_FUNCTION_PWM			0x05

#define PIN_FUNCTION_UARTRX			0x06

#define PIN_FUNCTION_UARTTX			0x07

#define PIN_LOW						0x00

#define PIN_HIGH					0x01

void processing_pin_setup(unsigned char pin, unsigned char function);

void processing_pin_clear(unsigned char pin);

void processing_pin_set(unsigned char pin);

void processing_pin_toggle(unsigned char pin);

unsigned char processing_pin_digital_read(unsigned char pin);

int processing_pin_analog_read(unsigned char pin);

int processing_pin_pulselength_read(unsigned char pin);

#endif
