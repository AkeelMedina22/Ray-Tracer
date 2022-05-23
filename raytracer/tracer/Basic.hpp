#pragma once

/**
    This class implements the basic ray tracer.
**/

#include "Tracer.hpp"

class World;
class RGBColor;

class Basic : public Tracer{
    public:
        Basic();
        Basic(World* w_ptr);
        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
        virtual ~Basic() = default;
};
