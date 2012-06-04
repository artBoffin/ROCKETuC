/* 
 * This file is part of the ROCKETuC Processing Library project
 *
 * Copyright (C) 2012 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC Processing Library is free software; you can redistribute 
 * it and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC Processing Library is distributed in the hope that it will 
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the JRocket firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

import rocketuc.processing.*;

/**
 * This class shows the main panel for a pin including the buttons
 * for selecting the pin mode. 
 */
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
  
  /**
   * Contructor
   * 
   * @param r	 connected ROCKETuC instance
   * @param pin	 ROCKETuC.PIN_x_y for which this panel is responsible
   * @param name Display name of panel
   * @param x    x-position of panel
   * @param y    y-position of panel
   */
  PinPanel(ROCKETuC r, byte pin, String name, int x, int y) {
    this.r = r;
    this.pin = pin;
    this.name = name;
    this.x = x; 
    this.y = y;
    
    fnt = createFont(PFont.list()[fntId], fntSize);

    pc = new PinControlIf(this);    
  }
  
  /**
   * Draw the panel an its current control object
   */
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
  
  /**
   * Check if one of the pin mode buttons was pressed.
   * If one is pressed, select the pin mode accordingly
   * by assigning an instance of the responsible PinControl.
   */
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

  /** 
   * Draw a pin mode button
   * 
   * @param label the button label to dispaly
   * @param dx    delta to parents x-position
   * @param dy    delta to parents x-position
   * @param w     button width 
   * @param h     button height 
   */
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
    
  /**
   * Check if mouse is over a rectangel, if so keep track of that rectangle.
   * 
   * @param label  label of the tracked button
   * @param x      x-position of button
   * @param y      y-position of button
   * @param w      button width 
   * @param h      button height 
   * @return       true if mouse is in given rectangle
   */
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
