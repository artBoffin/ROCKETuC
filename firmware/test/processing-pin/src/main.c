#include <msp430.h>

#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

#include "pin.h"

void clock_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

void dump_regs(const char *msg) 
{

	cio_printf("REGDUMP(%s): P1DIR=%x; P2DIR=%x; P1OUT=%x; P2OUT=%x; P1REN=%x; P2REN=%x; P1IN=%x, P2IN=%x\n\r",
				msg,
				P1DIR, P2DIR, P1OUT, P2OUT, P1REN, P2REN, P1IN, P2IN);
}

void delay() 
{
	volatile unsigned long i = 15000;

	do (i--);
	while (i != 0);
}

int main(void)
{
	clock_init();
	serial_init(9600);

	cio_print("** ROCKETuC - libprocessing PIN test **\n\r");

	dump_regs("initial");

	// invalid port
	if(processing_pin_setup(0x30, PIN_FUNCTION_OUTPUT) == PIN_STAT_ERR_INVALPORT) {
		cio_print("0x30 is an invalid port\n\r");
	}
	
	// invalid pin
	if(processing_pin_setup(0x2A, PIN_FUNCTION_OUTPUT) == PIN_STAT_ERR_INVALPIN) {
		cio_print("0x2A is an invalid pin\n\r");
	}

	// P1.1 + P1.2 are reserved for UART1
	if(processing_pin_setup(PIN_1_1, PIN_FUNCTION_OUTPUT) == PIN_STAT_ERR_INVALPIN) {
		cio_print("0x11 is an invalid (reserved) pin\n\r");
	}
	if(processing_pin_setup(PIN_1_2, PIN_FUNCTION_OUTPUT) == PIN_STAT_ERR_INVALPIN) {
		cio_print("0x12 is an invalid (reserved) pin\n\r");
	}

	// pins on port 2 do not support ADC
	int p;

	for(p = 0; p < 8; p++) { 
		if(processing_pin_setup(PIN_2_0 + p, PIN_FUNCTION_ANALOG_IN) == PIN_STAT_ERR_UNSUPFUNC) {
			cio_printf("0x2%i does not support ADC\n\r", p);
		}
	}
	
	// onyl one PIN at a time is allowed to be soft UART RX/TX
	cio_printf("Set UARTTX p1.4: %x\n\r",processing_pin_setup(PIN_1_4, PIN_FUNCTION_UARTTX));
	cio_printf("Set UARTTX p1.5: %x\n\r",processing_pin_setup(PIN_1_5, PIN_FUNCTION_UARTTX));
	cio_printf("Set UARTRX p1.4: %x\n\r",processing_pin_setup(PIN_1_4, PIN_FUNCTION_UARTRX));
	cio_printf("Set UARTRX p1.5: %x\n\r",processing_pin_setup(PIN_1_5, PIN_FUNCTION_UARTRX));


	// set P1.0 + P1.6 + P2.5 to output (the build in LEDs)
	processing_pin_setup(PIN_1_0, PIN_FUNCTION_OUTPUT);
	processing_pin_setup(PIN_1_6, PIN_FUNCTION_OUTPUT);
	processing_pin_setup(PIN_2_5, PIN_FUNCTION_OUTPUT);

	
	dump_regs("p1.0+p1.6+p2.5 output");

	// set P1.0 + P1.6i + P2.5 to HIGH
	processing_pin_set(PIN_1_0);
	processing_pin_set(PIN_1_6);
	processing_pin_set(PIN_2_5);

	dump_regs("p1.0+p1.6+p2.5 set");

	// read P1.0 + P1.6 + p2.5 states
	cio_printf("P1.0 is %x\n\r", processing_pin_digital_read(PIN_1_0));	
	cio_printf("P1.6 is %x\n\r", processing_pin_digital_read(PIN_1_6));	
	cio_printf("P2.5 is %x\n\r", processing_pin_digital_read(PIN_2_5));	
	
	// clear P1.0 + p1.6 + p2.5 to LOW 
	processing_pin_clear(PIN_1_0);
	processing_pin_clear(PIN_1_6);
	processing_pin_clear(PIN_2_5);

	dump_regs("p1.0+p1.6+p2.5 clear");

	// read P1.0 + P1.6 + 2.5 states
	cio_printf("P1.0 is %x\n\r", processing_pin_digital_read(PIN_1_0));	
	cio_printf("P1.6 is %x\n\r", processing_pin_digital_read(PIN_1_6));	
	cio_printf("P2.5 is %x\n\r", processing_pin_digital_read(PIN_2_5));	

	// toggle P1.0 + P1.6 + P2.5
	processing_pin_toggle(PIN_1_0);
	processing_pin_toggle(PIN_1_6);
	processing_pin_toggle(PIN_2_5);

	dump_regs("p1.0+p1.6+p2.5 toggle");

	// read P1.0 + P1.6 states
	cio_printf("P1.0 is %x\n\r", processing_pin_digital_read(PIN_1_0));	
	cio_printf("P1.6 is %x\n\r", processing_pin_digital_read(PIN_1_6));	
	cio_printf("P2.5 is %x\n\r", processing_pin_digital_read(PIN_2_5));	

	// toggle P1.0 + P1.6 + P2.5
	processing_pin_toggle(PIN_1_0);
	processing_pin_toggle(PIN_1_6);
	processing_pin_toggle(PIN_2_5);

	dump_regs("p1.0+p1.6+p2.5 toggle");

	// read P1.0 + P1.6 states
	cio_printf("P1.0 is %x\n\r", processing_pin_digital_read(PIN_1_0));	
	cio_printf("P1.6 is %x\n\r", processing_pin_digital_read(PIN_1_6));	
	cio_printf("P2.5 is %x\n\r", processing_pin_digital_read(PIN_2_5));	


	// set P1.3 to input float
	processing_pin_setup(PIN_1_3, PIN_FUNCTION_INPUT_FLOAT);

	dump_regs("p1.3 input float");

	cio_print("Press button on P1.3 to continue ...");

	while(processing_pin_digital_read(PIN_1_3)) __asm__("nop");

	cio_print(" OK\n\r");
	
	// set P2.3 to input pull-down 
	processing_pin_setup(PIN_2_3, PIN_FUNCTION_INPUT_PULLDOWN);

	dump_regs("p2.3 input pull-down");

	cio_print("Press button on P2.3 to continue ...");

	while(!processing_pin_digital_read(PIN_2_3)) __asm__("nop");

	cio_print(" OK\n\r");
	
	// set P2.4 to input pull-down 
	processing_pin_setup(PIN_2_4, PIN_FUNCTION_INPUT_PULLUP);

	dump_regs("p2.4 input pull-up");

	cio_print("Press button on P2.4 to continue ...");

	while(processing_pin_digital_read(PIN_2_4)) __asm__("nop");

	cio_print(" OK\n\r");
	
	processing_pin_set(PIN_1_0);
	processing_pin_clear(PIN_1_6);
	processing_pin_clear(PIN_2_5);

	// set P1.5 to analog in
	int i = 0;

	cio_printf("setup 1.5 for analog in: %x\n\r", processing_pin_setup(PIN_1_5, PIN_FUNCTION_ANALOG_IN));
	dump_regs("p1.5 analog in");
	
	int adcin1 = processing_pin_analog_read(PIN_1_5); 
	int adcin2 = 0; 
	cio_printf("Analog read p1.5: %x\n\r", adcin1);

	while (1) {
		delay();

		processing_pin_toggle(PIN_1_0);
		processing_pin_toggle(PIN_1_6);

		if(i++ % 2 == 0) {
			processing_pin_toggle(PIN_2_5);
		}

		if(!processing_pin_digital_read(PIN_1_3)) {
			processing_pin_toggle(PIN_1_6);
			while(!processing_pin_digital_read(PIN_1_3)) __asm__("nop");
		}

		adcin2 = processing_pin_analog_read(PIN_1_5); 

		// only output ADC value if delta was more then 5
		if(adcin2 - adcin1 > 5 || adcin1 - adcin2 > 5) {
			adcin1 = adcin2;
			cio_printf("Analog read at p1.5: %x (%i)\n\r", adcin2, adcin2);
		}
	}

	return 0;
}
