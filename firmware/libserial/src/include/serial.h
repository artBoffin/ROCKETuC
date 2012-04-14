/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
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

#ifndef __SERIAL_H_
#define __SERIAL_H_

/**
 * Initialize the default USART with the given baudrate.
 *
 * @param[in]	baudrate	the baudrate of the USART
 */
void serial_init(unsigned int baudrate);

/**
 * Send a byte non-blocking through the default USART.
 *
 * @param[in]	data	byte to send
 */
void serial_send(unsigned char data);

/**
 * Send a byte blocking through the default USART.
 *
 * @param[in]	data	byte to send
 */
void serial_send_blocking(unsigned char data);

/**
 * Receive a byte non-blocking from the default USART (makes
 * only sense when used in an ISR).
 *
 * @return	byte received
 */
unsigned char serial_recv();

/**
 * Receive a byte blocking from the default USART.
 *
 * @return	byte received
 */
unsigned char serial_recv_blocking();

#endif
