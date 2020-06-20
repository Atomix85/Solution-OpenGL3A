#pragma once

#include "Quaternion.h"
#include <stdio.h>
#include <stdlib.h>
#include "shader.hpp"
#include "BMP.h"
#include <string>

class Cube
{
private:
	float _x, _y, _z;
	float _size;
	Quaternion _rotation;
	GLuint _texture;
	GLuint _shader;
	unsigned int vaoID[1];
	unsigned int vboID[1];
	GLfloat* coord;
public:
	Cube(float x, float y, float z, float size, Quaternion rotation, std::string tex, std::string shader);
	GLuint LoadTexture(const char* filename);
	void solidColoredCube();
	void draw(int repere);
	Quaternion rotation;
};

