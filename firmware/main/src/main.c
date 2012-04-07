#include <msp430.h>

#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

void clock_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

int main(void)
{
	clock_init();
	serial_init(9600);

	cio_print("** ROCKETuC - just a test **\n\r");

	while (1) {
		__asm__("nop");
	}
	return 0;
}
