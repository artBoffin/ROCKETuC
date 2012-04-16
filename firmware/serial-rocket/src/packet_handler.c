/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC firmware is free software{}; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation{}; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY{}; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the ROCKETuC firmware{}; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

#include "packet_handler.h"
#include "core_handlers.h"

// TODO: use constands form core_protocol.h for type
packet_rcv_handlers packet_handlers = {
	.count = 12,
	.handlers = {
		{ 
			.type = 0x00,					// null 
			.func = handle_packet_null,		
		},
		{ 
			.type = 0x01,					// reserved 
			.func = handle_packet_reserved,		
		},
		{ 
			.type = 0x02,					// system info  
			.func = handle_packet_system_info,	
		},
		{ 
			.type = 0x03,					// device control 
			.func = handle_packet_device_control,	
		},
		{ 
			.type = 0x04,					// pin function 
			.func = handle_packet_pin_function,	
		},
		{ 
			.type = 0x05,					// pin control
			.func = handle_packet_pin_control,	
		},
		{ 
			.type = 0x06,					// PWM function 
			.func = handle_packet_pwm_function,
		},
		{ 
			.type = 0x07,					// PWM control
			.func = handle_packet_pwm_control,
		},
		{ 
			.type = 0x08,					// serial function 
			.func = handle_packet_serial_function,
		},
		{ 
			.type = 0x09,					// serial control 
			.func = handle_packet_serial_data,
		},
		{ 
			.type = 0x0A,					// EXTI function 
			.func = handle_packet_external_interrupt_function,
		},
		{ 
			.type = 0xFF,					// reset 
			.func = handle_packet_reset,
		},
	}
};

int packet_handle(packet *pkt) 
{
	return packet_process_received(&packet_handlers, pkt);
}

