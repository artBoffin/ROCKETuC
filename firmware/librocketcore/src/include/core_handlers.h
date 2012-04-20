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

#ifndef __COREHANDLERS_H_
#define __COREHANDLERS_H_

/**
 * Handle in-bound packet of type NULL. 
 *
 * For this kind of packet a STATUS response with ACK is sent back to the client.
 *
 * @param	length		length of data in bytes
 * 						which is zero for the NULL packet
 * @param	*data		the data part received with the in-bound packet
 * 						which is empty for the NULL packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the NULL packet
 */
int handle_packet_null(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type RESERVED. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the RESERVED packet
 */
int handle_packet_reserved(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type SYSTEM INFO. 
 *
 * For this kind of packet a SYSTEM INFO response with board-type, MCU-type and
 * firmware revision is sent back to the client.
 *
 * @param	length		length of data in bytes
 * 						which is zero for the SYSTEM INFO packet
 * @param	*data		the data part received with the in-bound packet
 * 						which is empty for the SYSTEM INFO packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the SYSTEM INFO packet
 */
int handle_packet_system_info(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type DEVICE CONTROL. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the DEVICE CONTROL packet
 */
int handle_packet_device_control(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type PIN FUNCTION. 
 *
 * For this kind of packet a STATUS response with ACK is sent back to the client if the return
 * status was PACKET_STAT_OK, and INVALID-PIN-COMMAND otherwise. 
 *
 * @param	length		length of data in bytes
 * 						which is 2 for the PIN FUNCTION packet
 * @param	*data		the data part received with the in-bound packet
 * 						which is ony byte each for PIN and FUNCTION for the PIN FUNCTION packet
 * @return				status regarding handling of this packet
 * 						which for the PIN FUNCTION packet is:
 * 						PACKET_STAT_OK if PIN setup was successfull, 
 * 						PACKET_ERR_LENGTH/PACKET_ERR_DATA if data was maleformed
 */
int handle_packet_pin_function(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type PIN CONTROL. 
 *
 * For this kind of packet a STATUS response with ACK is sent back on success for commands which
 * do not return a value (like PIN_SET, PIN_CLEAR, PIN_TOGGLE). For commands which return a value
 * (like DIGITAL_RED, ANALOG_READ), the corresponding response packet is sent back. On Error the
 * STATUS with type INVALID-PIN-COMMAND is sent back. 
 *
 * @param	length		length of data in bytes
 * 						which is 2 for the PIN CONTROL packet
 * @param	*data		the data part received with the in-bound packet
 * 						which is ony byte each for PIN and CONTROL for the PIN CONTROL packet
 * @return				status regarding handling of this packet
 * 						which for the PIN CONTROL packet is:
 * 						PACKET_STAT_OK if PIN control was successfull, 
 * 						PACKET_ERR_LENGTH/PACKET_ERR_DATA if data was maleformed
 */
int handle_packet_pin_control(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type PWM FUNCTION. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the PWM FUNCTION packet
 */
int handle_packet_pwm_function(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type PWM CONTROL. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the PWM CONTROL packet
 */
int handle_packet_pwm_control(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type SERIAL FUNCTION. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the SERIAL FUNCTION packet
 */
int handle_packet_serial_function(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type SERIAL DATA. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the SERIAL DATA packet
 */
int handle_packet_serial_data(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type EXTERNAL INTERRUPT FUNCTION. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the EXTERNAL INTERRUPT FUNCTION packet
 */
int handle_packet_external_interrupt_function(unsigned char length, unsigned char *data);

/**
 * Handle in-bound packet of type RESET. 
 *
 * NOT DEFINED / IMPLEMENTED 
 *
 * For this kind of packet a STATUS response with UNKNOWN is sent back to the client.
 *
 * @param	length		length of data in bytes
 * @param	*data		the data part received with the in-bound packet
 * @return				status regarding handling of this packet
 * 						which is allways PACKET_STAT_OK for the RESET packet
 */
int handle_packet_reset(unsigned char length, unsigned char *data);

#endif
