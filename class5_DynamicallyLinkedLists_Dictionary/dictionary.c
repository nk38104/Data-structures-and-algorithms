#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

Dictionary create() {
	Word* newDict = (Word*)malloc(sizeof(Word));
	if (!newDict) return;

	newDict->word = NULL;
	newDict->count = 0;
	newDict->next = NULL;

	return newDict;
}

void add(Dictionary dict, char *str)
{
	Dictionary dictPtr = dict;
	for (; dictPtr->next != NULL; dictPtr = dictPtr->next) {
		if (strcmp(dictPtr->next->word, str) == 0) {
			dictPtr->next->count += 1;
			return;
		}
		if (strcmp(dictPtr->next->word, str) > 0) {
			Word *newWord = create();
			newWord->word = _strdup(str);
			newWord->count = 1;
			newWord->next = dictPtr->next;
			dictPtr->next = newWord;
			return;
		}
	}

	Word* newWord = create();
	newWord->word = _strdup(str);
	newWord->count = 1;
	newWord->next = dictPtr->next;
	dictPtr->next = newWord;
}

void print(Dictionary dict) {
	Dictionary dictPtr = dict->next;

	for (; dictPtr->next != NULL; dictPtr = dictPtr->next) {
		printf("Word: %s\nCount: %d\n\n", dictPtr->word, dictPtr->count);
	}
}

void destroy(Dictionary dict) {
	Word *curr = dict, *delete = curr->next;

	for (; delete != NULL; delete = curr){
		curr = delete->next;
		free(delete->word);
		free(delete);
	}
	free(dict);
}

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word* w))
{
	Dictionary dictPtr = indict;
	Word* check = dictPtr->next;

	for (; dictPtr->next != NULL; check = dictPtr->next) {
		if (filter(check) < 1) {
			dictPtr->next = dictPtr->next->next;
			free(check->word);
			free(check);
			check = dictPtr->next;
		}
		else 
			dictPtr = dictPtr->next;
	}
	return indict;
}

int filter(Word *w) { 
	if ((w->count > 5 && w->count < 10) && strlen(w->word) > 3)
		return 1;
	return 0;
}

Dictionary delete_at_index(Dictionary dict, int index) {
	int i = 1;
	Dictionary ptr = dict;

	if (index == 1) {
		Dictionary delete = ptr;
		ptr = ptr->next;
		free(delete->word);
		free(delete);
		return ptr;
	}

	for (ptr = dict; ptr != NULL; ptr = ptr->next,  i++) {
		if (i == (index - 1)) {
			Dictionary delete = ptr->next;
			ptr->next = ptr->next->next;
			free(delete->word);
			free(delete);
		}
	}
	return dict;
}