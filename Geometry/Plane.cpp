#include "Plane.h"
#include <iostream>

Plane::Plane(double _A, double _B, double _C, double _D) : A(_A), B(_B), C(_C), D(_D)
{}

// plane defined as parallel to another plane and containing a specific point
Plane::Plane(const Plane& plane, const Point& point)
{
	// planes are parallel so their normal vectors and A,B,C coeffs are the same
	Vector normal = plane.getNormalVector();
	A = normal.getX();
	B = normal.getY();
	C = normal.getZ();
	
	D = 0 - (A*point.getX() + B*point.getY() + C*point.getZ());
}

// plane defined by a line perpendicular to it and containing a specific point
Plane::Plane(const Line& line, const Point& point)
{
	//normal vector is colinear with the lines's vector
	Vector normal = *(line.getVector());
	A = normal.getX();
	B = normal.getY();
	C = normal.getZ();

	D = -(A*point.getX() + B*point.getY() + C*point.getZ());
}

Plane::Plane(const Vector& vect1, const Vector& vect2, const Point& point)
{
	// if vector product is zero vector then vect1 and vect2 are colinear therefore we can't define a plane using them
	if (!(vect1^vect2).isZeroVector())
	{
		// normal is perpendicular to both vect1 and vect2 so it is perpendicular to the plane as well
		Vector normal = vect1.crossProduct(vect2);
		A = normal.getX();
		B = normal.getY();
		C = normal.getZ();

		D = -(point.getX()*A + point.getY()*B + point.getZ()*C);
	}
	else
		Plane();
}

// plane defined by three points it cointains
Plane::Plane(const Point& point1, const Point& point2, const Point& point3)
{
	// vect1 and vect2 will be on the plane
	Vector vect1 = Vector(point1, point2);
	Vector vect2 = Vector(point1, point3);

	Vector normal = vect1.crossProduct(vect2);
	A = normal.getX();
	B = normal.getY();
	C = normal.getZ();

	D = -(point3.getX()*A + point3.getY()*B + point3.getZ()*C);

	//Plane(vect1, vect2, point1);
}

Vector Plane::getNormalVector() const
{
	return Vector(A, B, C);
}

int Plane::relativePosition(const Plane& other) const
{
	// 0 - parallel   1-intersecting
	return !(getNormalVector()^other.getNormalVector()).getLength() == 0;
}

void Plane::showGeneralEquation() const
{
	std::cout << A << "x + " << B << "y + " << C << "z + " << D << " = 0" << std::endl;
}

void Plane::showParametricEquation() const
{
	// parametric equation is given by one point and two vector
	// choose 3 points that don't lie on the same line

}

//getters and setters
double Plane::getA() const { return A; }
double Plane::getB() const { return B; }
double Plane::getC() const { return C; }
double Plane::getD() const { return D; }
void Plane::setA(double _A) { A = _A; }
void Plane::setB(double _B) { B = _B; }
void Plane::setC(double _C) { C = _C; }
void Plane::setD(double _D) { D = _D; }


