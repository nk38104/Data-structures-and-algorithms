#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

int readWord(FILE* fd, char* buffer)
{
	int c;

	do {
		c = fgetc(fd);
		if (c == EOF)
			return 0;
	} while (!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if (c == 146)
			c = '\'';
	} while (isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

int main()
{
	char buffer[256];
	Dictionary dict = create();
	FILE* fd = fopen("liar.txt", "r");
	if (fd == NULL) {
		printf("Error opening file. Make sure it is in same directory and check the file name.\n");
		return;
	}

	while (readWord(fd, buffer)){
		add(dict, buffer);
	}
	fclose(fd);

	print(dict);

	/*filterDictionary(dict, filter);
	printf("------------------------------ FILTERED DICTIONARY ------------------------------\n");
	print(dict);*/
	printf("------------------------------ DELETED ------------------------------\n");
	dict = delete_at_index(dict, 1);
	print(dict);

	destroy(dict);
	
	return 0;
}