#ifndef BALL_H
#define BALL_H
#define screenX 120
#define screenY 200

#include <string>
#include "vector.h"

using namespace std;

class Ball
{
private:
    Vector position;
    Vector direction;
    double speed;
    double radius;
public:
    Ball();
    Ball(string);
    void move(double);
    bool changeScreen();
    bool loose();
};

#endif // BALL_H
