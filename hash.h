#ifndef HASH_H
#define HASH_H

typedef struct _HashElement {
	char *word;
	struct _HashElement*next;
} HashElement;

typedef struct {
	HashElement**table;
	int size, load;
} HashTable;

HashTable *NewTable(int size);
unsigned int hash(char *word);
HashElement* createElement(char*);
void Insert(HashTable *ht, char *word);
int Get(HashTable *ht, char *word);
void deleteElement(HashElement*);
void DeleteTable(HashTable *ht);

#endif