//To be used in conjunction with BSTree.h and Node.h
//When you modify this, please add your name and list any changes that you made
//A few member functions have been left blank so you, the student can implemement

/*Template Directions: #include "BSTREEInt.hpp"
but do NOT compile it (or add it to the project)*/
#include "BSTree.h"
#include "Actor.h"
#include "Picture.h"

// Constructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::BSTree() {
	root = nullptr;
}

// Destructor
template <typename DATATYPE, typename KEYTYPE>
BSTree<DATATYPE, KEYTYPE>::~BSTree() {
    if (root !=nullptr)
        freeNode(root);
}

// Free the node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::freeNode(Node<DATATYPE, KEYTYPE> * leaf)
{
	//Student must fill in
	if (Root() == leaf)			//if the root is the leaf, delete that leaf
	{
		delete leaf;
	}
	else						// otherwise if the leaf is not null
	{
		freeNode(leaf->Left());	//recursive call of the leaf's left
		freeNode(leaf->Right());	//recursive call of the leaf's right
		delete leaf;			//now delete the leaf
	}
}

// Add a node
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, DATATYPE &data)
{
	if (Root() == nullptr)
	{
		Node<DATATYPE, KEYTYPE> * newNodePtr = new Node<DATATYPE, KEYTYPE>;
		newNodePtr->setKey(key);
		newNodePtr->setData(data);
		root = newNodePtr;
		root->setParent(root);

	}
	else
		addNode(key, root, data);
}

// Add a node (private)
template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::addNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> * leaf, DATATYPE& data) {
	//Student must fill in
	//Don't forget to set your key, Parent, then left or right
	//Based on the case you use you will addNode recursively to the left or right
 
	if (Root() == nullptr)			//First check if root is null
	{
		Node<DATATYPE, KEYTYPE> * newNode = new Node<DATATYPE, KEYTYPE>();	//make a new node
		newNode -> setKey(key);		//set the key and data
		newNode -> setData(data);
		root = newNode;				//set the root
	}
	else 							//Otherwise
	{
		if(key < leaf->Key())		//Check to see if the key is < the leaf's key
		{
			if (leaf->Left() != nullptr)	// if left is not null then
				addNode(key, leaf->Left(), data);	//Add the node to the left (recursively)
			else		// Otherwise make a new node and attach it to the left
			{
				Node<DATATYPE, KEYTYPE> * newNode = new Node<DATATYPE, KEYTYPE>();
				newNode -> setKey(key);
				newNode -> setData(data);
				newNode -> setParent(leaf);
				leaf -> setLeft(newNode);
			}

		}
		else 	//Check to see if the key >= leaf's key
		{
			if (leaf->Right() != nullptr)	// if leaf's right is not null then
				addNode(key, leaf->Right(), data);//Add the node to the right (recursively)
			else		// Otherwise make new node and attach it to the right
			{
				Node<DATATYPE, KEYTYPE> * newNode= new Node<DATATYPE, KEYTYPE>();
				newNode -> setKey(key);
				newNode -> setData(data);
				newNode -> setParent(leaf);
				leaf -> setRight(newNode);
			}
		}
	}



			
}

template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key)
{
	return findNode(key, root);
}

// Find a node
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::findNode(KEYTYPE key, Node<DATATYPE, KEYTYPE> * node)
{
	//Student must fill in
	if (node == nullptr)		// trap nullptr first in case we've hit the end unsuccessfully.
			return nullptr;
	else if (node -> Key() == key)	// success base case
		return node;
	else if (key > node -> Key())  //Greater than (Right)
	    findNode(key, node -> Right());
	else    //Less than (Left)
	    findNode(key, node -> Left());

	
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder()
{
	printInorder(root);
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::printInorder(Node<DATATYPE, KEYTYPE> * node)
{
	//Student must fill in.  Use recursive algorithm.
	//Note that this prints using an Inorder, Depth-first search
	//but you may want to do something else when "visiting" the node....
	//like moving visited data to another datastructure
	//Don't forget your base case!

	if (Root() == nullptr)
    {
	    cout << "The tree is empty.\n";
	    return;
    }
    else
    {
    	if (node -> Left() != nullptr)
    		printInorder(node -> Left());

        node -> Data().print();

        if (node -> Right() != nullptr)
        	printInorder(node -> Right());
    }

}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::print(ostream & out, const DATATYPE & data)
{
	out << data.number << "\t" << data.name << endl;
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::inOrderTransfer(list<DATATYPE> &holderList)
{
	inOrderTransfer(holderList, root);  //Simply calls the private version of the function
}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::inOrderTransfer(list<DATATYPE> &holderList, Node<DATATYPE, KEYTYPE> *node)  //This function is just a modified version of the printInOrder function
{
	if (Root() == nullptr)      //Checks if tree is empty
	{
		cout << "The tree is empty.\n";
		return;
	}
	else        //If not empty
	{
		if (node -> Left() != nullptr)      //Checks if at the furthest left node
			inOrderTransfer(holderList, node -> Left());    //If it isn't, moves left again.

		holderList.push_back(node -> Data());       //Otherwise moves the data to the list parameter

		if (node -> Right() != nullptr)     //Begins to check rightwards
			inOrderTransfer(holderList, node -> Right());   //If not a leaf, moves to the next node to the right
	}

}

template <typename DATATYPE, typename KEYTYPE>
void BSTree<DATATYPE, KEYTYPE>::deleteNode(KEYTYPE key)
{
	setRoot(deleteNode(Root(), key));
}

//deleteNode (Private)
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::deleteNode(Node<DATATYPE, KEYTYPE> * aRoot,KEYTYPE value)
{
   
	/* Given a binary search tree and a key, this function deletes the key
	and returns the new root */
	
	// base case
	if (aRoot == nullptr) return aRoot;

	// If the key to be deleted is smaller than the aRoot's key,
	// then it lies in left subtree
	if (value < aRoot->Key())
		aRoot->setLeft(deleteNode(aRoot->Left(), value));

	// If the key to be deleted is greater than the root's key,
	// then it lies in right subtree
	else if (value > aRoot->Key())
		aRoot->setRight(deleteNode(aRoot->Right(), value));

	// if key is same as root's key, then This is the node
	// to be deleted
	else
	{
		// node with only one child or no child
		if (aRoot->Left() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Right();
			delete aRoot;	
			return temp;
		}
		else if (aRoot->Right() == nullptr)
		{
			Node<DATATYPE, KEYTYPE> *temp = aRoot->Left();
			delete aRoot;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		Node<DATATYPE, KEYTYPE> * temp = min(aRoot->Right());

		// Copy the inorder successor's content to this node
		aRoot->setKey(temp->Key());
		aRoot->setData(temp->Data());

		// Delete the inorder successor
		aRoot->setRight(deleteNode(aRoot->Right(), temp->Key()));
	}
	return aRoot;
}


// Find the node with min key
// Traverse the left sub-BSTree recursively
// till left sub-BSTree is empty to get min
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::min(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * current = node;

	/* loop down to find the leftmost leaf */
	while (current->Left() != nullptr)
		current = current->Left();

	return current;
}

// Find the node with max key
// Traverse the right sub-BSTree recursively
// till right sub-BSTree is empty to get max
template <typename DATATYPE, typename KEYTYPE>
Node<DATATYPE, KEYTYPE> * BSTree<DATATYPE, KEYTYPE>::max(Node<DATATYPE, KEYTYPE> * node)
{
	Node<DATATYPE, KEYTYPE> * tempNode = node;
	if (node == nullptr)
		tempNode = nullptr;
	else if (node->Right())
		tempNode = max(node->Right());
	else
		tempNode = node;

	return tempNode;
}