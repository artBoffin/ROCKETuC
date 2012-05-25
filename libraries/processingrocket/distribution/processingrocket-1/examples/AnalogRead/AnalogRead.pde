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
 * how to configure a pin for analog input (p1.5)
 * how to read the value for the analog input and convert it to volts 
 */

import rocketuc.processing.*;

// our instance of the ROCKETuC API
ROCKETuC r;

// we keep track of the last value, thus we could only update the
// display when the previous and the current value differat min. 0.1V
float pV = -1;

// where to disply the output on the screen
int tx = 30;
int ty = 70;

/**
 * setup function called by processing on startup
 */
void setup() {  
  
  // screen size
  size(480, 120);

  // get font 3 with font size 24
  PFont myFont = createFont(PFont.list()[3], 24);

  // use this font for writing text 
  textFont(myFont);
  
  // set background to black
  background(0);
             
  try {
	// connect to MCU on serial port ttyUSB0
    r = new ROCKETuC(this, "/dev/ttyUSB0");
    
	// configure p1.5 for analog input
    print("Set P1.5 to ANALOG: ");
    r.pinMode(ROCKETuC.PIN_1_5, ROCKETuC.ANALOG);
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
	// perform analog read on p1.5
    short a = r.analogRead(ROCKETuC.PIN_1_5);

    // convert value from analog read to volts: 
    // - assuming Vmax is 3.3V
    // - assuming max value from analog read is 1024
    float v = (float) ((3.3 / 1024.0) * (float)a);
    
	// only if delta between the current value (v) and the previous value (pV)
 	// is bigger than 0.1, update the display 
    if(pV - v > 0.1 || v - pV > 0.1) {
      background(0);
      text("AnalogRead P1.0: ~volts " + v, tx, ty);
      pV = v;
    }
  }
  catch(Exception e) {
 	// If something goes wrong while communication with the MCU
	// the catch block will be precessed. Here the error handling
	// should be done. 
   print(e.getMessage());
  }
}
