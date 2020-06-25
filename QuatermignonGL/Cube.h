#pragma once

#include "Quaternion.h"
#include <stdio.h>
#include <stdlib.h>
#include "shader.hpp"
#include "BMP.h"
#include <string>
#include "objloader.hpp"
#include "Vector.hpp"
#include <vector>

class Cube
{
private:
	float _x, _y, _z;
	float _rotB, _rotC, _rotD;
	float _theta;
	float _size;
	Quaternion _rotation;
	GLuint _texture;
	GLuint _shader;
	GLfloat* coord;
	GLfloat* modelviewMat;
	std::vector<vec3> out_vertices;
	std::vector<vec2> out_uvs;
	std::vector<vec3> out_normals;

public:
	Cube(float x, float y, float z, float rotb, float rotc, float rotd, float theta, float size, Quaternion rotation, std::string tex, std::string shader, std::string obj);
	~Cube();
	GLuint LoadTexture(const char* filename);
	void solidColoredCube();
	void draw(int repere);
	Quaternion rotation;
	void rotate(Quaternion);
	// -- GETTERS --
	GLfloat rotb() const;
	GLfloat rotc() const;
	GLfloat rotd() const;
	GLfloat thetha() const;
};

