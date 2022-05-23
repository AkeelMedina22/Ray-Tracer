#include "Point3D.hpp"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <sstream>

Point3D::Point3D ()
{
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D (const float c)
{
    x = c;
    y = c;
    z = c;
}

Point3D::Point3D (const float _x, const float _y, const float _z)
{
    x = _x;
    y = _y;
    z = _z;
}


std::string Point3D::to_string () const 
{
    std::string str =  "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    return str;
}


Point3D Point3D::operator- () const
{
    return Point3D(-x, -y, -z);
}

Vector3D Point3D::operator- (const Point3D& point) const
{
    Vector3D v;
    v.x = x -point.x;
    v.y = y -point.y;
    v.z = z -point.z;
    return v;
}

Point3D Point3D::operator+(const Vector3D& v) const
{
    return Point3D(x + v.x, y + v.y, z + v.z);
}

Point3D Point3D::operator-(const Vector3D& v) const
{
    return Point3D(x - v.x, y - v.y, z - v.z);
}
Point3D Point3D::operator* (const float a) const
{
    Point3D v;
    v.x = a * x;
    v.y = a * y;
    v.z = a * z;
    return v;
}

float Point3D::distance(const Point3D &p) const
{
    return sqrt(Point3D::d_squared(p));
}


float Point3D::d_squared(const Point3D& p) const
{
    return (pow((x - p.x),2) + pow((y - p.y),2) + pow((z - p.z),2));
}



Point3D operator*(const float a, const Point3D &pt)
{
    return Point3D(
    (a * pt.x),
    (a * pt.y),
    (a * pt.z));
}

Point3D min(const Point3D& a, const Point3D& b)
{
    return Point3D(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}

Point3D max(const Point3D& a, const Point3D& b)
{
    return Point3D(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
