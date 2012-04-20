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

#ifndef __COREPROTO_H_
#define __COREPROTO_H_

#include "packet.h"

/**
 * IN-bound packet of type NULL
 */
#define PACKET_IN_NULL  						0x00 

/**
 * IN-bound packet of type RESERVED 
 */
#define PACKET_IN_RESERVED  					0x01

/**
 * IN-bound packet of type SYSTEM INFO 
 */
#define PACKET_IN_SYSTEM_INFO 					0x02

/**
 * IN-bound packet of type DEVICE CONTROL 
 */
#define PACKET_IN_DEVICE_CONTROL  				0x03

/**
 * IN-bound packet of type PIN FUNCTION 
 */
#define PACKET_IN_PIN_FUNCTION  				0x04

/**
 * IN-bound packet of type PIN CONTROL 
 */
#define PACKET_IN_PIN_CONTROL  					0x05

/**
 * IN-bound packet of type PWM FUNCTION 
 */
#define PACKET_IN_PWM_FUNCTION  				0x06

/**
 * IN-bound packet of type PWM CONTROL 
 */
#define PACKET_IN_PWM_CONTROL  					0x07

/**
 * IN-bound packet of type SERIAL FUNCTION 
 */
#define PACKET_IN_SERIAL_FUNCTION 				0x08

/**
 * IN-bound packet of type SERIAL DATA 
 */
#define PACKET_IN_SERIAL_DATA  					0x09

/**
 * IN-bound packet of type EXTERNAL INTERRUPT FUNCTION 
 */
#define PACKET_IN_EXTERNAL_INTERRUPT_FUNCTION 	0x0A

/**
 * IN-bound packet of type RESET 
 */
#define PACKET_IN_RESET						 	0xFF


/**
 * OUT-bound packet of type NULL 
 */
#define PACKET_OUT_NULL							0x00

/**
 * OUT-bound packet of type STATUS
 */
#define PACKET_OUT_STATUS 						0x01

/**
 * OUT-bound packet of type SYSTEM INFO
 */
#define PACKET_OUT_SYSTEM_INFO					0x02

/**
 * OUT-bound packet of type DIGITAL PIN READ
 */
#define PACKET_OUT_DIGITAL_PIN_READ				0x03

/**
 * OUT-bound packet of type ANALOG PIN READ 
 */
#define PACKET_OUT_ANALOG_PIN_READ				0x04

/**
 * OUT-bound packet of type PULSE LENGTH READ 
 */
#define PACKET_OUT_PULSE_LEGHT_READ				0x05


/**
 * Return status UNKNOWN for the STATUS OUT-bound packet
 */
#define PACKET_RETURN_UNKNOWN					0x00

/**
 * Return status ACK for the STATUS OUT-bound packet
 */
#define PACKET_RETURN_ACK						0x01

/**
 * Return status BAD PACKET for the STATUS OUT-bound packet
 */
#define PACKET_RETURN_BAD_PACKET				0x02

/**
 * Return status INVALID PACKET for the STATUS OUT-bound packet
 */
#define PACKET_RETURN_INVALID_PACKET			0x03

/**
 * Return status INVLAID DATA for the STATUS OUT-bound packet
 */
#define PACKET_RETURN_INAVLID_DATA				0x04

/**
 * Return status INVALID PIN COMMAND for the STATUS OUT-bound packet
 */
#define PACKET_RETURN_INVALID_PIN_COMMAND		0x05


/**
 * Control command PIN CLEAR for the PIN CONTROL packet
 */
#define PIN_CONTROL_CLEAR						0x00

/**
 * Control command PIN SET for the PIN CONTROL packet
 */
#define PIN_CONTROL_SET							0x01

/**
 * Control command PIN TOGGLE for the PIN CONTROL packet
 */
#define PIN_CONTROL_TOGGLE						0x02

/**
 * Control command DIGITAL READ for the PIN CONTROL packet
 */
#define PIN_CONTROL_DIGITAL_READ				0x03

/**
 * Control command ANALOG READ for the PIN CONTROL packet
 */
#define PIN_CONTROL_ANALOG_READ					0x04

/**
 * Control command PULSELENGTH READ for the PIN CONTROL packet
 */
#define PIN_CONTROL_PULSELENGTH_READ			0x05

/**
 * IN-bound data for PIN FUNCTION packet
 */
typedef struct {
	/**
 	 * PIN to which function is applied
 	 */
	unsigned char	pin;

	/**
 	 * Function to apply to pin (one of PIN_FUNCTION_x) 
 	 */
	unsigned char	function;
} packet_data_in_pin_function;

/**
 * IN-bound data for PIN CONTROL packet
 */
typedef struct {
	/**
 	 * PIN to control 
 	 */
	unsigned char	pin;

	/**
 	 * Control command to apply to PIN (one of PIN_CONTROL_x) 
 	 */
	unsigned char	control;
} packet_data_in_pin_control;

/**
 * IN-bound data for PWM FUNCTION packet
 */
typedef struct {
	/**
 	 * PIN to which PWM function is applied
 	 */
	unsigned char	pin;

	/**
 	 * LSB of PWM period
 	 */
	unsigned char	period_lsb;

	/**
 	 * MSB of PWM period
 	 */
	unsigned char	period_msb;
} packet_data_in_pwm_function;

/**
 * IN-bound data for PWM CONTROL packet
 */
typedef struct {
	/**
 	 * PIN for which PWM duty cycle is controlled
 	 */
	unsigned char	pin;

	/**
 	 * PWM duty cycle in % (of PWM period)
 	 */
	unsigned char	duty_cycle;
} packet_data_in_pwm_control;

/**
 * IN-bound data for SERIAL FUNCTION packet
 */
typedef struct {
	/**
 	 * PIN for which to apply serial function
 	 */
	unsigned char	pin;
	// TODO define/implement
} packet_data_in_serial_function;

/**
 * IN-bound data for SERIAL DATA packet
 */
typedef struct {
	/**
 	 * PIN for which send/receive serial data 
 	 */
	unsigned char	pin;
	// TODO define/implement
} packet_data_in_serial_data;

/**
 * IN-bound data for EXTERNAL INTERRUPT FUNCTION packet
 */
typedef struct {
	/**
 	 * PIN for which to configure external interrupt function
 	 */
	unsigned char	pin;
	// TODO define/implement
} packet_data_in_external_interrupt_function;

/**
 * OUT-bound data for SYSTEM INFO packet
 */
typedef struct {
	/**
	 * Board type identifier
	 */
	unsigned char	board_type;

	/**
	 * MCU type identifier
	 */
	unsigned char	mcu_type;

	/**
 	 * Firmware revision
 	 */
	unsigned char	firmware_rev;
} packet_data_out_system_info;

/**
 * OUT-bound data for STATUS packet
 */
typedef struct {
	/**
 	 * Status (one of PACKET_RETURN_x)
 	 */
	unsigned char	status;
} packet_data_out_status;

/**
 * OUT-bound data for DIGITAL PIN READ packet
 */
typedef struct {
	/**
 	 * PIN for which data was read
 	 */
	unsigned char	pin;

	/**
  	 * State read for pin (0/1)
  	 */
	unsigned char	state;
} packet_data_out_digital_pin_read;

/**
 * OUT-bound data for ANALOG PIN READ packet
 */
typedef struct {
	/**
 	 * PIN for which data was read
 	 */
	unsigned char	pin;

	/**
 	 * LSB of analog value read for pin
 	 */
	unsigned char	value_lsb;

	/**
 	 * MSB of analog value read for pin
 	 */
	unsigned char	value_msb;
} packet_data_out_analog_pin_read;

/**
 * OUT-bound packets use this packet instance
 */
extern packet outp;

/**
 * IN-bound packets use this packet instance
 */
extern packet inp;

/**
 * Send a OUT-bound STATUS packet with the given state (which is one of
 * PACKET_RETURN_x).
 *
 * @param[in]	stat	Status to return (one of PACKET_RETURN_x)
 */
void send_status_packet(unsigned char stat);

#endif
