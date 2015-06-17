#ifndef POINT_H
#define POINT_H
#include "Line.h"
#include "Plane.h"
#include "Vector.h"

class Line;
class Plane;
class Vector;
class Point
{
private:
	double x, y, z;

public:
	Point(double = 0, double = 0, double = 0); // point as three coordinates
	Point(const Line&, const Line&); // point as an intersection of two lines
	Point(const Line&, const Plane&); // point as intersection of line and plane

	bool isOnLine(const Line&) const;
	bool isOnPlane(const Plane&) const;
	void translate(const Vector&, double);
	
	double getDistance(const Line&);		// defined in Point.cpp
	double getDistance(const Plane&);		// defined in Point.cpp

	//getters and setters
	void setX(double);
	void setY(double);
	void setZ(double);
	double getX() const;
	double getY() const;
	double getZ() const;
};

#endif