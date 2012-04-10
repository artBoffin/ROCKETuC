#include <msp430.h>
#include "pin.h"

int pin2port(unsigned char pin) 
{
	int port = (0xF0 & pin) >> 4;

	if(port >= 1 && port <= 2) { 
		return port;
	}

	return PIN_STAT_ERR_INVALPORT;
}

int pin2bit(unsigned char pin) 
{
	int bit_num = (0x0F & pin);
	int bit 	=  0x01 << bit_num;

	// RX/TX of uart1 are reserved, bits 0-7 are allowed 
	if(pin == PIN_1_1 || pin == PIN_1_2 || bit_num > 7) {
		return PIN_STAT_ERR_INVALPIN;	
	}

	return bit;
}

int processing_pin_capabilities(unsigned char pin) 
{
	return 0;
}

int processing_pin_has_capabilities(unsigned char pin, int capabilities) 
{
	return 0;
}

int processing_pin_setup(unsigned char pin, unsigned char function)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2port(pin)) < 0) return bit;

	switch(function) {
	case PIN_FUNCTION_INPUT_FLOAT:
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
		}
		break;
	case PIN_FUNCTION_INPUT_PULLUP:
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P1OUT |=  bit;					// setting out to HIGH enables pull-up                     
			P1REN |=  bit; 	                // enable pull-up/down 
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P2OUT |=  bit;					// setting out to HIGH enables pull-up                     
			P2REN |=  bit; 	                // enable pull-up/down 
		}
		break;
	case PIN_FUNCTION_INPUT_PULLDOWN:
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P1OUT &= ~bit;					// setting out to LOW enables pull-down                     
			P1REN |=  bit; 	                // enable pull-up/down 
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P2OUT &= ~bit;					// setting out to LOW enables pull-down                     
			P2REN |=  bit; 	                // enable pull-up/down 
		}
		break;
	case PIN_FUNCTION_OUTPUT:
		if(port == 1) {
			P1DIR |=  bit;					// set direction to out                 
  			P1OUT &= ~bit;					// set to LOW initially                     
			P1REN &= ~bit; 	                // disable pull-up/down 
		}
		else if(port == 2) {
			P2DIR |=  bit;					// set direction to out                 
  			P2OUT &= ~bit;					// set to LOW initially                     
			P2REN &= ~bit; 	                // disable pull-up/down 
		}
		break;
	case PIN_FUNCTION_ANALOG_IN:
		// TODO
		break;
	case PIN_FUNCTION_PWM:
		// TODO
		break;
	case PIN_FUNCTION_UARTRX:
		// TODO
		break;
	case PIN_FUNCTION_UARTTX:
		// TODO
		break;
	default:
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	return PIN_STAT_OK;
}

int processing_pin_clear(unsigned char pin)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2port(pin)) < 0) return bit;

	if(port == 1) {
  		P1OUT &= ~bit;					// set to LOW                   
	}
	else if(port == 2) {
  		P2OUT &= ~bit;					// set to LOW                    
	}

	return PIN_STAT_OK;
}

int processing_pin_set(unsigned char pin)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2port(pin)) < 0) return bit;

	if(port == 1) {
  		P1OUT |= bit;					// set to HIGH 
	}
	else if(port == 2) {
  		P2OUT |= bit;					// set to HIGH               
	}

	return PIN_STAT_OK;
}

int processing_pin_toggle(unsigned char pin)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2port(pin)) < 0) return bit;

	if(port == 1) {
  		P1OUT ^= bit;					// toggle 
	}
	else if(port == 2) {
  		P2OUT ^= bit;					// toggle           
	}

	return PIN_STAT_OK;
}

int processing_pin_digital_read(unsigned char pin)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2port(pin)) < 0) return bit;

	if(port == 1) {
  		return ((P1IN & bit) == bit ? 1 : 0);	// read and return 
	}

	return ((P2IN & bit) == bit ? 1 : 0);	// read and return 
}

int processing_pin_analog_read(unsigned char pin)
{
	// TODO
	return 0;
}

int processing_pin_pulselength_read(unsigned char pin)
{
	// TODO
	return 0;
}
