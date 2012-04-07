#include <msp430.h>

#include <libemb/serial/serial.h>
#include <libemb/conio/conio.h>

#include "packet.h"

void print_packet_data(unsigned char length, unsigned char *data) {

	unsigned char i;

	cio_printf("data_lenght=%x; data={ ", length);

	for(i = 0; i < length; i++) {
		cio_printf("[%x] ", data[i]);
	}	

	cio_print("} ");
}

void print_packet(packet *pkt) {

	cio_printf("start=%x; length=%x; type=%x; ", pkt->start, pkt->length, pkt->type);
	print_packet_data(pkt->length - 4, pkt->data);
	cio_print("\n\r");
}

int ph_pin_setup(unsigned char length, unsigned char *data) {

	cio_print("ph_pin_setup handler received data: ");
	print_packet_data(length, data);
	cio_print("\n\r");

	return 0;
}

int ph_system_info(unsigned char length, unsigned char *data) {

	cio_print("ph_system_info handler received data: ");
	print_packet_data(length, data);
	cio_print("\n\r");

	return 0;
}

packet_rcv_handlers rcvh = {
	.count = 2,
	.handlers = {
		{ 
			.type = 0x04,			// pin setup packet
			.func = ph_pin_setup,	// handler func
		},
		{ 
			.type = 0x02,			// system info packet 
			.func = ph_system_info,	// handler func
		},
	}
};

void clock_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

int packet_byte_to_sendq(unsigned char pkt_byte) {

	cio_printf("[%x] ", pkt_byte);

	return 0;
}

unsigned char packet_byte_from_rcvq() {

	static unsigned char i = 0;
	static unsigned char buf[] = { 
		0x24, 0x04, 0x02, 0x06, 					// system info request
		0x12, 0x33, 0x00,							// random bytes to be ignored
		0x24, 0x06, 0x04, 0x14, 0x03, 0x21, 		// configure pin 1.4 as output
		0x24, 0x06, 0x04, 0x14, 0x03, 0x22, 		// same but wrong CRC 
		0x24, 0x04, 0x02, 0x06, 					// system info request
		0x00, 0xff,									// random bytes to be ignored
		0x24, 0x06, 0x04, 0x14, 0x03, 0x21, 		// configure pin 1.4 as output
		0x24, 0x04, 0x00, 0x04,						// NULL request
	};	

	unsigned char b = buf[i];
	
	i++;

	if(i >= sizeof(buf)) i = 0;

	return b;
}

int main(void)
{
	packet outp;
	packet inp;

	int s;

	clock_init();
	serial_init(9600);

	cio_print("** ROCKETuC - libpacket test **\n\r");

	// assemble and dummy-send NULL packet 

	outp.start 		= 0x43;
	outp.length 	= 0x04;
	outp.type 		= 0x00;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	if(outp.crc == 0x04) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");
	
	// assemble and dummy-send ACK packet 
	outp.start 		= 0x43;
	outp.length 	= 0x05;
	outp.type 		= 0x01;
	outp.data[0]	= 0x01;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	if(outp.crc == 0x07) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");

	// receive system-info packet 
	s = packet_receive(&inp, 0x24);

	print_packet(&inp);
	if(s == 0) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");
	
	// receveive pin config package 
	s = packet_receive(&inp, 0x24);

	print_packet(&inp);
	if(s == 0) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");
	
	// receveive pin config package whith wron CRC 
	s = packet_receive(&inp, 0x24);

	print_packet(&inp);
	if(s == 0) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");
	
	// receveive and prcoess system info 
	if(packet_receive(&inp, 0x24) == 0) {
		print_packet(&inp);
		if(packet_process_received(&rcvh, &inp) == 0) {
			cio_print("OK\n\r"); 	
		}
		else {
			cio_print("FAIL UNKNOWN\n\r");
		}
	}
	else {
		cio_print("FAIL CRC\n\r");
	}
	
	// receveive and prcoess pin setup 
	if(packet_receive(&inp, 0x24) == 0) {
		print_packet(&inp);
		if(packet_process_received(&rcvh, &inp) == 0) {
			cio_print("OK\n\r"); 	
		}
		else {
			cio_print("FAIL UNKNOWN\n\r");
		}
	}
	else {
		cio_print("FAIL CRC\n\r");
	}
	
	// receveive and prcoess NULL (unknown) 
	if(packet_receive(&inp, 0x24) == 0) {
		print_packet(&inp);
		if(packet_process_received(&rcvh, &inp) == 0) {
			cio_print("OK\n\r"); 	
		}
		else {
			cio_print("FAIL UNKNOWN\n\r");
		}
	}
	else {
		cio_print("FAIL CRC\n\r");
	}

	while (1) {
		__asm__("nop");
	}

	return 0;
}
