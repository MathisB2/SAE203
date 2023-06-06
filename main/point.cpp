#include "point.h"
#include <cmath>

Point::Point(double x, double y):X(x), Y(y)
{
}

Point::Point():Point(0,0)
{
}


float Point::distanceTo(Point p){
  return sqrt(pow(p.X-this->X,2)+pow(p.Y-this->Y,2));
}

float Point::distanceTo(float X,float Y){
  return distanceTo(Point(X,Y));
}