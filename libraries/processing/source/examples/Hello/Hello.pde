import rocketuc.*;

ROCKETuC launchpad;

char led;
char button;

void setup() {
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600, "launchpad");

  led = launchpad.getPin("P1.0");
  button = launchpad.getPin("P1.4");
  launchpad.pinMode(led, ROCKETuC.OUTPUT);
  launchpad.pinMode(button, ROCKETuC.PULLUP);
}

void draw() {

  if (launchpad.digitalRead(button) == 0)
  {
    background(random(0, 255), random(0, 255), random(0, 255));
    fill(0, 255, 0);
    ellipse (50, 50, 50, 50);
  }
  else
  {
    fill(255, 0, 0);
    ellipse (50, 50, 50, 50);
  }

  if (mousePressed)
  {
    launchpad.digitalWrite(led, ROCKETuC.HIGH);
  }
  else
  {
    launchpad.digitalWrite(led, ROCKETuC.LOW);
  }
}

