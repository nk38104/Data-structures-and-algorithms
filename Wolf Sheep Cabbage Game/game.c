#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

Game* new_game()
{
	Game* game =(Game*)malloc(sizeof(Game));
	if (game == NULL) return 0;

	game->cabbage = 0;
	game->sheep = 0;
	game->wolf = 0;
	game->man = 0;
	game->parent = -1;

	return game;
}

int game_won(Game* game)
{
	return (game->wolf == 1 && game->sheep == 1 && game->cabbage == 1 && game->man == 1) ? 1 : 0;
}

int game_lost(Game* game)
{
	if (game->wolf == game->sheep && game->sheep != game->man)
		return 1;
	else if (game->sheep == game->cabbage && game->sheep != game->man)
		return 1;
	else
		return 0;
}

int solve(Game* game, int depth)
{
	if (game_won(game)) {
		printf("Game won!!!\n");
		print_state(game);
		return 1;
	}
	if (game_lost(game) || depth == 0)
		return 0;
	Game possibleMoves[4];
	int moves = make_move(game, possibleMoves);

	for (int i = 0; i < moves; i++) {
		if (solve(&possibleMoves[i], depth - 1)) {
			print_state(game);
			return 1;
		}
	}
	return 0;
}

int make_move(Game* game, Game possibleMoves[])
{
	int i;
	for (i = 0; i < 4; i++)
		possibleMoves[i] = *game;
	i = 0;

	if (game->man == 0)
		possibleMoves[i].man = 1;
	else
		possibleMoves[i].man = 0;
	i++;

	if (game->man == 0) {
		if (game->sheep == 0) {
			possibleMoves[i].man = 1;
			possibleMoves[i].sheep = 1;
			i++;
		}
		if (game->wolf == 0) {
			possibleMoves[i].man = 1;
			possibleMoves[i].wolf = 1;
			i++;
		}
		if (game->cabbage == 0) {
			possibleMoves[i].man = 1;
			possibleMoves[i].cabbage = 1;
			i++;
		}
	}
	else {
		if (game->sheep == 1) {
			possibleMoves[i].man = 0;
			possibleMoves[i].sheep = 0;
			i++;
		}
		if (game->wolf == 1) {
			possibleMoves[i].man = 0;
			possibleMoves[i].wolf = 0;
			i++;
		}
		if (game->cabbage == 1) {
			possibleMoves[i].man = 0;
			possibleMoves[i].cabbage = 0;
			i++;
		}
	}
	return i;
}

void print_state(Game* game)
{
	if (game->wolf == 0)
		printf("Wolf\n");
	else
		printf("\t\tWolf\n");

	if (game->sheep == 0)
		printf("Sheep\n");
	else
		printf("\t\tSheep\n");

	if (game->cabbage == 0)
		printf("Cabbage\n");
	else
		printf("\t\tCabbage\n");

	if (game->man == 0)
		printf("Man\n");
	else
		printf("\t\tMan\n");
	printf("---------------------------\n");
}

void copy_state(Game *src, Game* dest)
{
	dest->wolf = src->wolf;
	dest->sheep = src->sheep;
	dest->cabbage = src->cabbage;
	dest->man = src->man;
	dest->parent = src->parent;
}

