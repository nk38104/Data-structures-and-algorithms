#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "bst.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}

BSTree create_node(char* word) {
	BSTree newNode = (BSTree)malloc(sizeof(Node));
	if (!newNode) return 0;

	newNode->word = _strdup(word);
	newNode->right = NULL;
	newNode->left = NULL;

	return newNode;
}

void AddNode(BSTree* bst, char* word)
{
	// Rekurzivno se tra�i mjesto za novi �vor u stablu. Ako rije� postoji u stablu, ne dodaje se. bst parametar je dvostruki pokaziva�.
	if (*bst == NULL) {
		*bst = create_node(word);
		return;
	}
	else if (strcmp((*bst)->word, word) == 0) { return; }
	else if (strcmp((*bst)->word, word) > 0)
		AddNode(&(*bst)->left, word);
	else
		AddNode(&(*bst)->right, word);
}

int max(int a, int b) {
	return (a >= b) ? a : b;
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se prona�la najdu�a grana (visina stabla).
	if (bst == NULL) return 0;
	
	return 1 + max(BSTHeight(bst->left), BSTHeight(bst->right));
}

void PrintBSTree(BSTree bst)
{
	if (bst == NULL) return;
	//inorder( left, parent, right)
	PrintBSTree(bst->left);
	printf("%s ", bst->word);
	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE* fd)
{
	// Snima rije� po rije� iz stabla u tekstualnu datoteku. Rije�i su odvojene razmakom.
	// Pre-order �etnja po stablu (trenutni �vor pa djeca)
	if (bst == NULL) return;

	fputs(bst->word, fd);
	fputs(" ", fd);
	SaveBSTree(bst->left, fd);
	SaveBSTree(bst->right, fd);
}

void DeleteBSTree(BSTree bst)
{
	// Bri�e stablo (string word i sam �vor) iz memorije.
	// Post-order �etnja po stablu (prvo djeca pa trenutni �vor)
	if (bst == NULL) return;

	DeleteBSTree(bst->right);
	DeleteBSTree(bst->left);

	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE* fd)
{
	// U�itava rije� po rije� iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rije� duplicirati sa strdup().

	BSTree dict = NewBSTree();
	int wordCount = 0;
	char str[100];

	while (fscanf(fd, "%s", str) > 0){
		AddNode(&dict, str);
		wordCount++;
	}
	return dict;
}
