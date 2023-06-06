#include "Arduino.h"
#include "ball.h"
#include "bar.h"
#include "point.h"
#include "joystick.h"
#include <cmath>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
extern Adafruit_SH1107 display;
extern int screenWidth, screenHeight;
extern int joystickMiddle, joystickRange, joystickSensivity;
extern Bar playerBar, topBar, bottomBar, goalBar, portalBar;
extern Joystick j;

Ball::Ball()
  : position(Vector(screenHeight / 2.0, screenWidth / 2.0)), speed(20), radius(5), inPortal(false) {
    delay(500);
  int randomPos = random(360);
  Vector newDirection(cos(radians(randomPos)), cos(radians(randomPos)));

  direction = newDirection;
}

Ball::Ball(String ballInfo)
  : position(Vector(0, 0)), direction(Vector(.5, .5)) {
  position = Vector(screenHeight + (screenHeight - getSplitedString(ballInfo, 1)), screenWidth - getSplitedString(ballInfo, 2));
  direction = Vector(-getSplitedString(ballInfo, 3), -getSplitedString(ballInfo, 4));
  speed = getSplitedString(ballInfo, 5);
  radius = getSplitedString(ballInfo, 6);
  inPortal = true;
}

String Ball::toString() {
  String posStr = String(position.getX()) + ";" + String(position.getY());
  String dirStr = String(direction.getX()) + ";" + String(direction.getY());

  return "Ball;" + posStr + ";" + dirStr + ";" + speed + ";" + radius;
}


double Ball::getSplitedString(String s, int indexOfArray) {
  String result[7];
  int index = 0;
  String temp;
  for (String s : result) {
    s = "";
  }

  for (int i = 0; i < s.length(); ++i) {
    temp = s.substring(i, i + 1);
    if (temp.equals(";")) {
      ++index;
    } else {
      result[index] = result[index] + temp;
    }
  }

  return result[indexOfArray].toDouble();
}

void Ball::move(double delta) {
  if(position.getY()<topBar.getY()){
    position.setY(topBar.getY());
  }
  if(position.getY()>bottomBar.getY()){
    position.setY(bottomBar.getY());
  }
  if(position.getX()<goalBar.getX()){
    position.setX(bottomBar.getX());
  }

  position += direction * speed * delta;
  bool switchX = false;
  bool switchY = false;

  if (playerBar.isCollidedBy(*this)) {
    switchX = !switchX;
  }
  if (topBar.isCollidedBy(*this)) {
    switchY = !switchY;
  }else if (bottomBar.isCollidedBy(*this)) {
    switchY = !switchY;
  }

  if(switchX){
    direction.setX(direction.getX() * -1);
    Vector barVector = playerBar.getDirection() * playerBar.getSpeed()/6;
    Vector ballVector = direction * speed;
    Vector newDirection = barVector + ballVector;

    direction = newDirection/newDirection.magnitude;
  }
  if(switchY){
    direction.setY(direction.getY() * -1);
  }

  if(switchX || switchY){
    position += direction * speed * delta;
    speed+=1;
  }
}

bool Ball::changeScreen() {
  return position.getX() - radius > screenHeight && direction.getX() > 0;
}

bool Ball::loose() {
  return position.getX() - radius <= 0;
}

void Ball::draw() {
  Point temp;
  Point center(position.getX(), position.getY());

  display.setRotation(0);

  for (int y = position.getY() - radius; y <= position.getY() + radius; ++y) {
    for (int x = position.getX() - radius; x <= position.getX() + radius; ++x) {
      temp = Point(x, y);
      if (temp.distanceTo(center) <= radius) {
        display.drawPixel(x, y, SH110X_WHITE);
      }
    }
  }
}