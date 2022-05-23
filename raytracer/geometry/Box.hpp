#pragma once

#include "Geometry.hpp"
#include "../utilities/Ray.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../utilities/Constants.hpp"
#include "../utilities/BBox.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/Vector3D.hpp"

class Box : public Geometry {
public:
    Box();
    Box(Point3D p0_, Point3D p1_);
    Box(const Box& box);
    
    // Destructor.
   virtual ~Box() = default;

    Box& operator= (Box& rhs);

    virtual bool hit(const Ray& ray, float& t, ShadeInfo& s) const override;
    virtual bool shadow_hit(const Ray& ray, float& tmin) const override;
    Vector3D get_Vector3D(const int face_hit) const;

    void set_p0(const Point3D p0_);
    Point3D get_p0() const;
    
    void set_p1(const Point3D p1_);
    Point3D get_p1() const;
    
    void set_dimensions(const Point3D dimensions_);
    Point3D get_dimensions() const;

    void set_dimension_x(const float width);
    void set_dimension_y(const float height);
    void set_dimension_z(const float depth);

    // String representation.
    std::string to_string() const override;

    // Get bounding box.
    virtual BBox getBBox() const override;

protected:
    Point3D p0;
    Point3D p1;
    Point3D dimensions;
};  