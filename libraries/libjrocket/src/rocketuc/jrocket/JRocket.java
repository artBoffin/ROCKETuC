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

import rocketuc.jrocket.JRocketException;
import rocketuc.jrocket.comm.Packet;
import rocketuc.jrocket.comm.PacketException;
import rocketuc.jrocket.comm.PacketStream;

/**
 * Main JRocket class
 * 
 * @example Hello
 * 
 *       
 */
public class JRocket {

	/**
 	 * OUT-bound packet of type NULL
 	 */
	private final static byte PACKET_OUT_NULL 							= (byte)0x00; 

	/**
 	 * OUT-bound packet of type RESERVED 
 	 */
	private final static byte PACKET_OUT_RESERVED 						= (byte)0x01;

	/**
 	 * OUT-bound packet of type SYSTEM INFO 
 	 */
	private final static byte PACKET_OUT_SYSTEM_INFO 					= (byte)0x02;

	/**
 	 * OUT-bound packet of type DEVICE CONTROL 
 	 */
	private final static byte PACKET_OUT_DEVICE_CONTROL 				= (byte)0x03;

	/**
 	 * OUT-bound packet of type PIN FUNCTION 
 	 */
	private final static byte PACKET_OUT_PIN_FUNCTION 					= (byte)0x04;

	/**
 	 * OUT-bound packet of type PIN CONTROL 
 	 */
	private final static byte PACKET_OUT_PIN_CONTROL 					= (byte)0x05;

	/**
 	 * OUT-bound packet of type PWM FUNCTION 
 	 */
	private final static byte PACKET_OUT_PWM_FUNCTION 					= (byte)0x06;

	/**
  	 * OUT-bound packet of type PWM CONTROL 
 	 */
	private final static byte PACKET_OUT_PWM_CONTROL 					= (byte)0x07;

	/**
 	 * OUT-bound packet of type SERIAL FUNCTION 
 	 */
	private final static byte PACKET_OUT_SERIAL_FUNCTION 				= (byte)0x08;

	/**
 	 * OUT-bound packet of type SERIAL DATA 
 	 */
	private final static byte PACKET_OUT_SERIAL_DATA 					= (byte)0x09;

	/**
 	 * OUT-bound packet of type EXTERNAL INTERRUPT FUNCTION 
 	 */
	private final static byte PACKET_OUT_EXTERNAL_INTERRUPT_FUNCTION 	= (byte)0x0A;

	/**
 	 * OUT-bound packet of type RESET 
 	 */
	private final static byte PACKET_OUT_RESET							= (byte)0xFF;

	/**
 	 * IN-bound packet of type NULL 
 	 */
	private final static byte PACKET_IN_NULL 							= (byte)0x00;

	/**
 	 * IN-bound packet of type STATUS
 	 */
	private final static byte PACKET_IN_STATUS 							= (byte)0x01;

	/**
 	 * IN-bound packet of type SYSTEM INFO
 	 */
	private final static byte PACKET_IN_SYSTEM_INFO						= (byte)0x02;

	/**
 	 * IN-bound packet of type DIGITAL PIN READ
 	 */
	private final static byte PACKET_IN_DIGITAL_PIN_READ 				= (byte)0x03;

	/**
  	 * IN-bound packet of type ANALOG PIN READ 
 	 */
	private final static byte PACKET_IN_ANALOG_PIN_READ					= (byte)0x04;

	/**
 	 * IN-bound packet of type PULSE LENGTH READ 
 	 */
	private final static byte PACKET_IN_PULSE_LEGHT_READ 				= (byte)0x05;

	/**
 	 * Return status UNKNOWN for the STATUS OUT-bound packet
 	 */
	private final static byte PACKET_RETURN_UNKNOWN						= (byte)0x00;

	/**
 	 * Return status ACK for the STATUS OUT-bound packet
 	 */
	private final static byte PACKET_RETURN_ACK							= (byte)0x01;

	/**
 	 * Return status BAD PACKET for the STATUS OUT-bound packet
 	 */
	private final static byte PACKET_RETURN_BAD_PACKET					= (byte)0x02;

	/**
 	 * Return status INVALID PACKET for the STATUS OUT-bound packet
 	 */
	private final static byte PACKET_RETURN_INVALID_PACKET				= (byte)0x03;

	/**
 	 * Return status INVLAID DATA for the STATUS OUT-bound packet
 	 */
	private final static byte PACKET_RETURN_INAVLID_DATA				= (byte)0x04;

	/**
 	 * Return status INVALID PIN COMMAND for the STATUS OUT-bound packet
 	 */
	private final static byte PACKET_RETURN_INVALID_PIN_COMMAND			= (byte)0x05;

	/**
 	 * Control command PIN CLEAR for the PIN CONTROL packet
 	 */
	private final static byte PIN_CONTROL_CLEAR							= (byte)0x00;

	/**
 	 * Control command PIN SET for the PIN CONTROL packet
 	 */
	private final static byte PIN_CONTROL_SET							= (byte)0x01;

	/**
 	 * Control command PIN TOGGLE for the PIN CONTROL packet
 	 */
	private final static byte PIN_CONTROL_TOGGLE						= (byte)0x02;

	/**
 	 * Control command DIGITAL READ for the PIN CONTROL packet
 	 */
	private final static byte PIN_CONTROL_DIGITAL_READ					= (byte)0x03;

	/**
 	 * Control command ANALOG READ for the PIN CONTROL packet
 	 */
	private final static byte PIN_CONTROL_ANALOG_READ					= (byte)0x04;

	/**
 	 * Control command PULSELENGTH READ for the PIN CONTROL packet
 	 */
	private final static byte PIN_CONTROL_PULSELENGTH_READ				= (byte)0x05;

	/**
 	 * PIN function input float
 	 */
	private final static byte PIN_FUNCTION_INPUT_FLOAT					= (byte)0x00;

	/**
 	 * PIN function input with internal pull-up enabled
 	 */
	private final static byte PIN_FUNCTION_INPUT_PULLUP					= (byte)0x01;

	/**
 	 * PIN function input with internal pull-down enabled
 	 */
	private final static byte PIN_FUNCTION_INPUT_PULLDOWN				= (byte)0x02;

	/**
 	 * PIN function output 
 	 */
	private final static byte PIN_FUNCTION_OUTPUT						= (byte)0x03;

	/**
 	 * PIN function analog input
 	 */
	private final static byte PIN_FUNCTION_ANALOG_IN					= (byte)0x04;

	/**
 	 * PIN function PWM output
 	 */
	private final static byte PIN_FUNCTION_PWM							= (byte)0x05;

	/**
 	 * PIN function UART RX
 	 */
	private final static byte PIN_FUNCTION_UARTRX						= (byte)0x06;

	/**
 	 * PIN function UART TX
 	 */
	private final static byte PIN_FUNCTION_UARTTX						= (byte)0x07;

	/**
	 * Constant to write a low value to a pin (in a call to
	 * digitalWrite()).
	 */
	public final static byte LOW = PIN_CONTROL_CLEAR;

	/**
	 * Constant to write a high value to a pin (in a call to
	 * digitalWrite()).
	 */
	public final static byte HIGH = PIN_CONTROL_SET;

	/**
	 * Constant to write a high value to a pin (in a call to
	 * digitalWrite()).
	 */
	public final static byte TOGGLE = PIN_CONTROL_TOGGLE;

	/**
	 * Constant to set a pin to output mode (in a call to pinMode()).
	 */
	public final static byte OUTPUT = PIN_FUNCTION_OUTPUT;

	/**
	 * Constant to set a pin to input mode float(in a call to pinMode()).
	 */
	public final static byte INPUT = PIN_FUNCTION_INPUT_FLOAT;

	/**
	 * Constant to set a pin to input mode pull up(in a call to pinMode()).
	 */
	public final static byte PULLUP = PIN_FUNCTION_INPUT_PULLUP;

	/**
	 * Constant to set a pin to input mode pull down(in a call to pinMode()).
	 */
	public final static byte PULLDOWN = PIN_FUNCTION_INPUT_PULLDOWN;

	/**
	 * Constant to set a pin to input mode analog(in a call to pinMode()).
	 */
	public final static byte ANALOG = PIN_FUNCTION_ANALOG_IN;

	/**
	 * Constant to set a pin to output mode PWM(in a call to pinMode()).
	 */
	public final static byte PWM = PIN_FUNCTION_PWM;


	private static PacketStream packetStream;

	/**
	 * TODO
	 */
	public JRocket(PacketStream packetStream) {
		this.packetStream = packetStream;
	}

	private char[] serialSendPacket(char packet[]) {
		return null;
	}

	private Packet xferAndCheckType(byte type, byte[] data, byte checkType) throws JRocketException {
		
		Packet ret = null;

		byte length = (byte)(4 + (data == null ? 0 : data.length));	
		
		try {
			ret = packetStream.xfer(new Packet(Packet.PACKET_START_OUTB, length, type, data));

			if(ret.getType() != checkType) {
				throw new JRocketException("Wrong packet type. Expected " + checkType + 
										   " and received " + ret.getType());
			}
		}
		catch(Exception e) {
			throw new JRocketException(e);
		}

		return ret;
	}

	private void xferAndCheckAck(byte type, byte[] data) throws JRocketException {
		
		Packet ret = xferAndCheckType(type, data, PACKET_IN_STATUS);
		
		if(ret.getData()[0] != PACKET_RETURN_ACK) {
			String msg = "Wrong status. Expected ACK and received ";

 			switch(ret.getData()[0]) {
				case PACKET_RETURN_BAD_PACKET		: msg += "BAD PACKET";	 	break;
				case PACKET_RETURN_INVALID_PACKET	: msg += "INVALID PACKET"; 	break;
				case PACKET_RETURN_INAVLID_DATA		: msg += "INVALID DATA"; 	break;
				default:
					msg += "UNKNOWN";
			}

			throw new JRocketException(msg);
		} 
	}

	/**
	 * Send NULL packet 
	 */
	public void packetNull() throws JRocketException {

		xferAndCheckAck(PACKET_OUT_NULL, null);
	}

	/**
	 * Set a digital pin to input or output mode.
	 * Also sets pull-ups if present
	 *
	 * @param pin the pin whose mode to set 
	 * @param mode either input(with options) or output
	 */
	public void pinMode(byte pin, byte mode) throws JRocketException {

		xferAndCheckAck(PACKET_OUT_PIN_FUNCTION, new byte[] {pin, mode});
	}

	/**
	 * Setup PWM period
	 * Also sets pull-ups if present
	 *
	 * @param pin the pin whose mode to set 
	 * @param PWM period in milliseconds
	 */
	public void pwmPeriod(byte pin, short period) throws JRocketException {	

		byte lsb = (byte)( 0x00FF & period); 
		byte msb = (byte)((0xFF00 & period) >> 4);

		xferAndCheckAck(PACKET_OUT_PWM_FUNCTION, new byte[] {pin, lsb, msb});
	}

	/**
	 * Setup PWM duty cycle
	 * Also sets pull-ups if present
	 *
	 * @param pin the pin whose mode to set 
	 * @param PWM duty cycle 0-255 is 0-100%
	 */
	public void pwmDuty(byte pin, byte duty) throws JRocketException {	

		xferAndCheckAck(PACKET_OUT_PWM_CONTROL, new byte[] {pin, duty});
	}

	/**
	 * Write to a digital pin (the pin must have been put into output mode with
	 * pinMode()).
	 *
	 * @param pin the pin to write to 
	 * @param value the value to write: JRocket.LOW  or JRocket.HIGH 
	 */
	public void digitalWrite(byte pin, byte value) throws JRocketException {

		xferAndCheckAck(PACKET_OUT_PIN_CONTROL, new byte[] {pin, value});
	}

	/**
	 * Read from digital pin (the pin must have been put into input mode with
	 * pinMode()).
	 *
	 * @param pin the pin to read from 
	 * @return value of pin
	 */
	public byte digitalRead(byte pin) throws JRocketException {

		Packet ret = xferAndCheckType(PACKET_OUT_PIN_CONTROL, 
						new byte[] {pin, PIN_CONTROL_DIGITAL_READ}, PACKET_IN_DIGITAL_PIN_READ);

		return ret.getData()[1];
	}

	/**
	 * Read from analog pin (the pin must have been put into input mode with
	 * pinMode()).
	 *
	 * @param pin the pin to read from 
	 * @return value of pin
	 */
	public short analogRead(byte pin) throws JRocketException {

		Packet ret = xferAndCheckType(PACKET_OUT_PIN_CONTROL, 
						new byte[] {pin, PIN_CONTROL_ANALOG_READ}, PACKET_IN_ANALOG_PIN_READ);

		byte lsb = ret.getData()[1];
		byte msb = ret.getData()[2];

		return((short)(msb << 8 + lsb));
	}

	/**
	 * Reset MCU. 
	 */
	public void reset() throws JRocketException {

		xferAndCheckAck(PACKET_OUT_RESET, null);
	}
}
