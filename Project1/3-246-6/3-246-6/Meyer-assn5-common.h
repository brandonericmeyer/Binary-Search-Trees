//***************************************************************************
//  CODE FILENAME:  Meyer-assn5-common.h
// DESCRIPTION:		This file contains the function prototypes and constants used to illustrate
//					the implementation. It contains only the common constants and functions used
//					for implementation.
//***************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct BST 
{
	int integer;
	int count;

	BST *root, *left, *right;
};

const int ZERO = 0;
const int TEN = 10;
