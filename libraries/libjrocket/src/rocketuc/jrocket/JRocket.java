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

import java.util.HashMap;

import rocketuc.jrocket.comm.Packet;
import rocketuc.jrocket.comm.PacketEventHandler;
import rocketuc.jrocket.comm.PacketStream;

/**
 * Main JRocket class providing access to MCU via ROCKETuC protocol.
 */
public class JRocket implements PacketEventHandler {

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
	@SuppressWarnings("unused")
	private final static byte PACKET_OUT_DEVICE_CONTROL 					= (byte)0x03;

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
	private final static byte PACKET_RETURN_INAVLID_DATA					= (byte)0x04;

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
	private final static byte PIN_CONTROL_TOGGLE							= (byte)0x02;

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
	private final static byte PIN_FUNCTION_ANALOG_IN						= (byte)0x04;

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
	 * PIN function EXTERNAL INTERRUPT DISABLE
	 */
	private final static byte PIN_FUNCTION_EXTI_DISABLE 					= (byte) 0x00;
	
	/**
	 * PIN function EXTERNAL INTERRUPT HIGH-LOW
	 */
	private final static byte PIN_FUNCTION_EXTI_LOWHIGH 					= (byte) 0x01;
	
	/**
	 * PIN function EXTERNAL INTERRUPT HIGH-LOW
	 */
	private final static byte PIN_FUNCTION_EXTI_HIGHLOW 					= (byte) 0x02;

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

	public final static byte EDGE_NONE	= PIN_FUNCTION_EXTI_DISABLE;
	
	public final static byte EDGE_LOWHIGH = PIN_FUNCTION_EXTI_LOWHIGH;
	
	public final static byte EDGE_HIGHLOW = PIN_FUNCTION_EXTI_HIGHLOW;	
	
	/**
	 * PIN P1.0 on MSP430/Launchpad
	 */
	public final static byte PIN_1_0		= 0x10;

	/**
	 * PIN P1.1 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_1		= 0x11;
	
	/**
	 * PIN P1.2 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_2		= 0x12;
	
	/**
	 * PIN P1.3 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_3		= 0x13;
	
	/**
	 * PIN P1.4 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_4		= 0x14;
	
	/**
	 * PIN P1.5 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_5		= 0x15;
	
	/**
	 * PIN P1.6 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_6		= 0x16;
	
	/**
	 * PIN P1.7 on MSP430/Launchpad
	 */	
	public final static byte PIN_1_7		= 0x17;

	/**
	 * PIN P2.0 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_0		= 0x20;
	
	/**
	 * PIN P2.1 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_1		= 0x21;
	
	/**
	 * PIN P2.2 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_2		= 0x22;
	
	/**
	 * PIN P2.3 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_3		= 0x23;
	
	/**
	 * PIN P2.3 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_4		= 0x24;
	
	/**
	 * PIN P2.5 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_5		= 0x25;
	
	/**
	 * PIN P2.6 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_6		= 0x26;
	
	/**
	 * PIN P2.7 on MSP430/Launchpad
	 */	
	public final static byte PIN_2_7		= 0x27;

	/**
	 * Packet stream used for MCU communication vai ROCKETuC protocol
	 */
	protected PacketStream packetStream;

	/**
	 * Default constructor used in derived classes
	 */
	protected JRocket() {
		// noting here
	}
	
	/**
	 * Constructor which takes a packet stream as in input.
	 *  
	 * @param	packetStream	the packet stream to use for communication
	 * @throws JRocketException	 
	 * @throws Exception 
	 */
	public JRocket(PacketStream packetStream) throws JRocketException {
		init(packetStream);
	}
	
	/**
	 * Initialize the packet stream.
	 * 
	 * @param 	packetStream		the packet stream to initialize
	 * @throws 	JRocketException
	 */
	protected void init(PacketStream packetStream) throws JRocketException {
		this.packetStream = packetStream;
		this.packetStream.setEventHandler(this, false);
				
		try {
			this.packetStream.start();
		} catch (Exception e) {
			throw new JRocketException(e.getMessage());
		}
	}

	/**
	 * Send a packet, receive result and check type of result packet against given type. If revieved 
	 * and given type to not match, throw an exception.
	 * 
	 * @param 	type			type for packet to send 
	 * @param 	data			data for packet to send
	 * @param 	checkType		type to which the type of the returned packet is checked
	 * @return					the returned packet
	 * @throws 	JRocketException
	 */
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

	/**
	 * Send a packet, and check if the return packet was a ACK packet. If not, thrown an
	 * exception.
	 * 
	 * @param 	type			type for packet to send 
	 * @param 	data			data for packet to send
	 * @throws 	JRocketException
	 */
	private void xferAndCheckAck(byte type, byte[] data) throws JRocketException {
		
		Packet ret = xferAndCheckType(type, data, PACKET_IN_STATUS);
		
		if(ret.getData()[0] != PACKET_RETURN_ACK) {
			String msg = "Wrong status. Expected ACK and received ";

 			switch(ret.getData()[0]) {
				case PACKET_RETURN_BAD_PACKET			: msg += "BAD PACKET";	 		break;
				case PACKET_RETURN_INVALID_PACKET		: msg += "INVALID PACKET"; 		break;
				case PACKET_RETURN_INAVLID_DATA			: msg += "INVALID DATA"; 		break;
				case PACKET_RETURN_INVALID_PIN_COMMAND	: msg += "INVALID PIN COMMAND"; break;
				default:
					msg += "UNKNOWN";
			}

			throw new JRocketException(msg);
		} 
	}

	/**
	 * Send NULL packet 
 	 * @throws 	JRocketException
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
 	 * @throws 	JRocketException 
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
 	 * @throws 	JRocketException 
	 */
	public void pwmPeriod(byte pin, int period) throws JRocketException {	

		byte lsb = (byte)( 0x000000FF & period); 
		byte msb = (byte)((0x0000FF00 & period) >> 8);

		xferAndCheckAck(PACKET_OUT_PWM_FUNCTION, new byte[] {pin, lsb, msb});
	}

	/**
	 * Setup PWM duty cycle
	 * Also sets pull-ups if present
	 *
	 * @param pin the pin whose mode to set 
	 * @param PWM duty cycle 0-255 is 0-100%
 	 * @throws 	JRocketException 
	 */
	public void pwmDuty(byte pin, int duty) throws JRocketException {	

		xferAndCheckAck(PACKET_OUT_PWM_CONTROL, new byte[] {pin, (byte)duty});
	}

	/**
	 * Write to a digital pin (the pin must have been put into output mode with
	 * pinMode()).
	 *
	 * @param pin the pin to write to 
	 * @param value the value to write: LOW  or HIGH or TOGGLE
 	 * @throws 	JRocketException  
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
 	 * @throws 	JRocketException 
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
 	 * @throws 	JRocketException 
	 */
	public short analogRead(byte pin) throws JRocketException {

		Packet ret = xferAndCheckType(PACKET_OUT_PIN_CONTROL, 
						new byte[] {pin, PIN_CONTROL_ANALOG_READ}, PACKET_IN_ANALOG_PIN_READ);

		short lsb = (short) (0x00FF & ret.getData()[1]);
		short msb = (short) (0x00FF & ret.getData()[2]);
		short val = (short) (lsb | (msb << 8));
		
		return val;
	}

	/**
	 * System info from MCU.
	 *
	 * @return 						System info as a HashMap
 	 * @throws 	JRocketException 
	 */	
	public HashMap<String, Integer> systemInfo() throws JRocketException {
		
		Packet ret = xferAndCheckType(PACKET_OUT_SYSTEM_INFO, null, PACKET_IN_SYSTEM_INFO);

		HashMap<String, Integer> inf = new HashMap<String, Integer>();
		
		inf.put("board_type"	, (int) 0x000000FF & ret.getData()[0]);
		inf.put("mcu_type"		, (int) 0x000000FF & ret.getData()[1]);
		inf.put("firmware_rev"	, (int) 0x000000FF & ret.getData()[2]);
		
		return inf;
	}
	
	/**
	 * Reset MCU. 
 	 * @throws 	JRocketException 
	 */
	public void reset() throws JRocketException {

		xferAndCheckAck(PACKET_OUT_RESET, null);
	}

	/**
	 * TODO
	 * 
	 * @param pin the pin whose mode to set 
	 * @param mode for extrnal interrupt
 	 * @throws 	JRocketException 
	 */
	public void externalInterrupt(byte pin, byte mode) throws JRocketException {	

		xferAndCheckAck(PACKET_OUT_EXTERNAL_INTERRUPT_FUNCTION, new byte[] {pin, mode});
	}
	 
	/**
	 * The event handler called for MCU event packets. Override this method
	 * in a subclass if you like to handle MCU events.
	 * 
	 * @param	pkt		the packet received as an event
	 */
	@Override
	public void handleEvent(Packet pkt) {
		System.out.println("HANDLER received packet: " + pkt);		
	}	
	
	/**
	 * The destructor. Call this if you like to terminate the MCU connection.
	 */
	@Override
	public void finalize() throws Throwable{
		packetStream.stop();
	}	
}
