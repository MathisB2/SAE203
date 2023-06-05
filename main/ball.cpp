#include "ball.h"
#include "bar.h"
#include "point.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
extern Adafruit_SH1107 display;
extern int screenWidth, screenHeight;
extern Bar playerBar, topBar, bottomBar, goalBar;

Ball::Ball()
  : position(Vector(screenWidth / 2.0, screenHeight / 2.0)), direction(Vector(.5, .5)), speed(100), radius(20) {}

Ball::Ball(String ballInfo)
    :position(Vector(0, 0)), direction(Vector(.5, .5)) {
  position = Vector(getSplitedString(ballInfo, 1), getSplitedString(ballInfo, 2));
  direction = Vector(-getSplitedString(ballInfo, 3), getSplitedString(ballInfo, 4));
  speed = getSplitedString(ballInfo, 5);
  radius = getSplitedString(ballInfo, 6);
  move(.05);
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
  position += direction * speed * delta;
  bool switchX = false;
  bool switchY = false;

  if (playerBar.isCollidedBy(*this)) {
    switchX = !switchX;
  }
  if (goalBar.isCollidedBy(*this)) {  //loose
    switchX = !switchX;
  }
  if (topBar.isCollidedBy(*this)) {
    switchY = !switchY;
  }
  if (bottomBar.isCollidedBy(*this)) {
    switchY = !switchY;
  }


  if (switchX) {
    direction.setY(direction.getY() * -1);
  }
  if (switchY) {
    direction.setX(direction.getX() * -1);
  }
}
bool Ball::changeScreen() {
  return position.getX()-radius*2 > screenHeight;
}

bool Ball::loose() {
  return position.getX() <= 0;
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