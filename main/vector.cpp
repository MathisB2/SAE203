#include "vector.h"
#include <cmath>

Vector::Vector(double x, double y)
    :X(x), Y(y), magnitude(magnitudeOf(x,y))
{}
Vector::Vector()
    :X(0), Y(0), magnitude(magnitudeOf(0,0))
{}

void Vector::setX(double x)
{
    X = x;
    magnitude = magnitudeOf(X, Y);
}

void Vector::setY(double y)
{
    Y = y;
    magnitude = magnitudeOf(X, Y);
}

double Vector::magnitudeOf(double x, double y)
{
    return sqrt(x*x + y*y);
}

Vector Vector::operator/ (double value)
{
    return Vector(getX()/value, getY()/value);
}

Vector Vector::operator* (double value)
{
    return Vector(getX()*value, getY()*value);
}

Vector Vector::operator+ (const Vector& v2)
{
  return Vector(getX()+v2.getX(), getY()+v2.getY());
}
Vector& operator+= (Vector& v1, const Vector& v2)
{
    v1.setX(v1.getX()+v2.getX());
    v1.setY(v1.getY()+v2.getY());
    return v1;
}
