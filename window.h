/*
 *  window.h
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Specifies information for window.cpp
 *  Subclass of Fl_Gl_Window
 *
 */
#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
#include <Fl/Fl_Box.H>
#include <Fl/Fl_Window.H>
#include <Fl/Fl_Button.H>
#include "treeView.h"
#include "Node.h"
#include <vector>

class MyWindow:public Fl_Gl_Window
{
private:

	//////// Fl_Gl_Window class method

	void draw();

	Node current;
public:
	Node root;
	Node rootcpy;
	vector<Node> frames;

	//////// Animation

	Node getTreeToDraw();
	void setTreeToDraw(Node n);

	//////// Constructors & Destructors

	MyWindow(int x, int y, int w, int h, char* c);
	virtual ~MyWindow();
};
