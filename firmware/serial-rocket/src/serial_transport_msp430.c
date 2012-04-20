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
#include <legacymsp430.h>

#include "serial.h"
#include "serial_rb.h"
#include "core_proto.h"
#include "packet_handler.h"
#include "config.h"

/**
 * Serial ringbuffer to receive packet data
 */
SERIAL_RB_Q srx_buf[RB_SIZE];
serial_rb srx;

/**
 * Serial ringbuffer to send packet data
 */
SERIAL_RB_Q stx_buf[RB_SIZE];
serial_rb stx;

void packet_handler_init()
{
	serial_init(BAUDRATE);

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
		IE2 &= ~UCA0TXIE; 
    }
}

