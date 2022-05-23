#include "whitted.hpp"
#include <iostream>
#include "../world/World.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../materials/Material.hpp"

whitted::whitted() {
    this->world_ptr = nullptr;
}

whitted::whitted(World* w_ptr) {
    this->world_ptr = w_ptr;
}

RGBColor whitted::trace_ray(const Ray ray, const int depth) const {
    if (depth > world_ptr->vplane.max_depth) {
        return black;
    } else {
		ShadeInfo si(world_ptr->hit_objects(ray));

		if (si.hit) {
			si.depth = depth;
			si.ray = ray;
			return (si.material_ptr->shade(si));
		} else
			return (world_ptr->bg_color);
	}
}