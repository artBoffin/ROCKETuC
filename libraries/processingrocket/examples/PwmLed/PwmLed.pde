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
 * how to configure a pin for PWM output (p1.6, the internal LED on the Launchpad)
 * how to set the PWM period
 * how to set the PWM duty cycle 
 */

import rocketuc.processing.*;

// our instance of the ROCKETuC API
ROCKETuC r;

// current duty cycle
short dc  = 0;

// direction in which to increase/decrease the duty cycle
short dir = 3;

/**
 * setup function called by processing on startup
 */
void setup() {  
  try {
    // connect to MCU
    r = new ROCKETuC(this, "/dev/ttyACM0");
    
    // configure p1.6 (build in LED) as PWM output
    print("Set P1.6 to PWM: ");
    r.pinMode(ROCKETuC.PIN_1_6, ROCKETuC.PWM);
    println("OK");
    
    // set PWM period to 1000us on pin 1.6 
    print("Set P1.6 period to 1000us: ");
    r.pwmPeriod(ROCKETuC.PIN_1_6, 1000);
    println("OK");    
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    print(e.getMessage());
	exit();
  }
}

/**
 * draw is called cyclic from processing
 */
void draw() {
  try {
    
    // modifiy duty cycle
    dc += dir;
    
    // if max. duty cycle (0xFF) reached, reverse direction
    if(dc >= 0xFF) {
       dir *= -1;
       // make sure DC is still valid
       dc = 0xFF;
    }
    // if min. duty cycle (0x00) reached, reverse direction
    else if(dc <= 0x00) {
       dir *= -1;
       // make sure DC is still valid
       dc = 0x00;
    }
   
    // write modified DC   
    print("Set P1.6 duty cycle to " + dc + ": ");
    r.pwmDuty(ROCKETuC.PIN_1_6, dc);
    println("OK");    
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    print(e.getMessage());
  }
}
