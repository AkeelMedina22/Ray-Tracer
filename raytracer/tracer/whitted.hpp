#pragma once

/** Whitted Tracer - Updates depth in ShadeInfo
    Courtesy Kevin Suffern
**/

#include "Tracer.hpp"

class whitted : public Tracer {
    public:
        whitted();
        whitted(World* w_ptr);

        virtual ~whitted() = default;

        virtual RGBColor trace_ray(const Ray ray, const int depth) const;
};