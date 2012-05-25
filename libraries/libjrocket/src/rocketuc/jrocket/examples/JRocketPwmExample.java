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
import rocketuc.jrocket.JRocketException;
import rocketuc.jrocket.JRocketSerial;

/**
 * This example shows: 
 *
 * how to connect to the MCU through serial line, 
 * configure a pin for PWM output, set period and duty cycle
 * to controll a servo.
 */
public class JRocketPwmExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {		
			// connect through serial line to MCU
			JRocket jr = new JRocketSerial("/dev/ttyACM0");

			// configure pin 2.2 for hardware PWM
 			System.out.print("Set P2.2 to PWM: ");
			jr.pinMode(JRocket.PIN_2_2, JRocket.PWM);
			System.out.println("OK");
		
			// set PWM period to 2000us on pin 2.2 
 			System.out.print("Set P2.2 period to 2000us: ");
			jr.pwmPeriod(JRocket.PIN_2_2, 20000);
			System.out.println("OK");

			// set a duty cycle of 7.5% for PWM on pin 2.2. 
			// duty cycle could be specified in a range from 0 to 0xFF 
			// thus, 100% = 0xFF, 7.5% ~ 0x13
			// this moves the servo to its middle position
 			System.out.print("Set P2.2 duty cycle to 7.5%: ");
			jr.pwmDuty(JRocket.PIN_2_2, 0x13);
			System.out.println("OK");
			
			// wait a while, then reset the MCU
			Thread.sleep(2500);
			
			// reset MCU, this also disables the PWM
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
