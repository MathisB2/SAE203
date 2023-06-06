#ifndef BAR_H
#define BAR_H
#include "point.h"
#include "vector.h"
#include "ball.h"
#include <WiFi.h>

class Bar {
private:
  int length;
  Point p;
  Vector direction;
  double speed;
  bool horizontal;
  bool displayed;
  bool collide;
public:
  Bar(int, int, int, bool, bool, bool);
  Bar(int, int, int);
  Bar(int, int, int, bool);
  double getX();
  double getY();
  bool isDisplayed();
  bool canCollide();
  bool isCollidedBy(Ball&);
  Vector& getDirection() {return direction;}
  double getSpeed() {return speed;}
  void drawBar();
  void updateLocation();
  void resetLocation();
};

#endif  // BAR_H
