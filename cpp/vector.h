#ifndef VECTOR_H
#define VECTOR_H


class Vector{
private:
    double X, Y;
public:
    double magnitude;

    Vector(double x, double y);

    void setX(double x);
    void setY(double y);

    double getX() const {return X;}
    double getY()const{return Y;}

    friend Vector& operator/ (Vector& v1, double value);
private:
    double magnitudeOf(double x, double y);
};

Vector& operator/ (Vector& v1, double value);

#endif // VECTOR_H
