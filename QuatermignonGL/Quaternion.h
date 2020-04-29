#pragma once
#include "common.h"

class Quaternion
{
private:
	GLfloat _angle;
	GLfloat*_axis;
public:
	// -- CONSTRUCTORS & DESTRUCTORS --
	// empty constructor
	Quaternion();
	// constructor with parameters
	Quaternion(GLfloat a, GLfloat b, GLfloat c, GLfloat d);
	// deep copy constructor
	Quaternion(Quaternion const& copy);
	// destructor
	~Quaternion();

	// -- OVERLOADED OPERATORS --
	bool operator==(Quaternion const& other);
	Quaternion operator+(Quaternion const& other);
	Quaternion operator-(Quaternion const& other);
	Quaternion operator*(Quaternion const& other);
	Quaternion operator/(Quaternion const& other);
	Quaternion operator+=(Quaternion const& other);
	Quaternion operator-=(Quaternion const& other);
	Quaternion operator*=(Quaternion const& other);
	Quaternion operator/=(Quaternion const& other);

	// -- OTHERS --
	const double getA();
	const double getB();
	const double getC();
	const double getD();
	~Quaternion();
};

