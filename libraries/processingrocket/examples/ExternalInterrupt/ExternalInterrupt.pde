// Import the ROCKETuC stuff
import rocketuc.processing.*;

// Our API instance derived from ROCKETuC
MyROCKETuC r;

/**
 * setup function called by processing on startup
 */
void setup() {
  try {
	// connect to MCU
    r = new MyROCKETuC(this, "/dev/ttyUSB0");
    
	// setup P1.0 as digital output (the build in LED on the Launchpad)
    print("Set P1.0 to OUTPUT: ");
    r.pinMode(ROCKETuC.PIN_1_0, ROCKETuC.OUTPUT);
    println("OK");
    
	// set P1.3 as digital input-float
    print("Set P1.3 to INPUT FLOAT: ");
    r.pinMode(ROCKETuC.PIN_1_3, ROCKETuC.INPUT);
    println("OK");    
    
	// enable external interrupt for p1.3 on high-low transition
    print("Enable EXTI on HIGH-LOW transition for P1.3: ");
    r.externalInterrupt(ROCKETuC.PIN_1_3, ROCKETuC.EDGE_HIGHLOW);
    println("OK");    
  }
  catch(Exception e) {
    print(e.getMessage());
  }
}

/**
 * draw is called repeadedly from processing
 */
void draw() {
  
  try {
	// blink p1.0 by toggeling
    print("Toggle P1.0: ");
    r.digitalWrite(ROCKETuC.PIN_1_0, ROCKETuC.TOGGLE);
    println("OK");
  }
  catch(Exception e) {
    print(e.getMessage());
  }
  
  delay(500);
}

/**
 * We derive a class from ROCKETuC to override the
 * event handler for the external interrupt.
 */
class MyROCKETuC extends ROCKETuC {
    
  /**
   * Constructor just passes values to parent class
   */
  MyROCKETuC(PApplet applet, String port) throws Exception {
    super(applet, port);
  }
  
  /**
   * Interrupt handler, called every time p1.3 goes from high to low
   */
  void externalInterrupt(short pin) {
    println("External interrupt on PIN: " + pin);
  }  
}
