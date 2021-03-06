# Graphics & Animation Editor

## Overview

This code is structured to create a GUI that allows for manipulation of a scene graph. In order to create a scene graph, the user can create a new  Shape, then store the Shape and the desired transformations into a Node. The  user can then specify parent-child relationships. The Node class allows for traversal of the multi-layer parent-child tree using applyAllTransformations, which takes in a root Node. Then the user can draw this tree using drawAll(Node parent).

The graphical user interface allows for the user to add a node, remove a node from the scene graph, clear the entire tree, and reset the scene graph to its original state. For each Node, the user can manually change the RGB color values, translation, scale, rotation, and name.

The animation portion of the interface allows the user to create a simple, flip-book style animation and render the animation to jpeg files. The process of use is pretty simple: first, model any shapes you will use in the modeling window. Then, specify the number of frames needed for your animation and hit "BEGIN ANIMATING." The number of frames cannot be changed after this button is hit. Every frame will start off with the same structure identical to what is in the modeling window when this button is hit, so it is advantageous for the user to model all shapes before hand (easier to delete a Node than recreate it in multiple frames). At this point, the user can easily flip between frames, play the animation back (from the current frame), and finally, render the completed animation to jpeg images.

(Uses vec3, mat3, and treeView - not reviewed here)

The main method creates and displays a new widgetWindow, which is a subclass of Fl_Window. In the widgetWindow constructor, a new MyWindow is created. The scene graph is created and drawn in Window.cpp.

## Shape

Member variables:
* Private:
 * list<vec3> points: List of points that create the Shape
* Public:
 * vec3 color: color of the Shape
 * list<vec3> tempPoints: Temporary points stored after a transformation is applied. Used for drawing
 * enum Type { RECTANGLE, POLYGON, POLYLINE, TRIANGLE }: Defines Shape Type options
 * Type type: Specifies the Type of the Shape

Constructors & Destructor:
* Shape(): Constructs and empty Shape
* Shape(vec3 c, Type t): Creates a new Shape, taking in the color and type
* ~Shape(): Destructor

Getters & Setters:
* void setType(Type t): Sets the Type of the Shape
* vec3 getColor(): Returns the color of the Shape
* void setColor(int x, int y, int z): Sets the color of the Shape

Add & Remove a Point:
* void addPoint(vec3 point): Add a point to the Shape
* void addPoints(list<vec3> points): Add multiple points to the Shape
* void removePoint(int x, int y, int z): Remove a point from the Shape

Transformations & Drawing:
* void drawShape(list<vec3> pointList): Draws a Shape using the passed-in list of points to the Shape's points, storing the new points in tempPoints and returning the new parent transformation matrix

Printing:
* void printType(): Prints the Type of the Shape
* void printColor(): Prints the color of the Shape
* void printPoints(): Prints the points of the Shape
* void print(): Prints all relevant information about the Shape (Type, color, points)

## Node

Member variables:
* Private:
 * string name: name of the Node
* Public:
 * Shape shape: Shape object belonging to the Node
 * list<Node> children: Pointers to the Node's children
 * mat3 parentT: Transformations the Node has undergone
 * mat3 transformation: Transformation associated with the Node

Constructors & Destructor:
* Node(): Constructs an empty Node
* Node(string n, Shape s, mat3 transform): Creates a new Node, taking in the name, Shape, and transformation associated with the Node.
* ~Node(): Destructor

Getters & Setters:
* string getName(): Returns the Node name
* void setName(string n): Sets the Node name
* list<Node> getChildren(): Returns the Node's children
* Shape getShape(): Returns the Node's Shape
* void setParentTransf(mat3 t): Sets the Node's transformation background
* void setTransform(mat3* t): Sets the transformation associated with the Node
* Node* getNodeByName(Node* root, string name): Returns a pointer to a node retrieved using the name and root of tree

Add & Remove a Child:
* void addChild(Node child): Adds a child to the Node's children
* void removeChild(string n): Removes a child from the Node's children

Scene Graph Manipulation:
* void applyTranform(Node parent): Used internally to apply one set of transformations (the transformation applied to that Node and it's children)
* void applyAllTransformations(Node* parent): Used by user to apply all the transformations in the structure, starting with the root Node
* void drawAll(Node parent): Used by the user to draw the finished structure. For use after the transformations have been applied.

Printing:
* void printTransform(): Prints the transformation matrix associated with the Node
* void printChildren(): Prints the children associated with the Node
* void print(): Prints all relevant information about the Node (name, children, and transformation)

## MyWindow

Member variables:
* Private:
 * void draw(): Draws to the window
 * Node current: For use with animating - keeps track of the tree for the current frame
* Public:
 * Node root: The root of the tree
 * Node rootcpy: A copy of the original tree, used for reset feature
 * vector<Node> frames: For use with animating - holds the root of the tree for each frame

Animation:
* Node getTreeToDraw(): Returns the tree to be drawn (current)
* void setTreeToDraw(Node n): Changes current

Constructors & Destructor:
* MyWindow(int x, int y, int w, int h, char* c): Creates a new MyWindow. The scene graph is created here and stored in root
* virtual ~MyWindow(): Destructor

## widgetWindow

Member variables:
* Private:
 * bool isAnimating: Useful bool for indicating if the user has begun animating
 * bool isPlaying: Useful bool for indicating if the animation is undergoing playback
 * MyWindow* drawing: Pointer to the MyWindow created when widgetWindow is called
 * Flx::TreeView* trv: The TreeView widget for the GUI
 * Fl_Button* addB: The add button
 * Fl_Button* removeB: The remove button
 * Fl_Button* clearB: The clear button
 * Fl_Button* resetB: The reset button
 * Fl_Slider* R: R/G/B
 * Fl_Slider* G: R/G/B
 * Fl_Slider* B: R/G/B
 * Fl_Roller* moveX: X translation
 * Fl_Roller* moveY: Y translation
 * Fl_Roller* scaleX: X scale
 * Fl_Roller* scaleY: Y scale
 * Fl_Dial* rotate: Rotation
 * Fl_Input* textName: Name input field
 * Fl_Round_Button* rectangle: Indicates type of Shape to add
 * Fl_Round_Button* triangle: Indicates type of Shape to add
 * Fl_Round_Button* polygon: Indicates type of Shape to add
 * Fl_Round_Button* polyline: Indicates type of Shape to add
 * Fl_Button* createB: Create button
 * Fl_Value_Input* numFrames: Specify number of frames
 * Fl_Button* beginAnimation: Begin animation button
 * Fl_Value_Slider* changeFrame: Value slider to change the current frame
 * Fl_Button* moveForward: Button to move forward one frame
 * Fl_Button* goBack: Button to go back one frame
 * Fl_Button* playCurrent: Play the animation
 * Fl_Button* renderFull: Render the animation

Callback Methods (Private):
* static void selectCB(Flx::TreeView* tree, widgetWindow* win): Called when a Node of the TreeView is selected
* static void addCB(Fl_Button* button, widgetWindow* win): Called when the add button is pressed, enables the create button and the shapeType input field
* static void createCB(Fl_Button* button, widgetWindow* win): Called when the create button is pressed. Takes the input from the shapeType field and creates a new Shape
* static void removeCB(Fl_Button* button, widgetWindow* win): Removes a Node from the scene graph
* static void clearCB(Fl_Button* button, widgetWindow* win): Clears the scene graph
* static void resetCB(Fl_Button* button, widgetWindow* win): Resets the scene graph to its original state
* static void colorCB(Fl_Slider* slider, widgetWindow* win): Called to change the R/G/B values of a Node's Shape
* static void translCB(Fl_Slider* slider, widgetWindow* win): Called for all translations
* static void nameCB(Fl_Input* input, widgetWindow* win): Called to change the name of a Node

Animation (Private):
* static void beginAnimationCB(Fl_Button* button, widgetWindow* win): Called to begin animating
* static void changeFrameCB(Fl_Value_Slider* counter, widgetWindow* win): Called when user changes the current frame
* static void moveForwardCB(Fl_Button* button, widgetWindow* win): Increment slider and call changeFrameCB
* static void goBackCB(Fl_Button* button, widgetWindow* win): Decrement the slider and call changeFrameCB
* static void playCurrentCB(Fl_Button* button, widgetWindow* win): Called to start the animation playback, calls playCB
* static void playCB(void *data): Used to continually play each frame during animation playback
* static void renderFullCB(Fl_Button* button, widgetWindow* win): Renders the full animation to jpeg images

TreeView Manipulation:
* static void initialAddToTree(Node* root, Flx::TreeViewItemProxy* parent, Flx::TreeView* trv): Adds all the Nodes in the scene graph to the TreeView

Constructors & Destructor:
* widgetWindow(int x, int y, int w, int h, char* c): Creates a new widgetWindow by creating a new MyWindow and GUI
* virtual ~widgetWindow(): Destructor

## Example Usage

(in window.cpp, constructor)

Each Node for the scene graph has to be created. Create a Node by first
creating the points and a new Shape:

```cpp
    list<vec3> points;
    points.push_back(vec3(-1, -1, 1));
    points.push_back(vec3(-1, 1, 1));
    points.push_back(vec3(1, 1, 1));
    points.push_back(vec3(1, -1, 1));

    Shape redSquare(vec3(1, 0, 0), Shape::RECTANGLE);
    redSquare.addPoints(points);
```

Then create a new Node for the Shape:

```cpp
    Node square(string("Red Square"),
                redSquare,
                // Specify translation, rotation, and scale associated with
                // the Node here
                (mat3::translation2D(0, 0)*mat3::rotation2D(0)*mat3::scale2D(1, 1))
                );
```

After creating all the Nodes, specify parent-children relationships:

```cpp
    square.addChild(other_child_node);
```

Store the root node in root, and finally, write:

```cpp
    rootcpy = root;
```

To store a copy of the original scene graph (for use with reset button).

The rest is done for you in the draw() method, and the GUI is created in
widgetWindow.cpp.

## Difficulties

In order to create the animation features, I had to figure out the best way to handle playback without saving the images. I also had to find a way to store each frame's tree. I allow the user to still add/remove Nodes, because removing that feature would not have made my approach simpler.
