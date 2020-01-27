#define _CRT_SECURE_NO_WARNINGS
#include "queue.h"

Queue* create_queue()
{
	Queue* que = (Queue*)malloc(sizeof(Queue));
	if (que == NULL) return 0;

	que->first = 0;
	que->last = 0;
	que->filled = 1;
	que->arr[0] = new_game();

	return que;
}

void insert_element(Queue* que, Game* newElement, int parent)
{
	if (que->filled == QUELEN - 1) { return; }

	if ((que->last) + 1 == QUELEN)
		que->last = que->first;
	else
		(que->last)++;
	newElement->parent = parent;
	que->arr[que->last] = newElement;
	(que->filled)++;
}

Game* get(Queue* que)
{
	if (que->filled == 0) {
		printf("Queue empty\n");
		return NULL;
	}

	int index = que->first = ((que->first) + 1) % QUELEN;
	return que->arr[index];
}

int que_moves(Queue* que)
{
	int currentStateIndex = 0;
	Game currentState = *new_game();


	while (!game_won(&currentState))
	{
		Game possibleMoves[4];
		if (!possibleMoves) return;

		int movesMade = make_move(&currentState, possibleMoves);

		for (int i = 0; i < movesMade; i++) {
			if (!game_lost(&possibleMoves[i])) {
				insert_element(que, &possibleMoves[i], currentStateIndex);
			}
		}
	
		copy_state(get(que), &currentState);
		currentStateIndex = que->first;
	}
	printf("Game won!!!\n\n");

	return currentStateIndex;
}

int que_print(Queue* que, int winIndex)
{
	if (que->arr[winIndex]->parent == -1){
		print_state(que->arr[winIndex]);
		return 1;
	}
	print_state(que->arr[winIndex]);
	que_print(que, que->arr[winIndex]->parent);
	return 0;
}

int que_solve()
{
	Queue* newGame = create_queue();
	if (!newGame) return 0;

	int winIndex = que_moves(newGame);
	que_print(newGame, winIndex);
	return 0;
}

