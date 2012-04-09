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
	volatile unsigned long i = 59999;

	do (i--);
	while (i != 0);
}

int main(void)
{
	clock_init();
	serial_init(9600);

	cio_print("** ROCKETuC - libprocessing PIN test **\n\r");

	dump_regs("initial");

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

	int i = 0;

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
	}

	return 0;
}
