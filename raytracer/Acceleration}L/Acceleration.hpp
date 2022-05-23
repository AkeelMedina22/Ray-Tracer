#pragma once

#include <vector>
#include "../geometry/Geometry.hpp"

/**
 * Base Acceleration class, to be implemented by any acceleration structure
 * 
 */
class Acceleration {
    protected: 
        std::vector<Geometry *> &scene; // Holds all the geometry proccesed by the acceleration structure

    public: 
        /**
         * Construct a new Acceleration object
         * 
         * @param scene Geometry that compounds the scene
         */
        Acceleration(std::vector<Geometry*> &scene);

        /**
         * Cast a ray throught  the acceleration structure and returns the hit information
         * 
         * @param ray Ray to be cast
         * @param shadeInfo Initial shade information (just a pointer to allow the creation of another ShadeInfo)
         * @return ShadeInfo Hit information
         */
        ShadeInfo virtual hitObjects(const Ray &ray, ShadeInfo &shadeInfo) const = 0; // Cast a ray throught the acceleration structure an
};
