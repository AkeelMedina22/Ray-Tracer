#include "Geometry.hpp"

Geometry::Geometry(){
    material_ptr = NULL;
	
}
void Geometry::set_material(Material* mPtr){
	if(material_ptr != NULL){
		material_ptr = NULL;
	}
	material_ptr = mPtr;
}

Material* Geometry::get_material() const{
	return material_ptr;
}



