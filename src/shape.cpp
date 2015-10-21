/*
 *  Shape.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Shape class that specifies color, type, points relative to origin, points with applied transformations
 *  Contains methods to apply transformations, draw the shape, and change elements
 *
 */

#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
#include "assert.h"
#include "mat3.h"
#include "Shape.h"
#include <iostream>

//////// Constructors & Destructors

Shape::Shape(vec3 c, Type t)
{
	color = c;
	type = t;
};

Shape::Shape()
{
	color = vec3(0, 0, 0);
	type = RECTANGLE;
}

Shape::~Shape()
{
}

//////// Getters & Setters

void 
Shape::setType(Type t)
{
	type = t;
}

vec3 
Shape::getColor()
{
	return color;
}

void 
Shape::setColor(int x, int y, int z)
{
	color[0] = x;
	color[1] = y;
	color[2] = z;
}

//////// Add & Remove a Point

void 
Shape::addPoint(vec3 point)
{
	points.push_back(point);
}

void 
Shape::addPoints(list<vec3> p)
{
	list<vec3>::iterator i;
	for (i = p.begin(); i != p.end(); i++) { points.push_back(*i); }
}

void 
Shape::removePoint(int x, int y, int z)
{
	list<vec3>::iterator i;
	for (i = points.begin(); i != points.end(); i++)
	{
		if (((*i)[0] == x) && ((*i)[1] == y) && ((*i)[2] == z))
		{
			i = points.erase(i);
		}
	}
}

//////// Transformations & Drawing

void
Shape::drawShape(list<vec3> pointList)
{
	//glClearColor(0, 0, 0, 0);									// Clears screen entirely
	//glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(color[0], color[1], color[2]);					// Add color

	switch (type) 
	{
	case RECTANGLE: glBegin(GL_QUADS); break;
	case POLYGON: glBegin(GL_POLYGON); break;
	case POLYLINE: glBegin(GL_LINE_LOOP); break;
	case TRIANGLE: glBegin(GL_TRIANGLES); break;
	}

	list<vec3>::iterator i;
	for (i = pointList.begin(); i != pointList.end(); i++)
	{ 
		glVertex2f((*i)[0], (*i)[1]);
	}
	glEnd();
}

mat3
Shape::transform(mat3 parentTransf, mat3 transf)
{
	// Multiply the transformation by the transformation history
	parentTransf = (parentTransf*transf);

	// Create and save the adjusted points
	list<vec3> newPoints;
	list<vec3>::iterator i;
	for (i = points.begin(); i != points.end(); i++)
	{
		newPoints.push_back((parentTransf*(*i)));
	}

	tempPoints = newPoints;

	return parentTransf;
}

//////// Printing

void 
Shape::printType()
{
	switch (type)
	{
	case RECTANGLE: cout << "Rectangle" << endl;
	case POLYGON: cout << "Polygon" << endl;
	case POLYLINE: cout << "Polyline" << endl;
	case TRIANGLE: cout << "Triangle" << endl;
	}
}

void 
Shape::printColor()
{
	color.print();
}

void 
Shape::printPoints()
{
	list<vec3>::iterator i;
	for (i = points.begin(); i != points.end(); i++) { (*i).print(); }
}

void 
Shape::print()
{
	cout << "-------------------" << endl;
	printType();
	printColor();
	printPoints();
	cout << "-------------------" << endl;
}
