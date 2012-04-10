#include <msp430.h>
#include <legacymsp430.h>

#include <libemb/serial/serial.h>
#include <libemb/serial/serial_rb.h>

#include "packet.h"

#define RB_SIZE		64 

static SERIAL_RB_Q srx_buf[RB_SIZE];
static serial_rb srx;

static SERIAL_RB_Q stx_buf[RB_SIZE];
static serial_rb stx;

static packet outp;
static packet inp;

int ph_dummy_ack(unsigned char length, unsigned char *data);

int ph_system_info(unsigned char length, unsigned char *data);

int ph_null(unsigned char length, unsigned char *data);

packet_rcv_handlers rcvh = {
	.count = 9,
	.handlers = {
		{ 
			.type = 0x00,			// NULL 
			.func = ph_null,		// handler func
		},
		{ 
			.type = 0x02,			// system info packet 
			.func = ph_system_info,	// handler func
		},
		{ 
			.type = 0x04,			// pin setup packet
			.func = ph_dummy_ack,	// handler func
		},
		{ 
			.type = 0x05,			// pin control packet
			.func = ph_dummy_ack,	// handler func
		},
		{ 
			.type = 0x06,			// PWM setup packet
			.func = ph_dummy_ack,	// handler func
		},
		{ 
			.type = 0x07,			// PWM control packet
			.func = ph_dummy_ack,	// handler func
		},
		{ 
			.type = 0x08,			// serial setup packet
			.func = ph_dummy_ack,	// handler func
		},
		{ 
			.type = 0x09,			// serial control packet
			.func = ph_dummy_ack,	// handler func
		},
		{ 
			.type = 0x0A,			// EXTI setup packet
			.func = ph_dummy_ack,	// handler func
		},
	}
};

int ph_dummy_ack(unsigned char length, unsigned char *data) 
{
	outp.length 	= 0x05;
	outp.type 		= 0x01;
	outp.data[0]	= 0x01;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	return 0;
}

int ph_system_info(unsigned char length, unsigned char *data) 
{
	outp.length 	= 0x07;
	outp.type 		= 0x02;
	outp.data[0]	= 0xaa;
	outp.data[1]	= 0xbb;
	outp.data[2]	= 0xcc;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	return 0;
}

int ph_null(unsigned char length, unsigned char *data) 
{
	outp.length 	= 0x04;
	outp.type 		= 0x00;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	return 0;
}

void clock_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

void serirq_init(void)
{
    serial_rb_init(&srx, &(srx_buf[0]), RB_SIZE);
    serial_rb_init(&stx, &(stx_buf[0]), RB_SIZE);

    IE2 |= UCA0RXIE; 
	__bis_SR_register(GIE);
}

void packet_byte_to_sendq(unsigned char pkt_byte) 
{
	// wait until buffer empties 
	while(serial_rb_full(&stx)) {
		__asm__("nop");
	}

	serial_rb_write(&stx, pkt_byte);
	IE2 |= UCA0TXIE;
}

unsigned char packet_byte_from_rcvq() 
{
	// wait until data arrived in buffer
	while(serial_rb_empty(&srx)) {
		__asm__("nop");
	}

	return serial_rb_read(&srx);
}

interrupt(USCIAB0RX_VECTOR) USCI0RX_ISR(void)
{
	if (!serial_rb_full(&srx)) {
        serial_rb_write(&srx, UCA0RXBUF);
	}
}

interrupt(USCIAB0TX_VECTOR) USCI0TX_ISR(void)
{
	if(!serial_rb_empty(&stx)) {
    	serial_send(serial_rb_read(&stx));
    }
    else {
    	/* Disable the TX interrupt, it's no longer needed. */
		IE2 &= ~UCA0TXIE; 
    }
}

int main(void)
{
	clock_init();
	serial_init(9600);
	serirq_init();

	inp.start   = 0x24;
	outp.start	= 0x43;

	while (1) {
		// process packages endless ...
		if(packet_receive(&inp, 0x24) == PACKET_STAT_OK) {
			if(packet_process_received(&rcvh, &inp) == PACKET_STAT_ERR_UNKPACK) {
				// send ERROR packet (invalid packet type)
				outp.length 	= 0x05;
				outp.type 		= 0x01;
				outp.data[0]	= 0x03;
				outp.crc		= packet_calc_crc(&outp);

				packet_send(&outp);
			}
		}
		else {
			// send ERROR packet (invalid CRC/maleformed packet)
			outp.length 	= 0x05;
			outp.type 		= 0x01;
			outp.data[0]	= 0x02;
			outp.crc		= packet_calc_crc(&outp);

			packet_send(&outp);
		}
	}

	return 0;
}
