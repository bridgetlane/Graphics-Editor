/*
 *  Node.h
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Specifies information for Node.cpp
 *
 */

#ifndef NODE_H
#define NODE_H

#include <list>
#include <string>
#include "Shape.h"
#include "mat3.h"

using namespace std;

class Node
{
private:

	//////// Member variables

	string name;
public:
	Shape shape;
	list<Node> children;
	mat3 parentT;
	mat3 transformation;
	
	//////// Constructors & Destructors

	Node();
	Node(string n, Shape s, mat3 transform);
	~Node();

	//////// Getters & Setters

	string getName();
	void setName(string n);
	list<Node> getChildren();
	Shape getShape();
	void setParentTransf(mat3 t);
	void setTransform(mat3 t);
	Node* getNodeByName(Node* node, string name);

	//////// Add & Remove a Child

	void addChild(Node child);
	void removeChild(string n);

	//////// Scene Graph

	void applyTranform(Node parent);
	void applyAllTransformations(Node* parent);
	void drawAll(Node parent);

	//////// Printing

	void printTransform();
	void printChildren();
	void print();
};

#endif
