#pragma once

#include <vector>
#include "../geometry/Geometry.hpp"
#include "../utilities/Point3D.hpp"
#include "../utilities/BBox.hpp"

/**
 * Octree node
 * 
 */
class OctreeNode {       
    public:
        /**
         * Constructs an empty node
         * 
         */
        OctreeNode();

        /**
         * Construct an empty node with an initial size
         * 
         * @param pmin Min coordinate of the Bbox node 
         * @param pmax Max coordinate of the Bbox node
         */
        OctreeNode(const Point3D &pmin, const Point3D &pmax);
        
        /**
         * Destroy the Octree Node object
         * 
         */
        ~OctreeNode();
        
        /**
         * Change the Bbox size of the node
         * 
         * @param geometry Geometry to resize too
         */
        void resizeNode(Geometry* geometry);

        /**
         * Release al the information hold by the node, delete it's children
         */
        void clearNode();

        /**
         * Node's has children?
         * 
         * @return true Has children
         * @return false Dosen't have children
         */
        bool hasChildren() const;

        // Nodes geometries
        std::vector<Geometry*> geometries;
        
        // Nodes array of children (8 children per node or none)
        OctreeNode *children;

        // Defines the node bounding box
        BBox boundingBox;
};
