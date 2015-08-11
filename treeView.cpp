/*
 *  TreeView widget - code provided in class
 */

#include "treeView.h"

#include <FL/fl_draw.H>

// ------ TREE_VIEW_ITEM --------------------------------------------------- //
Flx::TreeView::Item::Item(){
	this->self = this;
	this->parent = NULL;
	this->child = NULL;
	this->next = NULL;
	this->previous = NULL;
    this->nextSibling = NULL;
    this->previousSibling = NULL;
}

Flx::TreeView::Item::Item(Item* parent, std::string label, void* data){
	this->self = this;
	this->parent = parent;
	this->child = NULL;
	this->next = NULL;
	this->previous = NULL;
    this->nextSibling = NULL;
    this->previousSibling = NULL;    
	this->label = label;
	this->data = data;
	if (parent != NULL)
		level = parent->level+1;
	else
		level = 0;
}

Flx::TreeViewItemProxy
Flx::TreeView::Item::getParent() const{
	return TreeViewItemProxy(parent);
}

Flx::TreeViewItemProxy
Flx::TreeView::Item::getPrevious() const{
	return TreeViewItemProxy(previous);
}

Flx::TreeViewItemProxy
Flx::TreeView::Item::getNext() const{
	return TreeViewItemProxy(next);
}

bool
Flx::TreeView::Item::isLeaf() const{
	return (child == NULL);
}

void*
Flx::TreeView::Item::getData() const{
	return data;
}

int
Flx::TreeView::Item::getLevel() const{
	return level;
}

std::string
Flx::TreeView::Item::getLabel() const{
	return label;
}

// ------ TREE_VIEW --------------------------------------------------------- //
Flx::TreeView::TreeView(int x, int y, int w, int h, int indent, int rowHeight)
		: Fl_Browser_(x, y, w, h){
	this->indent = indent;
	this->rowHeight = rowHeight;
	root = new Item();
	root->label = "SCENE GRAPH";
	root->level = 0;
	type(FL_HOLD_BROWSER);
}

Flx::TreeView::~TreeView(){
	Item* item = root;
	Item* next;
	while (item){
		next = item->next;
		delete item;
		item = next;
	}
}

Flx::TreeViewItemProxy
Flx::TreeView::getSelection() const{
	return TreeViewItemProxy(static_cast<Item*>(selection()));
}

Flx::TreeViewItemProxy
Flx::TreeView::getRoot() const{
	return TreeViewItemProxy(root);
}

void*
Flx::TreeView::item_first() const{
    return root;
}

int
Flx::TreeView::item_height(void *p) const{
	return rowHeight + 2;
}

int
Flx::TreeView::item_width(void * p) const{
	return w()-6;
}

void*
Flx::TreeView::item_next(void *p) const{
	if (!p)
		return NULL;
	Item* n = static_cast<Item*>(p);
	return n->next;
}

void*
Flx::TreeView::item_prev(void *p) const{
	if (!p)
		return NULL;
	Item* n = static_cast<Item*>(p);
//	if (n->previous == root and not rootVisible)
//		return NULL;
	return n->previous;
}

void
Flx::TreeView::item_draw(void* v, int X, int Y, int W, int H) const{
	Item* node = static_cast<Item*>(v);
	if (!node) // Like saying if (node == NULL)
		return;
    Fl_Font font = textfont();
	int fontSize = textsize();
    Fl_Color color = textcolor();
	
    if (getSelection() == TreeViewItemProxy(node))
		color = fl_contrast(color, selection_color());
    if (!active_r())
		color = fl_inactive(color);
	fl_font(font, fontSize);
	fl_color(color);
//	int x_begin = X+5+((node->getLevel()-(rootVisible ? 0:1))*indent);
	int x_begin = X + 5 + (node->getLevel()*indent);
	int triangleWidth = 10;
	int triangleHeight = 6;
	int y_begin = Y+(H-triangleHeight)/2;
	fl_polygon(x_begin, y_begin+triangleHeight/2 - 2,
			   x_begin, y_begin+triangleHeight/2 + 2, 
			   x_begin+triangleWidth, y_begin+triangleHeight/2 + 2,
			   x_begin+triangleWidth, y_begin+triangleHeight/2 - 2);
	if (node->child)  // Like saying if (node->child != NULL)
		fl_polygon(x_begin+triangleWidth/2 - 2, y_begin-2,
				   x_begin+triangleWidth/2 - 2, y_begin + triangleHeight+2,
				   x_begin+triangleWidth/2 + 2, y_begin + triangleHeight+2,
				   x_begin+triangleWidth/2 + 2, y_begin-2);
	fl_draw((node->label).c_str(), x_begin+triangleWidth+3, Y,
			W-x_begin-triangleWidth-8, H, 
			Fl_Align(FL_ALIGN_LEFT|FL_ALIGN_CLIP), 0, 0);
}
Flx::TreeViewItemProxy
Flx::TreeView::addChild(TreeViewItemProxy parent,std::string label, void* data){
    if (!parent.isValid())
        return TreeViewItemProxy();
    
    // Create a new node
    Item* newNode = new Item(parent->self, label, data);
    
    // Store the node where we'll be inserting
    Item* insertPoint = parent->next;
    
    // Linked List relationships
    if (parent->next != NULL)
        parent->next->previous = newNode;
    newNode->next = parent->next;
    newNode->previous = parent->self;
    parent->next = newNode;
    
    // Update Tree relationship;
    newNode->nextSibling = parent->child;
    
    if (newNode->nextSibling)
        newNode->nextSibling->previousSibling = newNode;
    parent->child = newNode;
    
    // Update the GUI
//    if (insertPoint)
//        inserting(insertPoint, newNode);
//    else
    redraw_lines();
    
    // Return our newly created node
    return TreeViewItemProxy(newNode);
}

bool
Flx::TreeView::removeLeaf(TreeViewItemProxy node){
	// You can't remove the root
	if (node == TreeViewItemProxy(root))
		return false;
		
	// You can only remove leaves;
	if (node->child)
		return false;
		
	// Only the root should have a parent of NULL.
	if (!(node->parent))
		return false;
		
	// Update the linked list structure
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
		
	// Update the tree structure
//	if (node->previous and node->previous->sibling == node->self)
//		node->previous->sibling = node->sibling;
    if (node->previousSibling)
        node->previousSibling->nextSibling = node->nextSibling;
    if (node->nextSibling)
        node->nextSibling->previousSibling = node->previousSibling;
    
	if (node->self == node->parent->child)
		node->parent->child = node->nextSibling;
		
	// Clean up the GUI
	deleting(node->self);
	
	// Clean up memory
	delete node->self;
	redraw_lines();
	// Node has been successfully removed
	return true;
}

void
Flx::TreeView::select(TreeViewItemProxy item){
	select_only(item->self);
}

void
Flx::TreeView::clear(){
    Item* item = root->child;
	Item* next;
	while (item){
		next = item->next;
		delete item;
		item = next;
	}
    root->child = NULL;
    root->next = NULL;    
    new_list();
}
