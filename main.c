#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{
	int food_x;
	int food_y;

	int head_x;
	int head_y;

	int tail[1];

	int direction;
} content;

void screen_render(int board[10][20], content contents);
void place_food(content *contents);

int main(void)
{
	// intialize randomizer
	srand(time(NULL));

	// define necessary variables
	int board[10][20];
	content contents;

	// build board
	place_food(&contents);
	contents.head_x = 1 + rand() % 10;
	contents.head_y = 1+ rand() % 21;	

	while(0)
	{
		// clear terminal and render screen
		printf("\033[2J\033[H");
		screen_render(board, contents);

		// wait for user input

		// move

		// sleep tick
	}

	return 0;
}

void move()
{
	//
}

void place_food(content *contents)
{
	contents->food_x = rand() % 11;
	contents->food_y = rand() % 21;
}

void screen_render(int board[10][20], content contents)
{
	printf("+--------------------+\n");
	for (int i = 0; i < 10; i++)
	{
		printf("|");
		for (int j = 0; j < 20; j++)
		{
			if (contents.food_x == i && contents.food_y == j)
			{
				printf("$");
			}
			else if (contents.head_x == i && contents.head_y == j)
			{
				printf("@");
			}
			else
			{
				printf(" ");
			}
		}
		printf("|\n");
	}
	printf("+--------------------+\n");
}