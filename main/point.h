#ifndef POINT_H
#define POINT_H


class Point{
public:
    double X, Y;
    Point(double,double);
    Point();
    float distanceTo(Point);
    float distanceTo(float,float);
};
#endif // POINT_H
