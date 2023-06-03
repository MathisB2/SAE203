#include "bar.h"
#include "point.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
extern Adafruit_SH1107 display;
extern int joystickMiddle, joystickRange, joystickSensivity;
extern int screenWidth, screenHeight;



Bar::Bar(int length, int x, int y, bool horizontal, bool displayed, bool collide) {
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


void Bar::updateLocation() {
  float move = (analogRead(A0) - joystickMiddle) / (float)joystickRange;
  Serial.print(move);
  if (move < 0.05 && move > -0.05) {
    move = 0;
  } else if (move > 1) {
    move = 1;
  } else if (move < -1) {
    move = -1;
  }
  Serial.print("    ");
  Serial.println(move);

  this->p.Y += move * (joystickSensivity / 100.0);
  if (this->p.Y < 0) {
    this->p.Y = 0;
  } else if (this->p.Y > screenWidth - this->length) {
    this->p.Y = screenWidth - this->length;
  }
}


void Bar::resetLocation() {
  this->p.Y = screenHeight - (int)(this->length / 2);
}



/*
int isCollidedBy(Ball b) {
  //return 0 if not collided by the ball
  //return 1 if horizontal and collided <=> need to reverse yVector
  //return 2 if vertical and collided <=> need to reverse xVector
  if (this->collide) {
    Point cursor();
    if (this->horizontal == true) {
      cursor.X = b.getX();
      cursor.Y = this->p.Y;
      if (cursor.distanceTo(b.getX(), b.getY()) < b.getRadius()) {
        return 1;
      }
    } else {

      cursor.X = this->p.X;
      cursor.Y = b.getY();

      if (cursor.distanceTo(b.getX(), b.getY()) < b.getRadius()) {
        return 2;
      }
    }
  }
  return 0;
}*/