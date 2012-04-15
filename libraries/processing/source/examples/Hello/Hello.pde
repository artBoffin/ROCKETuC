import rocketuc.*;

ROCKETuC launchpad;

void setup() {
  size(640, 480);
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600);
  launchpad.pinMode(char(0x10), ROCKETuC.OUTPUT);
}

void draw() {
  launchpad.digitalWrite(char(0x10), ROCKETuC.HIGH);
  delay(500);
  launchpad.digitalWrite(char(0x10), ROCKETuC.LOW);
  delay(500);
}

