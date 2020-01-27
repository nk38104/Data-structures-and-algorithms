#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Word {
	char* word;
	int count;
	struct Word* next;
} Word;

typedef Word* Dictionary;

Dictionary create();
void add(Dictionary, char *);
void print(Dictionary);
void destroy(Dictionary);
Dictionary filterDictionary(Dictionary, int (*)(Word *));
int filter(Word *);
Dictionary delete_at_index(Dictionary, int);

#endif
