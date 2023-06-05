#ifndef BALL_H
#define BALL_H
#include <String.h>
#include <Arduino.h>
#include "vector.h"

class Ball {
private:
  Vector position;
  Vector direction;
  double speed;
  double radius;
public:
  Ball();
  Ball(String);
  void move(double);
  
  double getSplitedString(String, int);
  double getX() const{return position.getX();}
  double getY() const{return position.getY();}
  double getRadius() const{return radius;}

  bool changeScreen();
  bool loose();
  void draw();

  String toString();
};

#endif  // BALL_H
