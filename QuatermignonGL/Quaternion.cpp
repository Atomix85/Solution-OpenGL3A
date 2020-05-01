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

Quaternion Quaternion::operator+(Quaternion const& q)
{
	return Quaternion(q.a() + this->a(),
					  q.b() + this->b(),
					  q.c() + this->c(),
					  q.d() + this->d());
}

Quaternion Quaternion::operator-(Quaternion const& q)
{
	return Quaternion(q.a() - this->a(),
					  q.b() - this->b(),
					  q.c() - this->c(),
					  q.d() - this->d());
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

int main() {
	printf("\n======== TEST QUATERNION ========\n\n");
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
		    "See the a value is making bullshit as it's expected now :  %d\n", q->a());
	printf("\n-- operator==\n\n");
	printf("q1 == q2 ? : %s\n", q1 == q2 ? "true" : "false");
	printf("q0 == q2 ? : %s\n", q0 == q2 ? "true" : "false");
	printf("\n-- operator + and -\n\n");
	cout << "q1+q2 = " << q1 + q2 << "\n";
	cout << "q1-q2 = " << q1 - q2 << "\n";
	cout << "q0-q2 = " << q0 - q2 << "\n";

	


	return 0;
}

std::ostream& operator<<(std::ostream& os, Quaternion const& q)
{
	os <<"("<< q.a() << "," << q.b() << "," << q.c() << "," << q.d() << ")";
	os << endl;
	return os;
}
