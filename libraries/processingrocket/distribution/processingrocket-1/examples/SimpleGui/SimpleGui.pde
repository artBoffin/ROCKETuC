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
 * This example provides a simple GUI to test the ROCKETuC firmware
 * running on a Launchpad. It provides for each pin (except the reserved
 * pins P1.1 (RX) and P1.2 (TX) a panel which allows you to configure the
 * pin mode, and which shows the status/value of each pin or allows you
 * to modify it (for ouputs). 
 * 
 * 
 * Pin Modes
 * ---------
 * 
 * The modes one could configure for a pin, are represented by six 
 * buttons right beside the pin label: 
 *
 * "DO" : Digital-Output 
 * "IF" : Input-Float (external Pull-Up/Down resistor)
 * "IU" : Input-Pull-Up (internal Pull-Up resistor enabled)
 * "ID" : Input-Pull-Down (internal Pull-Down resistor enabled)
 * "AR" : Analog-Read (with VCC=3.3V als a reference) 
 * "PW" : PWM output (with initial period of 1000usec and 100% duty cycle)
 * 
 * After startup, all pins are configured as "IF" (Input-Float) by default. 
 * The current mode which is configured for a pin is shown by the button 
 * which has a gray background color. You could change a pins mode at any
 * time by clicking on the corresponding button. 
 *  
 * 
 * Pin States
 * ----------
 * 
 * Right beside the pin modes, the current pin state is show. How the pin 
 * state is represented depends on the selected mode: 
 * 
 * For "DO" (Digital-Output): the pin state (HIGH/LOW) is shown at the left of
 * the status area. Also a a hint to click this area to change the state is
 * shown. At the right, a circle is shown. A green circle indicates HIGH state
 * for that output, a gray circle LOW state. The state of the output could 
 * be changed by clicking anywhere in the state area. 
 * 
 * For "IF", "IU", "ID" (Digital-Inputs): the pin state (HIGH/LOW) is shown at 
 * the left of the status area. At the right, a circle is shown. A green circle 
 * indicates HIGH state for that output, a gray circle LOW state.  
 * The state for all inputs is polled continuously from the MCU. As soon as the 
 * state changes, it is reflected in the state are of a pin. 
 * 
 * For AR (Analog Read): the value of the last ADC is shown in Volts and as raw
 * value. ADC is done continuously, and the values are updated accordingly. 
 *
 * For PW (Pulse Width): the current period P (in usec) and the current duty
 * cycle DC (in percent) are shown in the status area. The initial value for
 * P is 1000, and for DC 100. The red and two green
 * boxes beside P and DC allow you to adjust P or DC. The red boxes decrease
 * the value, the green ones increase it. The smaller boxes in-/decrease in small
 * steps, the biger ones in bigger steps.  
 * 
 * 
 * Errors
 * ------
 *
 * If an error occures for a pin, "ERROR" will be shown in the pins status
 * area. Normaly an error will be shown only when you try to assign a mode
 * to a pin which it does not support. E.g. only the P1.x pins allow "AR", 
 * and only "P1.5" or "P1.6" and "P2.1" or "P2.2" allow "PW". 
 * 
 * 
 * Some notes on the GUI responsivenes: 
 * ------------------------------------
 * 
 * The GUI behaves a little sluggish. This is due to the fact, that within the
 * redraw cycle, the polling of all input values is done (including ADC). Since
 * this takes some time (in which the GUI is not redrawn), the GUI seams to 
 * respond slow. Thus, for a production grade GUI, the polling must be done in a 
 * background thread. 
 */

import rocketuc.processing.*;

// all our pin panels are stored here
PinPanel pins[]; 

// our instance of the ROCKETuC API
ROCKETuC r;

/**
 * Setup connection to MCU and pin panels.
 */
void setup() {
  
  try {
    // connect to MCU, change port to reflect your setup
    r = new ROCKETuC(this, "/dev/ttyACM0");
	
	// reset MCU to its default state
    r.reset();
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    println(e.getMessage());
    exit();
  }
  
  // size of drawing area
  size(830, 490);
  
  pins = new PinPanel[14];
  
  // construct and place all the pin panels
  pins[0]  = new PinPanel(r, ROCKETuC.PIN_1_0, "P1.0",  10,  10);
  pins[1]  = new PinPanel(r, ROCKETuC.PIN_1_3, "P1.3",  10, 190);
  pins[2]  = new PinPanel(r, ROCKETuC.PIN_1_4, "P1.4",  10, 250);
  pins[3]  = new PinPanel(r, ROCKETuC.PIN_1_5, "P1.5",  10, 310);
  pins[4]  = new PinPanel(r, ROCKETuC.PIN_1_6, "P1.6",  10, 370);
  pins[5]  = new PinPanel(r, ROCKETuC.PIN_1_7, "P1.7",  10, 430);
  pins[6]  = new PinPanel(r, ROCKETuC.PIN_2_0, "P2.0", 420,  10);
  pins[7]  = new PinPanel(r, ROCKETuC.PIN_2_1, "P2.1", 420,  70);
  pins[8]  = new PinPanel(r, ROCKETuC.PIN_2_2, "P2.2", 420, 130);
  pins[9]  = new PinPanel(r, ROCKETuC.PIN_2_3, "P2.3", 420, 190);
  pins[10] = new PinPanel(r, ROCKETuC.PIN_2_4, "P2.4", 420, 250);
  pins[11] = new PinPanel(r, ROCKETuC.PIN_2_5, "P2.5", 420, 310);
  pins[12] = new PinPanel(r, ROCKETuC.PIN_2_6, "P2.6", 420, 370);
  pins[13] = new PinPanel(r, ROCKETuC.PIN_2_7, "P2.7", 420, 430);  
}

/**
 * Redraw all the pin panels. 
 */
void draw() {
  for(int i = 0; i < pins.length; i++) {
    pins[i].draw();
  }  
}

/**
 * Foreward a mouse presses to pin panels.
 */
void mousePressed() {
  for(int i = 0; i < pins.length; i++) {
    pins[i].checkPressed();
  }  
}
