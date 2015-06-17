#ifndef LINE_H
#define LINE_H
#include "Point.h"
#include "Vector.h"
#include "Plane.h"

class Point;
class Vector;
class Plane;

class Line
{
private:
	Point *point;
	Vector *vector;
public:
	Line();
	Line(const Point&, const Point&);
	Line(const Plane&, const Point&);
	Line(const Vector&, const Point&);
	Line(const Line&);
	Line& operator=(const Line&);
	~Line();

	Line getOrthogonalProjection(const Plane&) const;
	const Vector* getVector() const;
	const Point* getPoint() const;
	void showParametricEquation() const;
	int relativePosition(const Line&) const;   // -1 if non-intersecting ,  0 if parallel,  +1 if intersecting
	int relativePosition(const Plane&) const; // 0 if parallel, +1 if intersecting  -----  defined in Line.cpp
	double getDistanceTo(const Line&) const;

	friend double getAngle(const Line&, const Plane&);		// defined in Line.cpp
};

#endif
