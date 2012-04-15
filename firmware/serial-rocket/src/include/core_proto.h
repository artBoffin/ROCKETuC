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

#ifndef __COREPROTO_H_
#define __COREPROTO_H_

#define PACKET_IN_NULL  						0x00 
#define PACKET_IN_RESERVED  					0x01
#define PACKET_IN_SYSTEM_INFO 					0x02
#define PACKET_IN_DEVICE_CONTROL  				0x03
#define PACKET_IN_PIN_FUNCTION  				0x04
#define PACKET_IN_PIN_CONTROL  					0x05
#define PACKET_IN_PWM_FUNCTION  				0x06
#define PACKET_IN_PWM_CONTROL  					0x07
#define PACKET_IN_SERIAL_FUNCTION 				0x08
#define PACKET_IN_SERIAL_DATA  					0x09
#define PACKET_IN_EXTERNAL_INTERRUPT_FUNCTION 	0x0A
#define PACKET_IN_RESET						 	0xFF

#define PACKET_OUT_NULL							0x00
#define PACKET_OUT_STATUS 						0x01
#define PACKET_OUT_SYSTEM_INFO					0x02
#define PACKET_OUT_DIGITAL_PIN_READ				0x03
#define PACKET_OUT_ANALOG_PIN_READ				0x04
#define PACKET_OUT_PULSE_LEGHT_READ				0x05

#define PACKET_STATUS_UNKNOWN					0x00
#define PACKET_STATUS_ACK						0x01
#define PACKET_STATUS_BAD_PACKET				0x02
#define PACKET_STATUS_INVALID_PACKET			0x03
#define PACKET_STATUS_INAVLID_DATA				0x04
#define PACKET_STATUS_INVALID_PIN_COMMAND		0x05

typedef struct {
	unsigned char	pin;
	unsigned char	function;
} packet_data_in_pin_function;

typedef struct {
	unsigned char	pin;
	unsigned char	mode;
} packet_data_in_pin_control;

typedef struct {
	unsigned char	pin;
	unsigned char	period_lsb;
	unsigned char	period_msb;
} packet_data_in_pwm_function;

typedef struct {
	unsigned char	pin;
	unsigned char	duty_cycle;
} packet_data_in_pwm_control;

typedef struct {
	unsigned char	pin;
	// TODO
} packet_data_in_serial_function;

typedef struct {
	unsigned char	pin;
	// TODO
} packet_data_in_serial_data;

typedef struct {
	unsigned char	pin;
	// TODO
} packet_data_in_external_interrupt_function;

typedef struct {
	unsigned char	board_type;
	unsigned char	mcu_type;
	unsigned char	firmware_rev;
} packet_data_out_system_info;

typedef struct {
	unsigned char	status;
} packet_data_out_status;

typedef struct {
	unsigned char	pin;
	unsigned char	state;
} packet_data_out_digital_pin_read;

typedef struct {
	unsigned char	pin;
	unsigned char	value_lsb;
	unsigned char	value_msb;
} packet_data_out_analog_pin_read;

#endif
