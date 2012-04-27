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
import rocketuc.jrocket.comm.PacketEventHandler;
import rocketuc.jrocket.comm.SerialPacketStream;

public class PacketEventHandlerExample implements PacketEventHandler {

	@Override
	public void handleEvent(Packet pkt) {
		System.out.println("HANDLER received packet: " + pkt);
	}

	public static void main(String[] args) {
		
		PacketEventHandlerExample h = new PacketEventHandlerExample();
		
		SerialPacketStream sps = new SerialPacketStream();
		
		try {
			sps.connect("/dev/ttyUSB0");
			System.out.println("CONNECTED");

			sps.setEventHandler(h, true);			
			sps.start();
			
			// PIN FUNCTION digital p1.0 Packet
			sps.send(new Packet((byte)0x24, (byte)0x06, (byte)0x04, new byte[] { (byte)0x10, (byte)0x03 }));

			for(int i = 0; i < 10; i++) {
				// PIN CONTROL digital p1.0 
				sps.send(new Packet((byte)0x24, (byte)0x06, (byte)0x05, new byte[] { (byte)0x10, (byte)0x01 }));
				Thread.sleep(250);
				
				// PIN CONTROL digital p1.0 
				sps.send(new Packet((byte)0x24, (byte)0x06, (byte)0x05, new byte[] { (byte)0x10, (byte)0x00 }));			
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
