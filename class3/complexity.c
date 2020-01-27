#define _CRT_SECURE_NO_WARRNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define N 30000
#define M1 10000
#define STEP_COUNT 8
#define STEP 5000
#define R 10
#define RAND(x) rand() % x + 1

int* generate_array(int);
void shuffle(int*, int);
int* intersection_of_sets(const int*, const int*, int, int, char*);
//int *sorted_intersection_of_sets(const int *, int *, int, int);
int is_inside_set(int, int*, int);
int is_inside_sorted_set(int, int*, int);
int cmpfunc(const void*, const void*);

int main() {
	int* setA, * setB, * intersectionSet;
	clock_t startTime, endTime;
	double totalTime;

	srand(time(NULL));

	printf("---------- Intersection between 2 unsorted sets ----------\n");
	int sizeA = N, sizeB = M1;

	for (int i = 0; i < STEP_COUNT; i++)
	{
		setA = generate_array(sizeA), setB = generate_array(sizeB);
		shuffle(setA, sizeA);
		shuffle(setB, sizeB);
		startTime = clock();
		intersectionSet = intersection_of_sets(setA, setB, sizeA, sizeB, "reg");
		endTime = clock();
		totalTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
		printf("Set A[%d] and set B[%d] elements: %f sec\n", sizeA, sizeB, totalTime);

		free(setA);
		free(setB);
		free(intersectionSet);

		sizeB += STEP;
	}
	sizeA = M1, sizeB = N;
	putchar('\n');
	for (int i = 0; i < STEP_COUNT; i++)
	{
		setA = generate_array(sizeA), setB = generate_array(sizeB);
		shuffle(setA, sizeA);
		shuffle(setB, sizeB);
		startTime = clock();
		intersectionSet = intersection_of_sets(setA, setB, sizeA, sizeB, "reg");
		endTime = clock();
		totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("Set A[%d] and set B[%d] elements: %f sec\n", sizeA, sizeB, totalTime);

		free(setA);
		free(setB);
		free(intersectionSet);

		sizeA += STEP;
	}
	printf("\n---------- Intersection between unsorted and sorted set ----------\n");
	sizeA = N, sizeB = M1;

	for (int i = 0; i < STEP_COUNT; i++)
	{
		setA = generate_array(sizeA), setB = generate_array(sizeB);
		shuffle(setB, sizeB);
		startTime = clock();
		intersectionSet = intersection_of_sets(setA, setB, sizeA, sizeB, "reg");
		endTime = clock();
		totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("Set A[%d] and set B[%d] elements: %f sec\n", sizeA, sizeB, totalTime);

		free(setA);
		free(setB);
		free(intersectionSet);

		sizeB += STEP;
	}
	printf("\n---------- Intersection between unsorted and sorted set (bserach)----------\n");
	sizeA = N, sizeB = M1;
	for (int i = 0; i < STEP_COUNT; i++) {
		setA = generate_array(sizeA), setB = generate_array(sizeB);
		shuffle(setB, sizeB);
		startTime = clock();
		intersectionSet = intersection_of_sets(setA, setB, sizeA, sizeB, "bsearch");
		endTime = clock();
		totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("Set A[%d] and set B[%d] elements: %f sec\n", sizeA, sizeB, totalTime);

		free(setA);
		free(setB);
		free(intersectionSet);

		sizeB += STEP;
	}
	printf("\n---------- Intersection between unsorted and sorted set (qsort)----------\n");
	sizeA = N, sizeB = M1;

	for (int i = 0; i < STEP_COUNT; i++)
	{
		setA = generate_array(sizeA), setB = generate_array(sizeB);
		shuffle(setA, sizeA);
		shuffle(setB, sizeB);
		startTime = clock();
		qsort(setA, sizeA, sizeof(int), cmpfunc);
		intersectionSet = intersection_of_sets(setA, setB, sizeA, sizeB, "reg");
		endTime = clock();
		totalTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
		printf("Set A[%d] and set B[%d] elements: %f sec\n", sizeA, sizeB, totalTime);

		free(setA);
		free(setB);
		free(intersectionSet);

		sizeB += STEP;
	}
	return 0;
}

int* generate_array(int size) {
	int* set = (int*)malloc(size * sizeof(int));
	if (!set) return 0;

	set[0] = RAND(R);
	for (int i = 1; i < size; i++) {
		set[i] = set[i - 1] + RAND(R);
	}
	return set;
}

void shuffle(int* set, int size) {
	for (int i = 0, temp; i < size; i++) {
		int rIndex = rand() % size;
		temp = set[i];
		set[i] = set[rIndex];
		set[rIndex] = temp;
	}
}

int* intersection_of_sets(const int* setA, const int* setB, int sizeA, int sizeB, char* action) {
	int size = (sizeA >= sizeB) ? sizeA : sizeB, * interSet = (int*)malloc(size * sizeof(int));
	if (!interSet) return 0;

	int (*fun_ptr)(int, int*, int) = (!strcmp(action, "bsearch")) ? is_inside_sorted_set : is_inside_set;

	for (int i = 0, j = 0; i < sizeA; i++) {
		if (fun_ptr(setA[i], setB, sizeB)) {
			interSet[j] = setA[i];
			j++;
		}
	}
	return interSet;
}

int is_inside_set(int numberA, int* setB, int sizeB) {
	for (int i = 0; i < sizeB; i++) {
		if (numberA == setB[i]) return 1;
	}
	return 0;
}

int is_inside_sorted_set(int numberA, int* setB, int sizeB) {
	int* item = (int*)bsearch(&numberA, setB, sizeB, sizeof(int), cmpfunc);
	if (item)
		return 1;
	return 0;
}

//int* sorted_intersection_of_sets(const int* setA, int* setB, int sizeA, int sizeB) {  // set B is sorted with bsearch()
//	int size = (sizeA >= sizeB) ? sizeA : sizeB, * interSet = (int*)malloc(size * sizeof(int));
//	if (!interSet) return 0;
//
//	for (int i = 0, j = 0; i < sizeA; i++) {
//		if (is_inside_sorted_set(setA[i], setB, sizeB)) {
//			interSet[j] = setA[i];
//			j++;
//		}
//	}
//	return interSet;
//}

int cmpfunc(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}
