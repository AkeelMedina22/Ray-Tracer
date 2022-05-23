#include "Ray.hpp"
#include <sstream>

Ray::Ray (void)
	: 	o(0.0), 
		d(0.0, 0.0, 1.0),
		w(1)
{}

Ray::Ray (const Point3D& origin, const Vector3D& dir)
	: 	o(origin), 
		d(dir),
		w(1)
{}


std::string Ray::to_string() const
{
    std::stringstream output;
    output << "Origin Point: (" << o.x << "," << o.y << "," << o.z << ")" << '\n';
    output << "Direction Vector: (" << d.x << "," << d.y << "," << d.z << ")";
    return output.str();
}

