#ifndef __PACKET_H_
#define __PACKET_H_

#define PACKET_MAX_DATA	16

typedef struct {

	unsigned char  start;

	unsigned char  length;

	unsigned char  type;

	unsigned char  data[PACKET_MAX_DATA];

	unsigned char  crc;

} packet;

typedef struct {

	unsigned char  type;

    int (*func)(unsigned char length, unsigned char* data);

} packet_rcv_handler;

typedef struct {

    unsigned char		count;

	packet_rcv_handler 	handlers[];

} packet_rcv_handlers;

unsigned char packet_calc_crc(packet *pkt);

int	packet_check_crc(packet *pkt);

int packet_send(packet *pkt);

int packet_receive(packet *pkt, unsigned char start);

int packet_process_received(packet_rcv_handlers *rh, packet *pkt);

int packet_byte_to_sendq(unsigned char pkt_byte);

unsigned char packet_byte_from_rcvq();

#endif
