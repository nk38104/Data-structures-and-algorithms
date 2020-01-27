#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sorting.h"

bool choosePivot;
int numMin;

// pomocne funkcije
void print_array(int* niz, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", niz[i]);
	}
	printf("\n");
}

void shuffle(int* niz, int n) {
	for (int i = 0; i < n; i++) {
		int k1 = rand() % n;
		int tmp = niz[i];
		niz[i] = niz[k1];
		niz[k1] = tmp;
	}
}

// generiranje i ispis niza
int* generate_array(int n) {
	int* niz = (int*)malloc(sizeof(int) * n);
	if (!niz) return 0;

	niz[0] = rand() % 5;
	for (int i = 1; i < n; i++) {
		niz[i] = niz[i - 1] + rand() % 5;
	}
	shuffle(niz, n);

	return niz;
}

// selection sort
void selection_sort(int* niz, int n) {
	int i;
	for (i = 0; i < n - 1; i++) {
		int j, tmp, maxi = i;
		for (j = i + 1; j < n; j++) {
			if (niz[j] < niz[maxi])
				maxi = j;
		}

		tmp = niz[maxi];
		niz[maxi] = niz[i];
		niz[i] = tmp;
	}
}

// insertion sort
void insertion_sort(int* niz, int n) {
	int i;
	for (i = 1; i < n; i++) {
		int j = i;
		while (j > 0 && niz[j - 1] > niz[j]) {
			int tmp = niz[j - 1];
			niz[j - 1] = niz[j];
			niz[j] = tmp;
			j--;
		}
	}
}

// quick sort
int calc_median(int a, int b, int c) {
	return (a >= b) ? ((c >= a) ? a : ((b >= c) ? b : c)) : ((c >= b) ? b : ((a >= c) ? a : c));
}

int partition(int* niz, int n) {
	if (choosePivot == true) {
		int pivot = calc_median(niz[0], niz[n/2], niz[n-1]);
		int temp = niz[0]; 
		niz[0] = pivot;
		if (pivot == niz[n/2])
			niz[n/2] = temp;
		if (pivot == niz[n-1])
			niz[n-1] = temp;
	}

	int l = 1, r = n - 1;

	while (l < r) {
		if (niz[r] >= niz[0]) {
			r--;
		}
		else if (niz[l] < niz[0]) {
			l++;
		}
		else {
			int tmp = niz[l];
			niz[l] = niz[r];
			niz[r] = tmp;
		}
	}
	if (niz[0] < niz[r]) { // 1
		return 0;
	}
	else { // 3
		int tmp = niz[r];
		niz[r] = niz[0];
		niz[0] = tmp;
		return r;
	}
}

void quicksort(int* niz, int n) {
	if (n < numMin) {
		selection_sort(niz, n);
	}
	else {
		if (n < 2)
			return;
		int pi = partition(niz, n);
		quicksort(niz, pi);
		quicksort(niz + pi + 1, n - pi - 1);
	}
}

// merge sort
void merge(int* niz, int l, int m, int r) {
	// implemntirati merge funkciju
	int i, j, k, sizeLeft = m - l + 1, sizeRight = r - m;

	int *left = (int*)malloc(sizeLeft * sizeof(int)), *right = (int*)malloc(sizeRight * sizeof(int)); // temp lijeva i desna strana
	if (!left || !right) return;

	for (i = 0; i < sizeLeft; i++)  // kopiramo brojeve u njih
		left[i] = niz[l + i];
	for (j = 0; j < sizeRight; j++)
		right[j] = niz[m + 1 + j];

	for (i = 0, j = 0, k = l; i < sizeLeft && j < sizeRight; k++) {  // mergamo temp nazad u niz
		if (left[i] <= right[j]) {
			niz[k] = left[i];
			i++;
		}
		else {
			niz[k] = right[j];
			j++;
		}
	}

	for (; i < sizeLeft; i++, k++) {  // kopiraj ostatke lijeve i desne strane ako ima
		niz[k] = left[i];
	}

	for (; j < sizeRight; j++, k++) {
		niz[k] = right[j];
	}

	free(left), free(right);
}

// alocira i vraca kopiju niza
int* duplicate(int* niz, int n) {
	int i;
	int* novi = (int*)malloc(sizeof(int) * n);
	if (!novi) return 0;

	for (i = 0; i < n; i++) {
		novi[i] = niz[i];
	}
	return novi;
}

void merge_sort(int* niz, int l, int r) {
	if (l < r) {
		int m = l + (r - l) / 2;

		merge_sort(niz, l, m);
		merge_sort(niz, m + 1, r);

		merge(niz, l, m, r);
	}
}

// mjerenje vremena izvodenja funkcije sortiranja
double measure(void(*sort)(int* niz, int n), int* niz, int n) {
	clock_t start_time = clock();
	sort(niz, n);
	clock_t end_time = clock();
	return ((double)(end_time - start_time) / CLOCKS_PER_SEC);
}


double merge_measure(void(*sort)(int* niz, int n), int* niz, int l, int r) {
	clock_t start_time = clock();
	sort(niz, l, r);
	clock_t end_time = clock();
	return ((double)(end_time - start_time) / CLOCKS_PER_SEC);
}
