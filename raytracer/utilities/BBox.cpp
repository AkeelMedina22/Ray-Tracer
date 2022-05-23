#include "BBox.hpp"
#include <sstream>
#include <iostream>
#include "../utilities/Ray.hpp"
#include "../geometry/Geometry.hpp"
#include "../utilities/Constants.hpp"



BBox::BBox(const Point3D& min, const Point3D& max)
    : pmin(min)
    , pmax(max)
{}

// checking if ray hits the bounding box defined
bool BBox::hit(const Ray &ray, float &t_enter, float &t_exit) const{
    Point3D o(ray.o);
    Point3D d(ray.d.x, ray.d.y, ray.d.z); 
    Point3D t_min;
    Point3D t_max;

    double a = 1.0 / d.x;
    if(a >= 0){
        t_min.x = (pmin.x - o.x) * a;
        t_max.x = (pmax.x - o.x) * a; 
    }
    else{
        t_min.x = (pmax.x - o.x) * a;
        t_max.x = (pmin.x - o.x) * a;
    }
    double b = 1.0 / d.y;
    if(b >= 0){
        t_min.y = (pmin.y - o.y) * b;
        t_max.y = (pmax.y - o.y) * b; 
    }
    else{
        t_min.y = (pmax.y - o.y) * b;
        t_max.y = (pmin.y - o.y) * b;
    } 
    double c = 1.0 / d.z;
    if(c >= 0){
        t_min.z = (pmin.z - o.z) * c;
        t_max.z = (pmax.z - o.z) * c; 
    }
    else{
        t_min.z = (pmax.z - o.z) * c;
        t_max.z = (pmin.z - o.z) * c;
    }
    // finding largest
    if(t_min.x > t_min.y){
        t_enter = t_min.x;
    }
    else{
        t_enter = t_min.y;
    }
    if(t_min.z > t_enter){
        t_enter = t_min.z;
    }
    // find smallest
    if(t_max.x < t_max.y){
        t_exit = t_max.x;
    }
    else{
        t_exit = t_max.y;
    }
    if(t_max.z < t_exit){
        t_exit = t_max.z;
    }
    return (t_enter < t_exit && t_exit > kEpsilon);

}

std::string BBox::to_string() const {
    std::stringstream output;
    output << "pmin: " << pmin.to_string() << '\n';
    output << "pmax: " << pmax.to_string();
    return output.str();
}

// should be true even when p lies on boundary - check this
// checking if point lies inside the max and min points of bounding box
bool BBox::contains(const Point3D& p)  {
    return ((p.x > pmin.x && p.x < pmax.x) 
         && (p.y > pmin.y && p.y < pmax.y) 
         && (p.z > pmin.z && p.z < pmax.z));   
}

bool BBox::overlaps(Geometry* g) {
    BBox box = g->getBBox();
    return ((pmax.x > box.pmin.x) && (pmax.y > box.pmin.y) && (pmax.z > box.pmin.z));
}

bool BBox::overlaps(const BBox& b) {
    return ((pmax.x > b.pmin.x) && (pmax.y > b.pmin.y) && (pmax.z > b.pmin.z));
}


void BBox::extend(Geometry* g) {
    this->pmin = min(g->getBBox().pmin, pmin);
    this->pmax = max(g->getBBox().pmax, pmax);
}

void BBox::extend(const BBox& b) {
    this->pmin = min(b.pmin, pmin);
    this->pmax = max(b.pmax, pmax);
    //delta = pmax - pmin;
}

