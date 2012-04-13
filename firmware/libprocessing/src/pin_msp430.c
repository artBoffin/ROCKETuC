#include <msp430.h>
#include "pin.h"

unsigned char pin_curr_func[] = {
	PIN_FUNCTION_INPUT_FLOAT,    		// P1.0
	0,									// P1.1 - reserved/internal
	0,									// P1.2 - reserved/internal
	PIN_FUNCTION_INPUT_FLOAT,			// P1.3
	PIN_FUNCTION_INPUT_FLOAT,			// P1.4
	PIN_FUNCTION_INPUT_FLOAT,			// P1.5
	PIN_FUNCTION_INPUT_FLOAT,			// P1.6
	PIN_FUNCTION_INPUT_FLOAT,			// P1.7
	PIN_FUNCTION_INPUT_FLOAT,			// P2.0
	PIN_FUNCTION_INPUT_FLOAT,			// P2.1
	PIN_FUNCTION_INPUT_FLOAT,			// P2.2
	PIN_FUNCTION_INPUT_FLOAT,			// P2.3
	PIN_FUNCTION_INPUT_FLOAT,			// P2.4
	PIN_FUNCTION_INPUT_FLOAT,			// P2.5
	PIN_FUNCTION_INPUT_FLOAT,			// P2.6
	PIN_FUNCTION_INPUT_FLOAT,			// P2.7
};

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

void pin_set_curr_func(unsigned char pin, unsigned char func) 
{
	int port    = (0xF0 & pin) >> 4;
	int bit_num = (0x0F & pin);
	int idx  	= (port - 1) * 8 + bit_num;

	if((unsigned int)idx > sizeof(pin_curr_func)) {
		return;
	}

	pin_curr_func[idx] = func;
}

unsigned char processing_pin_function(unsigned char pin) 
{
	int port    = (0xF0 & pin) >> 4;
	int bit_num = (0x0F & pin);
	int idx  	= (port - 1) * 8 + bit_num;

	if((unsigned int)idx > sizeof(pin_curr_func)) {
		return 0;
	}

	return pin_curr_func[idx];
}

unsigned char processing_pin_with_function(unsigned char pin, unsigned char function) 
{
	int port    = (0xF0 & pin) >> 4;
	int bit_num = (0x0F & pin);
	int idx  	= (pin == 0 ? 0 : (port - 1) * 8 + bit_num + 1) ;
	int i;

	for(i = idx + 1; (unsigned int)i < sizeof(pin_curr_func); i++) {
		if(pin_curr_func[i] == function) {
			return (((i / 8 + 1) << 4) + (i % 8));
		}
	}

	return 0;
}

int processing_pin_capabilities(unsigned char pin) 
{
	int caps = 0;

	// PIN_CAP_INPUT
	if( pin == PIN_1_0 || pin == PIN_1_3 || pin == PIN_1_4 ||
		pin == PIN_1_5 || pin == PIN_1_6 || pin == PIN_1_7 ||	 
	    pin == PIN_2_0 || pin == PIN_2_1 || pin == PIN_2_2 ||
        pin == PIN_2_3 || pin == PIN_2_4 || pin == PIN_2_5 || 
		pin == PIN_2_6 || pin == PIN_2_7) {
	
		caps |= PIN_CAP_INPUT;
	} 

	// PIN_CAP_INPUT_RE
	if( pin == PIN_1_0 || pin == PIN_1_4 ||
		pin == PIN_1_5 || pin == PIN_1_6 || pin == PIN_1_7 ||	 
	    pin == PIN_2_0 || pin == PIN_2_1 || pin == PIN_2_2 ||
        pin == PIN_2_3 || pin == PIN_2_4 || pin == PIN_2_5 || 
		pin == PIN_2_6 || pin == PIN_2_7) {
	
		caps |= PIN_CAP_INPUT_RE;
	} 

	// PIN_CAP_OUTPUT
	// PIN_CAP_PWM
	// PIN_CAP_UARTRX
	// PIN_CAP_UARTTX
	if( pin == PIN_1_0 || pin == PIN_1_3 || pin == PIN_1_4 ||
		pin == PIN_1_5 || pin == PIN_1_6 || pin == PIN_1_7 ||	 
	    pin == PIN_2_0 || pin == PIN_2_1 || pin == PIN_2_2 ||
        pin == PIN_2_3 || pin == PIN_2_4 || pin == PIN_2_5 || 
		pin == PIN_2_6 || pin == PIN_2_7) {
	
		caps |= PIN_CAP_OUTPUT + PIN_CAP_PWM + PIN_CAP_UARTTX + PIN_CAP_UARTRX;
	} 

	// PIN_CAP_ANALOG_IN
	if( pin == PIN_1_0 || pin == PIN_1_3 || pin == PIN_1_4 ||
		pin == PIN_1_5 || pin == PIN_1_6 || pin == PIN_1_7) {
	
		caps |= PIN_CAP_ANALOG_IN;
	} 

	return caps;
}

int processing_pin_has_capabilities(unsigned char pin, int capabilities) 
{
	return ((processing_pin_capabilities(pin) & capabilities) == capabilities ? 1 : 0);
}

int processing_pin_setup(unsigned char pin, unsigned char function)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

	// see if PIN is already configured for the given function
	if(processing_pin_function(pin) == function) { 
		return PIN_STAT_OK;
	}

	switch(function) {
	case PIN_FUNCTION_INPUT_FLOAT:
		if(!processing_pin_has_capabilities(pin, PIN_CAP_INPUT)) {
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
			P1REN &= ~bit; 	                // disable pull-up/down 
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
			P2REN &= ~bit; 	                // disable pull-up/down 
		}
		break;
	case PIN_FUNCTION_INPUT_PULLUP:
		if(!processing_pin_has_capabilities(pin, PIN_CAP_INPUT_RE)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
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
		if(!processing_pin_has_capabilities(pin, PIN_CAP_INPUT_RE)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
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
		if(!processing_pin_has_capabilities(pin, PIN_CAP_OUTPUT)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
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
		if(!processing_pin_has_capabilities(pin, PIN_CAP_ANALOG_IN)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		P1DIR    &= ~bit;					// make sure to clear OUT flag for the pin                 
		P1REN &= ~bit; 	                	// disable pull-up/down 

		// VCC as +VRef, VSS as -VRef, 16 x ADC10CLKs
   		ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + ADC10ON;

		break;
	case PIN_FUNCTION_PWM:
		if(!processing_pin_has_capabilities(pin, PIN_CAP_PWM)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		// TODO
		break;
	case PIN_FUNCTION_UARTRX:
		if(!processing_pin_has_capabilities(pin, PIN_CAP_UARTRX) ||
			processing_pin_with_function(0, function)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		// TODO	
		break;
	case PIN_FUNCTION_UARTTX:
		if(!processing_pin_has_capabilities(pin, PIN_CAP_UARTTX) ||
			processing_pin_with_function(0, function)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		// TODO
		break;
	default:
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	pin_set_curr_func(pin, function);

	return PIN_STAT_OK;
}

int processing_pin_clear(unsigned char pin)
{
	unsigned char pf = processing_pin_function(pin);
 
	if(pf != PIN_FUNCTION_OUTPUT) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

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
	unsigned char pf = processing_pin_function(pin);
 
	if(pf != PIN_FUNCTION_OUTPUT) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

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
	unsigned char pf = processing_pin_function(pin);
 
	if(pf != PIN_FUNCTION_OUTPUT)  { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

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
	unsigned char pf = processing_pin_function(pin);
 
	if(pf != PIN_FUNCTION_OUTPUT && pf != PIN_FUNCTION_INPUT_FLOAT && 
	   pf != PIN_FUNCTION_INPUT_PULLUP && pf != PIN_FUNCTION_INPUT_PULLDOWN
	   && pf != PIN_FUNCTION_PWM) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

	if(port == 1) {
  		return ((P1IN & bit) == bit ? 1 : 0);	// read and return 
	}

	return ((P2IN & bit) == bit ? 1 : 0);	// read and return 
}

int processing_pin_analog_read(unsigned char pin)
{
	unsigned char pf = processing_pin_function(pin);
 
	if(pf != PIN_FUNCTION_OUTPUT && pf != PIN_FUNCTION_ANALOG_IN) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int s;

	if((s = pin2port(pin)) < 0) return s;
	if((s = pin2bit(pin))  < 0) return s;

	// configure channel
   	ADC10CTL1 = 0xF000 & (pin << 12); 

    ADC10CTL0 |= ENC + ADC10SC;             // sample 
    while (ADC10CTL1 & ADC10BUSY);          // wait while ADC10BUSY

	return ADC10MEM;
}

int processing_pin_pulselength_read(unsigned char pin)
{
	unsigned char pf = processing_pin_function(pin);
 
	if(pf != PIN_FUNCTION_INPUT_FLOAT && pf != PIN_FUNCTION_INPUT_PULLUP && 
	   pf != PIN_FUNCTION_INPUT_PULLDOWN) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	// TODO
	return 0;
}
