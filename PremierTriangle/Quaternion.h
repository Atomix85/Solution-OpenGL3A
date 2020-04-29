#pragma once
class Quaternion
{
private:
	double _a, _b, _c, _d;
public:
	Quaternion(double a, double b, double c, double d);
	friend Quaternion operator+(Quaternion const& first, Quaternion const& second);
	friend bool operator==(Quaternion const& first, Quaternion const& second);
	const double getA();
	const double getB();
	const double getC();
	const double getD();
	~Quaternion();
};

