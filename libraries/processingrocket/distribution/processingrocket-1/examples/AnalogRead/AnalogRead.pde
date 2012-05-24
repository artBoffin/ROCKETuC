import rocketuc.processing.*;

ROCKETuC r;

float pV = 0;

int tx = 30;
int ty = 70;

void setup() {  
  
  size(480, 120)
  ;
  PFont myFont = createFont(PFont.list()[3], 24);
  textFont(myFont);
  
  background(0);
  text("Use potentiometer on P1.5", tx, ty);
             
  try {
    r = new ROCKETuC(this, "/dev/ttyUSB0");
    
    print("Set P1.5 to ANALOG: ");
    r.pinMode(ROCKETuC.PIN_1_5, ROCKETuC.ANALOG);
    println("OK");
  }
  catch(Exception e) {
    print(e.getMessage());
  }
}

void draw() {
    
  try {    
    short a = r.analogRead(ROCKETuC.PIN_1_5);

    // convert value from analog read to volts: 
    // - assuming Vmax is 3.3V
    // - assuming max value from analog read is 1024
    float v = (float) ((3.3 / 1024.0) * (float)a);
    
    if(pV - v > 0.1 || v - pV > 0.1) {
      background(0);
      text("AnalogRead P1.0: ~volts " + v, tx, ty);
      pV = v;
    }
  }
  catch(Exception e) {
    print(e.getMessage());
  }
}