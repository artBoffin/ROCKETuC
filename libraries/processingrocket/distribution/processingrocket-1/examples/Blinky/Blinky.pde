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
 * how to configure a pin for digital output (p1.0, the internal LED on the Launchpad)
 * how to toggle the state for the output (blink the LED) 
 */

import rocketuc.processing.*;

// our instance of the ROCKETuC API
ROCKETuC r;

/**
 * setup function called by processing on startup
 */
void setup() {  
  try {
	// connect to MCU on serial port ttyUSB0
    r = new ROCKETuC(this, "/dev/ttyUSB0");
    
	// configure p1.0 (build in LED) as digital output
    print("Set P1.0 to OUTPUT: ");
    r.pinMode(ROCKETuC.PIN_1_0, ROCKETuC.OUTPUT);
    println("OK");
  }
  catch(Exception e) {
	// If something goes wrong while communication with the MCU
	// the catch block will be precessed. Here the error handling
	// should be done. 
    print(e.getMessage());
  }
}

/**
 * draw is called repeadedly from processing
 */
void draw() {
  try {
    // toggle p1.0 between high/low state (LED on/off)
    print("Toggle P1.0: ");
    r.digitalWrite(ROCKETuC.PIN_1_0, ROCKETuC.TOGGLE);
    println("OK");
  }
  catch(Exception e) {
	// If something goes wrong while communication with the MCU
	// the catch block will be precessed. Here the error handling
	// should be done. 
    print(e.getMessage());
  }
  
  // wait a little 
  delay(500);
}
