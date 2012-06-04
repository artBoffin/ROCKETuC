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

package rocketuc.jrocket.comm;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

public class SerialPacketStream extends PacketStream {

	private SerialPort serialPort;

	public SerialPacketStream() {
		super();
	}

	public void connect(String portName) throws CommException {
			
		try {

			CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
		
			if (portIdentifier.isCurrentlyOwned()) {
				throw new CommException("Port already in use");
			} else {
				CommPort commPort = portIdentifier.open(this.getClass().getName(), 2000);

				if (commPort instanceof SerialPort) {
					serialPort = (SerialPort) commPort;
					serialPort.setSerialPortParams(
						9600, 
						SerialPort.DATABITS_8,
						SerialPort.STOPBITS_1, 
						SerialPort.PARITY_NONE);

					init(serialPort.getInputStream(), serialPort.getOutputStream());
				} else {
					throw new CommException("Only serial ports are supported");
				}
			}
		} 
		catch(Exception e) {
			throw new CommException(e);
		}
	}
	
	public void disconnect() {
		
		try {
			stop();
		} catch (Exception e) {
			// ignore
		}
		
		if(serialPort != null) {
			serialPort.close();
		}
	}	
}
