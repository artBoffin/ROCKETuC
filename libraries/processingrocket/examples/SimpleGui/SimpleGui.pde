
import rocketuc.processing.*;

PinPanel p1_0;
PinPanel p1_3;
PinPanel p1_5;

PinPanel pins[]; 

// our instance of the ROCKETuC API
ROCKETuC r;

void setup() {
  
  try {
    // connect to MCU
    r = new ROCKETuC(this, "/dev/ttyACM0");
    r.reset();
  }
  catch(Exception e) {
    // If something goes wrong while communication with the MCU
    // the catch block will be processed. Here the error handling
    // should be done. 
    println(e.getMessage());
    exit();
  }
  
  size(830, 490);
  
  pins = new PinPanel[14];
  
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

void draw() {
  for(int i = 0; i < pins.length; i++) {
    pins[i].draw();
  }  
}

void mousePressed() {
  for(int i = 0; i < pins.length; i++) {
    pins[i].checkPressed();
  }  
}
