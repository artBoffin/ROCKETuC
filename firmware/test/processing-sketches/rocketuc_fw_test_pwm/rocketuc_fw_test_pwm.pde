/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC firmware is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the ROCKETuC firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

import processing.serial.*;

Serial port;      // The serial port

int tCount = 0;
int tFail  = 0;

// ACK 
int ack[]  = {0x2B, 0x05, 0x01, 0x01, 0x32};

// PIN setup
int pinf[] = {0x24, 0x06, 0x04, 0x22, 0x05, 0x55};

// PWM setup
int pwmf[] = {0x24, 0x07, 0x06, 0x22, 0x20, 0x4e, 0xc1};

// PWM control: servo center position
int pwmc_cen[] = {0x24, 0x06, 0x07, 0x22, 0x13, 0x66};

// PWM control: servo minimum position
int pwmc_min[] = {0x24, 0x06, 0x07, 0x22, 0x0e, 0x61};

// PWM control: servo maximum position
int pwmc_max[] = {0x24, 0x06, 0x07, 0x22, 0x18, 0x6b};

int[] rocketXfer(int data[]) {
  
  int pl[] = {};
  
  for(int i = 0; i < data.length; i++) {
    port.write(data[i]);
  }

  int s;
  int l;
  int c;
  
  while((s = port.read()) == -1); 
  
  if(s == 0x2B) {
    while((l = port.read()) == -1);
    
    pl = new int[l];
    
    pl[0] = (int)s;
    pl[1] = (int)l;
    
    for(int i = 0; i < l - 3; i++) {
      while((pl[i+2] = (int)port.read()) == -1);
    }   
    
    while((c = port.read()) == -1);
    pl[l-1] = (int)c;
  }
  else {
    println("ERROR: unexpected start int");
  }
  
  return pl;
}

void printData(int data[]) {
  
  print("data={");
  
  for(int i = 0; i < data.length; i++) {
    print(hex(data[i]) + "; ");
  }
  
  println("}");  
}

boolean dataEquals(int[] d1, int[] d2) {
  
  if(d1.length != d2.length) {
    return false;
  }
  
  for(int i = 0; i < d1.length; i++) {
    if(d1[i] != d2[i]) {
       return false;
    }
  }
  
  return true;
}

void testPacket(String test, int[] outp, int[] refInp) {
  
  tCount++;
  
  println("TEST: " + test);
  print(" -> ");
  printData(outp);
  print(" <- ");
  
  int inp[] = rocketXfer(outp);
  
  printData(inp);
  
  if(!dataEquals(refInp, inp)) {
     tFail++;
     println("FAIL: " + test);
  }
  else {
     println("OK: " + test);    
  }  
}

void setup() {
  
  println("*** ROCKETuC firmware test ***");

  String portName = "/dev/ttyUSB0";
  port = new Serial(this, portName, 9600);

  // PIN FUNCTION PWM p2.2
  testPacket("PIN FUNCTION PWM p2.2 packet", pinf, ack);

  // PWM FUNCTION p2.2 set period 20000us (20ms)
  testPacket("PWM FUNCTION PWM p2.2 packet", pwmf, ack);

  // PWM CONTROL p2.2 duty cycle 7.5% (1.5ms)
  testPacket("PWM CONTROL PWM p2.2 packet", pwmc_cen, ack);  
}

void draw() {
  delay(1500);  
  testPacket("PWM CONTROL PWM p2.2 packet", pwmc_min, ack);
  delay(1500);  
  testPacket("PWM CONTROL PWM p2.2 packet", pwmc_cen, ack);
  delay(1500);  
  testPacket("PWM CONTROL PWM p2.2 packet", pwmc_max, ack);
  delay(1500);  
  testPacket("PWM CONTROL PWM p2.2 packet", pwmc_cen, ack);  
}
