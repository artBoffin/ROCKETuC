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
import rocketuc.jrocket.comm.Packet;

/**
 * This example shows: 
 *
 * how to connect to the MCU through serial line, 
 * configure pins as digital input, 
 * enable external interrupts for this input,
 * and provide an event handler which is called
 * whenever a state change is detecetd on the input pin.
 * 
 * Note: to define our own callback handler, we need
 * to derive from "JRocketSerial", and then override
 * "handleEvent".
 */
public class JRocketExternalInterruptExample extends JRocketSerial{

	/**
 	 * Implement constructor which passes serial port to super-class.
 	 *
 	 * @param port	serial port to connect to
 	 * @throws JRocketException
 	 */
	public JRocketExternalInterruptExample(String port) throws JRocketException {
		super(port);
	}

	/**
 	 * Callback handler for external interrupts.
 	 *
 	 * @param pkt	packet received with this interrupt from the MCU
 	 */
	@Override
	public void handleEvent(Packet pkt) {
		// The packet for the external interrupt has the same structure as a packet for
		// a digital read. the payload at position 0 contains the pin, and position 1
		// the state of the pin (0-low, 1-high).
		System.out.println("-> Button pressed event on pin: " + Integer.toHexString(pkt.getData()[0]));
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		try {		
			// connect through serial line to MCU
			JRocket jr = new JRocketExternalInterruptExample("/dev/ttyACM0");

			// configure pin 1.3 (internal button on Launchpad) as input-float
 			System.out.print("Set P1.3 to INPUT FLOAT: ");
			jr.pinMode(JRocket.PIN_1_3, JRocket.INPUT);
			System.out.println("OK");

			// configure pin 2.3 as input-pulldown
 			System.out.print("Set P2.3 to INPUT PULLDOWN: ");
			jr.pinMode(JRocket.PIN_2_3, JRocket.PULLDOWN);
			System.out.println("OK");
			
			// configure pin 2.3 as input-pullup
			System.out.print("Set P2.4 to INPUT PULLUP: ");
			jr.pinMode(JRocket.PIN_2_4, JRocket.PULLUP);
			System.out.println("OK");
			
			// for pin 1.3 enable external interrupt for high-to-low transitions
 			System.out.print("Enable EXTI on HIGH-LOW transition for P1.3: ");
			jr.externalInterrupt(JRocket.PIN_1_3, JRocket.EDGE_HIGHLOW);
			System.out.println("OK");

			// for pin 2.3 enable external interrupt for low-to-high transitions
 			System.out.print("Enable EXTI on LOW-HIGH transition for P2.3: ");
			jr.externalInterrupt(JRocket.PIN_2_3, JRocket.EDGE_LOWHIGH);
			System.out.println("OK");

			// for pin 2.4 enable external interrupt for high-to-low transitions
 			System.out.print("Enable EXTI on HIGH-LOW transition for P2.4: ");
			jr.externalInterrupt(JRocket.PIN_2_4, JRocket.EDGE_HIGHLOW);
			System.out.println("OK");
	
			// Wait until user presses any key on the keyboard. Meanwhile
			// interrupts from pressing buttons on the MCU are received
			// and handled through the event handler. 	
			System.out.println("PRESS BUTTON on Launchpad to get INTERRUPT");
			System.out.println("PRESS ANY KEY to QUIT PROGRAMM");
			System.in.read();
			
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
