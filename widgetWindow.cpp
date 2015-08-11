/*
 *  widgetWindow.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Creates a GUI to manipulate the scene graph and animation
 *  Subclass of Fl_Window
 * 
 */

#include "widgetWindow.h"

//////// Modeling callback methods

void
widgetWindow::selectCB(Flx::TreeView* tree, widgetWindow* win)
{
	// Is called when a Node on the TreeView is selected
	if (tree->getSelection().isValid()) 
	{
		std::cout << tree->getSelection()->getLabel() << std::endl;

		if (win->trv->getSelection()->getData())
		{
			// If the selection is valid: state what GUI components will be activated/deactivated 
			// and update their values if needed
			win->textName->activate();
			win->R->activate();
			win->G->activate();
			win->B->activate();
			win->moveX->activate();
			win->moveY->activate();
			win->scaleX->activate();
			win->scaleY->activate();
			win->rotate->activate();
			win->addB->deactivate();
			win->removeB->deactivate();
			win->rectangle->deactivate();
			win->triangle->deactivate();
			win->polygon->deactivate();
			win->polyline->deactivate();
			win->createB->deactivate();
			Node* r = ((Node*)(win->trv->getSelection()->getData()));
			win->textName->value((win->trv->getSelection()->getLabel()).c_str());
			win->R->value(r->shape.color[0]);
			win->G->value(r->shape.color[1]);
			win->B->value(r->shape.color[2]);
			win->rotate->value(0);
		}
		else
		{
			// If the selection is not valid (is a closing Node), update the label if needed, then mark GUI components
			// as activated/deactivated
			if (win->trv->getSelection() != win->trv->getRoot())
			{
				win->trv->getSelection()->label = win->trv->getSelection()->getParent()->getLabel();
				win->trv->redraw();
			}
			
			win->textName->value("Close of Branch");
			win->textName->deactivate();
			win->R->deactivate();
			win->G->deactivate();
			win->B->deactivate();
			win->moveX->deactivate();
			win->moveY->deactivate();
			win->scaleX->deactivate();
			win->scaleY->deactivate();
			win->rotate->deactivate();
			win->addB->activate();
			win->removeB->activate();
			win->rectangle->deactivate();
			win->triangle->deactivate();
			win->polygon->deactivate();
			win->polyline->deactivate();
			win->createB->deactivate();
		}
	}
	else
		std::cout << "Deselect" << std::endl;
}

void
widgetWindow::addCB(Fl_Button* button, widgetWindow* win)
{
	// Is called when the add button is pressed: activates shapeType input form and Create button
	if (win->trv == NULL)
		return;
	Flx::TreeViewItemProxy selection = win->trv->getSelection();
	if (selection.isValid())
	{
		win->rectangle->activate();
		win->triangle->activate();
		win->polygon->activate();
		win->polyline->activate();
		win->createB->activate();
	}
}

void widgetWindow::createCB(Fl_Button* button, widgetWindow* win)
{
	// Is called when the Create button is pressed, creates a new Node and displays it

	// Deactivate active widgets used for selection
	win->rectangle->deactivate();
	win->triangle->deactivate();
	win->polygon->deactivate();
	win->polyline->deactivate();
	win->createB->deactivate();

	// Create an initial "auto" shape
	list<vec3> points;
	Shape s = Shape();
	if (win->rectangle->value())
	{
		cout << "rec" << endl;
		points.push_back(vec3(0, 0, 1));
		points.push_back(vec3(0, 1, 1));
		points.push_back(vec3(1, 1, 1));
		points.push_back(vec3(1, 0, 1));
		s = Shape(vec3(0, 0, 1), Shape::RECTANGLE);
	}
	if (win->triangle->value())
	{
		cout << "tri" << endl;
		points.push_back(vec3(0, 0, 1));
		points.push_back(vec3(1, 0, 1));
		points.push_back(vec3(0.5, 1, 1));
		s = Shape(vec3(0, 0, 1), Shape::TRIANGLE);
	}
	if (win->polygon->value())
	{
		cout << "poly" << endl;
		points.push_back(vec3(0, 0, 1));
		points.push_back(vec3(-0.5, 1, 1));
		points.push_back(vec3(0.5, 1.5, 1));
		points.push_back(vec3(1.5, 1, 1));
		points.push_back(vec3(1, 0, 1));
		s = Shape(vec3(0, 0, 1), Shape::POLYGON);
	}
	if (win->polyline->value())
	{
		cout << "polyline" << endl;
		points.push_back(vec3(0, 0, 1));
		points.push_back(vec3(1, 1, 1));
		s = Shape(vec3(0, 0, 1), Shape::POLYLINE);
	}
	s.addPoints(points);

	Node n(string("New Node"), s, (mat3::translation2D(0, 0)*mat3::rotation2D(0)*mat3::scale2D(1, 1)));

	if (win->trv->getSelection() != win->trv->getRoot())
	{
		Node* parentNode = (Node*)(win->trv->getSelection()->getParent()->getData());
		parentNode->children.push_back(n);
	}
	else
	{
		win->drawing->root = n;
	}

	win->trv->clear();
	win->initialAddToTree(&win->drawing->root, &win->trv->getRoot(), win->trv);
	win->drawing->redraw();

	// for use with animation
	if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
}

void
widgetWindow::removeCB(Fl_Button* button, widgetWindow* win)
{
	// Is called when the remove button is pressed: handles removal of a + or - Node
	cout << (win->trv->getSelection()->getParent()->getData() == NULL) << endl;

	if (!win->trv->getSelection()->isLeaf())
	{
		// If the Node is a leaf - don't do anything
		return;
	}

	if (win->trv->getSelection()->getParent()->getData() == NULL)
	{
		// If the Node being removed is the last Node, call the clear callback
		clearCB(win->clearB, win);
	}
	else
	{
		// Otherwise, remove the Node
		if (win->trv == NULL)
			return;
		Flx::TreeViewItemProxy selection = win->trv->getSelection();
		if (win->trv->getSelection()->getData() && selection != win->trv->getRoot())
		{
			// If it is a + Node/start of branch
			Flx::TreeViewItemProxy p = win->trv->getSelection()->getParent();
			Node* parent_node = (Node*)(p->getData());
			Node* child = (Node*)win->trv->getSelection()->getData();

			list<Node>::iterator i;
			for (i = parent_node->children.begin(); i != parent_node->children.end();)
			{
				if (!i->getName().compare(((Node*)selection->getData())->getName()))
				{
					i = parent_node->children.erase(i);
					i = parent_node->children.end();
				}
				else
				{
					++i;
				}
			}

			win->drawing->redraw();
		}
		if (selection.isValid() && selection->isLeaf() && selection != win->trv->getRoot())
		{

			// If it is a - Node/closing leaf
			string name = selection->getLabel();
			Flx::TreeViewItemProxy parent = selection->getParent();
			win->trv->removeLeaf(selection);
			if (!name.compare(parent->getLabel()))
			{
				// If the Node has a parent left with the same name, purposely don't call
				// selectCB (will deactivate remove button). This way the Node can be removed
				win->trv->select(parent);
			}
			else if (parent->isLeaf())
			{
				// If the parent Node is a leaf (the child has been removed), don't call selectCB
				win->trv->select(parent);
			}
			else
			{
				// If the opening Node and closing Node have been removed, the parent will have a new label
				// call selectCB to deactivate the remove button
				win->trv->select(parent);
				selectCB(win->trv, win);
			}

		}
	}

	// for use with animation
	if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
}

void
widgetWindow::clearCB(Fl_Button* button, widgetWindow* win)
{
	// Called to clear the tree and drawing
	if (win->trv == NULL)
		return;
	win->textName->deactivate();
	win->R->deactivate();
	win->G->deactivate();
	win->B->deactivate();
	win->moveX->deactivate();
	win->moveY->deactivate();
	win->scaleX->deactivate();
	win->scaleY->deactivate();
	win->rotate->deactivate();
	win->addB->deactivate();
	win->removeB->deactivate();
	win->rectangle->deactivate();
	win->triangle->deactivate();
	win->polygon->deactivate();
	win->polyline->deactivate();
	win->createB->deactivate();

	win->trv->clear();
	win->drawing->root = Node();
	win->drawing->redraw();

	// for use with animation
	if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
}

void
widgetWindow::resetCB(Fl_Button* button, widgetWindow* win)
{
	// "Magic Button" - called to reset the scene graph to its original form
	if (win->trv == NULL)
		return;
	win->trv->clear();
	win->drawing->root = win->drawing->rootcpy;
	initialAddToTree(&win->drawing->root, &win->trv->getRoot(), win->trv);
	win->drawing->redraw();

	// for use with animation
	if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
}

void
widgetWindow::colorCB(Fl_Slider* slider, widgetWindow* win)
{
	// Called whenever R, G, or B sliders are in use to actively change color of selected Node
	if (win->trv->getSelection().isValid()) {
		if (win->trv->getSelection()->getData())
		{
			std::cout << win->trv->getSelection()->getLabel() << std::endl;

			Node* r = ((Node*)(win->trv->getSelection()->getData()));
			r->shape.color[0] = (float)win->R->value();
			r->shape.color[1] = (float)win->G->value();
			r->shape.color[2] = (float)win->B->value();

			win->drawing->redraw();

			// for use with animation
			if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
		}
	}
	else
		std::cout << "Deselect" << std::endl;
}

void
widgetWindow::translCB(Fl_Slider* slider, widgetWindow* win)
{
	// Is called for all transformation changes: translation, rotation, and scale
	if (win->trv->getSelection().isValid()) {
		if (win->trv->getSelection()->getData())
		{
			std::cout << win->trv->getSelection()->getLabel() << std::endl;

			Node* r = ((Node*)(win->trv->getSelection()->getData()));

			r->transformation = (r->transformation)*(
				mat3::translation2D((float)win->moveX->value(), (float)win->moveY->value())
				// Unlike the rollers, the rotation widget does not work well if reset to 0 every time,
				// to solve the issue don't reset to 0, but use 0 value if the rotation value has been unchanged
				*mat3::rotation2D(win->rotate->changed() ? (float)win->rotate->value() : 0)
				*mat3::scale2D((float)win->scaleX->value(), (float)win->scaleY->value())
				);

			win->drawing->redraw();
			win->moveX->value(0); win->moveY->value(0);
			win->scaleX->value(1); win->scaleY->value(1);

			// for use with animation
			if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
		}
	}
	else
		std::cout << "Deselect" << std::endl;
}

void
widgetWindow::nameCB(Fl_Input* input, widgetWindow* win)
{
	// Called when the name input changes
	if (win->trv->getSelection().isValid()) {
		if (win->trv->getSelection()->getData())
		{
			std::cout << win->trv->getSelection()->getLabel() << std::endl;

			win->trv->getSelection()->label = win->textName->value();
			Node* node = ((Node*)(win->trv->getSelection()->getData()));
			node->setName(win->textName->value());
			win->trv->redraw();

			// for use with animation
			if (win->isAnimating) { win->drawing->frames[(win->changeFrame->value()) - 1] = win->drawing->root; }
		}
	}
	else
		std::cout << "Deselect" << std::endl;
}

//////// Animation callback methods

void 
widgetWindow::beginAnimationCB(Fl_Button* button, widgetWindow* win)
{
	// Called when the user is ready to begin animating. The number of frames can't be changed after this button is pressed.
	win->changeFrame->maximum(win->numFrames->value());
	win->changeFrame->activate(); win->playCurrent->activate(); win->renderFull->activate(); win->moveForward->activate(); win->goBack->activate();
	win->totalFrames = (win->numFrames->value()) - 1;
	win->numFrames->deactivate();
	win->beginAnimation->deactivate();

	for (int i = 0; i <= win->totalFrames; i++)
	{
		win->drawing->frames.push_back(win->drawing->root);
	}

	win->current = 0;
	win->isAnimating = true;
}

void
widgetWindow::moveForwardCB(Fl_Button* button, widgetWindow* win)
{
	// Called when the forward button is pressed
	int incr = win->changeFrame->value() + 1;
	if (incr <= (win->totalFrames + 1))
	{
		win->changeFrame->value(incr);
	}
	changeFrameCB(win->changeFrame, win);
}

void
widgetWindow::goBackCB(Fl_Button* button, widgetWindow* win)
{
	// Called when the back button is pressed
	int decr = win->changeFrame->value() - 1;
	if (decr >= 1)
	{
		win->changeFrame->value(decr);
	}
	changeFrameCB(win->changeFrame, win);
}

void 
widgetWindow::changeFrameCB(Fl_Value_Slider* counter, widgetWindow* win)
{
	// Called when the slider changes. Changes the frame by updating tree/treeView data
	win->trv->clear();
	win->drawing->root = win->drawing->frames[(win->changeFrame->value()) - 1];
	initialAddToTree(&win->drawing->root, &win->trv->getRoot(), win->trv);
	win->drawing->redraw();
}

void 
widgetWindow::playCurrentCB(Fl_Button* button, widgetWindow* win)
{
	// Plays the animation from the current frame the user is on by switching the screen at fps rate
	win->isPlaying = !win->isPlaying;
	win->current = win->changeFrame->value() - 1;

	// Calls playCB with specified FPS
	Fl::add_timeout(1.0 / FPS, playCB, win); // 5 fps
}

void 
widgetWindow::playCB(void *data)
{
	// Flips through the frames on a timer
	widgetWindow* win = (widgetWindow*)data;
	if (win->isPlaying)
	{
		if (win->current > win->totalFrames) 
		{ 
			// If all frames have been seen, stop and go back to animation mode
			changeFrameCB(win->changeFrame, win); 
			win->isPlaying = false; 
			win->changeFrame->activate(); 
		}
		else
		{
			// If there are still frames to be seen, keep going
			win->drawing->root = win->drawing->frames[win->current];
			win->drawing->redraw();
			win->current++;
			Fl::repeat_timeout(1.0 / FPS, playCB, win); // 5 fps
			win->changeFrame->deactivate();
		}
	}
}

void 
widgetWindow::renderFullCB(Fl_Button* button, widgetWindow* win)
{
	// Called to render the finished animation to jpeg files
	win->changeFrame->deactivate();

	int frames = 0;
	for (int i = 0; i <= win->totalFrames; i++)
	{
		// If all frames have not been rendered, go to the next frame
		win->drawing->root = win->drawing->frames[i];
		win->drawing->redraw();
		Fl::check();		// Wait for the window to update before exporting it to jpeg

		//////// Class-given code for FL_GL_Window->jpeg output:

		// Create the filename
		std::string s;
		std::stringstream out;
		out << frames++;
		s = out.str();
		std::string filename = "anim\\testing_" + s + ".jpg";

		// Create a BYTE array
		// Make the BYTE array, factor of 3 because it's RBG.
		int width = 500; int height = 500;
		BYTE* pixels = new BYTE[3 * width * height];

		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		struct jpeg_compress_struct cinfo;
		struct jpeg_error_mgr jerr;

		/* this is a pointer to one row of image data */
		JSAMPROW row_pointer[1];
		FILE *outfile = NULL;
		fopen_s(&outfile, filename.c_str(), "wb");

		if (!outfile)
		{
			std::cout << "Error opening output jpeg file:" << filename << std::endl;
			return;
		}
		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_compress(&cinfo);
		jpeg_stdio_dest(&cinfo, outfile);

		/* Setting the parameters of the output file here */
		cinfo.image_width = width;
		cinfo.image_height = height;
		cinfo.input_components = 3;		// bytes_per_pixel;
		cinfo.in_color_space = JCS_RGB; // color_space;
		/* default compression parameters, we shouldn't be worried about these */
		jpeg_set_defaults(&cinfo);
		/* Now do the compression .. */
		jpeg_start_compress(&cinfo, TRUE);
		/* like reading a file, this time write one row at a time */
		std::list<JDIMENSION> lines; // switch the image to right side up
		int cnt = 0;
		while (cnt < cinfo.image_height)
		{
			lines.push_front(cnt);
			cnt++;
		}
		std::list<JDIMENSION>::iterator it;

		for (it = lines.begin(); it != lines.end(); ++it){
			row_pointer[0] = &pixels[(*it) * cinfo.image_width *  cinfo.input_components];
			jpeg_write_scanlines(&cinfo, row_pointer, 1);
		}

		/* similar to read file, clean up after we're done compressing */
		jpeg_finish_compress(&cinfo);
		jpeg_destroy_compress(&cinfo);
		fclose(outfile);

		delete[] pixels;

		//////// End of class-given code
	}
	win->changeFrame->activate();
	changeFrameCB(win->changeFrame, win);
}

//////// Construct TreeView tree

void
widgetWindow::initialAddToTree(Node* root, Flx::TreeViewItemProxy* parent, Flx::TreeView* trv)
{
	// Called before TreeView use to add all scene graph Nodes to tree
	Flx::TreeViewItemProxy child = trv->addChild(*parent, root->getName(), (void*)root);
	trv->addChild(child, root->getName());

	int j = 0;
	while (j < root->children.size())
	{
		list<Node>::iterator i;
		for (i = root->children.begin(); i != root->children.end(); ++i)
		{
			initialAddToTree(&*i, &child, trv);
			j++;
		}
	}
}

//////// Constructors & Destructors

widgetWindow::widgetWindow(int x, int y, int w, int h, char* c):Fl_Window(x, y, w, h, c)
{
	// Create a new widgetWindow
	// Define a window for the drawing, then create the GUI
	drawing = new MyWindow(205, 0, 500, 500, "Display");

	trv = new Flx::TreeView(0, 5, 200, 300, 10, 20);
	trv->callback((Fl_Callback*)selectCB, this);

	addB = new Fl_Button(0, 310, 40, 30, "Add");
	addB->deactivate();
	addB->callback((Fl_Callback*)addCB, this);

	removeB = new Fl_Button(40, 310, 80, 30, "Remove");
	removeB->deactivate();
	removeB->callback((Fl_Callback*)removeCB, this);

	clearB = new Fl_Button(120, 310, 80, 30, "Clear");
	clearB->callback((Fl_Callback*)clearCB, this);

	resetB = new Fl_Button(120, 340, 80, 30, "Reset");
	resetB->callback((Fl_Callback*)resetCB, this);

	// animation handling

	numFrames = new Fl_Value_Input(225, 511, 48, 25, "# FRAMES");
	numFrames->labeltype(FL_ENGRAVED_LABEL); numFrames->minimum(1); numFrames->maximum(100); numFrames->step(1); numFrames->value(1); numFrames->align(Fl_Align(FL_ALIGN_LEFT));

	beginAnimation = new Fl_Button(120, 549, 154, 25, "BEGIN ANIMATING");
	beginAnimation->labeltype(FL_ENGRAVED_LABEL);
	beginAnimation->callback((Fl_Callback*)beginAnimationCB, this);

	changeFrame = new Fl_Value_Slider(283, 511, 193, 25, "CURRENT FRAME");
	changeFrame->labeltype(FL_ENGRAVED_LABEL); changeFrame->minimum(1); changeFrame->maximum(100); changeFrame->step(1); changeFrame->value(1); changeFrame->deactivate(); changeFrame->type(FL_HOR_NICE_SLIDER); changeFrame->align(Fl_Align(FL_ALIGN_BOTTOM_RIGHT));
	changeFrame->callback((Fl_Callback*)changeFrameCB, this);

	moveForward = new Fl_Button(320, 550, 25, 25, "@>");
	moveForward->labeltype(FL_ENGRAVED_LABEL); moveForward->deactivate();
	moveForward->callback((Fl_Callback*)moveForwardCB, this);

	goBack = new Fl_Button(283, 550, 25, 25, "@<");
	goBack->labeltype(FL_ENGRAVED_LABEL); goBack->deactivate();
	goBack->callback((Fl_Callback*)goBackCB, this);

	playCurrent = new Fl_Button(488, 511, 195, 25, "PLAY FROM THIS FRAME");
	playCurrent->labeltype(FL_ENGRAVED_LABEL); playCurrent->deactivate();
	playCurrent->callback((Fl_Callback*)playCurrentCB, this);

	renderFull = new Fl_Button(488, 549, 133, 25, "RENDER");
	renderFull->labeltype(FL_ENGRAVED_LABEL); renderFull->deactivate();
	renderFull->callback((Fl_Callback*)renderFullCB, this);

	// features: translate, rotate, scale, color, name

	box(FL_THIN_UP_BOX);

	R = new Fl_Slider(725, 25, 25, 55, "R");
	R->selection_color(FL_RED); R->labeltype(FL_ENGRAVED_LABEL); R->labelcolor(FL_RED); R->minimum(0); R->maximum(1); R->step(0.001); R->deactivate();
	R->callback((Fl_Callback*)colorCB, this);
	
	G = new Fl_Slider(750, 25, 25, 55, "G");
	G->selection_color(FL_DARK_GREEN); G->labeltype(FL_ENGRAVED_LABEL); G->labelcolor(FL_DARK_GREEN); G->minimum(0); G->maximum(1); G->step(0.001); G->deactivate();
	G->callback((Fl_Callback*)colorCB, this);
	
	B = new Fl_Slider(775, 25, 25, 55, "B");
	B->selection_color((Fl_Color)137); B->labeltype(FL_ENGRAVED_LABEL); B->labelcolor((Fl_Color)137); B->minimum(0); B->maximum(1); B->step(0.001); B->deactivate();
	B->callback((Fl_Callback*)colorCB, this);

	moveX = new Fl_Roller(725, 120, 25, 120, "MOVE X");
	moveX->box(FL_DOWN_BOX); moveX->labeltype(FL_ENGRAVED_LABEL); moveX->minimum(-10); moveX->maximum(10); moveX->deactivate();
	moveX->callback((Fl_Callback*)translCB, this);
	
	moveY = new Fl_Roller(793, 120, 25, 120, "MOVE Y");
	moveY->box(FL_DOWN_BOX); moveY->labeltype(FL_ENGRAVED_LABEL); moveY->minimum(-10); moveY->maximum(10); moveY->deactivate();
	moveY->callback((Fl_Callback*)translCB, this);

	scaleX = new Fl_Roller(861, 25, 30, 90, "SCALE X");
	scaleX->box(FL_DOWN_BOX); scaleX->labeltype(FL_ENGRAVED_LABEL); scaleX->minimum(0.001); scaleX->maximum(2); scaleX->step(0.001); scaleX->value(1); scaleX->deactivate();
	scaleX->callback((Fl_Callback*)translCB, this);

	scaleY = new Fl_Roller(861, 144, 30, 90, "SCALE Y");
	scaleY->box(FL_DOWN_BOX); scaleY->labeltype(FL_ENGRAVED_LABEL); scaleY->minimum(0.001); scaleY->maximum(2); scaleY->step(0.001); scaleY->value(1); scaleY->deactivate();
	scaleY->callback((Fl_Callback*)translCB, this);

	rotate = new Fl_Dial(755, 277, 100, 100, "ROTATION");
	rotate->labeltype(FL_ENGRAVED_LABEL); rotate->minimum(-10); rotate->maximum(10); rotate->step(1); rotate->value(0); rotate->deactivate();
	rotate->callback((Fl_Callback*)translCB, this);

	textName = new Fl_Input(725, 415, 130, 30, "NAME");
	textName->labeltype(FL_ENGRAVED_LABEL); textName->deactivate(); textName->align(Fl_Align(FL_ALIGN_TOP_LEFT));
	textName->callback((Fl_Callback*)nameCB, this);

	rectangle = new Fl_Round_Button(725, 450, 191, 24, "RECTANGLE");
	rectangle->labeltype(FL_ENGRAVED_LABEL); rectangle->type(FL_RADIO_BUTTON); rectangle->deactivate();
	triangle = new Fl_Round_Button(725, 470, 191, 24, "TRIANGLE");
	triangle->labeltype(FL_ENGRAVED_LABEL); triangle->type(FL_RADIO_BUTTON); triangle->deactivate();
	polygon = new Fl_Round_Button(725, 490, 191, 24, "POLYGON");
	polygon->labeltype(FL_ENGRAVED_LABEL); polygon->type(FL_RADIO_BUTTON); polygon->deactivate();
	polyline = new Fl_Round_Button(725, 510, 191, 24, "POLYLINE");
	polyline->labeltype(FL_ENGRAVED_LABEL); polyline->type(FL_RADIO_BUTTON); polyline->deactivate();

	createB = new Fl_Button(725, 540, 80, 30, "Create");
	createB->deactivate();
	createB->callback((Fl_Callback*)createCB, this);

	// call initialAddToTree to add all Nodes from the scene graph in drawing to the TreeView widget

	initialAddToTree(&drawing->root, &trv->getRoot(), trv);

	// useful bools for animation mode

	isAnimating = false;
	isPlaying = false;
}

widgetWindow::~widgetWindow()
{
	delete(drawing);
	delete(trv);
	delete(addB);
	delete(removeB);
	delete(clearB);
	delete(resetB);
	delete(R);
	delete(G);
	delete(B);
	delete(moveX);
	delete(moveY);
	delete(scaleX);
	delete(scaleY);
	delete(rotate);
	delete(textName);
	delete(rectangle);
	delete(triangle);
	delete(polygon);
	delete(polyline);
	delete(createB);
	delete(numFrames);
	delete(beginAnimation);
	delete(changeFrame);
	delete(moveForward);
	delete(goBack);
	delete(playCurrent);
	delete(renderFull);
	drawing = NULL;
	trv = NULL;
	addB = NULL;
	removeB = NULL;
	clearB = NULL;
	resetB = NULL;
	R = NULL;
	G = NULL;
	B = NULL;
	moveX = NULL;
	moveY = NULL;
	scaleX = NULL;
	scaleY = NULL;
	rotate = NULL;
	textName = NULL;
	rectangle = NULL;
	triangle = NULL;
	polygon = NULL;
	polyline = NULL;
	createB = NULL;
	numFrames = NULL;
	beginAnimation = NULL;
	changeFrame = NULL;
	moveForward = NULL;
	goBack = NULL;
	playCurrent = NULL;
	renderFull = NULL;
}
