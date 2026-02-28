/*
- only accept arrow keys
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10

typedef struct 
{
	int x;
	int y;
} fd;

typedef struct
{
	int head_x;
	int head_y;

	int direction;
} snk;

int game_over(int game_state, int i);
void display(fd food, snk snake);
int move_snake(snk *snake);
void eat_food(snk snake, fd *food);

int main(void)
{
	// initilialize randomizer
	srand(time(NULL));
	int game_state = 1;

	fd food;
	food.x = 1 + rand() % WIDTH;
	food.y = 1 + rand() % HEIGHT;

	snk snake;
	snake.head_x = 1 + rand() % WIDTH;
	snake.head_y = 1 + rand() % HEIGHT;
	snake.direction = 0;

	// initialization
	initscr(); // set up screen
	cbreak(); // disable enter requirement
	noecho(); // doesn't print typed keys
	keypad(stdscr, TRUE); // makes arrow keys readable
	nodelay(stdscr, TRUE); // doesn't wait for key to be entered

	int i = 4;
	while (game_state)
	{
		// build virtual screen
		clear();
		display(food, snake);

		// push virtual screen to real screen
		refresh();

		// make changes
		// get player input 
		int ch = getch();
		if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT)
		{
			snake.direction = ch;
		}

		// eat food if player's position eawuals the food's position
		eat_food(snake, &food);

		// move snake based on player input
		move_snake(&snake);

		// gameover?
		//game_state = game_over(game_state, i);

		// wait
		usleep(100000);
	}
	
	// restore terminal to normal state
	endwin();

	// end program
	return 0;
}

void eat_food(snk snake, fd *food)
{
	if (food->x == snake.head_x && food->y == snake.head_y)
	{
		food->x = 1 + rand() % WIDTH;
		food->y = 1 + rand() % HEIGHT;
	}
}

int move_snake(snk *snake)
{
	if (snake->direction != 0)
	{
		if (snake->direction == KEY_UP) // up
		{
			snake->head_y -= 1;
			return 0;
		}

		if (snake->direction == KEY_DOWN) // down
		{
			snake->head_y += 1;
			return 0;
		}

		if (snake->direction == KEY_LEFT) // left
		{
			snake->head_x -= 1;
			return 0;
		}

		if (snake->direction == KEY_RIGHT) // right
		{
			snake->head_x += 1;
			return 0;
		}
	}

	return 0;
}

void display(fd food, snk snake)
{
	// print top edge
	printw("+");
	for (int i = 0; i < WIDTH; i++)
	{
		printw("-");
	}
	printw("+\n");

	for (int i = 0; i <= HEIGHT; i++)
	{
		printw("|");

		for (int j = 0; j < WIDTH; j++)
		{
			if (food.x == j && food.y == i)
			{
				printw("$");
			}
			else if (snake.head_x == j && snake.head_y == i)
			{
				printw("@");
			}
			else
			{
				printw(" ");
			}
		}

		printw("|\n");
	}

	printw("\n");

	// print bottom edge
	printw("+");
	for (int i = 0; i < WIDTH; i++)
	{
		printw("-");
	}
	printw("+\n");
}

int game_over(int game_state, int i)
{
	if (game_state == 1)
	{
		if (i >= 10)
		{
			return 0;
		}
	}

	return 1;
}