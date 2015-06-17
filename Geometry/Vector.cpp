#include "Vector.h"
#include <cmath>

// vector as three coordinates
Vector::Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
{}


Vector::Vector(const Plane& plane)
{
	// gives the normal vector of the plane
	x = plane.getA();
	y = plane.getB();
	z = plane.getC();
}


Vector::Vector(const Point& begin, const Point& end)
{
	x = end.getX() - begin.getX();
	y = end.getY() - begin.getY();
	z = end.getZ() - begin.getZ();
}

//vector summation
Vector Vector::operator+(const Vector& other) const
{
	return Vector(x + other.x, y + other.y, z + other.z);
}

double Vector::operator*(const Vector& other) const
{
	return this->dotProduct(other);
}

Vector Vector::operator^(const Vector& other) const
{
	return this->crossProduct(other);
}

double Vector::getLength() const
{
	return sqrt(x*x + y*y + z*z); 
}

double Vector::dotProduct(const Vector& other) const
{
	return x*other.x + y*other.y + z*other.z;
}

Vector Vector::crossProduct(const Vector& other) const
{
	return Vector(y*other.z - z*other.y, -(x*other.z - z*other.x), x*other.y - y*other.x);
}

bool Vector::isZeroVector() const
{
	return (x == 0 && y == 0 && z == 0);
}

//multiplication with scalar parameters aka "numbers"
Vector operator*(const Vector& vect, double param)
{
	return Vector((vect.x)*param, (vect.y)*param, (vect.z)*param);
}
Vector operator*(double param, const Vector& vect)
{
	return operator*(vect, param);
}


//getters and setters
void Vector::setX(double _x) { x = _x; }
void Vector::setY(double _y) { y = _y; }
void Vector::setZ(double _z) { z = _z; }
double Vector::getX() const { return x; }
double Vector::getY() const { return y; }
double Vector::getZ() const { return z; }