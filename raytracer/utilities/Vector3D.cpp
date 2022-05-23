#include "Vector3D.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <sstream>

Vector3D::Vector3D ()
{
    x = 0;
    y = 0;
    z = 0;
}

Vector3D::Vector3D (const double c)
{
    x = c;
    y = c;
    z = c;
}

Vector3D::Vector3D (const double _x, const double _y, const double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

Vector3D::Vector3D(const Point3D& p):x(p.x), y(p.y), z(p.z) {}


Vector3D& Vector3D::operator= (const Point3D& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

std::string Vector3D::to_string () const 
{
    std::string str =  "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    return str;
}

Vector3D Vector3D::operator- () const
{
    return Vector3D(-x, -y, -z);
}

Vector3D Vector3D::operator+ (const Vector3D& v) const 
{
    Vector3D vect;
    vect.x = v.x + x;
    vect.y = v.y + y;
    vect.z = v.z + z;
    return vect;
}

Vector3D& Vector3D::operator+= (const Vector3D& vect)
{
    x += vect.x;
    y += vect.y;
    z += vect.z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D& vect) const
{
    Vector3D v;
    v.x = -vect.x + x;
    v.y = -vect.y + y;
    v.z = -vect.z + z;
    return v;
}


Vector3D Vector3D::operator-= (const Vector3D& vect)
{
    x -= vect.x;
    y -= vect.y;
    z -= vect.z;
    return *this;
}



Vector3D Vector3D::operator* (const double a) const
{
    Vector3D v;
    v.x = a * x;
    v.y = a * y;
    v.z = a * z;
    return v;
}

Vector3D Vector3D::operator/ (const double a) const
{
    Vector3D v;
    v.x = x / a;
    v.y = y / a;
    v.z = z / a;
    return v;
}

void Vector3D::normalize ()
{
    double norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    x = x/norm;
    y = y/norm;
    z = z/norm;
}

double Vector3D::length() const
{
    return sqrt(Vector3D::len_squared());
}

double Vector3D::len_squared() const
{
    return (pow(x, 2) + pow(y, 2) + pow(z, 2));
}

double Vector3D::operator*(const Vector3D &b) const
{
    return ((x * b.x) + (y * b.y) + (z * b.z));
}

Vector3D Vector3D::operator^(const Vector3D &v) const
{
    Vector3D temp;
    temp.x = (y * v.z)-(z * v.y);
    temp.y = (z * v.x)-(x * v.z);
    temp.z = (x * v.y)-(y * v.x);
    return temp;
}




Vector3D operator*(const double a, const Vector3D &v)
{
    return Vector3D(
    (a * v.x),
    (a * v.y),
    (a * v.z));
}