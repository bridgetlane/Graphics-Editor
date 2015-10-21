/*
 *  main.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Creates and displays a window. Calls to window.cpp
 *
 */

#include <iostream>
#include "vec3.h"
#include "mat3.h"
#include <cmath>
#include "widgetWindow.h"

using namespace std;

int main(int argc, char * const argv[]) 
{
	widgetWindow *g = new widgetWindow(100, 100, 930, 600, "Graphics Editor");

	//////// Shape is drawn in window.cpp and editor is created in widgetWindow.cpp
	g->end();
	g->show();
	return Fl::run();
}
