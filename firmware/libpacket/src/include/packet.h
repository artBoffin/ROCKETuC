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

#ifndef __PACKET_H_
#define __PACKET_H_

/**
 * Maximum size of packet data
 */
#define PACKET_MAX_DATA				64	

/**
 * Returned status for successful packet operation
 */
#define PACKET_STAT_OK				 0
	
/**
 * Returned status if packet data exceeds PACKET_MAX_DATA
 */
#define PACKET_STAT_ERR_LENGTH		-1

/**
 * Returned status if packet had CRC error
 */
#define PACKET_STAT_ERR_CRC			-2

/**
 * Returned status if packet type was unknown 
 */
#define PACKET_STAT_ERR_UNKPACK		-3

/**
 * Returned status if packet data was maleformed 
 */
#define PACKET_STAT_ERR_DATA		-4

/**
 * General definition of a binary packet
 */
typedef struct {

	/**
 	 * Start byte
 	 */
	unsigned char  start;

	/**
  	 * Overall packet length
  	 */
	unsigned char  length;

	/**
 	 * Packet type
 	 */
	unsigned char  type;

	/**
 	 * Packet payload
 	 */
	unsigned char  data[PACKET_MAX_DATA];

	/**
 	 * Packet CRC including everithing from type to data
 	 */
	unsigned char  crc;

} packet;

/**
 * Definition of a packet receive handler for a certain packet type
 */
typedef struct {

	/**
 	 * Packet type for which the handler applies
 	 */
	unsigned char  type;

	/**
	 * Handler function
	 */
    int (*func)(unsigned char length, unsigned char* data);

} packet_rcv_handler;

/**
 * Array of packet handlers
 */
typedef struct {

	/**
 	 * Number of handlers
 	 */
    unsigned char		count;

	/**
 	 * Array of handlers
 	 */
	packet_rcv_handler 	handlers[];

} packet_rcv_handlers;

/**
 * Calculate a packets CRC. The CRC includes everything from
 * type to data. 
 *
 * @param[in]	*pkt	pointer to packet for which to calculate the CRC
 * @return				the calculated CRC 
 */
unsigned char packet_calc_crc(packet *pkt);

/**
 * Calculate the packets CRC and compare it to the CRC given in the
 * packets CRC field.
 *
 * @param[in]	*pkt	pointer to packet for which to check the CRC
 * @return				1 if CRC matches, 0 otherwise	
 */
int	packet_check_crc(packet *pkt);

/**
 * Send a given packet. The method {@link packet_byte_to_sendq} is called for
 * each byte that has to be sent out. 
 *
 * @param[in]	*pkt	pointer to packet which has to be sent 
 * @return				on success return PACKET_STAT_OK, 
 * 						if given package length exceeds the maximum
 * 						data length PACKET_STAT_ERR_LENGHT
 */ 
int packet_send(packet *pkt);

/**
 * Receive a packet. The method {@link packet_byte_from_recvq} is called to  
 * fetch bytes from in queue. Bytes from in queue are discarded until the given start
 * byte is detected.  
 *
 * @param[out]	*pkt	pointer to packet which receives the data 
 * @param[in]	 start	start byte which indicates start of a package
 * @return				on success return PACKET_STAT_OK, 
 * 						if given package length exceeds the maximum
 * 						data length PACKET_STAT_ERR_LENGHT,
 * 						and PACKET_STAT_ERR_CRC on CRC error
 */ 
int packet_receive(packet *pkt, unsigned char start);

/**
 * Search given array handlers for a handler matching the type in the gvien 
 * packet. If a handler was found, it's handler function is called. 
 *
 * @param[in]	*rh		pointer to array which receive handlers
 * @oaram[in]	*pkt	pointer to packet which should be handled
 * @return			 	the return value from the handler function (which should be >= 0),
 * 						or if no handler was found for the packet, PACKET_STAT_ERR_UNKPACK	
 */ 
int packet_process_received(packet_rcv_handlers *rh, packet *pkt);

/**
 * Push a given byte to the send queue. The implementation of this function is
 * up to the user, since it could not be foreseen what means of transportation 
 * should be used. This operation should be implemented blocking. 
 *
 * @param[in]	pkt_byte	packet byte to push to send queue
 */
void packet_byte_to_sendq(unsigned char pkt_byte);

/**
 * Read a byte from the receive queue. The implementation of this function is
 * up to the user, since it could not be foreseen what means of transportation 
 * should be used. This operation should be implemented blocking. 
 *
 * @return 					the byte received	
 */
unsigned char packet_byte_from_rcvq();

#endif
