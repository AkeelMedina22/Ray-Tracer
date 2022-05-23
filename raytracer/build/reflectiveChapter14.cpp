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
  vplane.top_left.x = -200;
  vplane.top_left.y = 200;
  vplane.top_left.z = 100;
  vplane.bottom_right.x = 200;
  vplane.bottom_right.y = -200;
  vplane.bottom_right.z = 100;
  vplane.hres = 2200;
  vplane.vres = 2200;
  vplane.set_maxdepth(200);
  
  bg_color = black;  // background color.
  
  // camera and sampler.
  set_camera(new Parallel(0, 0, -1));
  set_tracer(new whitted(this));
  sampler_ptr = new Simple(camera_ptr, &vplane);
	
  // colors
  RGBColor yellow(1, 1, 0);  // yellow
  RGBColor brown(0.71, 0.40, 0.16);  
  RGBColor darkGreen(0.0, 0.41, 0.41);  // darkGreen
  RGBColor orange(1, 0.75, 0);  // orange
  RGBColor green(0, 0.6, 0.3);  
  RGBColor lightGreen(0.65, 1, 0.30);  
  RGBColor darkYellow(0.61, 0.61, 0);  
  RGBColor lightPurple(0.65, 0.3, 1);  
  RGBColor darkPurple(0.5, 0, 1);  
  RGBColor grey(0.25);  // grey

    Ambient* ambient_ptr = new Ambient;
	ambient_ptr->scale_radiance(0.2);
	set_ambient_light(ambient_ptr);

    Directional* dir_ptr = new Directional;
    dir_ptr->set_direction(50, 50, 50);
    dir_ptr->scale_radiance(2.0);
    dir_ptr->set_shadows(true);
    add_light(dir_ptr);

	Reflective* ref_ptr1 = new Reflective;
	ref_ptr1->set_ka(0.75);
	ref_ptr1->set_kd(0.75);
	// ref_ptr1->set_cd(static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX), static_cast <float> (rand()) / static_cast <float> (RAND_MAX));   
 ref_ptr1->set_cd(0.243, 0.018, 0.164);   
	ref_ptr1->set_ks(0.1);
	ref_ptr1->set_exp(200.0);
	ref_ptr1->set_kr(1.0);
	
  // spheres
  Sphere* sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30); 
  sphere_ptr1->set_material(ref_ptr1);  
  add_geometry(sphere_ptr1);
    
  Sphere* sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20); 
  sphere_ptr2->set_material(ref_ptr1);  
  add_geometry(sphere_ptr2);
    
  Sphere* sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17); 
  sphere_ptr3->set_material(ref_ptr1); 
  add_geometry(sphere_ptr3);
    
  Sphere* sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20); 
  sphere_ptr4->set_material(ref_ptr1); 
  add_geometry(sphere_ptr4);
    
  Sphere* sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27); 			
  sphere_ptr5->set_material(ref_ptr1); 
  add_geometry(sphere_ptr5);
    
  Sphere* sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25); 
  sphere_ptr6->set_material(ref_ptr1); 
  add_geometry(sphere_ptr6);
    
  Sphere* sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22); 
  sphere_ptr7->set_material(ref_ptr1);  
  add_geometry(sphere_ptr7);
    
  Sphere* sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);  
  sphere_ptr8->set_material(ref_ptr1);  
  add_geometry(sphere_ptr8);
    
  Sphere* sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23); 
  sphere_ptr9->set_material(ref_ptr1);  
  add_geometry(sphere_ptr9);
    
  Sphere* sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22); 
  sphere_ptr10->set_material(ref_ptr1);  
  add_geometry(sphere_ptr10);
    
  Sphere* sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22); 
  sphere_ptr11->set_material(ref_ptr1);  
  add_geometry(sphere_ptr11);
    
  Sphere* sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22); 
  sphere_ptr12->set_material(ref_ptr1);  
  add_geometry(sphere_ptr12);
    
  Sphere* sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10); 
  sphere_ptr13->set_material(ref_ptr1); 
  add_geometry(sphere_ptr13);
    
  Sphere* sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18); 
  sphere_ptr14->set_material(ref_ptr1);  
  add_geometry(sphere_ptr14);
    
  Sphere* sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18); 
  sphere_ptr15->set_material(ref_ptr1);  
  add_geometry(sphere_ptr15);
    
  Sphere* sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10); 
  sphere_ptr16->set_material(ref_ptr1);  
  add_geometry(sphere_ptr16);
    
  Sphere* sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15); 		
  sphere_ptr17->set_material(ref_ptr1);  
  add_geometry(sphere_ptr17);
    
  Sphere* sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15); 
  sphere_ptr18->set_material(ref_ptr1);  
  add_geometry(sphere_ptr18);
    
  Sphere* sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17); 
  sphere_ptr19->set_material(ref_ptr1);  
  add_geometry(sphere_ptr19);
    
  Sphere* sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15); 
  sphere_ptr20->set_material(ref_ptr1);  
  add_geometry(sphere_ptr20);
    
  Sphere* sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10); 
  sphere_ptr21->set_material(ref_ptr1);  
  add_geometry(sphere_ptr21);
    
  Sphere* sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12); 
  sphere_ptr22->set_material(ref_ptr1);  
  add_geometry(sphere_ptr22);
    
  Sphere* sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13);
  sphere_ptr23->set_material(ref_ptr1);  
  add_geometry(sphere_ptr23);	
    
  Sphere* sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12); 
  sphere_ptr24->set_material(ref_ptr1);  
  add_geometry(sphere_ptr24);
    
  Sphere* sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11); 			
  sphere_ptr25->set_material(ref_ptr1);  
  add_geometry(sphere_ptr25);
    
  Sphere* sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12); 		
  sphere_ptr26->set_material(ref_ptr1);  
  add_geometry(sphere_ptr26);
    
  Sphere* sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12); 		
  sphere_ptr27->set_material(ref_ptr1);  
  add_geometry(sphere_ptr27);
    
  Sphere* sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15); 
  sphere_ptr28->set_material(ref_ptr1);  
  add_geometry(sphere_ptr28);
    
  Sphere* sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15); 
  sphere_ptr29->set_material(ref_ptr1);  
  add_geometry(sphere_ptr29);
    
  Sphere* sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);  
  sphere_ptr30->set_material(ref_ptr1);  
  add_geometry(sphere_ptr30);
    
  Sphere* sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12); 
  sphere_ptr31->set_material(ref_ptr1);  
  add_geometry(sphere_ptr31);
    
  Sphere* sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);   
  sphere_ptr32->set_material(ref_ptr1);  //  green
  add_geometry(sphere_ptr32);
    
  Sphere* sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11); 
  sphere_ptr33->set_material(ref_ptr1);   
  add_geometry(sphere_ptr33);
    
  Sphere* sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10); 	
  sphere_ptr34->set_material(ref_ptr1);  
  add_geometry(sphere_ptr34);
    
  Sphere* sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12); 
  sphere_ptr35->set_material(ref_ptr1);  
  add_geometry(sphere_ptr35);
	
}

