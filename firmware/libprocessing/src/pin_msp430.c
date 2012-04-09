#include <msp430.h>
#include "pin.h"

void processing_pin_setup(unsigned char pin, unsigned char function)
{
	unsigned char port = (0xF0 & pin) >> 4;
	unsigned char bit  =  0x01 << (0x0F & pin);

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
	}
}

void processing_pin_clear(unsigned char pin)
{
	unsigned char port = (0xF0 & pin) >> 4;
	unsigned char bit  =  0x01 << (0x0F & pin);

	if(port == 1) {
  		P1OUT &= ~bit;					// set to LOW                   
	}
	else if(port == 2) {
  		P2OUT &= ~bit;					// set to LOW                    
	}
}

void processing_pin_set(unsigned char pin)
{
	unsigned char port = (0xF0 & pin) >> 4;
	unsigned char bit  =  0x01 << (0x0F & pin);

	if(port == 1) {
  		P1OUT |= bit;					// set to HIGH 
	}
	else if(port == 2) {
  		P2OUT |= bit;					// set to HIGH               
	}
}

void processing_pin_toggle(unsigned char pin)
{
	unsigned char port = (0xF0 & pin) >> 4;
	unsigned char bit  =  0x01 << (0x0F & pin);

	if(port == 1) {
  		P1OUT ^= bit;					// toggle 
	}
	else if(port == 2) {
  		P2OUT ^= bit;					// toggle           
	}
}

unsigned char processing_pin_digital_read(unsigned char pin)
{
	unsigned char port = (0xF0 & pin) >> 4;
	unsigned char bit  =  0x01 << (0x0F & pin);

	if(port == 1) {
  		return ((P1IN & bit) == bit ? 1 : 0);	// read and return 
	}
	else if(port == 2) {
  		return ((P2IN & bit) == bit ? 1 : 0);	// read and return 
	}

	return 0;
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
