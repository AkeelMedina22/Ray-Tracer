#include "ViewPlane.hpp"


ViewPlane::ViewPlane()
{
    hres = 640;
    vres = 480;
    normal = Vector3D(0, 0, -1);
    //normal = Vector3D(0, 0, 1);
    top_left = Point3D(320, 240, 0);
    bottom_right = Point3D(-320, -240, 0);
    max_depth = 0;
}


int ViewPlane::get_hres() const
{
    return hres;
}


void ViewPlane::set_hres(int hresVal)
{
    hres = hresVal;
}


int ViewPlane::get_vres() const
{
    return vres;
}


void ViewPlane::set_vres(int vresVal)
{
    vres = vresVal;
}
void ViewPlane::set_maxdepth(int d)
{
    max_depth = d;
}

