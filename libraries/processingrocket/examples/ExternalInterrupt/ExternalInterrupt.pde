import rocketuc.processing.*;

MyROCKETuC r;

void setup() {
  size(400,400);
  smooth();
  
  try {
    r = new MyROCKETuC(this, "/dev/ttyUSB0");
    
    print("Set P1.0 to OUTPUT: ");
    r.pinMode(ROCKETuC.PIN_1_0, ROCKETuC.OUTPUT);
    println("OK");
    
    print("Set P1.3 to INPUT FLOAT: ");
    r.pinMode(ROCKETuC.PIN_1_3, ROCKETuC.INPUT);
    println("OK");    
    
    print("Enable EXTI on HIGH-LOW transition for P1.3: ");
    r.externalInterrupt(ROCKETuC.PIN_1_3, ROCKETuC.EDGE_HIGHLOW);
    println("OK");    
  }
  catch(Exception e) {
    print(e.getMessage());
  }
  
  PFont font = createFont("",40);
  textFont(font);
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

class MyROCKETuC extends ROCKETuC {
    
  MyROCKETuC(PApplet applet, String port) throws Exception {
    super(applet, port);
  }
  
  void externalInterrupt(short pin) {
    println("External interrupt on PIN: " + pin);
  }  
}