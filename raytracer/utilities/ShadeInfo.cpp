#include "ShadeInfo.hpp"

ShadeInfo::ShadeInfo(const World& wr)
	: 	hit(false),
		hit_point(),
		material_ptr(NULL),
		normal(),
		w(&wr), // unsure since w is pointer in hpp
		ray(),
		depth(0),
		t(0)  // can try with t(kEpsilon)
{}

