#ifndef BAR_H
#define BAR_H
#include"point.h"
#include"ball.h"
#include <WiFi.h>

class Bar
{
private:
    int length;
    Point p;
    bool horizontal;
    bool displayed;
    bool collide;

public:
    Bar(int,int,int,bool,bool,bool);
    Bar(int,int,int);
    Bar(int,int,int,bool);

    bool isDisplayed();
    bool canCollide();
    bool isCollidedBy(Ball&);
    void drawBar();
    void updateLocation();
    void resetLocation();
   
};

#endif // BAR_H
