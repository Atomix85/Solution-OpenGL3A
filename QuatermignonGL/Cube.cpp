#include "Cube.h"

Cube::Cube(float x, float y, float z, Quaternion rotation)
	: _x(x), _y(y), _z(z), _rotation(rotation)
{

}

void Cube::draw()
{
	GLfloat* matrix;
	//GLfloat matrixIdentity[] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
	glPushMatrix();
	//glLoadIdentity();
	matrix = _rotation.quaternion2Matrix();

	glMultMatrixf(matrix);
	//glMultMatrixf(matrixIdentity);

	free(matrix);

	glutSolidCube(1.0f);

	//HELPER
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(2, 0, 0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 2, 0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 2);
	glEnd();

	glPopMatrix();

}
