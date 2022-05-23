#include "Triangle.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/BBox.hpp"

#include <sstream>


Triangle::Triangle()
    : Geometry(),
    v0(0),
    v1(0),
    v2(0)
{}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c)
    : Geometry()
    , v0(a)
    , v1(b)
    , v2(c) 
{}

Triangle::Triangle(const Triangle& triangle)
    : Geometry(triangle)
    , v0(triangle.v0)
    , v1(triangle.v1)
    , v2(triangle.v2)
{}


Triangle& Triangle::operator=(const Triangle& rhs){
    if(this == &rhs){
        return (*this);
    }
    Geometry::operator=(rhs);
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    return (*this);
}

std::string Triangle::to_string() const {
    std::stringstream output;
    output << "Point v0: (" << v0.x << "," << v0.y << "," << v0.z << ")" << '\n';
    output << "Point v1: (" << v1.x << "," << v1.y << "," << v1.z << ")" << '\n';
    output << "Point v2: (" << v2.x << "," << v2.y << "," << v2.z << ")";
    return output.str();
}

// finding the smallest and largest x, y, and z components triangle's three points.
BBox Triangle::getBBox() const {
    return BBox(min(min(v0, v1), v2), max(max(v0,v1), v2));

}

// checking if ray hits triangle
bool Triangle::hit(const Ray& ray, float& tmin, ShadeInfo& sr) const {
    
 	double a = v0.x - v1.x, b = v0.x - v2.x, c = ray.d.x, d = v0.x - ray.o.x; 
	double e = v0.y - v1.y, f = v0.y - v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z - v2.z, k = ray.d.z, l = v0.z - ray.o.z;
		
	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;
	
	double inv_denom  = 1.0 / (a * m + b * q + c * s);
	
	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;
	
	if (beta < 0.0)
	 	return (false);
	
	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;
	
	if (gamma < 0.0 )
	 	return (false);
	
	if (beta + gamma > 1.0)
		return (false);
			
	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;
	
	if (t < kEpsilon)  
		return (false);
					
	tmin 				= t;
	sr.hit_point 	= ray.o + t * ray.d;
    sr.ray = ray;	
    Vector3D normal = (v1 - v0) ^ (v2 - v0);  
	normal.normalize();
    sr.normal = normal;
	
	return (true);	
}


bool Triangle::shadow_hit(const Ray& ray, float& t) const {
    return false;
}