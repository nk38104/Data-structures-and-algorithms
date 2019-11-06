#include <stdio.h>
#include <stdlib.h>

#define SIZE 7
#define PARRSIZE 4
#define LESSTHAN 5

typedef struct {
	float x, y;
} Point;

typedef struct {
	int numPoints;
	Point *array;
} Polygon;

void print_array(int*, int); 
int* sub_array(int *, int , int);
int* filter_array(int *, int, int, int *);
int** divide_array(int*, int);

Polygon* new_polygon(float*, float*, int);
Point** positive_points(Polygon*, int*);

int main()
{
	int array[SIZE] = { 2, 6, 3, 7, 8, 4, 7 }, start = 2, stop = 5, newSize = stop - start, i;
  
	//SUBARRAY THAT CONSISTS OF ELEMENTS FROM START TO STOP
	int *ptr = sub_array(array, start, stop);
	printf("Array: "), print_array(array, SIZE);
	printf("Subarray[%d-%d]: ", start, stop), print_array(ptr, newSize);
	free(ptr);

	//FILTER ARRAY
	newSize = 0;
	ptr = filter_array(array, SIZE, LESSTHAN, &newSize);

	printf("Filtered array[< %d]: ", LESSTHAN), print_array(ptr, newSize);
	free(ptr);

	//DIVIDE ARRAY AND RETURN 2 POINTERS TO DIVIDED ARRAYS
	int **dPtr = divide_array(array, SIZE);

	print_array(array, SIZE);
	for (i = 0, newSize = SIZE/2; i < SIZE; i++) {
		if(i < newSize)
			printf("1:%d ", dPtr[0][i]);
		else
			printf("2:%d ", dPtr[1][i-newSize]);
	}

	free(dPtr[0]), free(dPtr[1]), free(dPtr);

	//CREATE NEW POLYGON
	float arrX[PARRSIZE] = { 2, 5, -7, 6 }, arrY[PARRSIZE] = { 1, 4, 2, 9 };
	Polygon *polyPtr = create_polygon(arrX, arrY, PARRSIZE);

	for (i = 0, printf("\n\n"); i<PARRSIZE; printf("parr[%d].x: %.1f parr[%d].y: %.1f\n", i, polyPtr->array[i].x, i, polyPtr->array[i].y), i++);

	//ARRAY OF POINTERS TO POLYGON WITH BOTH POSITIVE POINTS
	int posNum = PARRSIZE;

	Point **pntPtr = positive_points(polyPtr, &posNum);

	for (i = 0, putchar('\n'); i < posNum; i++) {
		printf("x[%d]: %.1f  y[%d]: %.1f\n", i, pntPtr[i]->x, i, pntPtr[i]->y);
	}

	free(pntPtr);
	free(polyPtr->array);
	free(polyPtr);

	return 0;
}

void print_array(int *arr, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		printf("%d ", *(arr + i));
	}
	printf("\n\n");;
}

int* sub_array(int *arr, int start, int stop)
{
	int *newArray = malloc((stop - start) * sizeof(int)), *ptr = (arr + start), i;
	if (!newArray) return 0;

	for (i = 0; start < stop; start++, ptr++, i++) {
		*(newArray + i) = *ptr;
	}

	return newArray;
}

int* filter_array(int* arr, int arrSize, int lessThan, int* nSize)
{
	int i;

	for (i = 0, *nSize = 0; i < arrSize; i++)
		*nSize += (*(arr + i) < lessThan) ? 1 : 0;

	int *newArray = malloc(*nSize * sizeof(int));
	if (!newArray) return 0;

	for (i = 0; i < *nSize; arr++)
		if (*arr < lessThan) {
			*(newArray + i) = *arr;
			i++;
		}

	return newArray;
}

int** divide_array(int *arr, int num)
{
	int **arrays, i, j, half = num / 2;

	if (half < 1) return 0;

	arrays = (int **)malloc(2 * sizeof(int *));
	if (!arrays) return 0;
	arrays[0] = (int*)malloc(half * sizeof(int));
	if (!arrays[0]) return 0;
	arrays[1] = (int*)malloc((num-half) * sizeof(int));
	if (!arrays[1]) return 0;

	for (i = 0; i < num; i++) {
		if (i < half)
			arrays[0][i] = arr[i];
		else 
			arrays[1][i - half] = arr[i];
	}

	return arrays;
}

Polygon* create_polygon(float *arrx, float *arry, int num)
{
	int i;

	if (num < 1) return 0;

	Polygon *np = malloc(sizeof(Polygon));
	if (!np) return 0;

	np->numPoints = num;
	np->array = malloc(num * sizeof(Point));
	if (!(np->array)) return 0;

	for (i = 0; i < num; i++) {
		np->array[i].x = arrx[i];
		np->array[i].y = arry[i];
	}

	return np;
}

Point** positive_points(Polygon *pg, int *num)
{
	int i, j, newNum;

	for (i = 0, newNum = 0; i < (*num); i++) {
		newNum += ((pg->array[i].x > 0) && (pg->array[i].y > 0)) ? 1 : 0;
	}

	if (!newNum) return 0;

	Point **ptr = malloc(newNum * sizeof(Point *));
	if (!ptr) return 0;

	for (i = 0, j = 0; i < (*num); i++) {
		if ((pg->array[i].x > 0) && (pg->array[i].y > 0)) {
			ptr[j] = &(pg->array[i]);
			j++;
		}
	}

	(*num) = newNum;
	return ptr;
}
