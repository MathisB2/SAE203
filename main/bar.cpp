#include "bar.h"
#include "point.h"
#include "joystick.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
extern Adafruit_SH1107 display;
extern int joystickMiddle, joystickRange, joystickSensivity;
extern int screenWidth, screenHeight;
extern Joystick j;


Bar::Bar(int length, int x, int y, bool horizontal, bool displayed, bool collide)
  :speed(100)
{
  this->length = length;
  this->p = Point(x, y);
  this->horizontal = horizontal;
  this->displayed = displayed;
  this->collide = collide;
}


Bar::Bar(int length, int x, int y)
  : Bar(length, x, y, true, true, true) {
}


Bar::Bar(int length, int x, int y, bool horizontal)
  : Bar(length, x, y, horizontal, true, true) {
}

bool Bar::isDisplayed() {
  return this->displayed;
}


bool Bar::canCollide() {
  return this->collide;
}


void Bar::drawBar() {
  if (this->displayed) {
    display.setRotation(0);
    if (this->horizontal) {
      display.drawLine(this->p.X, this->p.Y, this->p.X + this->length, this->p.Y, SH110X_WHITE);
    } else {
      display.drawLine(this->p.X, this->p.Y, this->p.X, this->p.Y + this->length, SH110X_WHITE);
    }
  }
}


void Bar::updateLocation(double delta) {
  float move = j.readY(false);
  direction = Vector(0,move);
  
  this->p.Y += move * speed * delta;
  if (this->p.Y < 0) {
    this->p.Y = 0;
  } else if (this->p.Y > screenWidth - this->length) {
    this->p.Y = screenWidth - this->length;
  }
}

double Bar::getX(){
  return p.X;
}

double Bar::getY(){
  return p.Y;
}
void Bar::resetLocation() {
  this->p.Y = screenHeight - (int)(this->length / 2);
}

bool Bar::isCollidedBy(Ball& b) {

  Point cursor;

  if (this->horizontal) {
    cursor.X = b.getX();

    cursor.Y = this->p.Y;
    if (cursor.X >= this->p.X && cursor.X < this->p.X + this->length) {
      if (cursor.distanceTo(b.getX(), b.getY()) < b.getRadius()) {
        return true;
      }
    }
  } else {

    cursor.X = this->p.X;
    cursor.Y = b.getY();

    if (cursor.Y >= this->p.Y && cursor.Y < this->p.Y + this->length) {
      if (cursor.distanceTo(b.getX(), b.getY()) < b.getRadius()) {
        return true;
      }
    }
  }

  return false;
}
