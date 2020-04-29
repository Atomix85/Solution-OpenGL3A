#include "Quaternion.h"

Quaternion::Quaternion(double a, double b, double c, double d)
	: _a(a), _b(b), _c(c), _d(d)
{
}
Quaternion Quaternion::operator+(const Quaternion& other)
{
	return Quaternion(other._a + this->_a,
		other._b + this->_b,
		other._c + this->_c,
		other._d + this->_d);
}

bool Quaternion::operator==(Quaternion const& other)
{
	return other._a == this->_a && other._b == this->_b
		&& other._c == this->_c && other._d == this->_d;
}

const double Quaternion::getA() {
	return _a;
}
const double Quaternion::getB() {
	return _b;
}
const double Quaternion::getC() {
	return _c;
}
const double Quaternion::getD() {
	return _d;
}

Quaternion::~Quaternion()
{
}
