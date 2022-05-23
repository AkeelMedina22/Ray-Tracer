/**
   This builds a simple scene that consists of a sphere, and a
   plane.
   Perspective viewing is used with a single sample per pixel.
*/

#include "../cameras/Perspective.hpp"

#include "../geometry/Plane.hpp"
#include "../geometry/Sphere.hpp"
#include "../geometry/Triangle.hpp"

#include "../materials/Cosine.hpp"
#include "../materials/Matte.hpp"


#include "../samplers/Simple.hpp"
#include "../samplers/Regular.hpp"

#include "../utilities/Constants.hpp"

#include "../light/Ambient.hpp"
#include "../light/Directional.hpp"
#include "../light/Point.hpp"
#include "../light/Spotlight.hpp"


#include "../tracer/Basic.hpp"
#include "../world/World.hpp"



void
World::build(void) {
    // View plane  .
    vplane.top_left.x = -10;
    vplane.top_left.y = 10;
    vplane.top_left.z = 10;
    vplane.bottom_right.x = 10;
    vplane.bottom_right.y = -10;
    vplane.bottom_right.z = 10;
    vplane.hres = 400;
    vplane.vres = 400;

    // Background color.  
    bg_color = black;
    
    // Camera and sampler.
 
	set_camera(new Perspective(0, 0, 20));
    set_tracer(new Basic(this));
    sampler_ptr = new Simple(camera_ptr, &vplane);

    //Point
    Point* light_ptr = new Point;
    light_ptr->set_position(13, 16, 6);
    light_ptr->scale_radiance(2.0);
    light_ptr->set_shadows(true);
    add_light(light_ptr);

    // Ambient
    // Ambient* ambient_ptr = new Ambient;
	// ambient_ptr->scale_radiance(0.5);
	// set_ambient_light(ambient_ptr);

    //Directional
    // Directional* dir_ptr = new Directional;
    // dir_ptr->set_direction(13, 16, 6);
    // dir_ptr->scale_radiance(2.0);
    // dir_ptr->set_shadows(true);
    // add_light(dir_ptr);
    

    // Spotlight
    // Spotlight* spotlight_ptr = new Spotlight;
    // spotlight_ptr->scale_radiance(2.0);
    // spotlight_ptr->set_theta(4.0);
    // spotlight_ptr->set_direction(13,10,6);
    // spotlight_ptr->set_shadows(true);
    // add_light(spotlight_ptr);


    //Materials and Spheres
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->set_ka(0.25);
	matte_ptr1->set_kd(0.65);
	matte_ptr1->set_cd(1, 0, 0);


    // sphere
    Sphere* sphere_ptr = new Sphere(Point3D(-3, 2, 0), 5); 
    sphere_ptr->set_material(matte_ptr1);
  
    add_geometry(sphere_ptr); 

    Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.3);
	matte_ptr3->set_kd(0.6);
	matte_ptr3->set_cd(0, 1, 0);
    // plane
    Plane* plane_ptr = new Plane(Point3D(0,1,0), Vector3D(0, 10, 2)); 
    plane_ptr->set_material(matte_ptr3);  // green
    add_geometry(plane_ptr);
}