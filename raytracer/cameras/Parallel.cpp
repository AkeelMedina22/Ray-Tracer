#include "Parallel.hpp"

Parallel::Parallel() 
{
	dir.x = 0.0;
	dir.y = 0.0;
	dir.z = -1.0;
}

Parallel::Parallel(float c) 
{
	dir.x = c;
	dir.y = c;
	dir.z = c;
}

Parallel::Parallel(float x, float y, float z) 
{
	dir.x = x;
	dir.y = y;
	dir.z = z;
}

Parallel::Parallel(const Vector3D &d) 
{
	dir = d;
}

Parallel::Parallel(const Parallel &camera) 
{
	dir = camera.dir;
}

Parallel& Parallel::operator=(const Parallel &other)
{
    dir = other.dir;
    return *this;
}

Vector3D Parallel::get_direction(const Point3D &p) const
{
    return dir; 
}
