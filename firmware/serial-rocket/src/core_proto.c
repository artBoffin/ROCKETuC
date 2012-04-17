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

#include "core_proto.h"
#include "packet_handler.h"

packet outp;
packet inp;

void send_status_packet(unsigned char stat)
{
	packet_data_out_status *pd = (packet_data_out_status *)&outp.data[0];

	outp.start	= PACKET_OUTBOUND_START;
	outp.length	= 4 + sizeof(packet_data_out_status);
	outp.type 	= PACKET_OUT_STATUS;
	pd->status  = stat;
	outp.crc	= packet_calc_crc(&outp);

	packet_send(&outp);
}

