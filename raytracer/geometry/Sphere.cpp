#include "Sphere.hpp"
#include "math.h"
#include <sstream>
#include "../utilities/Constants.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/BBox.hpp"

// maybe radius 0
Sphere::Sphere()	
	: 	Geometry(),
		c(0.0),
		r(0.0)
{}

Sphere::Sphere(const Point3D& c, float r): 	
        Geometry(),
		c(c),
		r(r)
{}

Sphere::Sphere (const Sphere& sphere)
	: 	Geometry(sphere),
		c(sphere.c),
		r(sphere.r)
{}

Sphere& Sphere::operator= (const Sphere& rhs)		
{
	if (this == &rhs)
		return (*this);

	Geometry::operator= (rhs);

	c = rhs.c;
	r= rhs.r;

	return (*this);
}

std::string Sphere::to_string() const {
    std::stringstream output;
    output << "center: (" << c.x << "," << c.y << "," << c.z << ")" << '\n';
    output << "radius: " << r;
    return output.str();
}

// checking if ray hits sphere
bool Sphere::hit(const Ray& ray, float& t, ShadeInfo& s) const {
    Vector3D oc = ray.o - c;
    double _a = ray.d*ray.d;
    double _b = 2*oc*ray.d;
    double _c = (oc*oc) - (r*r);
    double discriminant = (_b*_b) - (4*_a*_c);

    if (discriminant < 0) {
        return false;
    }

    double e = std::sqrt(discriminant);
    double denom = 2*_a;
    double t0 = (-_b - e)/denom;

    if (t0 > kEpsilon) {
        t = t0;
        s.normal = (oc + t * ray.d)/r;
        s.normal.normalize();
        s.hit_point = ray.o + (t*ray.d);
        s.ray = ray;
        s.t = t;
        //std::cout << "hit " << std::endl;
        return true;
    }

    t0 = (-_b + e)/denom;
    if (t0 > kEpsilon) {
        t = t0;
        s.normal = (oc + t * ray.d)/r;
        s.normal.normalize();
        s.hit_point = ray.o + (t*ray.d);
        s.ray = ray;
        s.t = t;
        return true;
    }
    return false;
}

BBox Sphere::getBBox() const {
    Point3D pmin(c.x - r, c.y - r, c.z - r);
    Point3D pmax(c.x + r, c.y + r, c.z + r);
    return BBox(pmin, pmax);
}


bool Sphere::shadow_hit(const Ray& ray, float& t) const {
    Vector3D oc = ray.o - c;
    double _a = ray.d*ray.d;
    double _b = 2*oc*ray.d;
    double _c = (oc*oc) - (r*r);
    double discriminant = (_b*_b) - (4*_a*_c);

    if (discriminant < 0) {
        return false;
    }

    double e = std::sqrt(discriminant);
    double denom = 2*_a;
    double t0 = (-_b - e)/denom;

    if (t0 > kEpsilon) {
        t = t0;
        return true;
    }

    t0 = (-_b + e)/denom;
    if (t0 > kEpsilon) {
        t = t0;
        return true;
    }
    return false;
}
