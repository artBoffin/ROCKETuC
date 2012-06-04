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

import java.util.HashMap;
import java.util.Map.Entry;

import rocketuc.jrocket.JRocket;
import rocketuc.jrocket.JRocketException;
import rocketuc.jrocket.JRocketSerial;

/**
 * This example shows: 
 *
 * how to connect to the MCU through serial line, 
 * configure a pin as output (LED 1 from Launchpad), switch the output
 * on/off, then reset the MCU. 
 */
public class JRocketBasicExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {		
			// connect through serial line to MCU
			JRocket jr = new JRocketSerial("/dev/ttyACM0");

			// send NULL packet
			System.out.print("Sending NULL: ");
			jr.packetNull();
			System.out.println("OK");

			// retrive system info an print it 
			System.out.print("Sending SYSTEMINFO: ");
			HashMap<String, Integer> inf = jr.systemInfo();
			System.out.println("OK");
			
			for(Entry<String, Integer> e : inf.entrySet()) {
				System.out.println(" - " + e.getKey() + " : " + Integer.toHexString(e.getValue()));
			}
			
			// configure pin 1.0 (internal LED on Launchpad) for output
 			System.out.print("Set P1.0 to OUTPUT: ");
			jr.pinMode(JRocket.PIN_1_0, JRocket.OUTPUT);
			System.out.println("OK");
			
			// set pin 1.0 to high (enable LED)
  			System.out.print("Set P1.0 to HIGH: ");
			jr.digitalWrite(JRocket.PIN_1_0, JRocket.HIGH);
			System.out.println("OK");

			// wait 0.5 sec., then set pin 1.0 to low (disable LED by toggeling)
			Thread.sleep(500);			

  			System.out.print("Set P1.0 to TOGGLE: ");
			jr.digitalWrite(JRocket.PIN_1_0, JRocket.TOGGLE);
			System.out.println("OK");

			// wait 0.5 sec., then set pin 1.0 to high (enable LED by toggeling)
			Thread.sleep(500);			

  			System.out.print("Set P1.0 to TOGGLE: ");
			jr.digitalWrite(JRocket.PIN_1_0, JRocket.TOGGLE);
			System.out.println("OK");
			
			// wait again 0.5 sec. then reset MCU (this again will disable the LED)
			Thread.sleep(500);
			
			System.out.print("RESET: ");
			jr.reset();
			System.out.println("OK");

			// call destructor to terminate physical connection correctely
			jr.finalize();
			
			System.out.println("DONE");

		} catch (JRocketException e) {
			// communication on physical or protocol layer failed
			e.printStackTrace();
		} catch (Throwable e) {
			// destructor (finalize) failed 
			e.printStackTrace();
		}			
	}
}
