import rocketuc.*;

ROCKETuC launchpad;

void setup() {
  size(640, 480);
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600);
  launchpad.pinMode(ROCKETuC.P10, ROCKETuC.OUTPUT);
  launchpad.pinMode(ROCKETuC.P13, ROCKETuC.INPUT);
   launchpad.digitalWrite(ROCKETuC.P13, ROCKETuC.HIGH);
}

void draw() {
  if(launchpad.digitalRead(ROCKETuC.P13) == ROCKETuC.HIGH)
  {
  launchpad.digitalWrite(ROCKETuC.P10, ROCKETuC.HIGH);
  }
  else
  {
  launchpad.digitalWrite(ROCKETuC.P10, ROCKETuC.LOW);
  }
}

