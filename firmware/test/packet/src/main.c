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

#include "serial.h"
#include "conio.h"
#include "packet.h"

int ph_pin_setup(unsigned char length, unsigned char *data);

int ph_system_info(unsigned char length, unsigned char *data);

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

void clock_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;
}

void packet_byte_to_sendq(unsigned char pkt_byte) {

	cio_printf("[%x] ", pkt_byte);
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
	outp.start 		= 0x2B;
	outp.length 	= 0x04;
	outp.type 		= 0x00;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	if(outp.crc == 0x04) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");
	
	// assemble and dummy-send ACK packet 
	outp.start 		= 0x2B;
	outp.length 	= 0x05;
	outp.type 		= 0x01;
	outp.data[0]	= 0x01;
	outp.crc		= packet_calc_crc(&outp);

	packet_send(&outp);

	if(outp.crc == 0x07) cio_print("OK\n\r"); else cio_print("FAIL CRC\n\r");

	// receive system-info packet 
	s = packet_receive(&inp, 0x24);

	print_packet(&inp);
	if(s == PACKET_STAT_OK) cio_print("OK\n\r"); else cio_printf("FAIL: %i\n\r", s);
	
	// receveive pin config package 
	s = packet_receive(&inp, 0x24);

	print_packet(&inp);
	if(s == PACKET_STAT_OK) cio_print("OK\n\r"); else cio_printf("FAIL: %i\n\r", s);
	
	// receveive pin config package whith wron CRC 
	s = packet_receive(&inp, 0x24);

	print_packet(&inp);
	if(s == PACKET_STAT_OK) cio_print("OK\n\r"); else cio_printf("FAIL: %i\n\r", s);

	// receveive and prcoess system info 
	if((s = packet_receive(&inp, 0x24)) == PACKET_STAT_OK) {
		print_packet(&inp);
		if(packet_process_received(&rcvh, &inp) != PACKET_STAT_ERR_UNKPACK) {
			cio_print("OK\n\r"); 	
		}
		else {
			cio_print("FAIL UNKNOWN\n\r");
		}
	}
	else {
		cio_printf("FAIL: %s\n\r", s);
	}
	
	// receveive and prcoess pin setup 
	if((s = packet_receive(&inp, 0x24)) == PACKET_STAT_OK) {
		print_packet(&inp);
		if(packet_process_received(&rcvh, &inp) != PACKET_STAT_ERR_UNKPACK) {
			cio_print("OK\n\r"); 	
		}
		else {
			cio_print("FAIL UNKNOWN\n\r");
		}
	}
	else {
		cio_printf("FAIL: %s\n\r", s);
	}
	
	// receveive and prcoess NULL (unknown) 
	if((s = packet_receive(&inp, 0x24)) == PACKET_STAT_OK) {
		print_packet(&inp);
		if(packet_process_received(&rcvh, &inp) != PACKET_STAT_ERR_UNKPACK) {
			cio_print("OK\n\r"); 	
		}
		else {
			cio_print("FAIL UNKNOWN\n\r");
		}
	}
	else {
		cio_printf("FAIL: %s\n\r", s);
	}

	while (1) {
		__asm__("nop");
	}

	return 0;
}
