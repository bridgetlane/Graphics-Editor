/*
 *  TreeView widget - code provided in class
 */

#ifndef TREEVIEW_H
#define TREEVIEW_H
 
#include <string>
#include <iostream>
#include <Fl/Fl_Browser_.H>

namespace Flx{

// Foward declaration
// Implementation will follow
class TreeViewItemProxy;

// This widget is a browser of data in a tree structure.
class TreeView : public Fl_Browser_{
friend class TreeViewItemProxy;
private:
    // Foward Declaration of an inner calss
	class Item;
	// How far to indent nodes between each level
	int indent;
	// How high each row is
	int rowHeight;
	// The root item.  The root does not have any siblings.
	Item* root;
protected:
	// ---------- Implemented from Fl_Browser_ ----------------------------- //
	// Draws a line in the flatlist.
	virtual void  item_draw(void* v, int X, int Y, int W, int H) const;
	// Returns the first item in the flatlist
	virtual void* item_first() const;
	// Returns the height of an item *p, which is a NodeInfo*
	virtual int   item_height(void *p) const;
	// Returns the next item of item *p, which is a NodeInfo*
	virtual void* item_next(void *p) const;
	// Returns the previous item of item *p, which is a NodeInfo*
	virtual void* item_prev(void *p) const;
	// Returns the width of item *p, which is a NodeInfo*	
	virtual int   item_width(void *p) const;	
	// ---------- End ------------------------------------------------------ //
public:
	// Constructs a new tree widget.  
	// indent is the space to indent at each level.
	// rowHeight is the height of each item in the list
	TreeView(int x, int y, int w, int h, int indent, int rowHeight);
	
	virtual ~TreeView();
	
	// Returns the root of the tree
	TreeViewItemProxy getRoot() const;
	// Returns data about the selected item
	TreeViewItemProxy getSelection() const;
	// Selects the given proxy.
	void select(TreeViewItemProxy item);
	
	// Creates a new node as a child of parent with the associated label and 
	// data.  If the parent already has children, this new child will become the
	// first child displayed after the parent in the list.
	// 
	// Returns the newly created child
	TreeViewItemProxy addChild(TreeViewItemProxy parent,std::string label, 
								  void* data = NULL);
	
	// Removes a node if its not the root and it is childless.  
	// 
	// Returns true only if the node was removed from the list and deleted.
	bool removeLeaf(TreeViewItemProxy node);
    
    // Erases every element in the tree (excluding the root).
    void clear();
private:
	// TreeViewItem is a class which represents one line or node in the tree
	// browser widget
	class Item{

	// Gives TreeWidget access to all of TreeViewItem private members
	friend class TreeView;

	private:
		// Pointers for maintaining the tree structure for adding/removing nodes
		Item* parent;
		Item* child;
		Item* nextSibling;
        Item* previousSibling;
	
		// Pointers for maintaining flatlist of the tree which gets displayed
		// The flatlist is the list that gets displayed
		Item* next;
		Item* previous;
	
		// The depth of the tree.  Used to determine how far to indent the
        // display.
		int level;
	
		// Associates data with the node.  This is useful when you get the
        // selected node and want to find out which node in the model its
        // associated with.
		void* data;
	
		// Hack to access private members for friends.  This is a pointer
		// which should point to the current TreeViewItem
		Item* self;
	
		// Default constructor.  Used by the tree widget to create the root.
		//
		// By making the constructor private only this class and its friends can
		// instantiate it
		Item();
	
		// Constructor for adding nodes to a hierarchy
		Item(Item* parent, std::string, void* data);
	public:
		// Display text
		std::string label;

		// Returns the node's label
		std::string getLabel() const;

		// Returns the data that the node is storing
		void* getData() const;

		// Returns the level of the node
		int getLevel() const;
	
		// Returns the parent in the tree structure
		TreeViewItemProxy getParent() const;
		
		// Returns the previous item in the flatlist
		TreeViewItemProxy getPrevious() const;
		
		// Returns the next item in the flatlist
		TreeViewItemProxy getNext() const;
	
		// Returns true if and only if the node is 
		bool isLeaf() const;
	};
};

// A simple proxy for our tree view item
//
// We can treat TreeViewItemProxy like a pointer to a TreeViewItem
// except it hides the underlying memory to keep memory management
// responsiblities internal.
class TreeViewItemProxy{
	private:
		TreeView::Item* data;
	public:
		// Constructs an invalid/NULL Proxy
		TreeViewItemProxy(){data = NULL;}
		
		// Contructs a proxy for the given pointer
		TreeViewItemProxy(TreeView::Item* data){this->data = data;}
		
		// Destructor
		virtual ~TreeViewItemProxy(){}
		
		// Overloading the arrow operator allows the Proxy to behave like a
		// a pointer.  Returns the internal pointer to the TreeViewItem
		TreeView::Item*		   operator-> () { return data;}
		TreeView::Item const*  operator-> () const { return data;}

		// Compares the pointers for equality
		bool operator==(const TreeViewItemProxy& h){return data == h.data;}
		bool operator!=(const TreeViewItemProxy& h){return data != h.data;}		
		
		// A proxy is valid if and only if it is not NULL
		bool isValid() const{return data;}	
};

}

#endif
