#include "Line.h"
#include <iostream>
#include <cmath>
#define PI 3.14159265

// default constructor
Line::Line()
{
	point = new Point();
	vector = new Vector();
}

Line::Line(const Point& point1, const Point& point2)
{
	point = new Point(point1);

	// create vector from two points which the line will be parallel to
	vector = new Vector(point1, point2);
}

// line perpendicular to a plane at a specific point
Line::Line(const Plane& _plane, const Point& _point)
{
	Line(_plane.getNormalVector(), _point);
}

Line::Line(const Vector& _vector, const Point& _point)
{
	point = new Point(_point);
	vector = new Vector(_vector);
}

Line::Line(const Line& other)
{
	*this = other;
}

Line& Line::operator=(const Line& other)
{
	if (this != &other)
	{
		delete point;
		delete vector;
		point = new Point(*other.point);
		vector = new Vector(*other.vector);
	}
	return *this;
}

Line::~Line()
{
	delete vector;
	delete point;
}

/*
Line Line::getOrthogonalProjection(const Plane& plane) const
{
	
} */

const Vector* Line::getVector() const
{
	return vector;
}

const Point* Line::getPoint() const
{
	return point;
}

void Line::showParametricEquation() const
{
	std::cout << "X = " << point->getX() << " + " << vector->getX() << "s\n";
	std::cout << "Y = " << point->getY() << " + " << vector->getY() << "s\n";
	std::cout << "Z = " << point->getZ() << " + " << vector->getZ() << "s\n";
}

int Line::relativePosition(const Line& other) const     // -1 if non-intersecting ,  0 if parallel,  +1 if intersecting
{
	Vector cross = vector->crossProduct(*(other.getVector()));

	if (cross.getLength() == 0)
		return 0;  //parallel

	//check if lines are skew(non-intersecting) by determining the distance between them
	//norm the vector
	cross = cross*(1 / cross.getLength());
	double distance = cross.dotProduct(Vector(*point, *other.point));

	if (distance == 0)
		return 1; // lines intersect
	
	//lines are skew
	return -1;
}

double Line::getDistanceTo(const Line& other) const
{
	if (relativePosition(other) != 0) // distance between non-parallel lines
	{
		Vector cross = vector->crossProduct(*(other.getVector()));
		//norm the vector
		cross = cross*(1 / cross.getLength());
		double distance = cross.dotProduct(Vector(*point, *other.point));
		return distance;
	}
	else // distance between parallel lines
	{
		Point P1 = *point;
		Point P2 = *other.point;
		Vector differenceVector = Vector(P1, P2);
		Vector projectionVector = ((vector->dotProduct(differenceVector)) / (pow(vector->getLength(), 2))) * (*vector);
		Vector distanceVector = differenceVector + (-1)*projectionVector;
		return distanceVector.getLength();
	}
}

// 0 - parallel , 1 - non-parallel
int Line::relativePosition(const Plane& _plane) const
{
	if (_plane.getNormalVector().dotProduct(*vector) == 0)
		return 0;
	
	return 1;
}


double getAngle(const Line& _line, const Plane& _plane)
{
	Vector normal = _plane.getNormalVector();

	//arcsine of the angle between the line vector and the normal vector
	double angleArcsine = asin( normal.dotProduct(*_line.vector) / 
					(normal.getLength()*_line.vector->getLength()));
	//return converted to degrees
	return angleArcsine*180.0 / PI;
} 
