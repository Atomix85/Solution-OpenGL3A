#pragma once

#include "Quaternion.h"

class Cube
{
private:
	float _x, _y, _z;
	GLfloat* coord;
public:
	Cube(float x, float y, float z, Quaternion rotation);
	void solidColoredCube();
	void draw();
	Quaternion rotation;
};

