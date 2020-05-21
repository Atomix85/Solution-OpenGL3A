#include "Cube.h"

Cube::Cube(float x, float y, float z, Quaternion rotation)
	: _x(x), _y(y), _z(z), _rotation(rotation)
{

}

void Cube::draw()
{
	GLfloat* matrix;
	GLfloat matrixIdentity[] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	glPushMatrix();
	//glLoadIdentity();
	matrix = _rotation.quaternion2Matrix();

	glLoadMatrixf(matrix);
	glMultMatrixf(matrixIdentity);

	free(matrix);

	glutSolidCube(1.0f);
	glPopMatrix();

}
