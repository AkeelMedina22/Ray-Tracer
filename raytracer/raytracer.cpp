#include <iostream>

#include "materials/Cosine.hpp"

#include "samplers/Sampler.hpp"

#include "utilities/Image.hpp"
#include "utilities/RGBColor.hpp"
#include "utilities/Ray.hpp"
#include "utilities/ShadeInfo.hpp"

#include "world/World.hpp"
#include "world/ViewPlane.hpp"
#include "tracer/Tracer.hpp"
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv) {
  srand (static_cast <unsigned> (time(0)));
  World world;
  world.build();

  Tracer* tracer = world.tracer_ptr;
  Sampler *sampler = world.sampler_ptr;
  ViewPlane &viewplane = world.vplane;
  Image image(viewplane);

  std::vector<Ray> rays;
  for (int x = 0; x < viewplane.hres; x++) {   // across.
    for (int y = 0; y < viewplane.vres; y++) { // down.
      // Get rays for the pixel from the sampler. The pixel color is the
      // weighted sum of the shades for each ray.
      RGBColor pixel_color(0);
      rays = sampler->get_rays(x, y);
      for (const auto &ray : rays) {
        // float weight = ray.w; // ray weight for the pixel.
        // ShadeInfo sinfo = world.hit_objects(ray);
        //pixel_color += weight * sinfo.material_ptr->shade(sinfo);
        pixel_color += tracer->trace_ray(ray, 0);
        //pixel_color += weight * world.bg_color;
    
      }
      // If Regular sampling, uncomment the line below. 
      // pixel_color /= sampler->get_num_rays();
      // Save color to image.
      image.set_pixel(x, y, pixel_color);
    }
  }
  // Write image to file.
  image.write_ppm("scene.ppm");

  std::cout << "Wrote image.\n";
  
  return 0;
}
