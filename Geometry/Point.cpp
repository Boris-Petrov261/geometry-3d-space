#include "Point.h"
#include <cmath>
#include <iostream>

// point as three coordinates
Point::Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
{}

// point as an intersection of two lines
Point::Point(const Line& line1, const Line& line2)
{
	// uses formula  s(V1xV2) = (P2 - P1)xV2 + V2xV2 to find s which is the parameter in the first line's equation
	// check if lines are intersecting
	if (line1.relativePosition(line2) == 1)
	{
		Vector v1 = *line1.getVector();
		Vector v2 = *line2.getVector();
		Vector lineVectorProduct = v1^v2;

		//get cross product of (P1 - P2) and V2
		Vector v3 = (Vector(*line1.getPoint(), *line2.getPoint()) ^ v2);

		double s = 0;

		//check for divisions by zero
		if (lineVectorProduct.getX() != 0)
			s = v3.getX() / lineVectorProduct.getX();
		else if (lineVectorProduct.getY() != 0)
			s = v3.getY() / lineVectorProduct.getY();
		else if (lineVectorProduct.getZ() != 0)
			s = v3.getZ() / lineVectorProduct.getZ();

		x = line1.getPoint()->x + s*v1.getX();
		y = line1.getPoint()->y + s*v1.getY();
		z = line1.getPoint()->z + s*v1.getZ();
	}
	else
		Point();
}

// point as intersection of line and plane
Point::Point(const Line& line, const Plane& plane)
{
	// line and plane mustn't be parallel
	if (line.relativePosition(plane) == 1)
	{
		Point point = Point(*line.getPoint());
		Vector vector = Vector(*line.getVector());
		double  A = plane.getA(),
				B = plane.getB(),
				C = plane.getC(),
				D = plane.getD();

		double s = (-D - A*point.x - B*point.y - C*point.z) /
			(A*vector.getX() + B*vector.getY() + C*vector.getZ());

		x = point.x + s*vector.getX();
		y = point.y + s*vector.getY();
		z = point.z + s*vector.getZ();
	}
	else
		Point(); // assign object to zero vector if there is no intersection
}

bool Point::isOnLine(const Line& line) const
{
	// this will be our ratio     line = P + s.V	x = p1 + s*v1 <=> s = (x - p1) / v1  etc.
	double s = 0;

	// get the ratio s between one of the point's coordinates and the line's corresponding coordinates
	// check for non-zero divisor
	if (line.getVector()->getX() != 0)
		s = (x - line.getPoint()->getX()) / line.getVector()->getX();
	else if (line.getVector()->getY() != 0)
		s = (y - line.getPoint()->getY()) / line.getVector()->getY();
	else if (line.getVector()->getZ() != 0)
		s = (z - line.getPoint()->getZ()) / line.getVector()->getZ();
	else // if line's vector is the zero vector (??) compare the two points
		return x == line.getPoint()->getX() && y == line.getPoint()->getY() && line.getPoint()->getZ();

	// once we have s we can check if every pair of coordinates has the exact same ratio s which means the point is on the line
	// if we get a pair of coordinates which has a ratio != s then the point is not on the line
	// once again check for zero in the divisors
	if (line.getVector()->getX() != 0)
	{
		if ((x - line.getPoint()->getX()) / line.getVector()->getX() != s)
			return false;
	}
	else if (x != line.getPoint()->getX())
			return false;

	if (line.getVector()->getY() != 0)
	{
		if ((y - line.getPoint()->getY()) / line.getVector()->getY() != s)
			return false;
	}
	else if (y != line.getPoint()->getY())
			return false;

	if (line.getVector()->getZ() != 0)
	{
		if ((z - line.getPoint()->getZ()) / line.getVector()->getZ() != s)
			return false;
	}
	else if (z != line.getPoint()->getZ())
			return false;

	// function hasn't returned false which means everything is OK and the point is on the line
	return true;
}

bool Point::isOnPlane(const Plane& plane) const
{
	return (x*plane.getA() + y*plane.getB() + z*plane.getC() + plane.getD()) == 0;
}

// @param distance - the offset amount for translating the point along the vector
void Point::translate(const Vector& vector, double distance = 1)
{
	x = x + distance*vector.getX();
	y = y + distance*vector.getY();
	z = z + distance*vector.getZ();
}

double Point::getDistance(const Plane& plane)
{
	double A = plane.getA(), B = plane.getB(), C = plane.getC(), D = plane.getD();
	return (x*A + y*B + z*C + D) / (sqrt(A*A + B*B + C*C));
}

double Point::getDistance(const Line& line)
{
	//get two points from the line
	Point P1 = *line.getPoint();
	Point P2 = P1;
	// move the second point so we know it's different than the first
	P2.translate(*line.getVector(), 2);

	Vector v1(P1, *this), v2(P2, *this), v3(P1, P2);
	// we use the well-known formulas for (*this, P1, P2)triangle area to get the height from the point to the line
	double distance = (v1^v2).getLength() / v3.getLength();
	return distance;
}

//getters and setters
void Point::setX(double _x) { x = _x; }
void Point::setY(double _y) { y = _y; }
void Point::setZ(double _z) { z = _z; }
double Point::getX() const { return x; }
double Point::getY() const { return y; }
double Point::getZ() const { return z; }