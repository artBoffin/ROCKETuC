/**
 * ROCKETuC
 * Library for fast prototyping of micro-controllers through serial protocols
 * http://www.rocketuc.com
 *
 * Copyright (C) 2012 Alexander Reben 
 *
 * Contains some code / ideas from:
 * Processing/Arduino library, Copyright 2006-08 David A. Mellis 
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Alexander Reben
 * @modified    4/14/2012
 * @version     v0.1.1 (1)
 */

package rocketuc;

import processing.core.*;
import processing.serial.*;

/**
 * Main ROCKETuC class
 * 
 * @example Hello
 * 
 *       
 */

public class ROCKETuC {

	// mymyParent is a reference to the myParent sketch
	PApplet myParent;
	Serial serial;
	SerialProxy serialProxy;


	public final static String VERSION = "v0.1.1";

	 /**
	   * Constant to write a low value to a pin (in a call to
	   * digitalWrite()).
	   */
	  public static final char LOW = 0x00;
	  /**
	   * Constant to write a high value to a pin (in a call to
	   * digitalWrite()).
	   */
	  public static final char HIGH = 0x01;
	  /**
	   * Constant to set a pin to output mode (in a call to pinMode()).
	   */
	  public static final char OUTPUT = 0x03;


	
	private final char PACKET_OUT_START = 						0x24; //PACKET_OUT-bound start of packet char "$"
	private final char PACKET_OUT_NULL = 						0x00; //PACKET_OUT-bound packet type "NULL"
	//private final char PACKET_OUT_RESERVED = 					0x01; //PACKET_OUT-bound packet type 
	private final char PACKET_OUT_SYSTEM_INFO =					0x02; //PACKET_OUT-bound packet type "system info"
	private final char PACKET_OUT_DEVICE_CONTROL = 				0x03; //PACKET_OUT-bound packet type "device control"
	private final char PACKET_OUT_PIN_FUNCTION = 				0x04; //PACKET_OUT-bound packet type "pin function"
	private final char PACKET_OUT_PIN_FUNCTION_LENGTH = 		0x06; //PACKET_OUT-bound "pin function" length, 6 chars
	private final char PACKET_OUT_PIN_CONTROL = 				0x05; //PACKET_OUT-bound packet type "pin control"
	private final char PACKET_OUT_PWM_FUNCTION = 				0x06; //PACKET_OUT-bound packet type "pwm function"
	private final char PACKET_OUT_PWM_CONTROL = 				0x07; //PACKET_OUT-bound packet type "pwm control"
	private final char PACKET_OUT_SERIAL_FUNCTION =				0x08; //PACKET_OUT-bound packet type "serial function"
	private final char PACKET_OUT_SERIAL_DATA = 				0x09; //PACKET_OUT-bound packet type "serial data"
	private final char PACKET_OUT_EXTERNAL_INTERRUPT_FUNCTION = 0x0A; //PACKET_OUT-bound packet type "external interrupt function"


	/**
	 *
	 * We need a class descended from PApplet so that we can override the
	 * serialEvent() method to capture serial data.  We can't use the ROCKETuC
	 * class itself, because PApplet defines a list() method that couldn't be
	 * overridden by the static list() method we use to return the available
	 * serial ports.  This class needs to be public so that the Serial class
	 * can access its serialEvent() method.
	 */
	public class SerialProxy extends PApplet {
		public SerialProxy() {
			/**
			 * Create the container for the registered dispose() methods, so that
			 * our Serial instance can register its dispose() method (which it does
			 * automatically).
			 * 
			 */
			
			  disposeMethods = new RegisteredMethods();
			 
		}

		public void serialEvent(Serial which) {
			// Notify the ROCKETuC class that there's serial data for it to process.
			while (available() > 0)
				processInput();
		}
	}

	public void dispose() {
		this.serial.dispose();
	}

	/**
	 * Get a list of the available uC's; currently all serial devices
	 * (i.e. the same as Serial.list()).  In theory, this should figure out
	 * what's an uC and what's not.
	 */
	public static String[] list() {
		return Serial.list();
	}

	/**
	 * Create a proxy to a uC running the ROCKETuC firmware at the
	 * default baud rate of 9600.
	 *
	 * @param myParent the Processing sketch creating this ROCKETuC board
	 * (i.e. "this").
	 * @param iname the name of the serial device associated with the ROCKETuC
	 * board (e.g. one the elements of the array returned by ROCKETuC.list())
	 */
	public ROCKETuC(PApplet myParent, String iname) {
		this(myParent, iname, 9600);
	}

	/**
	 * Create a proxy to uC board running the ROCKETuC firmware.
	 *
	 * @param myParent the Processing sketch creating this ROCKETuC board
	 * (i.e. "this").
	 * @param iname the name of the serial device associated with the uC
	 * (e.g. one the elements of the array returned by ROCKETuC.list())
	 * @param irate the baud rate to use to communicate with the ROCKETuC board
	 * (the ROCKETuC library defaults to 9600, and the examples use this rate,
	 * but other firmwares may override it)
	 */
	public ROCKETuC (PApplet myParent, String iname, int irate) {
		this.myParent = myParent;
		this.serialProxy = new SerialProxy();
		this.serial = new Serial(serialProxy, iname, irate);

		try {
			System.out.println("Loading...");
			Thread.sleep(3000); //time for serial init?
		} catch (InterruptedException e) {}

		//do stuff on first connect
		System.out.println("Connected");
		myParent.registerDispose(this);
	}


	/**
	 * Set a digital pin to input or output mode.
	 * Also sets pull-ups if present
	 *
	 * @param pin the pin whose mode to set 
	 * @param mode either input(with options) or output
	 */
	public void pinMode(char pin, char mode) {
		char crcCheck[] = {PACKET_OUT_START, PACKET_OUT_PIN_FUNCTION_LENGTH, PACKET_OUT_PIN_FUNCTION, pin, mode};
		char crc = packetCrcCalc(crcCheck);
		char packet[] = {PACKET_OUT_START, PACKET_OUT_PIN_FUNCTION_LENGTH, PACKET_OUT_PIN_FUNCTION, pin, mode, crc};
		serialSendPacket(packet);
	}

	/**
	 * Write to a digital pin (the pin must have been put into output mode with
	 * pinMode()).
	 *
	 * @param pin the pin to write to 
	 * @param value the value to write: ROCKETuC.LOW  or ROCKETuC.HIGH
	 * 
	 */
	public void digitalWrite(char pin, char value) {
		char crcCheck[] = {PACKET_OUT_START, PACKET_OUT_PIN_FUNCTION_LENGTH, PACKET_OUT_PIN_CONTROL, pin, value};
		char crc = packetCrcCalc(crcCheck);
		char packet[] = {PACKET_OUT_START, PACKET_OUT_PIN_FUNCTION_LENGTH, PACKET_OUT_PIN_CONTROL, pin, value, crc};
		serialSendPacket(packet);
	}


	private int available() {
		return serial.available();
	}

	private void processInput() {
		int inputData = serial.read();
		//char command;
        System.out.println(inputData); 
	}
	
	private void serialSendPacket(char[] packetIn)
	{
        String out = new String(packetIn); //convert char array to string
        //System.out.print(out);
		serial.write(out);
	}
	
	private char packetCrcCalc(char[] packetIn) {

		char crc = 0;

		for(int i = 0; i < packetIn.length; i++) {
			crc += packetIn[i];
		} 

		return crc;
	}
}

