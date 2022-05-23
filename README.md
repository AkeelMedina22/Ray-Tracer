# About the Project

This is the final project #2 from CS 440 Computer Graphics, offered at Habib University at Fall 2021.

It is a fully functional ray tracer built using C++, following the book Ray Tracing from the Ground Up by Kevin Suffern. The details are given through the accompanying website which is hosted at [Hanoi Unlock](https://hafsairfan.github.io/CG-Project-Website/). 

## Demo

<p align="middle">
  <img src="https://user-images.githubusercontent.com/56905673/169743094-1c72678e-22a0-4b8e-a093-02cf46dbfab5.png" width="300" caption="n=4" />
  <img src="https://user-images.githubusercontent.com/56905673/169743124-1c11f050-c642-4caf-b99d-8decd3dc6539.png" width="300"caption="n=6" /> 
</p>

## Instructions

Command to run: g++ raytracer.cpp world/World.cpp world/ViewPlane.cpp utilities/BBox.cpp utilities/Image.cpp utilities/Point3D.cpp utilities/Vector3D.cpp utilities/Ray.cpp utilities/RGBColor.cpp utilities/ShadeInfo.cpp samplers/Sampler.cpp samplers/Regular.cpp geometry/Geometry.cpp geometry/Plane.cpp geometry/Sphere.cpp geometry/Triangle.cpp cameras/Parallel.cpp cameras/Perspective.cpp materials/Cosine.cpp samplers/Simple.cpp samplers/random.cpp tracer/Basic.cpp tracer/Tracer.cpp materials/Matte.cpp materials/Phong.cpp materials/Reflective.cpp light/Ambient.cpp light/Directional.cpp light/Light.cpp light/Point.cpp light/Spotlight.cpp BRDF/GlossySpecular.cpp BRDF/Lambertian.cpp BRDF/PerfectSpecular.cpp tracer/whitted.cpp build/reflectiveChapter14.cpp

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

This project was done in a group of 4, from which the octree was done by my partners, Ammar and Jazib. The rest was divided between me and Hafsa Irfan, who has hosted the website.
