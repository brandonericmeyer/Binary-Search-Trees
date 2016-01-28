//***************************************************************************
//  FILENAME:	 Meyer-assn5-funcs.cpp
//  CLASS/DATE:  Adv Programming & Algorithms/Su8w2-Week 6 - 8/11/2015
//***************************************************************************

#include "Meyer-assn5-common.h"      // global definitions
#include "Meyer-assn5-funcs.h"		// function definition

//*************************************************************************
//  FUNCTION:					CreateTree
//  DESCRIPTION:				Allocate a binary search tree structure, and 
//								initialize the root pointer in it to NULL and 
//								the count to 0, to indicate an empty tree. 
//								Returns a pointer to the new binary search 
//								tree structure.
//  INPUT:       Parameter:     tree - root to be intitalized.
//  OUTPUT: 	 Return value:  tree.root - returns initialized root value.
//	CALLS TO:					none
//*************************************************************************
BST *CreateTree(BST &tree)
{
	tree.root = NULL; // Empty tree

	tree.count = 0;

	return tree.root;
}
//*************************************************************************
//  FUNCTION:					IsEmpty
//  DESCRIPTION:				returns true if binary search tree is empty, 
//								false otherwise
//  INPUT:       Parameter:     root - root node of tree to be checked.
//  OUTPUT: 	 Return value:  none
//	CALLS TO:					none
//*************************************************************************
bool IsEmpty(BST *root)
{
	return (root == NULL); // Checking if root is null.
}
//*************************************************************************
//  FUNCTION:					CreateNode
//  DESCRIPTION:				allocate and fills new node. Passes back 
//								pointer to new node, or NULL if node could not be allocated.
//  INPUT:       Parameter:     itemInsert - item to be stored in new node.
//  OUTPUT: 	 Return value:  newNode - newly created node.
//	CALLS TO:					none
//*************************************************************************
BST *CreateNode(const int & itemInsert)
{
	BST * newNode = NULL; // new node to insert value in to.

	newNode = new(nothrow)BST; // create node dynamically

	if (newNode == NULL)  // Checking for allocation
	{
		cout << endl << "Error - Cannot allocate memory!" << endl;
	}
	else
	{
		newNode->integer = itemInsert;

		newNode->left = NULL; // Set to have zero children.

		newNode->right = NULL; // Set to have zero children.
	}

	return newNode;
}
//*************************************************************************
//  FUNCTION:					InsertNode
//  DESCRIPTION:				inserts a new node into the correct location 
//								within a binary search tree.
//  INPUT:       Parameter:     root - root node.  temp - newly created node.
//								tree - used for accessing the count.
//  OUTPUT: 	 Return value:  none
//	CALLS TO:					FindNode, IsEmpty
//*************************************************************************
void InsertNode(BST *&root, BST * &temp, BST & tree)
{
	BST * current = NULL; // used in traversing the tree.
	BST * trailCurrent = NULL; // item before current.
	BST * newNode = NULL; // new node to insert value in to.
	bool found = false; // flag for duplicates
	bool failedAllocation = false; // flag for memory

	int itemInsert = temp->integer;

	FindNode(root, itemInsert, found);

	if (found == true)
	{
		cout << "The number you are trying to insert is already in the list." << endl;

		cout << "Duplicates are not allowed.  Therefore, " << itemInsert << " will be ignored." << endl << endl;
	}
	else
	{
		newNode = temp;

		if (newNode == NULL)
		{
			cout << "Number " << itemInsert << " was not inserted into the list." << endl << endl;
		}
		else
		{
			if (IsEmpty(root)) // No nodes have been created.  First node.
			{
				root = newNode;

				tree.count++;
			}
			else
			{
				tree.count++;

				current = root;

				while (current != NULL) // Looking for proper placement of item.
				{
					trailCurrent = current;

					if (current->integer > itemInsert)
					{
						current = current->left;
					}
					else
					{
						current = current->right;
					}
				} // end while

				if (trailCurrent->integer > itemInsert)
				{
					trailCurrent->left = newNode;
				}
				else
				{
					trailCurrent->right = newNode;
				}
			} // end else
		} // end else
	}
}
//*************************************************************************
//  FUNCTION:					FindNode
//  DESCRIPTION:				searches for a value within a binary search 
//								tree. Passes back a flag indicating if the 
//								value was found and a pointer to a node. 
//								If the value was found, the pointer will 
//								point to the node containing the value. 
//								If the value was not found, the pointer will 
//								point to the last node searched before 
//								determining that the value could not be 
//								found (or NULL if the tree was empty).
//  INPUT:       Parameter:     root - root node.  findItem - item we are
//								searching for.  found - flag if item found.
//  OUTPUT: 	 Return value:  trailCurrent - node where found.
//	CALLS TO:					none
//*************************************************************************
BST *FindNode(BST *root, const int & findItem, bool & found)
{
	BST * current = NULL; // used in traversing the tree.
	BST * trailCurrent = NULL; // item before current.

	found = false; // flag

	current = root;

	while (current != NULL && !found) // Search through tree
	{
		trailCurrent = current;

		if (current->integer == findItem) // Item has been found
		{
			found = true;
		}
		else if (current->integer > findItem) // Search continued
		{
			current = current->left;

		}
		else
		{
			current = current->right;
		}
	} // end while

	return trailCurrent; // return pointer to node
}
//*************************************************************************
//  FUNCTION:					DeleteNode
//  DESCRIPTION:				deletes a node from the binary search tree.
//  INPUT:       Parameter:     root - root node before deletion. deleteItem
//								- item to be deleted.
//  OUTPUT: 	 Return value:  root - returns new root value
//	CALLS TO:					DeleteNode, FindMin
//*************************************************************************
BST *DeleteNode(BST *root, int deleteItem)
{
	if (root == NULL)
	{
		return root;
	}
	else if (deleteItem < root->integer) // Look through tree
	{
		root->left = DeleteNode(root->left, deleteItem);
	}
	else if (deleteItem > root->integer)
	{
		root->right = DeleteNode(root->right, deleteItem);
	}
	else
	{
		if (root->left == NULL && root->right == NULL) // No children
		{
			delete root;

			root = NULL;

		}
		else if (root->left == NULL) // One child
		{
			BST * temp = root;

			root = root->right; // Set root to point to the right child

			delete temp;

		}
		else if (root->right == NULL) // One child
		{
			BST * temp = root;

			root = root->left; // Set root to point to the left child

			delete temp;
		}
		else // Two children
		{
			BST *temp = FindMin(root->right);

			root->integer = temp->integer;

			root->right = DeleteNode(root->right, temp->integer);
		}
	} // end else

	return root;
}
//*************************************************************************
//  FUNCTION:					FindMin
//  DESCRIPTION:				Searches for the minimum in value in a tree.
//  INPUT:       Parameter:     root - root node
//  OUTPUT: 	 Return value:  root
//	CALLS TO:					none
//*************************************************************************
BST* FindMin(BST* root)
{
	while (root->left != NULL)
	{
		root = root->left;
	}

	return root;
}
//*************************************************************************
//  FUNCTION:					InOrderDisplay
//  DESCRIPTION:				neatly displays all integers in the list in 
//								sorted order, using a recursive, in-order 
//								traversal.
//  INPUT:       Parameter:     ptr - points to root node.  count - used for
//								keeping count of how many items were displayed.
//  OUTPUT: 	 Return value:  none
//	CALLS TO:					InOrderDisplay
//*************************************************************************
void InOrderDisplay(BST *ptr, int & count)
{
	if (ptr != NULL)
	{
		InOrderDisplay(ptr->left, count);

		cout << setw(7) << ptr->integer << setw(7); // Output

		count++;

		if (count % TEN == ZERO) // After displaying 10 items, newline
		{
			cout << endl;
		}

		InOrderDisplay(ptr->right, count);
	}

}
//*************************************************************************
//  FUNCTION:					FreeNodes
//  DESCRIPTION:				Recursively de-allocates all dynamic memory 
//								allocated to nodes in the binary search tree.
//  INPUT:       Parameter:     tree - holds pointer to the root node.
//  OUTPUT: 	 Return value:  none
//	CALLS TO:					FreeNodes
//*************************************************************************
void FreeNodes(BST *tree)
{
	if (tree != NULL)
	{
		FreeNodes(tree->left);

		FreeNodes(tree->right);

		delete tree;

		tree = NULL;
	}
}
//*************************************************************************
//  FUNCTION:					DestroyTree				
//  DESCRIPTION:				De-allocates all dynamic memory allocated
//								for the binary search tree.		
//  INPUT:       Parameter:     tree - reference to BST structure.
//  OUTPUT: 	 Return value:  none
//	CALLS TO:					none
//*************************************************************************
void DestroyTree(BST &tree)
{
	tree.root = NULL;

	tree.left = NULL;

	tree.right = NULL;
}
//*************************************************************************
//  FUNCTION:					emptyFile			
//  DESCRIPTION:				Checks for an empty file.		
//  INPUT:       Parameter:     fileName - holds file to be read.
//  OUTPUT: 	 Return value:  read - boolean if the file is empty or not.
//	CALLS TO:					none
//*************************************************************************
bool emptyFile(const string &fileName)
{
	ifstream inFile;
	bool read = false;
	int numReadIn;

	inFile.open(fileName);

	if (!(inFile >> numReadIn))
	{
		cout << endl << "File is empty.  Proceeding to menu." << endl << endl;

		read = true;
	}

	inFile.close();

	return read;
}
//*************************************************************************
//  FUNCTION:					readFile				
//  DESCRIPTION:				Reads the contents of a file.		
//  INPUT:       Parameter:     root - root node.  tree - reference to BST
//								structure.  fileName - holds name of file 
//								to be read.
//  OUTPUT: 	 Return value:  none
//	CALLS TO:					emptyFile, FindNode, CreateNode, InsertNode
//*************************************************************************
void readFile(BST *&root, BST & tree, const string &fileName)
{
	ifstream inFile;
	BST *temp = NULL;
	int numReadIn;
	bool found = false;
	bool checkEmpty = false;
	bool allocationFailed = false;

	checkEmpty = emptyFile(fileName); // Check if file is empty

	if (!checkEmpty) // File is not empty.  Read contents.
	{
		inFile.open(fileName);

		while (inFile >> numReadIn && !allocationFailed) // Read integers
		{
			FindNode(root, numReadIn, found); // Search for duplicates

			if (!found)
			{
				temp = CreateNode(numReadIn);

				if (temp == NULL) // Check for succesful allocation
				{
					allocationFailed = true;
				}
				else
				{
					InsertNode(root, temp, tree);
				}
			}

		} // end while

		inFile.close();
	}
}