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

void
World::build(void) {
    // View plane  .
    vplane.top_left.x = -10;
    vplane.top_left.y = 10;
    vplane.top_left.z = 10;
    vplane.bottom_right.x = 10;
    vplane.bottom_right.y = -10;
    vplane.bottom_right.z = 10;
    vplane.hres = 1200;
    vplane.vres = 1200;
    vplane.set_maxdepth(12);

    // Background color.  
    bg_color = black;
    
    // Camera and sampler.
 
	set_camera(new Perspective(0, 0, 20));
    set_tracer(new whitted(this));
    sampler_ptr = new Simple(camera_ptr, &vplane);

    //Point
    Point* light_ptr = new Point;
    light_ptr->set_position(13, 16, 6);
    light_ptr->scale_radiance(2.0);
    light_ptr->set_shadows(true);
    add_light(light_ptr);

    // Ambient
    Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.5);
	set_ambient_light(ambient_ptr);

    //Directional
    Directional* dir_ptr = new Directional;
    dir_ptr->set_direction(13, 16, 6);
    dir_ptr->scale_radiance(2.0);
    dir_ptr->set_shadows(true);
    add_light(dir_ptr);
    

	Reflective* ref_ptr1 = new Reflective;
	ref_ptr1->set_ka(0.75);
	ref_ptr1->set_kd(0.75);
	ref_ptr1->set_cd(0.243, 0.018, 0.164);     	// red
	ref_ptr1->set_ks(0.1);
	ref_ptr1->set_exp(20.0);
	ref_ptr1->set_kr(1.0);

    Matte* matte_ptr3 = new Matte;
	matte_ptr3->set_ka(0.3);
	matte_ptr3->set_kd(0.6);
	matte_ptr3->set_cd(0, 1, 0);

    // sphere
    Sphere* sphere_ptr = new Sphere(Point3D(-3, 2, 0), 5); 
    sphere_ptr->set_material(ref_ptr1);
    add_geometry(sphere_ptr); 

    // plane
    Plane* plane_ptr = new Plane(Point3D(0,1,0), Vector3D(2, 8, 5)); 
    plane_ptr->set_material(ref_ptr1);  
    add_geometry(plane_ptr);
}
