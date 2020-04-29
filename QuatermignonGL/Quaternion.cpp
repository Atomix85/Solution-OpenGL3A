#include "Quaternion.h"

Quaternion::Quaternion()
{
	_angle = 0.0;
	_axis = (GLfloat*) calloc(3,sizeof(GLfloat));
	if (!_axis) throw ("Unable to allocate memory");
}

Quaternion::Quaternion(GLfloat a, GLfloat b, GLfloat c, GLfloat d)
{
	_angle = a;
	_axis = (GLfloat*) malloc(3*sizeof(GLfloat));
	if (!_axis) throw ("Unable to allocate memory");
	else {
		_axis[0] = b;
		_axis[1] = c;
		_axis[2] = d;
	}
}

Quaternion::Quaternion(Quaternion const& q)
{
	_angle = q.a;
	_axis = (GLfloat*)malloc(3 * sizeof(GLfloat));
	if (!_axis) throw ("Unable to allocate memory");
	else {
		_axis[0] = q.b;
		_axis[1] = q.c;
		_axis[2] = q.d;
	}


}

Quaternion::~Quaternion()
{
	delete[] _axis;
}
