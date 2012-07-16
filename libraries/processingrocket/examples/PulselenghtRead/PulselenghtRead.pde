/* 
 * This file is part of the ROCKETuC Processing Library project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC Processing Library is free software; you can redistribute 
 * it and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC Processing Library is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
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
 * how to connect to the MCU through serial line, 
 * configure pin 1.3 as input-float (the build in button of the Launchpad),
 *
 * It then measures the first pulselength for the input on pin 1.3. 
 */

import rocketuc.processing.*;

// our instance of the ROCKETuC API
ROCKETuC r;

/**
 * setup function called by processing on startup
 */
void setup() {  
  try {
    // connect to MCU
    r = new ROCKETuC(this, "/dev/ttyACM0");
    
    // configure p1.3 (build in button) as digital input
    print("Set P1.3 to INPUT (float): ");
    r.pinMode(ROCKETuC.PIN_1_0, ROCKETuC.INPUT);
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
    // read pin 1.3 until state changed form high to low
    println("Read P1.3 DIGITAL (wait for button press)");
    short pl = r.pulselengthRead(ROCKETuC.PIN_1_3); 

    // a pulse lenght of 0x7FFF indicates a timeout while waiting 
    // for high-low or low-high transition
    if(pl != 0x7FFF) {
      println("Pulselenght was: " + pl);
    }
    else {
      println("Timed out while waiting for state change");
    }
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    println(e.getMessage());
  }
  
  // wait a little 
  delay(500);
}