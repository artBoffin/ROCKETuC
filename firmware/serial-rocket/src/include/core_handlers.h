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

#ifndef __COREHANDLERS_H_
#define __COREHANDLERS_H_

int handle_packet_null(unsigned char length, unsigned char *data);

int handle_packet_reserved(unsigned char length, unsigned char *data);

int handle_packet_system_info(unsigned char length, unsigned char *data);

int handle_packet_device_control(unsigned char length, unsigned char *data);

int handle_packet_pin_function(unsigned char length, unsigned char *data);

int handle_packet_pin_control(unsigned char length, unsigned char *data);

int handle_packet_pwm_function(unsigned char length, unsigned char *data);

int handle_packet_pwm_control(unsigned char length, unsigned char *data);

int handle_packet_serial_function(unsigned char length, unsigned char *data);

int handle_packet_serial_data(unsigned char length, unsigned char *data);

int handle_packet_external_interrupt_function(unsigned char length, unsigned char *data);

int handle_packet_reset(unsigned char length, unsigned char *data);

#endif
