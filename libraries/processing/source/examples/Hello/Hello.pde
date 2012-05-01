import rocketuc.*;

ROCKETuC launchpad;

char led;
char led2;
char button;
char on;
char off;

void setup() {
  println(ROCKETuC.list());
  launchpad = new ROCKETuC(this, ROCKETuC.list()[0], 9600, "launchpad");

  led = launchpad.getPin("P1.0");
  button = launchpad.getPin("P1.4");
  led2 = launchpad.getPin("P1.6");
  on = launchpad.HIGH;
  off = launchpad.LOW;
  
  //launchpad.pinMode(led, launchpad.OUTPUT);
    launchpad.pinMode(led2, launchpad.PWM);
    launchpad.pwmPeriod(led2, 20000);
 // launchpad.pinMode(button, launchpad.PULLUP);
}

void draw() {
  for(char i = 0; i < 255; i++)
  {
         launchpad.pwmDuty(led2, i);
  }
/*  if (launchpad.digitalRead(button) == 0)
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
    launchpad.digitalWrite(led, on);
  }
  else
  {
    launchpad.digitalWrite(led, off);
  }*/
}

