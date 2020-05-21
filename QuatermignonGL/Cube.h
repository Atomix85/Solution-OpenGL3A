#pragma once

#include "Quaternion.h"

class Cube
{
private:
	float _x, _y, _z;
	Quaternion _rotation;
public:
	Cube(float x, float y, float z, Quaternion rotation);
	void solidColoredCube();
	void draw();
};

