import rocketuc.processing.*;

class PinPanel 
{
  protected ROCKETuC r;
  protected byte   pin;
  protected String name;
  
  protected int x;
  protected int y;
  protected int w = 400;
  protected int h = 45;  

  protected PFont fnt;
  protected int   fntId   = 3;
  protected int   fntSize = 10;

  protected String buttonHl  = "_none_";
  protected String buttonAkt = "IF";
  
  protected PinControl pc = null;
  
  PinPanel(ROCKETuC r, byte pin, String name, int x, int y) {
    this.r = r;
    this.pin = pin;
    this.name = name;
    this.x = x; 
    this.y = y;
    
    fnt = createFont(PFont.list()[fntId], fntSize);

    pc = new PinControlIf(this);    
  }
  
  void draw() {
    fill(255);
    rect(x, y, w, h);
    
    buttonHl = "_none_";
    button("DO",  40, 10, 25, 25);
    button("IF",  70, 10, 25, 25);
    button("IU", 100, 10, 25, 25);
    button("ID", 130, 10, 25, 25);    
    button("AR", 160, 10, 25, 25);
    button("PW", 190, 10, 25, 25);
    
    fill(0);
    textFont(fnt);    
    text(name, x +  10, y + (h / 2) + (fntSize / 2));
    
    pc.draw();
  }
  
  void checkPressed() {
    if(buttonHl != "_none_") {
      buttonAkt = buttonHl;
      
      if(buttonAkt == "DO") {
         pc = new PinControlDo(this);
      }
      else if(buttonAkt == "IF") {
        pc = new PinControlIf(this);
      }
      else if(buttonAkt == "IU") {
        pc = new PinControlIu(this);
      }
      else if(buttonAkt == "ID") {
        pc = new PinControlId(this);
      }            
      else if(buttonAkt == "AR") {
        pc = new PinControlAr(this);
      }
      else if(buttonAkt == "PW") {
        pc = new PinControlPw(this);
      }            
    }
  }

  protected void button(String label, int dx, int dy, int w, int h)  {
    
    if(overRect(label, x + dx, y + dy, w, h)) {
      fill(128);
    }
    else if(buttonAkt == label) {
      fill(180);
    }
    else {
      fill(255);
    }
    rect(x +  dx, y + dy, w, h);
    
    fill(0);
    textFont(fnt);
    text(label, x +  dx + 5, y + dy + (h / 2) + (fntSize / 2));
  }
    
  protected boolean overRect(String label, int x, int y, int w, int h)  {
    if (mouseX >= x && mouseX <= x + w && 
        mouseY >= y && mouseY <= y + h) {
      buttonHl = label;
      return true;
    } else {
      return false;
    }
  }    
  
  public ROCKETuC getROCKETuC() {
    return r;
  }

  public byte getPin() {
    return pin;
  }
  
  public String getPinName() {
    return name;
  }
  
  public int getX() {
    return x;
  }
  
  public int getY() {
    return y;
  }  
  
  public int getW() {
    return w;
  }  
  
  public int getH() {
    return h;
  }  
}
