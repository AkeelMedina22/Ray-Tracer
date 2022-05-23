#include "OctreeNode.hpp"

OctreeNode::OctreeNode():boundingBox() {
    this->children = nullptr;
}

OctreeNode::OctreeNode(const Point3D &pmin, const Point3D &pmax): boundingBox(pmin, pmax) { 
    this->children = nullptr;
}

OctreeNode::~OctreeNode() {
    this->clearNode();
}

void OctreeNode::clearNode() {   
    if(this->children != nullptr)
        delete [] this->children;

    this->geometries.clear();
}

void OctreeNode::resizeNode(Geometry *geometry) {
    this->boundingBox.extend(geometry);
}

bool OctreeNode::hasChildren() const {
    return this->children != nullptr;
}
