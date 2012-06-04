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

package rocketuc.jrocket.examples;

import rocketuc.jrocket.comm.Packet;
import rocketuc.jrocket.comm.PacketEventHandler;
import rocketuc.jrocket.comm.SerialPacketStream;

/**
 * This example shows: 
 *
 * How to use the generic packet and packet-stream implementations
 * to send a request to the MCU and receive responses through an
 * event handler. 
 *
 * Note: to register as packet event handler, a class must be derived 
 * from "PacketEventHandler".
 */
public class PacketEventHandlerExample implements PacketEventHandler {

	/**
 	 * Callback handler for external interrupts.
 	 *
 	 * @param pkt	packet received with this interrupt from the MCU
 	 */
	public void handleEvent(Packet pkt) {
		System.out.println("HANDLER received packet: " + pkt);
	}

	public static void main(String[] args) {
		
		// instance of the event handler
		PacketEventHandlerExample h = new PacketEventHandlerExample();
		
		// packet stream over serial line
		SerialPacketStream sps = new SerialPacketStream();
		
		try {
			// connect serial line
			sps.connect("/dev/ttyACM0");

			// register event handler
			sps.setEventHandler(h, true);			

			// start send-/receive-threads
			sps.start();
			
			// send PIN FUNCTION digital out p1.0 (LED on Launchpad) 
			sps.send(new Packet(
				(byte)0x24, (byte)0x06, (byte)0x04, 
				new byte[] { (byte)0x10, (byte)0x03 }));

			// blinks p1.0 10 times
			for(int i = 0; i < 10; i++) {
				// PIN CONTROL digital p1.0 LOW 
				sps.send(new Packet(
					(byte)0x24, (byte)0x06, (byte)0x05, 
					new byte[] { (byte)0x10, (byte)0x01 }));

				Thread.sleep(250);
				
				// PIN CONTROL digital p1.0 HIGH 
				sps.send(new Packet(
					(byte)0x24, (byte)0x06, (byte)0x05, 
					new byte[] { (byte)0x10, (byte)0x00 }));			

				Thread.sleep(250);
			}
			
			// stop send-/receive-threads
			sps.stop();

			// disconnect serial line
			sps.disconnect();
	
			System.out.println("DISCONNECTED");
			
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
