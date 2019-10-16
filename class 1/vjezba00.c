#pragma warning(disable : 4996)  // ovim iskljucujemo upozorenja radi strcpy jer je nesigurna funkcija, kompajler preporuca strpcy_s 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

int mystrlen(const char*); // funkcija prima string (char*) i vraæa integer koji predstavlja dužinu stringa
char* mystrcpy(char*, const char*); // funkcija prima 2 stringa i kopira 2. string u 1. string
int mystrcmp(const char*, const char*); // funkcija prima dva stringa i usporeðuje ih, vraæa broj<0 ako je prvi<drugog stringa (po													  // leksikografskom poretku), broj>0 ako je drugi<prvog inula ako su stringovi jednaki.

char* mystrcat(char*, const char*); // funkcija prima 2 stringa i dodaje 2.string na kraj 1og
char* mystrstr(const char*, const char*); // funkcija vraæa pokazivaè (unutar prvog stringa) koji pokazuje na prvo pojavljivanje drugog													 stringa, ako ga ne pronaðe funkcija vraæa NULL
char* reverse(const char*, char*); // prima 2 stringa i kopira 1.string u 2. string naopako (funkcija ne postoji u string.h)

//Napisati testove za funkcije koji æe ispisivati rezultat „my“ verzije funkcije i originalne verzije funkcije
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
	for (; *str1 && (*str1 == *str2); str1++, str2++); /* vrtimo petlju dok str ne dode do terminatora i dok su znakovi jednaki, kad dodemo do														razlicitih znakova vracamo razliku njihovih ASCII vrijednosti*/
	return *str1 - *str2;
}

char* mystrcat(char *dest, const char *src)
{
	char *ptr = (dest + mystrlen(dest)); // pointer stavimo na kraj stringa(+1) i to je startna pozicija za pocetak kopiranja iz drugog stringa

	for (; *src != '\0'; *ptr = *src, src++, ptr++, *ptr = '\0');

	return dest;
}

char* mystrstr(const char *str, const char *substr)
{
	char* ptr = substr;

	for (; (*ptr != '\0') && (*str != '\0'); str++) {  // u slucaju da nema podstr u str treba provjeravat jesmo dosli do kraja str
		ptr = (*ptr == *str) ? ++ptr : substr;		  // povecavamo podstr do terminatora ako su isti znakovi ako nisi vrati podstr na pocetak
	}

	return (*ptr == '\0') ? str -= mystrlen(substr) : NULL;
}

char* reverse(const char *src, char *dest)
{
	char *sptr = (src + (mystrlen(src) - 1)), *dptr = dest;

	for (; *src != '\0'; *dptr = *sptr, src++, dptr++, sptr--, *dptr = '\0');

	return dest;
}