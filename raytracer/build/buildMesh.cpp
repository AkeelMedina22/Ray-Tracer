#include "../world/ViewPlane.hpp"
#include "../world/World.hpp"

#include "../utilities/RGBColor.hpp"
#include "../geometry/Geometry.hpp"
#include "../samplers/Sampler.hpp"
#include "../utilities/ShadeInfo.hpp"

#include "../cameras/Perspective.hpp"
#include "../cameras/Parallel.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"
#include "../materials/Reflective.hpp"

#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"

#include "../utilities/Constants.hpp"
#include "../utilities/Point3D.hpp"
#include "../light/Ambient.hpp"
#include "../light/Directional.hpp"
#include "../light/Point.hpp"


void World::build(void) {
  // view plane
  vplane.top_left = Point3D(-1, 1, 2);
  vplane.bottom_right = Point3D(1, -1, 2);
  vplane.hres = 800;
  vplane.vres = 800;
  vplane.set_maxdepth(12);

  // Background color.
  RGBColor grey(0.3, 0.35, 0.3);
  bg_color = grey;

  // camera and sampler.
  set_camera(new Perspective(0, 0, 10));
  set_tracer(new whitted(this));
  sampler_ptr = new Simple(camera_ptr, &vplane);

  Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.2);
	set_ambient_light(ambient_ptr);

    Directional* dir_ptr = new Directional;
    dir_ptr->set_direction(0, 0, 400);
    dir_ptr->scale_radiance(2.0);
    dir_ptr->set_shadows(true);
    add_light(dir_ptr);

    Reflective* ref_ptr1 = new Reflective;
	ref_ptr1->set_ka(0.75);
	ref_ptr1->set_kd(0.75);
	ref_ptr1->set_cd(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));     
	ref_ptr1->set_ks(0.1);
	ref_ptr1->set_exp(200.0);
	ref_ptr1->set_kr(1.0);

  //load mesh
  addOBJ("monke.obj", ref_ptr1);
}