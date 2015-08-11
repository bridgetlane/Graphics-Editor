/*
 *  Shape.h
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Specifies information for shape.cpp
 *
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "mat3.h"
#include <list>

using namespace std;		// For use with list

class Shape
{
private:

	//////// Member variables

	list<vec3> points;
public:
	vec3 color;
	list<vec3> tempPoints;
	enum Type { RECTANGLE, POLYGON, POLYLINE, TRIANGLE };
	Type type;

	//////// Constructors & Destructors

	Shape();
	Shape(vec3 c, Type t);
	~Shape();

	//////// Getters & Setters

	void setType(Type t);
	vec3 getColor();
	void setColor(int x, int y, int z);

	//////// Add & Remove a Point

	void addPoint(vec3 point);
	void addPoints(list<vec3> points);
	void removePoint(int x, int y, int z);

	//////// Transformations & Drawing

	void drawShape(list<vec3> pointList);							// Draw the created shape
	mat3 transform(mat3 parentTransf, mat3 transf);

	//////// Printing

	void printType();
	void printColor();
	void printPoints();
	void print();
};

#endif
