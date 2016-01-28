//***************************************************************************
//  CODE FILENAME:  Meyer-assn5-funcs.h
//  DESCRIPTION:    Prototypes of functions  
//***************************************************************************/ 

BST *CreateTree(BST &tree);
bool IsEmpty(BST *root);
BST *CreateNode(const int & itemInsert);
void InsertNode(BST *&root, BST * &temp, BST & tree);
BST *FindNode(BST *root, const int & findItem, bool & found);
BST *DeleteNode(BST *root, int deleteItem);
BST* FindMin(BST* root);
void InOrderDisplay(BST *ptr, int & count);
void FreeNodes(BST *tree);
void DestroyTree(BST &tree);
bool emptyFile(const string &fileName);
void readFile(BST *&root, BST & tree, const string &fileName);