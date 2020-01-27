#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#define QUELEN 100

typedef struct _Queue {
	int first, last, filled;
	Game* arr[QUELEN];
}Queue;

Queue* create_queue(void);
void insert_element(Queue*, Game*, int);
Game* get(Queue*);
int que_moves(Queue*);
int que_print(Queue*, int);
int que_solve(void);





