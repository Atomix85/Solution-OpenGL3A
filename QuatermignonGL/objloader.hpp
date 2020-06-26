#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <iostream>
#include <vector>
#include "Vector.hpp"

bool loadOBJ(
	const char * path, 
	
	std::vector<vec3> & out_vertices, 
	std::vector<vec2> & out_uvs, 
	std::vector<vec3> & out_normals
);

#endif