#include "packet.h"

unsigned char packet_calc_crc(packet *pkt) {

	unsigned char i;
	unsigned char crc = 0;

	crc += pkt->length;
	crc += pkt->type;

	for(i = 0; i < pkt->length - 4; i++) {
		crc += pkt->data[i];
	} 

	return crc;
}

int	packet_check_crc(packet *pkt) {

	return (packet_calc_crc(pkt) != pkt->crc);
}

int packet_send(packet *pkt) {

	unsigned char  i;

	// check length
	if(pkt->length - 4 > PACKET_MAX_DATA) {
		return PACKET_STAT_ERR_LENGTH;
	}
 
	// write start byte
	packet_byte_to_sendq(pkt->start);

	// write length
	packet_byte_to_sendq(pkt->length);

	// write type
	packet_byte_to_sendq(pkt->type);

	// write data
	for(i = 0; i < pkt->length - 4; i++) {	
		packet_byte_to_sendq(pkt->data[i]); 
	}

	// write crc 
	packet_byte_to_sendq(pkt->crc);
	
	return PACKET_STAT_OK;
}

int packet_receive(packet *pkt, unsigned char start) {

	unsigned char  i;

	// discard everything until start byte found in buffer
	while(packet_byte_from_rcvq() != start);

	pkt->start = start;

	// read length
	pkt->length = packet_byte_from_rcvq();
	
	// check length
	if(pkt->length - 4 > PACKET_MAX_DATA) {
		return PACKET_STAT_ERR_LENGTH;
	}
 
	// read type
	pkt->type = packet_byte_from_rcvq();
 	
	// read data
	for(i = 0; i < pkt->length - 4; i++) {	
		pkt->data[i] = packet_byte_from_rcvq();
	}
	
	// read crc 
	pkt->crc = packet_byte_from_rcvq();
	
	// check crc
	return (packet_check_crc(pkt) ? PACKET_STAT_OK : PACKET_STAT_ERR_CRC);
}

int packet_process_received(packet_rcv_handlers *rh, packet *pkt) {

	int i;

    for(i = 0; i < rh->count; i++) {
		if(rh->handlers[i].type == pkt->type) {
			// call handler function
    		return (rh->handlers[i].func)(pkt->length - 4, pkt->data);
		}
    }

	return PACKET_STAT_ERR_UNKPACK;
}
