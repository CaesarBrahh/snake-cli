/*
- organization
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10
#define MAX 99

int body_length = 0;
int speed = 100000;

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
	int previous_direction;
} snk;

typedef struct
{
	int x;
	int y;
} bdy;

int game_over(int game_state, snk snake, bdy body[body_length]);
void display(fd food, snk snake, bdy body[body_length]);
int move_snake(snk *snake, bdy body[body_length]);
void eat_food(snk snake, fd *food);

int main(void)
{
	// initilialize randomizer
	srand(time(NULL));
	int game_state = 1;

	// initialize food
	fd food;
	food.x = 1 + rand() % WIDTH;
	food.y = 1 + rand() % HEIGHT;

	// initialize snake 
	snk snake;
	snake.head_x = 1 + rand() % WIDTH;
	snake.head_y = 1 + rand() % HEIGHT;
	snake.direction = 0;
	snake.previous_direction = 0;

	// initialize body
	bdy body[MAX];

	// initialize ncurses
	initscr(); // set up screen
	cbreak(); // disable enter requirement
	noecho(); // doesn't print typed keys
	keypad(stdscr, TRUE); // makes arrow keys readable
	nodelay(stdscr, TRUE); // doesn't wait for key to be entered

	while (game_state)
	{
		// build virtual screen
		clear();
		display(food, snake, body);

		// push virtual screen to real screen
		refresh();

		// make changes
		// get player input 
		int ch = getch();
		if (ch == KEY_UP && snake.direction != KEY_DOWN|| ch == KEY_DOWN && snake.direction != KEY_UP|| ch == KEY_LEFT && snake.direction != KEY_RIGHT|| ch == KEY_RIGHT && snake.direction != KEY_LEFT)
		{
			snake.direction = ch;
		}

		// gameover?
		game_state = game_over(game_state, snake, body);

		// eat food if player's position eawuals the food's position
		eat_food(snake, &food);

		// move snake based on player input
		move_snake(&snake, body);

		// wait
		usleep(speed);
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
		// change food position
		food->x = 1 + rand() % WIDTH;
		food->y = 1 + rand() % HEIGHT;

		// increment snake length
		body_length++;
	}
}

void move_body(bdy body[body_length], int new_x, int new_y)
{
	// remove oldest
	// shift everything up by 1 removing the first (oldest) element
	for (int i = 0; i < body_length; i++)
	{
		body[i] = body[i+1];
	}

	// add newest to back
	body[body_length-1].x = new_x;
	body[body_length-1].y = new_y;
}

int move_snake(snk *snake, bdy body[body_length])
{
	if (snake->direction != 0)
	{
		if (snake->direction == KEY_UP) // up
		{
			// update body
			move_body(body, snake->head_x, snake->head_y);

			// update head
			snake->head_y -= 1;

			// update speed
			speed = 150000;
		}
		else if (snake->direction == KEY_DOWN) // down
		{
			// update body
			move_body(body, snake->head_x, snake->head_y);

			// update head
			snake->head_y += 1;

			// update speed
			speed = 150000;
		}
		else if (snake->direction == KEY_LEFT) // left
		{
			// update body
			move_body(body, snake->head_x, snake->head_y);

			// update head
			snake->head_x -= 1;

			// update speed
			speed = 100000;
		}
		else if (snake->direction == KEY_RIGHT) // right
		{
			// update body
			move_body(body, snake->head_x, snake->head_y);

			// update head
			snake->head_x += 1;

			// update speed
			speed = 100000;
		}
	}

	return 0;
}

void display(fd food, snk snake, bdy body[body_length])
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

		for (int j = 1; j <= WIDTH; j++)
		{
			// food
			if (food.x == j && food.y == i)
			{
				printw("$");
			}
			// head
			else if (snake.head_x == j && snake.head_y == i)
			{
				printw("@");
			}
			// body or empty space
			else
			{
				// body
				int is_body = 0;
				for (int k = 0; k < body_length; k++)
				{
					if (body[k].x == j && body[k].y == i)
					{
						printw("0");
						is_body = 1;
						break;
					}
				}

				// empty space
				if (!is_body)
				{
					printw(" ");
				}
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

int game_over(int game_state, snk snake, bdy body[body_length])
{
	if (game_state == 1)
	{
		// wall collision
		if (snake.head_x >= WIDTH || snake.head_y > HEIGHT || snake.head_x <= 0 || snake.head_y < 0)
		{
			return 0;
		}

		// body collision
		for (int i = 0; i < body_length; i++)
		{
			if (snake.head_x == body[i].x && snake.head_y == body[i].y)
			{
				return 0;
			}
		}
	}

	return 1;
}