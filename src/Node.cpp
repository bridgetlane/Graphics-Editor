/*
 *  Node.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Used to create and manipulate a Node. Contains methods to
 *  run and display a scene graph, constructed as a tree of Nodes.
 *
 */

#include "Node.h"
#include "window.h"
#include <iostream>

using namespace std;

//////// Constructors & Destructors

Node::Node(string n, Shape s, mat3 t)
{
	shape = s;
	name = n;
	parentT = mat3::identity();
	transformation = t;
}

Node::Node()
{
	shape = Shape();
	name = string("blank");
	parentT = mat3::identity();
	transformation = mat3::identity();
}

Node::~Node()
{
}

//////// Getters & Setters

string 
Node::getName()
{
	return name;
}

void 
Node::setName(string n)
{
	name = n;
}

list<Node> 
Node::getChildren()
{
	return children;
}

Shape 
Node::getShape()
{
	return shape;
}

void 
Node::setParentTransf(mat3 t)
{
	parentT = t;
}

void
Node::setTransform(mat3 t)
{
	transformation = t;
}

Node* 
Node::getNodeByName(Node* node, string name)
{
	if (!(node->getName().compare(name))) 
	{
		return node;
	}
	else {
		int j = 0;
		while (j < node->children.size())
		{
			list<Node>::iterator i;
			for (i = node->children.begin(); i != node->children.end(); ++i)
			{
				i->getNodeByName(&*i, name);
				j++;
			}
		}
	}
}

//////// Add & Remove a Child

void 
Node::addChild(Node child)
{
	children.push_back(child);
}

void 
Node::removeChild(string n)
{
	list<Node>::iterator i;
	for (i = children.begin(); i != children.end(); )
	{
		if ((i->name.compare(n)) == 0)
		{
			cout << i->name << " equals " <<n << endl;
			i = children.erase(i);
		}
		else
		{
			++i;
		}
	}
}

//////// Scene Graph

void
Node::applyTranform(Node parent)
{
	// use parent's Node.transformation (transformation to be applied)
	// use current Node's parentTransf (transformation history)
	// apply the transformation to the current Node and all children
	parentT = shape.transform(parentT, parent.transformation);

	int j = 0;
	while (j < children.size())
	{
		list<Node>::iterator i;
		for (i = children.begin(); i != children.end(); ++i)
		{
			(*i).applyTranform(parent);
			j++;
		}
	}
}

void
Node::applyAllTransformations(Node* parent)
{
	// apply all transformations in the tree, starting with the given parent
	applyTranform(*parent);

	list<Node>::iterator i;
	for (i = parent->children.begin(); i != parent->children.end(); i++)
	{
		(*i).applyAllTransformations(&*i);
	}

	parent->parentT = mat3::identity();
}

void 
Node::drawAll(Node parent)
{
	// draw the entire tree (to be used after transformations are applied)
	shape.drawShape(parent.shape.tempPoints);

	list<Node>::iterator i;
	for (i = parent.children.begin(); i != parent.children.end(); i++)
	{
		(*i).drawAll(*i);
	}
}

//////// Printing

void 
Node::printTransform()
{
	cout << "transform: " << endl;
	transformation.print();
	cout << endl;
}

void
Node::printChildren()
{
	cout << "children:" << endl;
	list<Node>::iterator i;
	for (i = children.begin(); i != children.end(); i++) { cout << (*i).getName() << endl; }
	cout << endl;
}

void
Node::print()
{
	cout << "-------------------" << endl;
	cout << name << endl;
	cout << endl;
	printChildren();
	printTransform();
	cout << "-------------------" << endl;
}
