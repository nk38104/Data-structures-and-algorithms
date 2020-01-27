#pragma once
#ifndef game_h
#define game_h

#include <stdio.h>
#include <stdlib.h>

typedef struct Game
{
	int wolf, sheep, cabbage;
	int man, parent;
}Game;

Game* new_game(void);
int game_won(Game*);
int game_lost(Game*);
void print_state(Game*);
int solve(Game*, int);
int make_move(Game*, Game[]);
void copy_state(Game*, Game*);

#endif /* game_h */

