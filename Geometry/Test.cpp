#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Line.h"
#include "Plane.h"

using namespace std;

int main()
{
	// Plane test
	cout << "Plane test:\n";
	Plane plane(1, 5, -5, 3); 
	plane.showGeneralEquation();
	cout << plane.relativePosition(plane) << endl;
	cout << plane.relativePosition(Plane(1, 5, 2, 5)) << endl;

	plane = Plane(Point(2, 3, 6) , Point(-2, 5, 8) , Point(1,6,4));
	plane.showGeneralEquation();
	plane = Plane(Vector(-4, 2, 2), Vector(-1, 3, -2), Point(1, 6, 4));
	plane.showGeneralEquation();

	// Point test
	cout << "Point test:\n";
	Point point(1, 5, -2.5);
	cout << point.isOnPlane(plane)<< endl;
	cout << Point(2, 3, 6).isOnPlane(plane) << endl;
	cout << point.isOnLine(Line(Vector(5,6,2), point)) << endl;
	cout << point.isOnLine(Line(Vector(5, 6, 2), Point(5,2,-3))) << endl;
	Point point2(Line(Vector(10, 10, 6), Point(5, 5, 4)), Line(Vector(10, 10, 3), Point(5, 5, 5)));
	cout << point2.getX() << " " << point2.getY() << " " << point2.getZ() << endl;

	// Line test
	cout << "Line test:\n";
	Line line(Point(5, 2, 8), Point(-2, 5, 4));
	line.showParametricEquation();
	cout << endl;
	cout << line.relativePosition(Line(Vector(-7, 3, -4), Point(2, 3, 1))) << endl; // 0 - parallel
	cout << line.getDistanceTo(Line(Vector(-6, 2, -4), Point(200, -5, 1))) << endl;
	
	// Vector test
	cout << "Vector test:\n";
	Vector vect1 = Vector(Plane(1, 5, -5, 7));				 // (1, 5 , -5)
	Vector vect2 = Vector(Point(1, 0, 2), Point(3, -1, 0));  // (2, -1, -2) 
	cout << vect1*vect2 << endl; // dot product  1*2 -1*5 -5*-2 = 7
	Vector vect3 = vect1^vect2; // vector product
	cout << vect3.getX() << " " << vect3.getY() << " " <<vect3.getZ() << endl; 
	cout << vect2.getLength() << endl; // sqrt(2^2 + (-1)^2 + (-2)^2) = 3
	Vector vect4 = vect1 + vect2 + Vector(3, 2 ,1);
	cout << vect4.getX() << " " << vect4.getY() << " " << vect4.getZ() << endl;



	system("pause");
	return 0;
}