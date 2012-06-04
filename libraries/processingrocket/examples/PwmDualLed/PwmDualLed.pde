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
 * how to configure two pins for PWM output (p1.6+p2.1, the internal LED on the Launchpad + one extra LED)
 * how to set the PWM period
 * how to set the PWM duty cycle 
 */

import rocketuc.processing.*;

// our instance of the ROCKETuC API
ROCKETuC r;

// current duty cycle of P1.6 and P2.1
short dc1  = 0;
short dc2  = 0xFF;

// direction in which to increase/decrease the duty cycle on P1.6 and P2.1
short dir1 =  5;
short dir2 = -5;

/**
 * setup function called by processing on startup
 */
void setup() {  
  try {
    // connect to MCU
    r = new ROCKETuC(this, "/dev/ttyACM0");
    
    // configure p1.6+p2.1 (build in LED + extra LED) as PWM output
    print("Set P1.6+P2.1 to PWM: ");
    r.pinMode(ROCKETuC.PIN_1_6, ROCKETuC.PWM);
    r.pinMode(ROCKETuC.PIN_2_1, ROCKETuC.PWM);    
    println("OK");
    
    // set PWM period to 1000us on p1.6+1p2.1 
    print("Set P1.6+P2.1 period to 1000us: ");
    r.pwmPeriod(ROCKETuC.PIN_1_6, 1000);
    r.pwmPeriod(ROCKETuC.PIN_2_1, 1000);    
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
    
    // modifiy duty cycle
    dc1 += dir1;
    
    // if max. duty cycle (0xFF) reached, reverse direction
    if(dc1 >= 0xFF) {
       dir1 *= -1;
       // make sure DC is still valid
       dc1 = 0xFF;
    }
    // if min. duty cycle (0x00) reached, reverse direction
    else if(dc1 <= 0x00) {
       dir1 *= -1;
       // make sure DC is still valid
       dc1 = 0x00;
    }

    // modifiy duty cycle
    dc2 += dir2;
    
    // if max. duty cycle (0xFF) reached, reverse direction
    if(dc2 >= 0xFF) {
       dir2 *= -1;
       // make sure DC is still valid
       dc2 = 0xFF;
    }
    // if min. duty cycle (0x00) reached, reverse direction
    else if(dc2 <= 0x00) {
       dir2 *= -1;
       // make sure DC is still valid
       dc2 = 0x00;
    }

    // write modified DC   
    print("Set P1.6+P2.1 duty cycle to " + dc1 + "/" + dc2 + ": ");
    r.pwmDuty(ROCKETuC.PIN_1_6, dc1);
    r.pwmDuty(ROCKETuC.PIN_2_1, dc2);
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
