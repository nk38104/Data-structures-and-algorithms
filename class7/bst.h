#ifndef TREE_H
#define TREE_H
#include <string.h>

// �vor stabla sa pokaziva�om na rije� i na djecu �vora
typedef struct _Node{
	char* word;
	struct _Node *left, *right;
}Node;

// Stablo odnosno pokaziva� na korijen stabla
typedef Node* BSTree;

BSTree NewBSTree();
BSTree create_node(char*);
int max(int, int);
void AddNode(BSTree* bst, char* word);
int BSTHeight(BSTree bst);
void PrintBSTree(BSTree bst);
void SaveBSTree(BSTree bst, FILE* fd);
void DeleteBSTree(BSTree bst);
BSTree LoadBSTree(FILE* fd);

#endif