import rocketuc.*;

ROCKETuC launchpad;

void setup() {
  size(640, 480);
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600);
  launchpad.pinMode(ROCKETuC.P20, ROCKETuC.OUTPUT);
  launchpad.pinMode(ROCKETuC.P13, ROCKETuC.INPUT);
  launchpad.pinMode(ROCKETuC.P15, ROCKETuC.ANALOG);
  // launchpad.digitalWrite(ROCKETuC.P13, ROCKETuC.HIGH);
}

void draw() {
 
  println(hex(launchpad.digitalRead(ROCKETuC.P13)));

  launchpad.digitalWrite(ROCKETuC.P20, ROCKETuC.HIGH);
  println(launchpad.analogRead(ROCKETuC.P15));
  delay(500);
  launchpad.digitalWrite(ROCKETuC.P20, ROCKETuC.LOW);
  println(launchpad.analogRead(ROCKETuC.P15));
  delay(500);
}

