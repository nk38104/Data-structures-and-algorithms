#pragma warning(disable : 4996)  // VS recommends strcpy_s instead of strcpy(unsafe function)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

int mystrlen(const char*);
char* mystrcpy(char*, const char*);
int mystrcmp(const char*, const char*);
char* mystrcat(char*, const char*); 
char* mystrstr(const char*, const char*); 												
char* reverse(const char*, char*);

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
	printf("\nString: %s  cmpstr: %s  strcmp: %d  mystrcmp(1=2): %d cmpstr: %s  mystrcmp(1>2): %d  mystrcmp(1<2): %d\n",
	       str, dest, strcmp(dest, str), mystrcmp(dest, str), myDest, mystrcmp(myDest, dest), mystrcmp(dest, myDest));

	printf("strlen: %d  mystrlen: %d\n", mystrlen(dest), mystrlen(myDest));

	//mystrcat()
	printf("\nString 1: %s String 2: %s  ", dest, myDest);
	strcat(dest, myDest), mystrcat(myDest, string);
	printf("strcat: %s  mystrcat: %s\n", dest, myDest);

	//mystrstr()
	char substr1[] = "efg", substr2[] = "78d";
	char* p = strstr(dest, substr1), *myp = mystrstr(myDest, substr2);

	printf("\nString: %s  Podstring: %s  strstr: %s  myString: %s  myPodstring: %s  mystrstr: %s\n", dest, substr1, p, myDest, substr2, myp);

	//reverse
	printf("\nString: %s  reverse: %s\n", substr1, reverse(substr1, substr2));
}

int mystrlen(const char *str)
{
	int count = 0;

	for(; *str != '\0'; count += 1, str++);

	return count;
}

char* mystrcpy(char *dest, const char *src)
{
	char *start = dest;

	for (; *src != '\0'; *dest = *src, dest++, src++, *dest = '\0');

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

	for (; *src != '\0'; *ptr = *src, src++, ptr++, *ptr = '\0');

	return dest;
}

char* mystrstr(const char *str, const char *substr)
{
	char* ptr = substr;

	for (; (*ptr != '\0') && (*str != '\0'); str++) {  
		ptr = (*ptr == *str) ? ++ptr : substr;		 
	}

	return (*ptr == '\0') ? str -= mystrlen(substr) : NULL;
}

char* reverse(const char *src, char *dest)
{
	char *sptr = (src + (mystrlen(src) - 1)), *dptr = dest;

	for (; *src != '\0'; *dptr = *sptr, src++, dptr++, sptr--, *dptr = '\0');

	return dest;
}
