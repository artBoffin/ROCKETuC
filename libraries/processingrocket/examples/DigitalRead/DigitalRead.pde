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
 * how to connect to a MCU through a serial line
 * how to configure pins for digital input (p1.3, the internal button on the Launchpad)
 * how to read the state of an digital input 
 */

// import ROCKETuC API
import rocketuc.processing.*;

// our instance of the ROCKETuC API referenced through variable r
ROCKETuC r;

/**
 * setup function called by processing on startup
 */
void setup() {  
  try {
    // connect to MCU, replace "/dev/ttyACM0" with you virtual COM port
    r = new ROCKETuC(this, "/dev/ttyACM0");
    
    // set P1.3 as digital input
    r.pinMode(ROCKETuC.PIN_1_3, ROCKETuC.INPUT);
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
    if(r.digitalRead(ROCKETuC.PIN_1_3) == ROCKETuC.LOW) {
      println("Button pressed!");
    }
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    println(e.getMessage());
    exit();
  }
  delay(100);
}

