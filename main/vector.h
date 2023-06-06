#ifndef VECTOR_H
#define VECTOR_H


class Vector{
private:
    double X, Y;
public:
    double magnitude;

    Vector(Vector const &);
    Vector(double, double);
    Vector();

    void setX(double x);
    void setY(double y);

    double getX() const {return X;}
    double getY()const{return Y;}

    Vector operator/ (double value);
    Vector operator* (double value);
    Vector operator+ (const Vector& v2);
    friend Vector& operator+= (Vector& v1, const Vector& v2);
private:
    double magnitudeOf(double x, double y);
};

Vector& operator+= (Vector& v1, const Vector& v2);

#endif // VECTOR_H
