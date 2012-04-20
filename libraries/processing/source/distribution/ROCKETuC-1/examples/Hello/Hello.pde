import rocketuc.*;

ROCKETuC launchpad;

void setup() {
  size(640, 480);
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600);
  launchpad.pinMode(ROCKETuC.P10, ROCKETuC.OUTPUT);
}

void draw() {
  launchpad.digitalWrite(ROCKETuC.P10, ROCKETuC.HIGH);
  delay(500);
  launchpad.digitalWrite(ROCKETuC.P10, ROCKETuC.LOW);
  delay(500);
}

