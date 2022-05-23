#include "World.hpp"
#include <iostream>
#include <cstring>
#include <fstream>

World::World()
{
    vplane = ViewPlane();
    bg_color = RGBColor();
    ambient_ptr = new Ambient;
    camera_ptr = nullptr;
    sampler_ptr = nullptr;
    tracer_ptr = nullptr;
}


World::~World()
{
    for (auto i: geometry)
    {
        delete i;
    }
     for (auto i: lights)
    {
        delete i;
    }

    delete camera_ptr;
    delete sampler_ptr;
    delete ambient_ptr;
    delete tracer_ptr;

}

void World::add_geometry(Geometry *geom_ptr)
{
    this->geometry.push_back(geom_ptr);
}

void World::add_light(Light* light_ptr)
{
    lights.push_back(light_ptr);
}
void World::set_camera(Camera *c_ptr)
{
    this->camera_ptr = c_ptr;
}

void World::set_tracer(Tracer* t_ptr)
{
    tracer_ptr = t_ptr;
}
void World::set_ambient_light(Ambient* amb_ptr)
{
    if (ambient_ptr){
        delete ambient_ptr;
    }
    ambient_ptr = amb_ptr->clone();
}

ShadeInfo World::hit_objects(const Ray &ray)
{
    float tmin = kHugeValue;
    ShadeInfo s(*this);
    Vector3D normal;
    Point3D local_hit;
    float t;

    for (auto i: geometry)
    {
        bool ray_intersection = i->hit(ray, t, s);

        if (ray_intersection && t < tmin)
        {
            tmin = t;
            //std::cout << object_shade.hit << "\n";
            s.material_ptr = i->get_material();
            s.hit = true;
            normal = s.normal;
            local_hit = s.hit_point;
            
        }
    }

    if (s.hit){
        s.t = tmin;
        s.normal = normal;
        s.hit_point = local_hit;
    }

    return s;
}

void World::addOBJ(const char *path, Material *mPtr)
{
    std::vector<uint64_t> vertex_indices, normal_indices;
    std::vector<Point3D> vertices;
    std::vector<Vector3D> normals;

    FILE *file = fopen(path, "r");

    if (file == NULL)
    {
        std::cout << "Cannot open file " << path << "\n";
        return;
    }

    while (1)
    {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;

        if (strcmp(lineHeader, "v") == 0)
        {
            Point3D vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            Vector3D normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string v1, v2, v3;
            int vertexIndex[3], normalIndex[3];
            fscanf(file, "%d/%*d/%d %d/%*d/%d %d/%*d/%d\n", &vertexIndex[0],
                   &normalIndex[0], &vertexIndex[1], &normalIndex[1],
                   &vertexIndex[2], &normalIndex[2]);
            vertex_indices.push_back(vertexIndex[0]);
            vertex_indices.push_back(vertexIndex[1]);
            vertex_indices.push_back(vertexIndex[2]);

            normal_indices.push_back(normalIndex[0]);
            normal_indices.push_back(normalIndex[1]);
            normal_indices.push_back(normalIndex[2]);
        }
    }

    // now we have four arrays 1) Vertices 2) Normals 3) Vertex Indices 4) Normal Indices
    // to get faces we need to iterate over vertex indices and normal indices and create triangles
    for (int i = 0; i < vertex_indices.size(); i += 3)
    {
        Triangle *triangle = new Triangle(vertices[vertex_indices[i] - 1],
                                          vertices[vertex_indices[i + 1] - 1],
                                          vertices[vertex_indices[i + 2] - 1]);
        triangle->set_material(mPtr);
        // triangle->set_normal(normals[normal_indices[i] - 1],
        //                      normals[normal_indices[i + 1] - 1],
        //                      normals[normal_indices[i + 2] - 1]);
        add_geometry(triangle);
    }
}

