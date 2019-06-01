#pragma once
#include "pch.h"
#include "SnakeGame.h"

#define _COORDINATE_EQUALS(a,b) (a).x == (b).x && (a).y == (b).y

// ----------
// - Player -
// ----------

SnakeGame::Player::Player()
{
	location = { 5,5 };
	ushort &x = location.x, &y = location.y;
	
	
	int i = size = STARTING_SIZE;
	dir = DOWN;
	while (i > 0)
	{
		tailQueue[tailQueuePointer] = { x,y };
		tailQueuePointer++;
		y++;
		i--;
	}
	tailQueuePointer = 0;
}

SnakeGame::Player::~Player()
{
}

// ---------
// - Snake -
// ---------

SnakeGame::SnakeGame(double screenChangeFrequency)
{
	Screen::changeScreenSize(800, 800);
	Screen::turnOffCursor();

	speed = screenChangeFrequency;
	foodLocation = { 10,10 };

	board = new char*[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		board[i] = new char[BOARD_SIZE] {' '};

	gui = new char*[GUI_HEIGHT];
	for (int i = 0; i < GUI_HEIGHT; i++)
		gui[i] = new char[GUI_WIDTH] {' '};
	
	grid = new char*[GRID_HEIGHT];
	for (int i = 0; i < GRID_HEIGHT; i++)
		grid[i] = new char[GRID_WIDTH];
}

SnakeGame::~SnakeGame()
{
	for (int i = 0; i < BOARD_SIZE; i++)
		delete board[i];
	delete board;

	for (int i = 0; i < GUI_HEIGHT; i++)
		delete gui[i];
	delete gui;

	for (int i = 0; i < GRID_HEIGHT; i++)
		delete grid[i];
	delete grid;
}

void SnakeGame::move()
{
	Coordinate nextPosition = snake.location;
	Coordinate *q = snake.tailQueue;

	ushort &x = nextPosition.x, &y = nextPosition.y;

	switch (snake.dir)
	{
	case Player::Direction::LEFT:
		x--;
		break;
	case Player::Direction::RIGHT:
		x++;
		break;
	case Player::Direction::UP:
		y--;
		break;
	case Player::Direction::DOWN:
		y++;
		break;
	}

	if (x == 0 || x == BOARD_SIZE - 1 || y == 0 || y == BOARD_SIZE - 1)
	{
		snake.isDead = true;
		return;
	}

	if (_COORDINATE_EQUALS(foodLocation, nextPosition))
	{
		for (int i = snake.size; i > snake.tailQueuePointer; i--)
			q[i] = q[i - 1];

		snake.size++;

		bool foodOverlap = false;
		do
		{
			foodOverlap = false;
			foodLocation = { rand() % (BOARD_SIZE - 2) + 1, rand() % (BOARD_SIZE - 2) + 1 };

			for (int i = 0; i < snake.size || foodOverlap; i++)
			{
				foodOverlap = _COORDINATE_EQUALS(foodLocation, q[i]);
				if (foodOverlap)
					break;
			}

			foodOverlap = (_COORDINATE_EQUALS(foodLocation, snake.location) || _COORDINATE_EQUALS(foodLocation, nextPosition));
				
		} while (foodOverlap);
	}

	q[snake.tailQueuePointer] = snake.location;
	snake.location = nextPosition;

	snake.tailQueuePointer++;
	if (snake.tailQueuePointer == snake.size)
		snake.tailQueuePointer = 0;
}

void SnakeGame::prepareSquare()
{
	const char BORDER = '#';
	const char INSIDE = ' ';

	Coordinate position;
	ushort &x = position.x, &y = position.y;

	for (x = 0; x < BOARD_SIZE; x++)
		for (y = 0; y < BOARD_SIZE; y++)
		{
			if (x == 0 || x == BOARD_SIZE - 1 || y == 0 || y == BOARD_SIZE - 1)
				board[y][x] = BORDER;
			else
				board[y][x] = INSIDE;
		}
}

void SnakeGame::drawBoard()
{
	Coordinate position = { 1, 1 };
	Coordinate* q = snake.tailQueue;
	ushort &x = position.x, &y = position.y;

	for (y = 1; y < BOARD_SIZE - 1; y++)
		for (x = 1; x < BOARD_SIZE - 1; x++)
			board[y][x] = ' ';

	prepareSquare();

	for (int i = 0; i < snake.size; i++)
	{
		board[q[i].y][q[i].x] = SNAKE_SEGMENT;
	}

	board[snake.location.y][snake.location.x] = SNAKE_HEAD[snake.dir];
	board[foodLocation.y][foodLocation.x] = FOOD_ICON;
}

void SnakeGame::drawGUI()
{
	const static int ROW_INDENT = STATS_OFFSET;
	const static Coordinate ROW_START = { ROW_INDENT, 3 };
	const static ushort &x0 = ROW_START.x;
	const static ushort &y0 = ROW_START.y;
	
	const static Coordinate HIGH_SCORE_POS = { x0,y0 };
	const static Coordinate SCORE_POS = { x0 + 3, y0 + 1 };
	const static Coordinate SIZE_POS = { x0 + 3, y0 + 2 };

	const static char* HIGH_SCORE_STRING = "High score: ";
	char highScoreValue[50];
	strcpy_s(highScoreValue, HIGH_SCORE_STRING);
	strcat_s(highScoreValue, std::to_string(0).c_str());

	const static char* SCORE_STRING = "Score: ";
	char scoreValue[50];
	strcpy_s(scoreValue, SCORE_STRING);
	strcat_s(scoreValue, std::to_string(score).c_str());

	const static char* SIZE_STRING = "Size: ";
	char sizeValue[50];
	strcpy_s(sizeValue, SIZE_STRING);
	strcat_s(sizeValue, std::to_string(snake.size).c_str());

	Screen::writeToBuffer(gui, (char**)&highScoreValue, (ushort) strlen(highScoreValue), 1, HIGH_SCORE_POS);
	Screen::writeToBuffer(gui, (char**)&scoreValue, (ushort) strlen(scoreValue), 1, SCORE_POS);
	Screen::writeToBuffer(gui, (char**)&sizeValue, (ushort) strlen(sizeValue), 1, SIZE_POS);
}

void SnakeGame::drawGrid()
{
	for (int y = 0; y < BOARD_SIZE; y++)
		for (int x = 0; x < BOARD_SIZE; x++)
			grid[y][x] = board[y][x];

	for (int y = 0; y < GUI_HEIGHT; y++)
		for (int x = 0; x < GUI_WIDTH; x++)
			grid[y][x + BOARD_SIZE] = gui[y][x];
}

void SnakeGame::drawScreen()
{
	drawBoard();
	// drawGUI();
	drawGrid();

	Screen::writeToScreen(grid, GRID_WIDTH, GRID_HEIGHT);
}

long SnakeGame::play()
{
	drawScreen();

	return 0;
}