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


#define PIN_CAP_INPUT				0b00000001

#define PIN_CAP_INPUT_RE			0b00000010

#define PIN_CAP_OUTPUT				0b00000100

#define PIN_CAP_ANALOGIN			0b00001000

#define PIN_CAP_PWM					0b00001000

#define PIN_CAP_UARTRX				0b00010000

#define PIN_CAP_UARTTX				0b00010000


#define PIN_STAT_OK					0

#define PIN_STAT_ERR_UNSUPFUNC		-1

#define PIN_STAT_ERR_INVALPORT		-2

#define PIN_STAT_ERR_INVALPIN		-3

int processing_pin_capabilities(unsigned char pin); 

int processing_pin_has_capabilities(unsigned char pin, int capabilities); 

int processing_pin_setup(unsigned char pin, unsigned char function);

int processing_pin_clear(unsigned char pin);

int processing_pin_set(unsigned char pin);

int processing_pin_toggle(unsigned char pin);

int processing_pin_digital_read(unsigned char pin);

int processing_pin_analog_read(unsigned char pin);

int processing_pin_pulselength_read(unsigned char pin);

#endif
