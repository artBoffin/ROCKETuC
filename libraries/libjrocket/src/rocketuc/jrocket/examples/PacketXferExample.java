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

package rocketuc.jrocket.examples;

import rocketuc.jrocket.comm.Packet;
import rocketuc.jrocket.comm.SerialPacketStream;

public class PacketXferExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		SerialPacketStream sps = new SerialPacketStream();
		
		try {
			sps.connect("/dev/ttyUSB0");
			System.out.println("CONNECTED");
			
			sps.start();
 
			Packet ret;
			
			// PIN FUNCTION digital p1.0 Packet
			ret = sps.xfer(new Packet((byte)0x24, (byte)0x06, (byte)0x04, new byte[] { (byte)0x10, (byte)0x03 }));
			System.out.println("Set P1.0 to digital IO responded with: " + ret);

			for(int i = 0; i < 10; i++) {
				// PIN CONTROL digital p1.0 
				ret = sps.xfer(new Packet((byte)0x24, (byte)0x06, (byte)0x05, new byte[] { (byte)0x10, (byte)0x01 }));
				System.out.println("Set P1.0 HIGH responded with: " + ret);
	
				Thread.sleep(250);
				
				// PIN CONTROL digital p1.0 
				ret = sps.xfer(new Packet((byte)0x24, (byte)0x06, (byte)0x05, new byte[] { (byte)0x10, (byte)0x00 }));
				System.out.println("Set P1.0 LOW responded with: " + ret);
				
				Thread.sleep(250);
			}
			
			sps.stop();
			
			sps.disconnect();			

			System.out.println("DISCONNECTED");
			
		} catch (Exception e) {
			e.printStackTrace();
		}			
	}

}
