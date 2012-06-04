/* 
 * This file is part of the JRocket Library project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The JRocket Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * JRocket Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the JRocket firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

package rocketuc.jrocket.comm;

public class Packet {

	public static final int PACKET_MAX_DATA 		= 32;

	public static final byte PACKET_START_OUTB		= 0x24;

	public static final byte PACKET_START_INB 		= 0x2b;
	
	public static final byte PACKET_START_INBEV		= 0x21;

	private static final int PACKET_FILL_WAIT 		= 0;

	private static final int PACKET_FILL_START 		= 1;
	
	private static final int PACKET_FILL_LENGTH		= 2;
	
	private static final int PACKET_FILL_TYPE 		= 3;
	
	private static final int PACKET_FILL_DATA 		= 4;
	
	private static final int PACKET_FILL_CRC 		= 5;

	private static final int PACKET_FILL_COMPLETE 	= 6;
	
	private int currFill = 0;
	
	private int currDataLength = 0;

	/**
	 * Start byte
	 */
	private byte start;

	/**
	 * Overall packet length
	 */
	private byte length;

	/**
	 * Packet type
	 */
	private byte type;

	/**
	 * Packet payload
	 */
	private byte data[];

	/**
	 * Packet CRC including everything from type to data
	 */
	private byte crc;

	public Packet() {
		clear();
	}

	public Packet(byte[] pkt) throws PacketException {
		fromByteArray(pkt);
	}

	public Packet(byte start, byte length, byte type, byte data[]) throws PacketException {
		clear();

		this.start 	= start;
		this.length = length;
		this.type 	= type;
		this.data 	= data;

		currFill = PACKET_FILL_COMPLETE;

		this.crc 	= calcCrc();
		
	}

	public Packet(byte start, byte length, byte type, byte data[], byte crc) throws PacketException {
		clear();

		this.start 	= start;
		this.length = length;
		this.type 	= type;
		this.data 	= data;
		this.crc 	= crc;

		currFill = PACKET_FILL_COMPLETE;

		if(!checkCrc()) {
			throw new PacketException("CRC error");
		}
	}

	/**
	 * Calculate a packets CRC. The CRC includes everything from type to data.
	 * 
	 * @return the calculated CRC
	 */
	byte calcCrc() throws PacketException {

		byte[] p = toByteArray();

		byte newCrc = 0;

		for(int i = 0; i < p.length - 1; i++) {
			newCrc += p[i];
		}

		return newCrc;
	}

	/**
	 * Calculate the packets CRC and compare it to the CRC given in the packets
	 * CRC field.
	 * 
	 * @return 		true if CRC matches, false otherwise
	 */
	boolean checkCrc() throws PacketException {
		return (crc == calcCrc());
	}
	
	public void clear() {
		start 			= 0;
		length 			= 0;
		type 			= 0;
		data 			= null;
		crc 			= 0;
		currFill		= 0;
		currDataLength  = 0;
	}
	
	public void addByte(byte b) throws PacketException {
		
		switch(currFill) {
		case PACKET_FILL_WAIT:
			if(b == PACKET_START_OUTB || b == PACKET_START_INB || b == PACKET_START_INBEV) {
				currFill++;
			}
			else {
				break;
			}
		case PACKET_FILL_START:
			start = b;
			crc += b;
			currFill++;
			break;
		case PACKET_FILL_LENGTH:
			length = b;
			crc += b;
			if(length - 4 > PACKET_MAX_DATA) {
				throw new PacketException("Packet to big: was " + length + ", allowd " + 
											(PACKET_MAX_DATA + 4));
			}

			if(length - 4 > 0) {
				data = new byte[length - 4];
			}

			currFill++;
			break;
		case PACKET_FILL_TYPE:
			type = b;
			crc += b;
			currFill++;
			if(data == null) {
				currFill++;
			}
			break;
		case PACKET_FILL_DATA:
			if(data != null) {
				data[currDataLength++] = b;
				crc += b;
				if(currDataLength == length - 4) {
					currFill++;
				}
			}
			break;
		case PACKET_FILL_CRC:
			currFill++;
			if(b != crc) {
				throw new PacketException("CRC error: expected " + Integer.toHexString(crc) + " and got " + Integer.toHexString(b));
			}			
			break;	
		default:
			throw new PacketException("Packet already complete");
		}
	}
	
	public boolean isComplete() {
		return (currFill == PACKET_FILL_COMPLETE);
	}
	
	public void fromByteArray(byte[] pkt) throws PacketException {
		clear();
		
		for(byte b : pkt) {
			addByte(b);
		}
	}
	
	public byte[] toByteArray() throws PacketException {

		if(!isComplete()) {
			throw new PacketException("Incompelte packet");
		}

		if(length > 4 && (data == null || data.length != length - 4)) {
			throw new PacketException("Invalid packet");
		}

		byte p[] = new byte[length];

		p[0] = start;
		p[1] = length;
		p[2] = type;
	
		if(data != null) {
			int i = 3;

			for(byte b :data) {
				p[i++] = b;			
			}
		}
		
		p[length - 1] = crc;

		return p;
	}
	
	@Override
	public String toString(){
 
		byte[] p = {};

		try {
			p = toByteArray();
		}
		catch(PacketException e) {
			return e.getMessage();
		}

		String s = "{";

		for(byte b : p) {
			s += Integer.toHexString(0x000000FF & b) + ", ";
		}

		s += "}";

		return s;
	}

	public byte getStart() {
		return start;
	}
	public byte getType() {
		return type;
	}

	public byte[] getData() {
		return data;
	}

	public byte getLength() {
		return length;
	}

	public byte getCrc() {
		return crc;
	}

	public static void main(String[] args) {

		System.out.println("PacketTest");

		// empty packet
		Packet p1 = new Packet();
		System.out.println("p1: " + p1);

		// fill from bytes
  		byte pNull[] = {0x24, 0x04, 0x00, 0x28};

		try {
			p1.fromByteArray(pNull);
			System.out.println("p1: " + p1);
		}
		catch(PacketException e) {
			System.err.println(e.getMessage());
		}

		// from single parameters, including CRC
		try {
			Packet p2 = new Packet((byte)0x24, (byte)0x04, (byte)0x02, null, (byte)0x2a);
			System.out.println("p2: " + p2);
		}
		catch(PacketException e) {
			System.err.println(e.getMessage());
		}
		
		// from single parameters, excluding CRC
		try {
			Packet p3 = new Packet((byte)0x24, (byte)0x04, (byte)0x02, null);
			System.out.println("p3: " + p3);
		}
		catch(PacketException e) {
			e.printStackTrace();
			System.err.println(e.getMessage());
		}
		
		// from byte array
		try {
			byte[] data = {(byte)0x24, (byte)0x07, (byte)0x06, (byte)0x22, (byte)0x20, (byte)0x4e, (byte)0xc1};
			Packet p4 = new Packet(data);
			System.out.println("p4: " + p4);
		}
		catch(PacketException e) {
			e.printStackTrace();
			System.err.println(e.getMessage());
		}		
		
		// consume from byte array with leading garbage
		try {
			byte[] data = {
					(byte)0x18, (byte)0x01, 
					(byte)0x24, (byte)0x07, (byte)0x06, (byte)0x22, (byte)0x20, (byte)0x4e, (byte)0xc1,
					(byte)0xFF, 
					(byte)0x24, (byte)0x06, (byte)0x05, (byte)0x13, (byte)0x03, (byte)0x45,
			};
			
			Packet p5 = new Packet();
			
			for(byte b : data) {
			
				p5.addByte(b);
				
				if(p5.isComplete()) {
					System.out.println("Found packet in stream: " + p5);
					p5.clear();
				}
			}
		}
		catch(PacketException e) {
			e.printStackTrace();
			System.err.println(e.getMessage());
		}
		
		// from single parameters, including WRONG CRC
		try {
			Packet p2 = new Packet((byte)0x24, (byte)0x04, (byte)0x02, null, (byte)0x20);
			System.out.println("p2: " + p2);
		}
		catch(PacketException e) {
			System.err.println(e.getMessage());
		}		
	}
}
