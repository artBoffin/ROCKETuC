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

import rocketuc.jrocket.JRocket;
import rocketuc.jrocket.comm.SerialPacketStream;

public class JRocketBasicExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		SerialPacketStream sps = new SerialPacketStream();
		
		try {
			sps.connect("/dev/ttyUSB0");
			System.out.println("CONNECTED");
			
			JRocket jr = new JRocket(sps);

			sps.start();

			System.out.print("Sending NULL: ");
			jr.packetNull();
			System.out.println("OK");

 			System.out.print("Set P1.0 to OUTPUT: ");
			jr.pinMode((byte)0x10, JRocket.OUTPUT);
			System.out.println("OK");

  			System.out.print("Set P1.0 to HIGH: ");
			jr.digitalWrite((byte)0x10, JRocket.HIGH);
			System.out.println("OK");
 
  			System.out.print("RESET: ");
			jr.reset();
			System.out.println("OK");

			sps.stop();
			
			sps.disconnect();			

			System.out.println("DISCONNECTED");
			
		} catch (Exception e) {
			e.printStackTrace();
		}			
	}

}
