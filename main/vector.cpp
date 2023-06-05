#include "vector.h"
#include <cmath>

Vector::Vector(double x, double y)
    :X(x), Y(y), magnitude(magnitudeOf(x,y))
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

Vector& operator/ (Vector& v1, double value)
{
    v1.setX(v1.getX()/value);
    v1.setY(v1.getY()/value);
    return v1;
}

Vector& operator* (Vector& v1, double value)
{
    v1.setX(v1.getX()*value);
    v1.setY(v1.getY()*value);
    return v1;
}

Vector& operator+ (Vector& v1, const Vector& v2)
{
    v1.setX(v1.getX()+v2.getX());
    v1.setY(v1.getY()+v2.getY());
    return v1;
}
Vector& operator+= (Vector& v1, const Vector& v2)
{
    v1.setX(v1.getX()+v2.getX());
    v1.setY(v1.getY()+v2.getY());
    return v1;
}
