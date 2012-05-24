import rocketuc.processing.*;

ROCKETuC r;

void setup() {  
  try {
    r = new ROCKETuC(this, "/dev/ttyUSB0");
    
    print("Set P1.0 to OUTPUT: ");
    r.pinMode(ROCKETuC.PIN_1_0, ROCKETuC.OUTPUT);
    println("OK");
    
    
  }
  catch(Exception e) {
    print(e.getMessage());
  }
}

void draw() {
  try {
    print("Toggle P1.0: ");
    r.digitalWrite(ROCKETuC.PIN_1_0, ROCKETuC.TOGGLE);
    println("OK");
  }
  catch(Exception e) {
    print(e.getMessage());
  }
  
  delay(500);
}