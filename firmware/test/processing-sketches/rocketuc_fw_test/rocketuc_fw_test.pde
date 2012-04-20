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

  int refAck[] = {0x2B, 0x05, 0x01, 0x01, 0x32};
  
  // NULL Packet
  int pNull[] = {0x24, 0x04, 0x00, 0x28};
  
  testPacket("NULL packet", pNull, refAck);

  // SYSTEM INFO Packet
  int pSys[] = {0x24, 0x04, 0x02, 0x2A};
  int refSys[] = {0x2B, 0x07, 0x02, 0xCA, 0xFF, 0xEE, 0xEB};
  
  testPacket("SYSTEM INFO packet", pSys, refSys);

  // PIN FUNCTION digital p1.0 Packet
  int pPf1[] = {0x24, 0x06, 0x04, 0x10, 0x03, 0x41};
  
  testPacket("PIN FUNCTION digital p1.0 packet", pPf1, refAck);

  // PIN CONTROL digital p1.0 HIGH Packet
  int pPc1[] = {0x24, 0x06, 0x05, 0x10, 0x01, 0x40};
  
  testPacket("PIN CONTROL digital p1.0 HIGH packet", pPc1, refAck);
  
  delay(1000);

  // PIN CONTROL digital p1.0 LOW Packet
  int pPc2[] = {0x24, 0x06, 0x05, 0x10, 0x00, 0x3F};
  
  testPacket("PIN CONTROL digital p1.0 LOW packet", pPc2, refAck);

  // PIN FUNCTION digital IN p1.3 Packet
  int pPf2[] = {0x24, 0x06, 0x04, 0x13, 0x00, 0x41};
  
  testPacket("PIN FUNCTION digital IN p1.3 packet", pPf2, refAck);

  // PIN CONTROL digital p1.0 READ Packet
  int pPc3[] = {0x24, 0x06, 0x05, 0x13, 0x03, 0x45};
  // only if button not pressed
  int refDr1[] = {0x2B, 0x06, 0x03, 0x13, 0x01, 0x48};
  // if button  pressed
  // int refDr1[] = {0x2B, 0x06, 0x03, 0x13, 0x00, 0x47};
  
  testPacket("PIN CONTROL digital p1.3 READ packet", pPc3, refDr1);

  // PIN FUNCTION analog IN p1.5 Packet
  int pPf3[] = {0x24, 0x06, 0x04, 0x15, 0x04, 0x47};
  
  testPacket("PIN FUNCTION analog IN p1.5 packet", pPf3, refAck);
  
  // PIN CONTROL analog p1.5 READ Packet
  int pPc4[] = {0x24, 0x06, 0x05, 0x15, 0x04, 0x48};
  // only if valu of poti is 0
  int refAr1[] = {0x2B, 0x07, 0x04, 0x15, 0x00, 0x00, 0x4B};
  
  testPacket("PIN CONTROL digital p1.3 READ packet", pPc4, refAr1);

  println("");
  println("DONE: tests=" + tCount + ", fail=" + tFail + ", ok=" + (tCount - tFail));
}


