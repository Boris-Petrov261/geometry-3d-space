#ifndef VECTOR_H
#define VECTOR_H
#include "Point.h"
#include "Plane.h"

class Point;
class Plane;

class Vector
{
private:
	double x, y, z;
public:
	Vector(double = 0, double = 0, double = 0);
	Vector(const Plane&);
	Vector(const Point&, const Point&);

	Vector operator+(const Vector&) const; // vector summation

	double operator*(const Vector&) const; // dot product
	Vector operator^(const Vector&) const; // cross product

	/*
	there are already operator functions for dot and cross product however
	they are very ambiguous from a user stand point so for convenience 
	here are the explicit functions
	*/
	double dotProduct(const Vector&) const;
	Vector crossProduct(const Vector&) const;
	double getLength() const;				//vector length
	bool isZeroVector() const;

	/*for expressions of type ((5*a + b*7.4)*c)*5 or similar
	where a,b,c are vectors */
	friend Vector operator*(const Vector&, double);
	friend Vector operator*(double, const Vector&);

	//getters and setters
	void setX(double);
	void setY(double);
	void setZ(double);
	double getX() const;
	double getY() const;
	double getZ() const;


};

#endif
