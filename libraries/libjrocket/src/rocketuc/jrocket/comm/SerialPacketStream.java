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

package rocketuc.jrocket.comm;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;

public class SerialPacketStream extends PacketStream {

	private SerialPort serialPort;

	public SerialPacketStream() {
		super();
	}

	public void connect(String portName) throws Exception {
		
		CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
		
		if (portIdentifier.isCurrentlyOwned()) {
			System.err.println("Error: Port is currently in use");
			// TODO: throw exception
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
				System.err.println("Error: Only serial ports are handled by this example.");
				// TODO: throw exception
			}
		}
	}
	
	public void disconnect() {
		if(serialPort != null) {
			serialPort.close();
		}
	}
	
	public static void main(String[] args) {
		
		SerialPacketStream sps = new SerialPacketStream();
		
		try {
			sps.connect("/dev/ttyUSB0");
			System.out.println("CONNECTED");
			sps.start();
			
			Packet p1 = new Packet();
			
			// fill from bytes
	  		byte pNull[] = {0x24, 0x04, 0x00, 0x28};

			try {
				p1.fromByteArray(pNull);
				System.out.println("p1: " + p1);
			}
			catch(PacketException e) {
				System.err.println(e.getMessage());
			}
			
			sps.send(p1);
			
			Packet p2 = sps.receive();
			
			System.out.println("p2: " + p2);
			
			sps.stop();
			
		} catch (Exception e) {
			e.printStackTrace();
		}	
		
		// System.exit(0);
	}
}
