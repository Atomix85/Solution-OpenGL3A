#pragma once
class Quaternion
{
private:
	double _a, _b, _c, _d;
public:
	Quaternion(double a, double b, double c, double d);
	Quaternion operator+(Quaternion const& other);
	bool operator==(Quaternion const& other);
	const double getA();
	const double getB();
	const double getC();
	const double getD();
	~Quaternion();
};

