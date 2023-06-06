#include "joystick.h"

#include "Arduino.h"



Joystick::Joystick() {
  reset();
  xRange = 1200;
  yRange = 1200;
  deadZone = 0.05;
}


double Joystick::readX(bool decimal) {
  float move = (analogRead(A5) - xCenter) / (float)xRange;
  int mov;
  if (move < deadZone && move > -deadZone) {
    return 0;
  } else if (move > 1){
    move = 1;
    mov=1;
  }
    
  else if (move < -1){
     move = -1;
    mov=-1;
  }
   

  if (decimal) {
    return move;
  } else {
    return mov;
  }
}



double Joystick::readY(bool decimal) {
  float move = (analogRead(A4) - yCenter) / (float)yRange;
   int mov;
  if (move < deadZone && move > -deadZone) {
    return 0;
  } else if (move > 1){
    mov = 1;
    move=1;
  }
    
  else if (move < -1){
    mov = -1;
    move=-1;
  }
    
  
  
  if (decimal) {
    return move;
  } else {
    return mov;
  }
}


void Joystick::resetX() {
  xCenter = analogRead(A5);
}


void Joystick::resetY() {
  yCenter = analogRead(A4);
}


void Joystick::reset() {
  resetX();
  resetY();
}



bool Joystick::isClicked(){
  return analogRead(A4)==4095;
}
