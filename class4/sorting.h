#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef sorting_h
#define sorting_h

typedef enum { false, true } bool;
extern bool choosePivot;
extern int numMin;

void print_array(int*, int);
int* generate_array(int);
void shuffle(int*, int);
void selection_sort(int*, int);
void insertion_sort(int*, int);
int partition(int*, int);
void quicksort(int*, int);
void merge(int*, int, int, int);
int* duplicate(int*, int);
void merge_sort(int*, int);
double measure(void(*)(int*, int), int*, int);
double merge_measure(void(*)(int*, int), int*, int, int);

#endif
