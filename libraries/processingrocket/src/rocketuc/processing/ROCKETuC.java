/* 
 * This file is part of the JRocket firmware project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The JRocket firmware is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * JRocket firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the JRocket firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

package rocketuc.processing;

import processing.core.*;
import rocketuc.jrocket.JRocket;
import rocketuc.jrocket.JRocketException;
import rocketuc.jrocket.JRocketSerial;
import rocketuc.jrocket.comm.Packet;

/**
 * This calss implements the processing binding to ROCKETuC by
 * extending JRocketSerial from the libjrocket library. Basically
 * the only thing this class does is extending JRocketSerial with
 * the things needed for processing integration.
 */
public class ROCKETuC extends JRocketSerial {
	
	/**
 	 * Reference to the parent sketch
 	 */
	PApplet parent;
	
	/**
 	 * Library version
 	 */
	public final static String VERSION = "0.1";

	/**
	 * A Constructor, usually called in the setup() method in your sketch to
	 * initialize and start the library.
	 * 
	 * @param parent		reference to parent skatch
	 * @param port			serial port to throuch which to connect to MCU
	 * @throws JRocketException
	 */
	public ROCKETuC(PApplet parent, String port) throws JRocketException {
		this.parent = parent;
		init(port);
	}
	
	/**
 	 * Override event handler to pass events along to more
 	 * specific operations.
 	 *
 	 * @param	pkt		packet for event
 	 */
	@Override
	public void handleEvent(Packet pkt) {
		// TODO: if we introduce other events then the
		// external interrupt, we need to dispatch them here
		// to go to different handlers ... 
		externalInterrupt(pkt.getData()[0]);
	}

	/**
 	 * Handler called if external interrupt was received from MCU.
 	 *
 	 * @param pin	the pin for which the interrupt happened
 	 */	
	public void externalInterrupt(short pin) {		
		// Override in processing PDE
	}
	
	/**
	 * Return the version of the library.
	 * 
	 * @return String
	 */
	public static String version() {
		return VERSION;
	}
}

