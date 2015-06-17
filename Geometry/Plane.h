#ifndef PLANE_H
#define PLANE_H
#include "Line.h"
#include "Point.h"
#include "Vector.h"

class Line;
class Point;
class Vector;

class Plane
{
private:
	double A, B, C, D;  // Ax + By + Cz + D = 0
public:
	Plane(double = 0, double = 0, double = 0, double = 0);
	Plane(const Plane&, const Point&);
	Plane(const Line&, const Point&);
	Plane(const Vector&, const Vector&, const Point&);
	Plane(const Point&, const Point&, const Point&);

	void showGeneralEquation() const;
	void showParametricEquation() const;
	Vector getNormalVector() const;
	int relativePosition(const Plane&) const; // 0 if parallel , 1 if intersecting

	friend double getAngle(const Line&, const Plane&);		// defined in Line.cpp
	

	//getters and setters
	double getA() const;
	double getB() const;
	double getC() const;
	double getD() const;
	void setA(double);
	void setB(double);
	void setC(double);
	void setD(double);
};

#endif