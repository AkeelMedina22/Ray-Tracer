#include "Octree.hpp"
#include <iostream>
#include <algorithm>

Octree::Octree(unsigned int maxObjectsPerChild, unsigned int maxDepthAllowed, std::vector<Geometry*> &scene): Acceleration(scene) {
    this->maxObjectsPerChild = maxObjectsPerChild;
    this->maxDepthAllowed= maxDepthAllowed;
    this->updateOctree(); // Builds the octree
}

ShadeInfo Octree::castLeaft(const Ray &ray, const OctreeNode &leaf, ShadeInfo &shadeInfo) const {
    float tmin = kHugeValue;
    Vector3D normal;
    Point3D local_hit;
    float t;

    /**
     * Same code as the basic ray cast use by the tracer
     * intersect with each geometry inside the leaf, and keeps the closest hit
     */ 
    for (auto i: leaf.geometries)
    {
        bool ray_intersection = i->hit(ray, t, shadeInfo);

        if (ray_intersection && shadeInfo.t < tmin)
        {
            tmin = shadeInfo.t;
            shadeInfo.material_ptr = i->get_material();
            shadeInfo.hit = true;
            normal = shadeInfo.normal;
            local_hit = shadeInfo.hit_point;
            
        }
    }

    if (shadeInfo.hit){
        shadeInfo.t = tmin;
        shadeInfo.normal = normal;
        shadeInfo.hit_point = local_hit;
    }

    return shadeInfo;
}

ShadeInfo Octree::castRay(const Ray &ray, const OctreeNode &currentNode, ShadeInfo &shadeInfo) const {
    float tEnter, tOut;

    // Computes the center of the node, will be use as the position of the tree planes that subdivides the node
    Point3D bbCenter = (currentNode.boundingBox.pmin + currentNode.boundingBox.pmax) * 0.5f;

    // Origing of the ray
    Point3D currentRayOrigin = ray.o;

    // If the current origin of the array its outside the node
    if(!currentNode.boundingBox.contains(currentRayOrigin)) {

        // Find the intersection point with the node
        bool rayIntersection = currentNode.boundingBox.hit(ray, tEnter, tOut);

        // If no intersection discard this node (octant) for testing
        if(!rayIntersection) {
            shadeInfo.hit = false;
            shadeInfo.t = kHugeValue;
            return shadeInfo;
        }

        // Moves the origing to the intersection point (inside the node)
        currentRayOrigin = ray.o + ray.d * tEnter;
    }

    // If the current node is a leaft, test the ray against the geometries it holds
    if(!currentNode.hasChildren())
       return this->castLeaft(ray, currentNode, shadeInfo);

    
    // Compute if the origin of the ray its at the right of the plane that divides the node in the X axis
    bool xPositive = currentRayOrigin.x - bbCenter.x >= 0;
    // Compute if the origin of the ray its at the top of the plane that divides the node in the Y axis
    bool yPositive = currentRayOrigin.y - bbCenter.y >= 0;
    // Compute if the origin of the ray its at the front of the plane that divides the node in the Z axis
    bool zPositive = currentRayOrigin.z - bbCenter.z >= 0;

    // Compute the distance of the origin to each plane, if the ray will never intersect the plane the distance is kHugeValue
    // to intercept the plane the direction of the ray must be the opposite to the position of the origin, relative to the evaluated plane
    double xDist = xPositive == ray.d.x < 0 ? (bbCenter.x - currentRayOrigin.x) / ray.d.x : kHugeValue;
    double yDist = yPositive == ray.d.y < 0 ? (bbCenter.y - currentRayOrigin.y) / ray.d.y : kHugeValue;
    double zDist = zPositive == ray.d.z < 0 ? (bbCenter.z - currentRayOrigin.z) / ray.d.z : kHugeValue;
    

    // 3 steps, to iterate between the 3 planes directions if no intersection its found
    for(unsigned int steps = 0; steps < 3; steps++) {
        // Finds the first hitted node position inside the tree
        unsigned int idx = (zPositive ? 1 : 0) | (yPositive ? 2 : 0) | (xPositive ? 4 : 0);

        // Cast the ray inside the first node hitted
        auto intersection = castRay(ray, currentNode.children[idx], shadeInfo);

        // If an intersection is found, this should be the closest one, we can finish
        if(intersection.hit) return intersection;

        // Otherwise, we compute the min distance to the next node intersected
        double minDist = std::min(std::min(xDist, yDist), zDist);

        // There is no other aviable node to intersect
        if(std::abs(minDist-kHugeValue) <= kEpsilon ) {
            shadeInfo.hit = false;
            shadeInfo.t = kHugeValue;
            return shadeInfo;
        }

        // Update the ray origin to the next node position
        currentRayOrigin = currentRayOrigin + ray.d * minDist;

        // If the origin it's outside the octree, no intersection found
        if(!this->root.boundingBox.contains(currentRayOrigin)) {
            shadeInfo.hit = false;
            shadeInfo.t = kHugeValue;
            return shadeInfo;
        }

        // Check witch plane is the closest one to the origin of the array (plane close to intersection)
        if(std::abs(minDist - xDist) <= kEpsilon) {
            // If it's the x plane, we where on the incorrect side of the plane, otherwise an intersection would occur
            xPositive = !xPositive;
            // We change the xDist to allow the evaluation of the next closest plane if no intersection occur
            xDist = kHugeValue;
        // Same if applied to each plane
        } else if(std::abs(minDist - yDist) <= kEpsilon) {
            yPositive = !yPositive;
            yDist = kHugeValue;
        } else if(std::abs(minDist - zDist) <= kEpsilon) {
            zPositive = !zPositive;
            zDist = kHugeValue;
        }
    }

    // No intersection found
    shadeInfo.hit = false;
    shadeInfo.t = kHugeValue;
    return shadeInfo;
}

// ShadeInfo Octree::hit_objects(const Ray &ray, const OctreeNode &currentNode, ShadeInfo &shadeInfo) const {
//     float tEnter, tOut;

//     bool rayIntersection = currentNode.boundingBox.hit(ray, tEnter, tOut);

//     if(!rayIntersection) return shadeInfo;

//      if(rayIntersection && !currentNode.hasChildren()) 
//         return this->hit_geometry(ray, currentNode, shadeInfo);
     

//     ShadeInfo finalShadeInfo(shadeInfo);
//     finalShadeInfo.t = kHugeValue;

//     Naive octree transverse, intersects the ray with all the children of the current node   
//     for(unsigned int index = 0; index < 8; index++) {
//         shadeInfo = this->hit_objects(ray, currentNode.children[index], shadeInfo);

//         if(shadeInfo.t < finalShadeInfo.t) 
//             finalShadeInfo = shadeInfo;
//     }

//     return finalShadeInfo;
// }

ShadeInfo Octree::hitObjects(const Ray &ray, ShadeInfo &shadeInfo) const {
    shadeInfo.t = kHugeValue;
    shadeInfo.hit = false;
    // Cast the ray inside the octree
    return this->castRay(ray, this->root, shadeInfo);
}


void Octree::updateOctree() {
    this->root.clearNode();

    // Set the size of the root node so it covers the whole scene
    for(auto geometry:scene) 
        this->root.resizeNode(geometry);
    

    // Adds each geometry to the octree
    for(auto geometry:scene) 
            this->addGeometry(this->root, 0, geometry);
    
}

void Octree::addGeometry(OctreeNode &currentNode, unsigned int currentDepth, Geometry* geometry) 
{
    // No geometry to add
    if(geometry == nullptr) return;

    // Node capacity exceded, subdivide the node
    if(currentNode.geometries.size() + 1 > this->maxObjectsPerChild && !currentNode.hasChildren() && currentDepth < this->maxDepthAllowed)
        this->buildChildren(currentNode, currentDepth);
        

    // Add the geometry to the current node beacuse it dosen't have children
    if(!currentNode.hasChildren()) {
        currentNode.geometries.push_back(geometry);
        return;
    }

    // Adds the geometry to the correct node child
    addToChildren(currentNode, currentDepth, geometry);
}

void Octree::addToChildren(OctreeNode &currentNode, unsigned int currentDepth, Geometry* geometry) {
    BBox bbox = geometry->getBBox();

    for(int index = 0; index < 8; index++ ) {
        // If the geometry intersects the node, it should be inside this node (this will duplicate the same geometry in many nodes)
        if(bbox.intersects(currentNode.children[index].boundingBox))
            this->addGeometry(currentNode.children[index], currentDepth + 1, geometry);
    }
}

void Octree::buildChildren(OctreeNode &currentNode, unsigned int currentDepth) {
    const Point3D pmin(currentNode.boundingBox.pmin);
    const Point3D pmax(currentNode.boundingBox.pmax);
    const Point3D pmid(
        (pmin.x + pmax.x) / 2.0f,
        (pmin.y + pmax.y) / 2.0f,
        (pmin.z + pmax.z) / 2.0f
    );

    currentNode.children = new OctreeNode[8] {
        // Left-Bottom-Back [0,0,0] => 0
        OctreeNode(pmin, pmid), 
        // Left-Bottom-Front [0,0,1] => 1
        OctreeNode(Point3D(pmin.x, pmin.y, pmid.z), Point3D(pmid.x, pmid.y, pmax.z)), 
        // Left-Top-Back [0,1,0] => 2
        OctreeNode(Point3D(pmin.x, pmid.y, pmin.z), Point3D(pmid.x, pmax.y, pmid.z)), 
        // Left-Top-Font [0,1,1] => 3
        OctreeNode(Point3D(pmin.x, pmid.y, pmid.z), Point3D(pmid.x, pmax.y, pmax.z)),
        // Right-Bottom-Back [1,0,0] => 4
        OctreeNode(Point3D(pmid.x, pmin.y, pmin.z), Point3D(pmax.x, pmid.y, pmid.z)),
        // Right-Bottom-Front [1,0,1] => 5
        OctreeNode(Point3D(pmid.x, pmin.y, pmid.z), Point3D(pmax.x, pmid.y, pmax.z)),
        // Right-Top-Back [1,1,0] => 6
        OctreeNode(Point3D(pmid.x, pmid.y, pmin.z), Point3D(pmax.x, pmax.y, pmid.z)),
        // Right-Top-Front [1,1,1] => 7
        OctreeNode(pmid, pmax)
    };

    // Store the geometry into the new childrens
    for(auto geometry:currentNode.geometries)
        addToChildren(currentNode, currentDepth, geometry);

    // Clears the geometries from the current node, as they are inside the childs now
    currentNode.geometries.clear();
}
