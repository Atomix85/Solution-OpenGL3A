#pragma once
#ifndef __QUAT_H__
#define __QUAT_H__
#include "common.h"
#include <iostream>

class Quaternion
{
private:
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

	bool operator==(Quaternion const&);
	bool operator!=(Quaternion const&);
	Quaternion& operator=(const Quaternion&);

	Quaternion operator+(Quaternion const&);
	Quaternion operator-(Quaternion const&);
	Quaternion operator*(Quaternion const&);
	Quaternion operator/(Quaternion const&);

	Quaternion operator+=(Quaternion const&);
	Quaternion operator-=(Quaternion const&);
	Quaternion operator*=(Quaternion const&);
	Quaternion operator/=(Quaternion const&);

	// scalar product
	friend Quaternion operator* (GLfloat scalar, Quaternion const&);
	friend Quaternion operator* (Quaternion const& ,GLfloat scalar);
	//friend Quaternion operator*= (GLfloat scalar, Quaternion const&);

	// c out and c in
	friend std::ostream& operator<<(std::ostream&, Quaternion const& );
	//friend std::istream& operator>>(std::istream&, Quaternion &);

	// -- GETTERS --
	GLfloat a() const;
	GLfloat b() const;
	GLfloat c() const;
	GLfloat d() const;

	// -- OTHER MATHS OPERATIONS --

	Quaternion conjugate();
	GLfloat norm() const;
	void normalize();
	Quaternion matrix2Quaternion(GLfloat* const&);
	GLfloat* quaternion2Matrix();
};

#endif