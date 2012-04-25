import rocketuc.*;

ROCKETuC launchpad;

char led = ROCKETuC.P16;
char button = ROCKETuC.P13;

void setup() {
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600);
  launchpad.pinMode(led, ROCKETuC.OUTPUT);
  launchpad.pinMode(button, ROCKETuC.PULLUP);
  launchpad.pinMode(ROCKETuC.P14, ROCKETuC.OUTPUT);
  launchpad.digitalWrite(ROCKETuC.P14, ROCKETuC.HIGH);
}

void draw() {

  if (launchpad.digitalRead(button) == 0)
  {
    background(random(0,255),random(0,255),random(0,255));
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

