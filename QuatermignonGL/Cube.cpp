#include "Cube.h"

Cube::Cube(float x, float y, float z, Quaternion rotation)
	: _x(x), _y(y), _z(z), _rotation(rotation)
{

}

void Cube::solidColoredCube()
{

	GLfloat coord[] =
	{
		-0.5,-0.5,-0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5,
		-0.5,0.5,-0.5,
		-0.5,-0.5,0.5,
		0.5,-0.5,0.5,
		0.5,0.5,0.5,
		-0.5,0.5,0.5
	};

	GLfloat color[6][3] =
	{
		{1.0,0.0,0.0},
		{0.0,1.0,0.0},
		{0.0,0.0,1.0},
		{0.0,1.0,1.0},
		{1.0,1.0,0.0},
		{1.0,0.0,1.0},
	};

	GLubyte num[6][4] =
	{ {0,1,2,3},
	{1,5,6,2},
	{4,5,6,7},
	{0,4,7,3},
	{0,1,5,4},
	{2,6,7,3}
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, coord);

	for (int x = 0; x != 6; x++)
	{
		glBegin(GL_QUADS);
		glColor3f(color[x][0], color[x][1], color[x][2]);        
		for (int i = 0; i != 4; ++i)
			glArrayElement(num[x][i]);
		glEnd();
	}

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

	this->solidColoredCube();

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
