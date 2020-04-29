#include "Quaternion.h"

Quaternion::Quaternion(double a, double b, double c, double d)
	: _a(a), _b(b), _c(c), _d(d)
{
}
Quaternion operator+(const Quaternion& first,const Quaternion& second)
{
	return Quaternion(first._a + second._a,
		first._b + second._b,
		first._c + second._c,
		first._d + second._d);
}

bool operator==(Quaternion const& first, Quaternion const& second)
{
	return first._a == second._a && first._b == second._b
		&& first._c == second._c && first._d == second._d;
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
