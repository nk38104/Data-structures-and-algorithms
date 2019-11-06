#pragma warning(disable : 4996) 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mystrlen(const char*);
char* mystrcpy(char*, const char*);
int mystrcmp(const char*, const char*);
char* mystrcat(char*, const char*);
char* mystrstr(const char*, const char*);
char* reverse(const char*, char*); 

//MY STRING.H FUNCTIONS
int main()
{
	char str[] = "abcd1234";

	printf("String: %s  strlen: %d  mystrlen: %d\n", str, strlen(str), mystrlen(str));

	//mystrcpy
	char dest[40], myDest[40], string[] = "defg5678";

	strcpy(dest, str);
	mystrcpy(myDest, string);

	printf("\nString: %s  strcpy: %s  String: %s  mystrcpy: %s\n", str, dest, string, myDest);

	//mystrcmp
	printf("\nString: %s  cmpstr: %s  strcmp: %d  mystrcmp(1=2): %d cmpstr: %s  mystrcmp(1>2): %d  mystrcmp(1<2): %d\n", str, dest, strcmp(dest, str), mystrcmp(dest, str), myDest, mystrcmp(myDest, dest), mystrcmp(dest, myDest));

	printf("strlen: %d  mystrlen: %d\n", mystrlen(dest), mystrlen(myDest));

	//mystrcat()
	printf("\nString 1: %s String 2: %s  ", dest, myDest);
	strcat(dest, myDest), mystrcat(myDest, string);
	printf("strcat: %s  mystrcat: %s\n", dest, myDest);

	//mystrstr()
	char substr1[] = "efg", substr2[] = "aab";
	char* p = strstr(dest, substr1), *myp = mystrstr(mystrcpy(myDest, "aaaab"), substr2);

	printf("\nString: %s  Podstring: %s  strstr: %s  myString: %s  myPodstring: %s  mystrstr: %s\n", dest, substr1, p, myDest, substr2, myp);

	//reverse
	printf("\nString: %s  reverse: %s\n", substr1, reverse(substr1, substr2));
}

int mystrlen(const char *str)
{
	int count;

	for (count = 0; *str != '\0'; str++) {
		count += 1;
	}

	return count;
}

char* mystrcpy(char *dest, const char *src)
{
	char *start = dest;

	for (; *src != '\0'; dest++, src++) {
		*dest = *src;
	}
	*dest = '\0';

	return start;
}

int mystrcmp(const char *str1, const char *str2)
{
	for (; *str1 && (*str1 == *str2); str1++, str2++);
	return *str1 - *str2;
}

char* mystrcat(char *dest, const char *src)
{
	char *ptr = (dest + mystrlen(dest));

	for (; *src != '\0'; src++, ptr++) {
		*ptr = *src;
	}
	*ptr = '\0';
	
	return dest;
}

char* mystrstr(const char *str, const char *substr)
{
	char *ptr = substr, *p;

	for (; *str != '\0'; ) {
		if (*ptr == *str) {
			for (p = str; ((*p) == (*ptr)) && (*p != '\0') && (*ptr != '\0'); ptr++, p++);

			if (*ptr == '\0')
				return str;	
			else {
				str = (--p);
				ptr = substr;
			}
		}
		else{
			str++;
		}
	}
	return NULL;
}

char* reverse(const char *src, char *dest)
{
	char *sptr = (src + (mystrlen(src) - 1)), *dptr = dest;

	for (; *src != '\0'; src++, dptr++, sptr--) {
		*dptr = *sptr;
	}
	*dptr = '\0';

	return dest;
}
