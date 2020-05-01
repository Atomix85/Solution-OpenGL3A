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
	printf("a : %f\n", q0.a());
	printf("b: %f\n", q0.b());
	printf("c : %f\n", q0.c());
	printf("d : %f\n", q0.d());
	printf("\n-- parameters constructor\n\n");
	Quaternion q1(60.5, 1.0, 0.0, 0.0);
	printf("a : %f\n", q1.a());
	printf("b: %f\n", q1.b());
	printf("c : %f\n", q1.c());
	printf("d : %f\n", q1.d());
	printf("\n-- copy constructor\n\n");
	Quaternion q2(q1);
	printf("a : %f\n", q2.a());
	printf("b: %f\n", q2.b());
	printf("c : %f\n", q2.c());
	printf("d : %f\n", q2.d());
	printf("\n-- destructor\n\n");
	Quaternion* q = new Quaternion(15,0,1,0);
	cout << "A dynamically allocated quaternion : \n Q = " << *q << "\n";
	delete q;
	printf("The quaternion Q has been successfully freed.\n"
		    "See the a value is making bullshit as it's expected now :  %d\n", q->a());
	printf("\n-- operator==\n\n");
	printf("q1 == q2 ? : %s\n", q1 == q2 ? "true" : "false");
	printf("q0 == q2 ? : %s\n", q0 == q2 ? "true" : "false");

	


	return 0;
}

std::ostream& operator<<(std::ostream& os, Quaternion const& q)
{
	os <<"("<< q.a() << "," << q.b() << "," << q.c() << "," << q.d() << ")";
	os << endl;
	return os;
}
