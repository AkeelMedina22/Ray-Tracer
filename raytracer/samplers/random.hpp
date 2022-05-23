#pragma once

/**
   This file declares the random class which represents a random sampler.

   It shoots a single ray of weight 1 through a pixel.

   Courtesy Kevin Suffern.
*/

#include "Sampler.hpp"

class random : public Sampler {
protected:
  // add members to cache values to avoid recomputation in get_rays().

public:
  // Constructors.
  random() = default;                      // initializes members to NULL.
  random(Camera *c_ptr, ViewPlane *v_ptr); // set members.

  // Copy constuctor and assignment operator.
  random(const random &camera);
  random &operator=(const random &other);

  // Desctructor.
  virtual ~random() = default;

  // Shoot a ray of weight 1 through the center of the pixel.
  std::vector<Ray> get_rays(int px, int py) const override;
};
