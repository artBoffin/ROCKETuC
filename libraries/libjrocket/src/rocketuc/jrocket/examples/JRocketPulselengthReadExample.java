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

import rocketuc.jrocket.JRocket;
import rocketuc.jrocket.JRocketException;
import rocketuc.jrocket.JRocketSerial;

/**
 * This example shows: 
 *
 * how to connect to the MCU through serial line, 
 * configure pin 1.3 as input-float (the build in button of the Launchpad),
 *
 * It then measures the first pulselength for the input on pin 1.3. 
 */
public class JRocketPulselengthReadExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {		
			// connect through serial line to MCU
			JRocket jr = new JRocketSerial("/dev/ttyACM0");

			// configure pin 1.3 (build in button) as input-float
 			System.out.print("Set P1.3 to INPUT FLOAT: ");
			jr.pinMode(JRocket.PIN_1_3, JRocket.INPUT);
			System.out.println("OK");
			
			// read pin 1.3 until state changed form high to low
 			System.out.println("Read P1.3 DIGITAL (wait for button press)");

			short pl = 0;

			while(true) {
				try {
					pl = jr.pulselengthRead(JRocket.PIN_1_3); 
					break;
				}
				catch(JRocketException e) {
					// this usually happens because auf a timeout waiting for 
					// state changes on the input
					System.out.println(e.getMessage());
				}
			}

			System.out.println("Pulselenght was: " + pl);
		
			// reset MCU
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
