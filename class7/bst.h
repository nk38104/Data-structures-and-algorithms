#ifndef TREE_H
#define TREE_H
#include <string.h>

// Èvor stabla sa pokazivaèom na rijeè i na djecu èvora
typedef struct _Node{
	char* word;
	struct _Node *left, *right;
}Node;

// Stablo odnosno pokazivaè na korijen stabla
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