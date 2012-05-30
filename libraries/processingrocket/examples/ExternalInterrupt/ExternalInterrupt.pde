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

/**
 * This example shows:
 * 
 * how to connect to a MCU through a serial line
 * how to configure a pin for floating digital input (p1.3, the build in button) 
 * how to enable external interrupting for state changes on p1.3
 * how to derive out own class form ROCKETuC to implement the callback handler
 * 
 * To show, that event handling/processing is done completely in the background
 * the build in LED (p1.0) is blinking constantly.
 */

import rocketuc.processing.*;

// our very own API instance derived from ROCKETuC
MyROCKETuC r;

/**
 * setup function called by processing on startup
 */
void setup() {
  try {
    // connect to MCU
    r = new MyROCKETuC(this, "/dev/ttyACM0");
    
    // setup P1.0 as digital output (the build in LED on the Launchpad)
    print("Set P1.0 to OUTPUT: ");
    r.pinMode(ROCKETuC.PIN_1_0, ROCKETuC.OUTPUT);
    println("OK");
    
    // set P1.3 as digital input-float
    print("Set P1.3 to INPUT FLOAT: ");
    r.pinMode(ROCKETuC.PIN_1_3, ROCKETuC.INPUT);
    println("OK");    
    
    // enable external interrupt for p1.3 on high-low transition
    print("Enable EXTI on HIGH-LOW transition for P1.3: ");
    r.externalInterrupt(ROCKETuC.PIN_1_3, ROCKETuC.EDGE_HIGHLOW);
    println("OK");    
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    println(e.getMessage());
	exit();
  }
}

/**
 * draw is called cyclic from processing
 */
void draw() {
  
  try {
    // blink p1.0 by toggeling
    print("Toggle P1.0: ");
    r.digitalWrite(ROCKETuC.PIN_1_0, ROCKETuC.TOGGLE);
    println("OK");
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    println(e.getMessage());
	exit();
  }
  
  // wait a little
  delay(500);
}

/**
 * We derive a class from ROCKETuC to override the
 * event handler for the external interrupt.
 */
class MyROCKETuC extends ROCKETuC {
    
  /**
   * Constructor just passes values to parent class
   */
  MyROCKETuC(PApplet applet, String port) throws Exception {
    super(applet, port);
  }
  
  /**
   * Interrupt handler, called every time p1.3 goes from high to low
   */
  void externalInterrupt(short pin) {
    // The pin returned is in HEX notation. E.g. pin 1.3 is 0x13 in HEX,
    // and 19 in dec.  
    println("External interrupt on PIN: " + pin);
  }  
}
