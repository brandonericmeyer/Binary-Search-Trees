//***************************************************************************
// Section CS372 -  Advanced Programming
// File Name:		Meyer-assn5-main.cpp
// Student:			Brandon Meyer
// Homework Number: Week 7, Assign 5
// Description:		a program to implement storing a list of integers into a binary 
//					search tree.
// Start Date:		8/11/2015
// Last Changed:    8/17/2015
//***************************************************************************

#include "Meyer-assn5-common.h"      // global definitions
#include "Meyer-assn5-funcs.h"		// function definition

int main( )
{
	ifstream inFile;

	BST binaryTree;
	BST *ptrTree = NULL;
	BST *temp = NULL;
	BST *temp2 = NULL;
	string fileName;
	bool found = false;
	bool exitProgram = false;
	int userChoice = 0;
	int readInt = 0;
	int count = 0;

	ptrTree = CreateTree(binaryTree); // Returns pointer to root of tree.

	do
	{
		cout << "Enter the name of the file you wish to read: ";

		cin >> fileName;

		inFile.open(fileName);

		if (!inFile)
		{
			cout << endl << "Error - File not found.  Try again." << endl << endl;
		}

	} while (!inFile);  // Until we can read a valid file, do over.

	inFile.close();

	readFile(ptrTree, binaryTree, fileName);

	do
	{
		cout << endl << "USER MENU:" << endl
			<< "1.  Show all integers" << endl
			<< "2.  Add an integer" << endl
			<< "3.  Delete an integer" << endl
			<< "4.  Display subtree of an integer" << endl
			<< "5.  Exit the program" << endl;

		cout << endl << "Your choice: ";

		cin >> userChoice;

		switch (userChoice)
		{
		case 1:
			if (IsEmpty(ptrTree))
			{
				cout << endl << "Tree is empty.  Cannot display what is not there." << endl << endl;
			}
			else
			{
				cout << endl << "Values stored in entire binary search tree are:" << endl;

				count = 0;

				InOrderDisplay(ptrTree, count);

				cout << endl;
			}
			break;
		case 2:
			cout << endl << "Enter an integer to add: ";

			cin >> readInt;

			FindNode(ptrTree, readInt, found);

			temp2 = CreateNode(readInt);

			InsertNode(ptrTree, temp2, binaryTree);
		
			break;
		case 3:
			if (IsEmpty(ptrTree))
			{
				cout << endl << "Tree is empty.  Cannot delete what is not there." << endl << endl;
			}
			else
			{
				cout << endl << "Enter an integer to delete: ";

				cin >> readInt;

				FindNode(ptrTree, readInt, found);

				if (found)
				{
					ptrTree = DeleteNode(ptrTree, readInt);

					FindNode(ptrTree, readInt, found);

					if (!found)
					{
						cout << endl << "Integer has been successfully removed." << endl;
					}
					else
					{
						cout << endl << "Error : Integer deletion failed." << endl;
					}
				}
				else
				{
					cout << endl << "Error : Integer not found.  Nothing to delete." << endl;
				}
			}
			break;
		case 4:
			if (IsEmpty(ptrTree))
			{
				cout << endl << "Tree is empty.  Cannot display what is not there." << endl << endl;
			}
			else
			{
				cout << endl << "Enter value to find: ";

				cin >> readInt;

				temp = FindNode(ptrTree, readInt, found);

				if (found && temp != NULL)
				{
					cout << endl << "Values stored subtree with root " << readInt << " are:" << endl;

					count = 0;

					InOrderDisplay(temp, count);

					cout << endl;
				}
				else
				{
					cout << endl << "Error : Integer not found." << endl;
				}
			}			
			break;
		case 5:
			exitProgram = true;
			break;
		default:
			cout << endl << "Invalid choice.  Please try again." << endl << endl;
			break;
		}

	} while (!exitProgram);


	FreeNodes(ptrTree); // Removes nodes with pointer

	DestroyTree(binaryTree); // Removes remaining tree.

	system("Pause");
   	return 0;
}

