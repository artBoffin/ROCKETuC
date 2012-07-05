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
#include "core_proto.h"
#include "core_handlers.h"
// #include "conio.h"

packet_rcv_handlers packet_handlers = {
	.count = 9,
	.handlers = {
		{ 
			.type = PACKET_IN_NULL,	
			.func = handle_packet_null,		
		},
		{ 
			.type = PACKET_IN_RESERVED,
			.func = handle_packet_reserved,		
		},
		{ 
			.type = PACKET_IN_SYSTEM_INFO,
			.func = handle_packet_system_info,	
		},
		{ 
			.type = PACKET_IN_PIN_FUNCTION,
			.func = handle_packet_pin_function,	
		},
		{ 
			.type = PACKET_IN_PIN_CONTROL,
			.func = handle_packet_pin_control,	
		},
		{ 
			.type = PACKET_IN_PWM_FUNCTION, 
			.func = handle_packet_pwm_function,
		},
		{ 
			.type = PACKET_IN_PWM_CONTROL,
			.func = handle_packet_pwm_control,
		},
		{ 
			.type = PACKET_IN_EXTERNAL_INTERRUPT_FUNCTION, 
			.func = handle_packet_external_interrupt_function,
		},
		{ 
			.type = PACKET_IN_RESET, 
			.func = handle_packet_reset,
		},
	}
};

void packet_do_handle()
{
	if(packet_receive(&inp, PACKET_INBOUND_START) == PACKET_STAT_OK) {
		if(packet_process_received(&packet_handlers, &inp) == PACKET_STAT_ERR_UNKPACK) {
			send_status_packet(PACKET_RETURN_INVALID_PACKET);
		}
	}
	else {
		send_status_packet(PACKET_RETURN_BAD_PACKET);
	}
}
