#ifndef __PIN_H_
#define __PIN_H_

#ifdef __MSP430__
#include "pin_msp430.h"
#endif

/**
 * PIN function input float
 */
#define PIN_FUNCTION_INPUT_FLOAT	0x00

/**
 * PIN function input with internal pull-up enabled
 */
#define PIN_FUNCTION_INPUT_PULLUP	0x01

/**
 * PIN function input with internal pull-down enabled
 */
#define PIN_FUNCTION_INPUT_PULLDOWN	0x02

/**
 * PIN function output 
 */
#define PIN_FUNCTION_OUTPUT			0x03

/**
 * PIN function analog input
 */
#define PIN_FUNCTION_ANALOG_IN		0x04

/**
 * PIN function PWM output
 */
#define PIN_FUNCTION_PWM			0x05

/**
 * PIN function UART RX
 */
#define PIN_FUNCTION_UARTRX			0x06

/**
 * PIN function UART TX
 */
#define PIN_FUNCTION_UARTTX			0x07


/**
 * PIN has no capability 
 */
#define PIN_CAP_NONE				0b00000000

/**
 * PIN has capability input 
 */
#define PIN_CAP_INPUT				0b00000001

/**
 * PIN has capability input with internal pull-up/down resistor 
 */
#define PIN_CAP_INPUT_RE			0b00000010

/**
 * PIN has capability output 
 */
#define PIN_CAP_OUTPUT				0b00000100

/**
 * PIN has capability analog input 
 */
#define PIN_CAP_ANALOG_IN			0b00001000

/**
 * PIN has capability PWM output 
 */
#define PIN_CAP_PWM					0b00010000

/**
 * PIN has capability UART RX 
 */
#define PIN_CAP_UARTRX				0b00100000

/**
 * PIN has capability UART TX 
 */
#define PIN_CAP_UARTTX				0b01000000


/**
 * PIN status was OK
 */
#define PIN_STAT_OK					0

/**
 * PIN status was unsupported function 
 */
#define PIN_STAT_ERR_UNSUPFUNC		-1

/**
 * PIN status was invalid port 
 */
#define PIN_STAT_ERR_INVALPORT		-2

/**
 * PIN status was invalid pin 
 */
#define PIN_STAT_ERR_INVALPIN		-3

/**
 * Get the capabilites for a PIN as defined with the PIN_CAP_x constants.
 *
 * @param[in]	pin		PIN for which to get capablities
 * @return				PIN capablities as defined with PIN_CAP_x
 */
int processing_pin_capabilities(unsigned char pin); 

/**
 * Check if a given PIN has given capabilities.
 *
 * @param[in]	pin					PIN for which to check capablities
 * @param[in]	capabilities		capablities to check for as defined in PIN_CAP_x
 * @return							1 if PIN has capabilities, 0 otherwise	
 */
int processing_pin_has_capabilities(unsigned char pin, int capabilities); 

/**
 * Get the function for which a given PIN is currently configured.
 *
 * @param[in]	pin		PIN for which to get the current function
 * @return 				current PIN function as defined with PIN_FUNCTION_x 
 */
unsigned char processing_pin_function(unsigned char pin); 

/**
 * Check if there is already a PIN configured with the given function. 
 *
 * @param[in]	pin			PIN after which to start checking for the next PIN with this function
 * @param[in]	function	function to find a PIN for
 * @return 					first PIN found with given function or 0 if no PIN with this function was found
 */
unsigned char processing_pin_with_function(unsigned char pin, unsigned char function); 

/** 
 * Setup up a PIN for a certain function.
 *
 * @param[in]	pin			PIN to setup 
 * @param[in]	function	function to assign to the PIN
 * @return					PIN_STAT_OK if function assigned
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_setup(unsigned char pin, unsigned char function);

/**
 * Clear the output for a given PIN
 *
 * @param[in]	pin			PIN to perform this action for 
 * @return					PIN_STAT_OK if function assigned
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function 
 * 							(since it is not configured as OUTPUT)	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_clear(unsigned char pin);

/**
 * Set the output for a given PIN
 *
 * @param[in]	pin			PIN to perform this action for 
 * @return					PIN_STAT_OK if function assigned
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function 
 * 							(since it is not configured as OUTPUT)	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_set(unsigned char pin);

/**
 * Toggle the output for a given PIN
 *
 * @param[in]	pin			PIN to perform this action for 
 * @return					PIN_STAT_OK if function assigned
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function 
 * 							(since it is not configured as OUTPUT)	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_toggle(unsigned char pin);

/**
 * Read the digital state of an input/output for a given PIN
 *
 * @param[in]	pin			PIN to perform this action for 
 * @return					PIN_STAT_OK if function assigned
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function 
 * 							(since it is not configured as INPUT/OUTPUT/PWM)	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_digital_read(unsigned char pin);

/**
 * Read the analog state of an input/output for a given PIN
 *
 * @param[in]	pin			PIN to perform this action for 
 * @return				    analog value sampled on success (positive value)	
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function 
 * 							(since it is not configured as ANALOG INPUT)	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_analog_read(unsigned char pin);

/**
 * Read the digital pulselengh for a given PIN. If PIN is LOW when function is called,
 * the function waits for next raising edge, then measures the time until a falling
 * edge is detected. If PIN is HIGH when functino is called, the function waits for next
 * falling edge, then measures the time until a rising edge is detexted. 
 *
 * @param[in]	pin			PIN to perform this action for 
 * @return				    pulse lenght in ms on succes (positive value)	
 * 							PIN_STAT_ERR_UNSUPFUNC if PIN does not support this function 
 * 							(since it is not configured as INPUT)	
 * 							PIN_STAT_ERR_UNKPORT if given port for PIN is not known
 * 							PIN_STAT_ERR_UNKPIN  if given pin nr. for PIN is not known
 */
int processing_pin_pulselength_read(unsigned char pin);

#endif
