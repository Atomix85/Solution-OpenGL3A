#include "Quaternion.h"
#include <iostream>
using namespace std;

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
	_angle = q.a();
	_axis = (GLfloat*)malloc(3 * sizeof(GLfloat));
	if (!_axis) throw ("Unable to allocate memory");
	else {
		_axis[0] = q.b();
		_axis[1] = q.c();
		_axis[2] = q.d();
	}
}

Quaternion::~Quaternion()
{
	delete[] _axis;
}

bool Quaternion::operator==(Quaternion const& q)
{
	return this->a() == q.a() &&
		   this->b() == q.b() &&
		   this->c() == q.c() &&
		   this->d() == q.d();
}

Quaternion& Quaternion::operator=(const Quaternion& q)
{
	if (this == &q) return *this;
	this->_angle   = q.a();
	this->_axis[0] = q.b();
	this->_axis[1] = q.c();
	this->_axis[2] = q.d();
	return *this;
}

Quaternion Quaternion::operator+(Quaternion const& q)
{
	return Quaternion(q.a() + this->a(),
					  q.b() + this->b(),
					  q.c() + this->c(),
					  q.d() + this->d());
}

Quaternion Quaternion::operator-(Quaternion const& q)
{
	return Quaternion(this->a() - q.a(),
		              this->b() - q.b(),
					  this->c() - q.c(),
		              this->d() - q.d());
}

Quaternion Quaternion::operator*(Quaternion const& q)
{
	return Quaternion(this->a() * q.a() - this->b() * q.b() - this->c() * q.c() - this->d() * q.d(),
					  this->a() * q.b() + q.a() * this->b() + this->c() * q.d() - q.c() * this->d(),
					  this->a() * q.c() + q.a() * this->c() + q.b() * this->d() - this->b() * q.d(),
					  this->a() * q.d() + q.a() * this->d() + this->b() * q.c() - q.b() * this->c()
				      );
}



Quaternion Quaternion::operator+=(Quaternion const& q)
{
	*this = *this + q;
	return *this;
}

Quaternion Quaternion::operator-=(Quaternion const& q)
{
	
	*this = *this - q;
	return *this;
}

Quaternion Quaternion::operator*=(Quaternion const& q)
{
	*this = *this * q;
	return *this;
}

GLfloat Quaternion::a() const
{
	return _angle;
}

GLfloat Quaternion::b() const
{
	return _axis[0];
}

GLfloat Quaternion::c() const
{
	return _axis[1];
}

GLfloat Quaternion::d() const
{
	return _axis[2];
}

std::ostream& operator<<(std::ostream& os, Quaternion const& q)
{
	os << "(" << q.a() << "," << q.b() << "," << q.c() << "," << q.d() << ")";
	os << endl;
	return os;
}

int main() {
	printf("\n======== TEST QUATERNION OVERLOADED OPERATORS ========\n\n");
	printf("\n-- empty constructor\n\n");
	Quaternion q0;
	cout << "q0 = " << q0 << "\n";
	printf("\n-- parameters constructor\n\n");
	Quaternion q1(60.5, 1.0, 0.0, 0.0);
	cout << "q1 = " << q1 << "\n";
	printf("\n-- copy constructor\n\n");
	Quaternion q2(q1);
	cout << "q2 = " << q2 << "\n";
	printf("\n-- destructor\n\n");
	Quaternion* q = new Quaternion(15,0,1,0);
	cout << "A dynamically allocated quaternion : \n Q = " << *q << "\n";
	delete q;
	printf("The quaternion Q has been successfully freed.\n"
		    "Look how the Q.a() value is making bullshit as it's expected now :  %d\n", q->a());
	printf("\n-- operator==\n\n");
	printf("q1 == q2 ? : %s\n", q1 == q2 ? "true" : "false");
	printf("q0 == q2 ? : %s\n", q0 == q2 ? "true" : "false");
	printf("\n-- operator + and -\n\n");
	cout << "q1+q2 = " << q1 + q2 << "\n";
	cout << "q1-q2 = " << q1 - q2 << "\n";
	cout << "q0-q2 = " << q0 - q2 << "\n";
	printf("\n-- operator += and -=\n\n");
	q1 += q1;
	cout << "after q1+=q1 we got q1 = " << q1 << "\n";
	q1 -= q2;
	cout << "after q1-=q2 we got q1 = " << q1 << "\n";
	printf("\n-- operator *\n\n");
	Quaternion q3(0,1,0,0);
	Quaternion q4(0,0,1,0);
	Quaternion e(1,0,0,0);
	cout << "q3 = " << q3 << "q4 = " << q4 <<"\n neutral element : e ="<< e <<"\n absorbent element o = " << q0 <<"\n";
	cout << "q3*q4 = " << q3 * q4 << "\n";
	cout << "q4*q3 = " << q4 * q3 << "\n";
	cout << "q4*e = " <<  q4 * e << "\n";
	cout << "e*q4 = " <<  e  * q4 << "\n";
	cout << "o*q4 = " <<  q0 * q4 << "\n";
	cout << "q4*o = " <<  q4 * q0 << "\n";

	return 0;
}

