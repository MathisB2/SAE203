#ifndef BALL_H
#define BALL_H
#define screenX 120
#define screenY 200

#include <String.h>
#include <Arduino.h>
#include "vector.h"

class Ball
{
private:
    Vector position;
    Vector direction;
    double speed;
    double radius;
public:
    Ball();
    Ball(String);
    void move(double);
    String toString();
    bool changeScreen();
    bool loose();
};

#endif // BALL_H
