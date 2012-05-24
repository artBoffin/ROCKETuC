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
 
package rocketuc.jrocket;

import rocketuc.jrocket.comm.CommException;
import rocketuc.jrocket.comm.SerialPacketStream;

/**
 * JRocket class using serial connection to MCU.
 */
public class JRocketSerial extends JRocket {

	/**
	 * New JRocket instance connection to MCU through a serial port.
	 *
	 * @param port	serial port to use for connection
	 * @throws JRocketException
	 */
	public JRocketSerial(String port) throws JRocketException {
		super();
		
		init(port);
	}

	/**
 	 * New, unconnected JRocket instance (use init to connect).
 	 */
	protected JRocketSerial() {
		super();
	}

    /**
	 * Connect JRocket instance to MCU through a serial port.
	 *
	 * @param port	serial port to use for connection
	 * @throws JRocketException
	 */
	protected void init(String port) throws JRocketException {
		
		try {
			SerialPacketStream packetStream = new SerialPacketStream();
			packetStream.connect(port);
		
			super.init(packetStream);		
		}
		catch(CommException e) {
			throw new JRocketException(e); 
		}
	}
	
	/**
 	 * Destructor 
 	 */
	@Override
	public void finalize() throws Throwable {
		super.finalize();
		((SerialPacketStream)packetStream).disconnect();
	}
}
