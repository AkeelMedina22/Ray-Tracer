#pragma once

#include "Acceleration.hpp"
#include "OctreeNode.hpp"
#include "../utilities/ShadeInfo.hpp"

/**
 * 8 children space partition tree
 * 
 */
class Octree: public Acceleration {

    private: 
        // Maximun amount of objects to be hold by a single node of tree (when this limit is overflowed the node is subdivided)
        unsigned int maxObjectsPerChild;

        // Maximun depth of the tree (if reached the leaft will not be subdivided even if the max object allowed its overflowed)
        unsigned int maxDepthAllowed;

        // Root of the tree
        OctreeNode root;

        /**
         * Recursively finds the correct node to add the given geometry to the tree
         * 
         * @param currentNode Current node where the geometry will be added
         * @param currentDepth Current depth of the node inside the tree
         * @param geometry Geometry to be added inside the tree
         */
        void addGeometry(OctreeNode &currentNode, unsigned int currentDepth, Geometry* geometry);

        /**
         * Checks if the geometry intersects any of the node's children and adds it to them
         * 
         * @param currenNode Parent of the nodes to be tested
         * @param currentDepth Current Parent node's depth inside the tree
         * @param geometry Geometry to be added to the tree
         */
        void addToChildren(OctreeNode &currenNode, unsigned int currentDepth, Geometry *geometry);

        /**
         * Builds the childrens of the given node spreading its contained geometries ammong them
         * 
         * @param currentNode Node whos children will be created
         * @param currentDepth Current depth of the node inside the tree
         */
        void buildChildren(OctreeNode &currentNode, unsigned int currentDepth);

        /**
         * Recursively cast a ray through the nodes of the tree
         * 
         * @param ray Ray to be cast
         * @param currentNode Node to cast the ray through
         * @param shadeInfo Initial hit information
         * @return ShadeInfo Hit information
         */
        ShadeInfo castRay(const Ray &ray, const OctreeNode &currentNode, ShadeInfo &shadeInfo) const;

        /**
         * Cast a ray through the geometries contained by a leaf node
         * 
         * @param ray Ray to be cast
         * @param leaf Leaf node
         * @param ShadeInfo Initial hit information
         * @return ShadeInfo Hit infomration
         */
        ShadeInfo castLeaft(const Ray &ray, const OctreeNode &leaf, ShadeInfo &ShadeInfo) const;
    public:

        /**
         * Construct a new Octree object
         * 
         * @param maxObjectsPerChild Max number of objects allowed inside a leaf node before subdiving it
         * @param maxDepthAllowed Max depth of the tree
         * @param scene Geometries to be hold by the structure
         */
        Octree(unsigned int maxObjectsPerChild, unsigned int maxDepthAllowed, std::vector<Geometry*> &scene);

        /**
         * @brief Cast ray through the scene
         * 
         * @param ray Ray to be cast
         * @param shadeInfo Initial Hit information
         * @return ShadeInfo Hit information
         */
        ShadeInfo hitObjects(const Ray &ray, ShadeInfo &shadeInfo) const;
        
        /**
         * Builds the Octree
         */
        void updateOctree();
};
