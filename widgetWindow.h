/*
 *  widgetWindow.h
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Specifies information for widgetWindow.cpp
 *  Subclass of Fl_Window
 * 
 *  NOTE: It is useful to note that the user may want to draw a "starter" shape or clear the screen
 *        before entering animation mode. Whatever is on the window when entering animation mode will be
 *        the starting image for every window.
 *
 */

#include "window.h"
#include <FL/Fl_Group.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Counter.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <sstream>
#include <jpeg/jpeglib.h>

#define		FPS		5

class widgetWindow:public Fl_Window  // subclass of Fl_Window where the widgets and graphics will be displayed.
{
private:
	bool isAnimating;
	bool isPlaying;
	int current;
	int totalFrames;

	//////// Member variables

	MyWindow* drawing;
	Flx::TreeView* trv;
	Fl_Button* addB;
	Fl_Button* removeB;
	Fl_Button* clearB;
	Fl_Button* resetB;
	Fl_Slider* R;
	Fl_Slider* G;
	Fl_Slider* B;
	Fl_Roller* moveX;
	Fl_Roller* moveY;
	Fl_Roller* scaleX;
	Fl_Roller* scaleY;
	Fl_Dial* rotate;	
	Fl_Input* textName;
	Fl_Round_Button* rectangle;
	Fl_Round_Button* triangle;
	Fl_Round_Button* polygon;
	Fl_Round_Button* polyline;
	Fl_Button* createB;
	Fl_Value_Input* numFrames;
	Fl_Button* beginAnimation;
	Fl_Value_Slider* changeFrame;
	Fl_Button* moveForward;
	Fl_Button* goBack;
	Fl_Button* playCurrent;
	Fl_Button* renderFull;

	//////// Modeling callback methods

	static void selectCB(Flx::TreeView* tree, widgetWindow* win);
	static void addCB(Fl_Button* button, widgetWindow* win);
	static void createCB(Fl_Button* button, widgetWindow* win);
	static void removeCB(Fl_Button* button, widgetWindow* win);
	static void clearCB(Fl_Button* button, widgetWindow* win);
	static void resetCB(Fl_Button* button, widgetWindow* win);
	static void colorCB(Fl_Slider* slider, widgetWindow* win);
	static void translCB(Fl_Slider* slider, widgetWindow* win);
	static void nameCB(Fl_Input* input, widgetWindow* win);

	//////// Animation callback methods

	static void beginAnimationCB(Fl_Button* button, widgetWindow* win);
	static void changeFrameCB(Fl_Value_Slider* counter, widgetWindow* win);
	static void moveForwardCB(Fl_Button* button, widgetWindow* win);
	static void goBackCB(Fl_Button* button, widgetWindow* win);
	static void playCurrentCB(Fl_Button* button, widgetWindow* win);
	static void playCB(void *data);
	static void renderFullCB(Fl_Button* button, widgetWindow* win);
public:

	//////// Construct TreeView tree

	static void initialAddToTree(Node* root, Flx::TreeViewItemProxy* parent, Flx::TreeView* trv);

	//////// Constructors & Destructors

	widgetWindow(int x, int y, int w, int h, char* c);
	virtual ~widgetWindow();
};
