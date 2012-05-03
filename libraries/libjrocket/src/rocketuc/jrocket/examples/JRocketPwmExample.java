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
import rocketuc.jrocket.JRocketSerial;

public class JRocketPwmExample {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {		
			JRocket jr = new JRocketSerial("/dev/ttyUSB0");

 			System.out.print("Set P2.2 to PWM: ");
			jr.pinMode(JRocket.PIN_2_2, JRocket.PWM);
			System.out.println("OK");

 			System.out.print("Set P2.2 period to 2000us: ");
			jr.pwmPeriod(JRocket.PIN_2_2, 20000);
			System.out.println("OK");

 			System.out.print("Set P2.2 duty cycle to 7.5%: ");
			jr.pwmDuty(JRocket.PIN_2_2, 0x13);
			System.out.println("OK");
			
			Thread.sleep(2500);
			
			System.out.print("RESET: ");
			jr.reset();
			System.out.println("OK");

			jr.finalize();
			
			System.out.println("DONE");
			
		} catch (Exception e) {
			e.printStackTrace();
		} catch (Throwable e) {
			e.printStackTrace();
		}			
	}
}
