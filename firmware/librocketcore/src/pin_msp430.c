/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC firmware is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the ROCKETuC firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

#include <msp430.h>

#include "pin.h"

// #define PIN_DBG	

#ifdef  PIN_DBG
#include "conio.h"
#endif

unsigned char pin_curr_func[] = {
	PIN_FUNCTION_INPUT_FLOAT,    		// P1.0
	PIN_FUNCTION_INPUT_FLOAT,			// P1.1 
	PIN_FUNCTION_INPUT_FLOAT,			// P1.2 
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

void pin_reserve(unsigned char pin) 
{
	pin_set_curr_func(pin, PIN_FUNCTION_RESERVED);	
}

unsigned char pin_function(unsigned char pin) 
{
	int port    = (0xF0 & pin) >> 4;
	int bit_num = (0x0F & pin);
	int idx  	= (port - 1) * 8 + bit_num;

	if((unsigned int)idx >= 16) {
		return PIN_FUNCTION_UNKNOWN;
	}

	return pin_curr_func[idx];
}

unsigned char pin_with_function(unsigned char pin, unsigned char function) 
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

int pin_capabilities(unsigned char pin) 
{
	int caps = 0;

	// PIN_CAP_INPUT
	// PIN_CAP_OUTPUT
	if( pin == PIN_1_0 || pin == PIN_1_1 || pin == PIN_1_2 ||
		pin == PIN_1_3 || pin == PIN_1_4 || pin == PIN_1_5 || 
		pin == PIN_1_6 || pin == PIN_1_7 ||	pin == PIN_2_0 || 
		pin == PIN_2_1 || pin == PIN_2_2 || pin == PIN_2_3 || 
		pin == PIN_2_4 || pin == PIN_2_5 || pin == PIN_2_6 || 
		pin == PIN_2_7) {
	
		caps |= PIN_CAP_INPUT + PIN_CAP_INPUT_RE + PIN_CAP_OUTPUT;
	} 

	// PIN_CAP_PWM
	if( pin == PIN_1_2 || pin == PIN_1_6 || pin == PIN_2_1 || 
		pin == PIN_2_2) {
	
		caps |= PIN_CAP_PWM;
	} 

	// PIN_CAP_ANALOG_IN
	if( pin == PIN_1_0 || pin == PIN_1_1 || pin == PIN_1_2 ||
		pin == PIN_1_3 || pin == PIN_1_4 || pin == PIN_1_5 || 
		pin == PIN_1_6 || pin == PIN_1_7) {
	
		caps |= PIN_CAP_ANALOG_IN;
	} 

	return caps;
}

int pin_has_capabilities(unsigned char pin, int capabilities) 
{
	return ((pin_capabilities(pin) & capabilities) == capabilities ? 1 : 0);
}

int pin_setup(unsigned char pin, unsigned char function)
{
	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

	unsigned char f;

	f = pin_function(pin); 
	
#ifdef PIN_DBG
	cio_printf("pin %x has current function %x\n\r", pin, f);
#endif

	// see if PIN is already configured for the given function
	if(f == function) { 
		return PIN_STAT_OK;
	}
	// PIN is reserved
	else if(f == PIN_FUNCTION_RESERVED) {
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	switch(function) {
	case PIN_FUNCTION_INPUT_FLOAT:
		if(!pin_has_capabilities(pin, PIN_CAP_INPUT)) {
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
			P1REN &= ~bit; 	                // disable pull-up/down 
  			P1SEL &= ~bit;                  // remove option
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
			P2REN &= ~bit; 	                // disable pull-up/down 
  			P2SEL &= ~bit;                  // remove option
		}
		break;
	case PIN_FUNCTION_INPUT_PULLUP:
		if(!pin_has_capabilities(pin, PIN_CAP_INPUT_RE)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P1OUT |=  bit;					// setting out to HIGH enables pull-up                     
			P1REN |=  bit; 	                // enable pull-up/down 
  			P1SEL &= ~bit;                  // remove option
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P2OUT |=  bit;					// setting out to HIGH enables pull-up                     
			P2REN |=  bit; 	                // enable pull-up/down 
  			P2SEL &= ~bit;                  // remove option
		}
		break;
	case PIN_FUNCTION_INPUT_PULLDOWN:
		if(!pin_has_capabilities(pin, PIN_CAP_INPUT_RE)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		if(port == 1) {
			P1DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P1OUT &= ~bit;					// setting out to LOW enables pull-down                     
			P1REN |=  bit; 	                // enable pull-up/down 
  			P1SEL &= ~bit;                  // remove option
		}
		else if(port == 2) {
			P2DIR &= ~bit;					// make sure to clear OUT flag for the pin                 
  			P2OUT &= ~bit;					// setting out to LOW enables pull-down                     
			P2REN |=  bit; 	                // enable pull-up/down 
  			P2SEL &= ~bit;                  // remove option
		}
		break;
	case PIN_FUNCTION_OUTPUT:
		if(!pin_has_capabilities(pin, PIN_CAP_OUTPUT)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}
		if(port == 1) {
			P1DIR |=  bit;					// set direction to out                 
  			P1OUT &= ~bit;					// set to LOW initially                     
			P1REN &= ~bit; 	                // disable pull-up/down 
  			P1SEL &= ~bit;                  // remove option
		}
		else if(port == 2) {
			P2DIR |=  bit;					// set direction to out                 
  			P2OUT &= ~bit;					// set to LOW initially                     
			P2REN &= ~bit; 	                // disable pull-up/down 
  			P2SEL &= ~bit;                  // remove option
		}
		break;
	case PIN_FUNCTION_ANALOG_IN:
		if(!pin_has_capabilities(pin, PIN_CAP_ANALOG_IN)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}

		P1DIR &= ~bit;						// make sure to clear OUT flag for the pin                 
		P1REN &= ~bit; 	                	// disable pull-up/down 
  		P1SEL &= ~bit;                  	// remove option

		// VCC as +VRef, VSS as -VRef, 16 x ADC10CLKs
   		ADC10CTL0 = SREF_0 + ADC10SHT_2 + REFON + ADC10ON;

		break;
	case PIN_FUNCTION_PWM:
		if(!pin_has_capabilities(pin, PIN_CAP_PWM)) { 
			return PIN_STAT_ERR_UNSUPFUNC;
		}

		if(port == 1) {
			// only one pin on port 1 is able to perform PWM
			unsigned char pf = pin_with_function(PIN_1_0, function);

			if(pf > 0 && pf < PIN_2_0) { 
				return PIN_STAT_ERR_UNSUPFUNC;
			}
			P1DIR |=  bit;					// set direction to out                 
  			P1OUT &= ~bit;					// set to LOW initially                     
			P1REN &= ~bit; 	                // disable pull-up/down 
  			P1SEL |=  bit;                  // select TA option
		}
		else if(port == 2) {
			// only one pin on port 2 is able to perform PWM
			if(pin_with_function(PIN_2_0, function)) { 
				return PIN_STAT_ERR_UNSUPFUNC;
			}
			P2DIR |=  bit;					// set direction to out                 
  			P2OUT &= ~bit;					// set to LOW initially                     
			P2REN &= ~bit; 	                // disable pull-up/down 
  			P2SEL |=  bit;                  // select TA option
		}
		break;
	default:
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	pin_set_curr_func(pin, function);

	return PIN_STAT_OK;
}

int pin_clear(unsigned char pin)
{
	unsigned char pf = pin_function(pin);
 
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

int pin_set(unsigned char pin)
{
	unsigned char pf = pin_function(pin);
 
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

int pin_toggle(unsigned char pin)
{
	unsigned char pf = pin_function(pin);
 
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

int pin_digital_read(unsigned char pin)
{
	unsigned char pf = pin_function(pin);
 
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

int pin_analog_read(unsigned char pin)
{
	unsigned char pf = pin_function(pin);
 
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

int pin_pulselength_read(unsigned char pin)
{
	unsigned char pf = pin_function(pin);
 
	if(pf != PIN_FUNCTION_INPUT_FLOAT && pf != PIN_FUNCTION_INPUT_PULLUP && 
	   pf != PIN_FUNCTION_INPUT_PULLDOWN) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int to = 32767;
	int t  = 0;

	// 1. check current state s of pin
	int s  = pin_digital_read(pin); 
	
	// 2. wait until pin toggeles to ~s
    int ds = s;

    if(s < 0) return s;

   	while(ds == s) {
		ds = pin_digital_read(pin);

    	if(ds < 0) return ds;

		// if max-t is reached, return (timeout)
		if(t++ == to) return to;
	}

	// 3. wait until pin toggles back to s, measure time 
	t = 0;

   	while(ds != s) {
		ds = pin_digital_read(pin);

    	if(ds < 0) return ds;

		// if max-t is reached, return (timeout)
		if(t++ == to) return to;
	}

	return t;
}

int pin_pwm_function(unsigned char pin, int period)
{
	unsigned char pf = pin_function(pin);
 
	if(pf != PIN_FUNCTION_PWM) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

	if(port == 1) {
  		TA0CCR0  = period - 1;					// Set period 
		TA0CCTL1 = OUTMOD_7;                    // CCR1 reset/set
		TA0CTL   = TASSEL_2 + MC_1;             // SMCLK, up mode
	}
	else {
  		TA1CCR0  = period - 1;					// Set period 
		TA1CCTL1 = OUTMOD_7;                    // CCR1 reset/set
		TA1CTL   = TASSEL_2 + MC_1;             // SMCLK, up mode
	}

	return PIN_STAT_OK;
}

int pin_pwm_control(unsigned char pin, unsigned char duty_cycle)
{
	unsigned char pf = pin_function(pin);
 
	if(pf != PIN_FUNCTION_PWM) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

	if(port == 1) {
		// e.g. DC=50%: (20000 / 100) * (128 / 2.55) ~ 10000 
		TA0CCR1 = (TA0CCR0 / 100) * (duty_cycle / 2.55); 
	}
	else {
		// e.g. DC=50%: (20000 / 100) * (128 / 2.55) ~ 10000 
		TA1CCR1 = (TA1CCR0 / 100) * (duty_cycle / 2.55); 
	}

	return PIN_STAT_OK;
}

int pin_exti_function(unsigned char pin, unsigned char function)
{
	unsigned char pf = pin_function(pin);
 
	if(pf != PIN_FUNCTION_INPUT_FLOAT && pf != PIN_FUNCTION_INPUT_PULLUP && pf != PIN_FUNCTION_INPUT_PULLDOWN) { 
		return PIN_STAT_ERR_UNSUPFUNC;
	}

	int port;
	int bit;

	if((port = pin2port(pin)) < 0) return port;
	if((bit  = pin2bit(pin))  < 0) return bit;

	if(port == 1) {
		if(function == PIN_FUNCTION_EXTI_HIGHLOW) {
    		P1IES |=  bit;		// set mode high-low 
		} 
		else {
    		P1IES &= ~bit;		// set mode low-high 
		}

 	    P1IFG &= ~bit;			// reset interrupt flag

		if(function == PIN_FUNCTION_EXTI_DISABLE) {
 	    	P1IE  &= ~bit;		// disable interrupt
		}
		else {
 	    	P1IE  |=  bit;		// enable interrupt
		}
	}
	else {
		if(function == PIN_FUNCTION_EXTI_HIGHLOW) {
    		P2IES |=  bit;		// set mode high-low 
		} 
		else {
    		P2IES &= ~bit;		// set mode low-high 
		}

 	    P2IFG &= ~bit;			// reset interrupt flag

		if(function == PIN_FUNCTION_EXTI_DISABLE) {
 	    	P2IE  &= ~bit;		// disable interrupt
		}
		else {
 	    	P2IE  |=  bit;		// enable interrupt
		}
	}

	return PIN_STAT_OK;
}

