#include "Quaternion.h"
#include <iostream>
#include <math.h>
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

bool Quaternion::operator!=(Quaternion const&q)
{
	return !(*this==q);
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

Quaternion Quaternion::operator/(Quaternion const& q)
{
	GLfloat invNorm = 1.0 / q.norm();
	Quaternion  q2(q.a()* invNorm, -q.b() * invNorm, -q.c() * invNorm, -q.d() * invNorm);
	return (*this * q2);
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

Quaternion Quaternion::operator/=(Quaternion const& q)
{
	*this = *this / q;
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

Quaternion Quaternion::conjugate()
{
	return Quaternion(this->a(), -this->b(), -this->c(), -this->d());
}

GLfloat Quaternion::norm() const
{
	GLfloat sum = _angle * _angle;
	for (int i = 0; i < 3; i++) { sum += _axis[i]; }
	return sqrt(sum);
}

void Quaternion::normalize()
{
	GLfloat norm = this->norm();
	_angle = _angle / norm;
	for (int i = 0; i < 3; i++) { _axis[i] = _axis[i] / norm; }
}

Quaternion Quaternion::matrix2Quaternion(GLfloat* const& m)
{
	
	
	GLfloat trace = m[0] + m[5] + m[10];
	GLfloat S, X, Y, Z, W;

	if (trace >= 0) { 
		S = sqrt(trace + m[15]);
		W = 0.5f * S;
		S = 0.5f / S;
		X = (m[6] - m[9]) * S;
		Y = (m[8] - m[2]) * S;
		Z = (m[1] - m[4]) * S;
		return Quaternion(W, X, Y, Z);
	}
	if (m[0] > m[5] && m[0] > m[10]) { 
		S = sqrt(m[15] + m[0] - m[5] - m[10]);
		X = S * 0.5f;
		S = 0.5f / S;
		Y = (m[1] + m[4]) * S;
		Z = (m[8] + m[2]) * S;
		W = (m[6] - m[9]) * S;
		return Quaternion(W, X, Y, Z);
	}
	if (m[5] > m[10]) { // by y
		S = sqrt(m[15] + m[5] - m[0] - m[10]);
		Y = S * 0.5f;
		S = 0.5f / S;
		X = (m[1] + m[4]) * S;
		Z = (m[6] + m[9]) * S;
		W = (m[8] - m[2]) * S;
		return Quaternion(W, X, Y, Z);
	}
	
		S = sqrt(1 + m[10] - m[0] - m[5]);
		Z = S * 0.5f;
		S = 0.5f / S;
		X = (m[8] + m[2]) * S;
		Y = (m[6] + m[9]) * S;
		W = (m[1] - m[4]) * S;
		return Quaternion(W, X, Y, Z);

}

GLfloat* Quaternion::quaternion2Matrix()
{
	// always normalize
	this->normalize();
	GLfloat* matrix = (GLfloat*) malloc(16 * sizeof(GLfloat));

	// 4th line and 4th column are put to 0 because their are extra element
	// only used for openGL compatibility.
	matrix[3] = matrix[7] = matrix[11] = matrix[12] = matrix[13] = matrix[14] = 0;
	matrix[15] = 1;

	// the 3x3 rotation sub-matrix is here : 
	matrix[0] = 1 - 2 * (this->c() * this->c() + this->d() * this->d());
	matrix[1] = 2 * (this->b() * this->c() - this->d() * this->a());
	matrix[2] = 2 * (this->b() * this->d() + this->c() * this->a());

	matrix[4] = 2 * (this->b() * this->c() + this->d() * this->a());
	matrix[5] = 1 - 2 * (this->b() * this->b() + this->d() * this->d());
	matrix[6] = 2 * (this->c() * this->d() -  this->b() * this->a());

	matrix[8] = 2 * (this->b() * this->d() - this->c() * this->a());
	matrix[9] = 2 * (this->c() * this->d() +  this->b() * this->a());
	matrix[10] = 1 - 2 * (this->b() * this->b() + this->c() * this->c());

	

	return matrix;
}



Quaternion operator*(GLfloat alpha, Quaternion const& q)
{
	return Quaternion(q.a() * alpha, q.b() * alpha, q.c() * alpha, q.d() * alpha);
}

Quaternion operator*(Quaternion const& q, GLfloat alpha)
{
	return Quaternion(q.a() * alpha, q.b() * alpha, q.c() * alpha, q.d() * alpha);
}

std::ostream& operator<<(std::ostream& os, Quaternion const& q)
{
	os << "(" << q.a() << "," << q.b() << "," << q.c() << "," << q.d() << ")";
	os << endl;
	return os;
}
/*
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
	printf("\n-- operator== and !=\n\n");
	printf("q1 == q2 ? : %s\n", q1 == q2 ? "true" : "false");
	printf("q0 == q2 ? : %s\n", q0 == q2 ? "true" : "false");
	printf("q1 != q2 ? : %s\n", q1 != q2 ? "true" : "false");
	printf("q0 != q2 ? : %s\n", q0 != q2 ? "true" : "false");
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
	printf("\n-- operator * for scalar product\n\n");
	cout << "q3 * 2 = " <<  q3 * 2  << "\n";
	cout << "2 * q3 = " <<  2 * q3 << "\n";
	printf("testing rotation\n"); 
	Quaternion qRot(50, 0, 1 , 1); 
	cout << "qRot = " << qRot;
	GLfloat* rot = qRot.quaternion2Matrix();	
	cout << "qRot norm = " << qRot;

	for (int i = 0; i < 16; i++)
	{
		if (i % 4 == 0)
			cout << '\n';
		cout << rot[i] <<" | ";
	}
	cout << "\n" << qRot.matrix2Quaternion(rot);

	return 0;
}*/
