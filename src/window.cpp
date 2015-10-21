/*
 *  window.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Specifies information for window.cpp
 *  Subclass of Fl_Gl_Window
 *
 */

#include "window.h"
#include "Shape.h"
#include "Node.h"
#include <list>
#include <iostream>

using namespace std;	// for use with list

MyWindow::MyWindow(int x, int y, int w, int h, char* c) :Fl_Gl_Window(x, y, w, h, c)
{
	///////////////////////////////////////////////////////////////////
	//////// Create the Body: Red Rectangle, No Transformation ////////
	//////// Root Node: Child of Nothing                       ////////
	///////////////////////////////////////////////////////////////////

	list<vec3> body_pnts;
	body_pnts.push_back(vec3(-2, -1, 1));
	body_pnts.push_back(vec3(-2, 1, 1));
	body_pnts.push_back(vec3(2, 1, 1));
	body_pnts.push_back(vec3(2, -1, 1));

	Shape red(vec3(1, 0, 0), Shape::RECTANGLE);
	red.addPoints(body_pnts);

	///////////////// Change Body Transformations Here ////////////////

	// Root Translation			Root Rotation			Root Scale
	root = Node(string("body"), red, (mat3::translation2D(0, 0)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));


	///////////////////////////////////////////////////////////////////
	///// Create the Head: Light Blue Rectangle, (2,1) Translation ////
	///// Child of Body Node                                      /////
	///////////////////////////////////////////////////////////////////

	list<vec3> head_pnts;
	head_pnts.push_back(vec3(0, 0, 1));
	head_pnts.push_back(vec3(0, 1.5, 1));
	head_pnts.push_back(vec3(2, 1, 1));
	head_pnts.push_back(vec3(2, 0.5, 1));

	Shape lightblue(vec3(0, 1, 1), Shape::RECTANGLE);
	lightblue.addPoints(head_pnts);

	///////////////// Change Head Transformations Here ////////////////
	// Head Rotation
	Node head(string("head"), lightblue, (mat3::translation2D(2, 1)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));


	////////////////////////////////////////////////////////////////////////////////
	///// Create the Tail: Blue Rectangle, (-2,1) Translation, 160deg Rotation /////
	///// Child of Body Node                                                   /////
	////////////////////////////////////////////////////////////////////////////////

	list<vec3> tail_pnts;
	tail_pnts.push_back(vec3(0, 0, 1));
	tail_pnts.push_back(vec3(0, 0.4, 1));
	tail_pnts.push_back(vec3(2, 0.4, 1));
	tail_pnts.push_back(vec3(2, 0, 1));

	Shape blue(vec3(0, 0, 1), Shape::RECTANGLE);
	blue.addPoints(tail_pnts);

	/////////////////////// Change Tail Transformations Here //////////////////////

	Node tail(string("tail"), blue, (mat3::translation2D(-2, 1)*mat3::rotation2D(160)*mat3::scale2D(1, 1)));


	//////////////////////////////////////////////////////////////////////
	///// Create the Legs: Light Green Rectangles, Many Translations /////
	///// Children of Body Node                                      /////
	//////////////////////////////////////////////////////////////////////

	list<vec3> leg_pnts;
	leg_pnts.push_back(vec3(0, 0, 1));
	leg_pnts.push_back(vec3(0, -2, 1));
	leg_pnts.push_back(vec3(0.3, -2, 1));
	leg_pnts.push_back(vec3(0.3, 0, 1));

	Shape green1(vec3(0, 1, 0), Shape::RECTANGLE);
	green1.addPoints(leg_pnts);
	Shape green2(vec3(0, 1, 0), Shape::RECTANGLE);
	green2.addPoints(leg_pnts);
	Shape green3(vec3(0, 1, 0), Shape::RECTANGLE);
	green3.addPoints(leg_pnts);
	Shape green4(vec3(0, 1, 0), Shape::RECTANGLE);
	green4.addPoints(leg_pnts);

	/////////////////// Change Leg Transformations Here //////////////////
	// Limb 1 Upper Rotation
	Node leg4(string("leg4"), green1, (mat3::translation2D(-2, -1)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));
	// Limb 2 Upper Rotation
	Node leg3(string("leg3"), green2, (mat3::translation2D(-1, -1)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));
	// Limb 3 Upper Rotation
	Node leg2(string("leg2"), green3, (mat3::translation2D(1, -1)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));
	// Limb 4 Upper Rotation
	Node leg1(string("leg1"), green4, (mat3::translation2D(2, -1)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));


	////////////////////////////////////////////////////////////////////////
	///// Create the Sub-Legs: Yellow Rectangles, (0,-1.5) Translation /////
	///// Children of Leg Nodes                                        /////
	////////////////////////////////////////////////////////////////////////

	list<vec3> subleg_pnts;
	subleg_pnts.push_back(vec3(0, 0, 1));
	subleg_pnts.push_back(vec3(0.2, 0, 1));
	subleg_pnts.push_back(vec3(0.2, -1, 1));
	subleg_pnts.push_back(vec3(0, -1, 1));

	Shape yellow1(vec3(1, 1, 0), Shape::RECTANGLE);
	yellow1.addPoints(subleg_pnts);
	Shape yellow2(vec3(1, 1, 0), Shape::RECTANGLE);
	yellow2.addPoints(subleg_pnts);
	Shape yellow3(vec3(1, 1, 0), Shape::RECTANGLE);
	yellow3.addPoints(subleg_pnts);
	Shape yellow4(vec3(1, 1, 0), Shape::RECTANGLE);
	yellow4.addPoints(subleg_pnts);

	/////////////////// Change Leg Transformations Here //////////////////
	// Limb 1 Lower Rotation
	Node subleg4(string("subleg4"), yellow1, (mat3::translation2D(0, -2)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));
	// Limb 2 Lower Rotation
	Node subleg3(string("subleg3"), yellow2, (mat3::translation2D(0, -2)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));
	// Limb 3 Lower Rotation
	Node subleg2(string("subleg2"), yellow3, (mat3::translation2D(0, -2)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));
	// Limb 4 Lower Rotation
	Node subleg1(string("subleg1"), yellow4, (mat3::translation2D(0, -2)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));


	////////////////////////////////////////////////////////////////////////
	//////// Specify Parent-Child Relationships                     ////////
	////////////////////////////////////////////////////////////////////////

	leg1.addChild(subleg1); leg2.addChild(subleg2); leg3.addChild(subleg3); leg4.addChild(subleg4);
	root.addChild(tail); root.addChild(leg4); root.addChild(leg3); root.addChild(leg2); root.addChild(leg1); root.addChild(head);

	rootcpy = root;												// Stores a copy of the original drawing, used for magic button
	current = root;												// What gets drawn - for use with animation
}

MyWindow::~MyWindow()
{
}

//////// Animation

Node 
MyWindow::getTreeToDraw()
{
	return current;
}

void 
MyWindow::setTreeToDraw(Node n)
{
	current = n;
}

//////// Fl_Gl_Window class method

void
MyWindow::draw()
{
	//////// FLTK Housekeeping

	if (!valid()){
		valid(1);

		// glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
		glViewport(0, 0, w(), h());  // lower left coordinate and width and height

		//glOrtho describes a transformation that produces a parallel projection.
		glOrtho(-10, 10, -10, 10, -1, 1);  // left, right, bottom, top, near, far
	}


	////////////////////////////////////////////////////////////////////////
	//////// Run the Scene Graph                                    ////////
	////////////////////////////////////////////////////////////////////////

	glClearColor(0, 0, 0, 0);									// Clears screen entirely
	glClear(GL_COLOR_BUFFER_BIT);
	Node* r = &root;
	root.applyAllTransformations(r);
	root.drawAll(root);
}
