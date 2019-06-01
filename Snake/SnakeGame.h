#pragma once
#include "pch.h"
#include "Screen.h"
#include <iostream>
#include <string>
#include <string.h>

using Screen::Coordinate;

class SnakeGame
{
public:
	SnakeGame(double screenChangeFrequency = 1.0);
	~SnakeGame();

	long play(); // Returns the score from playing Snake.

private:
	const char FOOD_ICON = 'D';
	const char SNAKE_HEAD[4] = { 'V', '<', '^', '>' };
	const char SNAKE_SEGMENT = 'O';
	const unsigned char WALL_CHARACTER = 0xB2;
	const short STATS_OFFSET = 3;

	const short BOARD_SIZE = 20 + 2; // Board is BOARD_SIZE x BOARD_SIZE in size including walls.
	const short GUI_WIDTH = 40 - BOARD_SIZE;
	const short GUI_HEIGHT = BOARD_SIZE;
	const short GRID_HEIGHT = (BOARD_SIZE > GUI_HEIGHT) ? BOARD_SIZE : GUI_HEIGHT;
	const short GRID_WIDTH = BOARD_SIZE + GUI_WIDTH;

	const Coordinate STARTING_CORNER = { 0, 0 };
	const Coordinate ENDING_CORNER = { BOARD_SIZE - 1, BOARD_SIZE - 1 };
	const Coordinate SCORE_POSITION = { STATS_OFFSET - 1, 2 };
	const Coordinate TIME_POSITION = { STATS_OFFSET, SCORE_POSITION.y + 2 };
	const Coordinate SIZE_POSITION = { STATS_OFFSET, TIME_POSITION.y + 1 };
	const Coordinate SCORE_RATE_POSITION = { STATS_OFFSET, SIZE_POSITION.y + 1 };

	struct Player
	{
		enum Direction { DOWN, LEFT, UP, RIGHT };

		Coordinate location;
		Direction dir;

		Player();
		~Player();

		const static int MAX_SIZE = 0xFFFF;
		const static int STARTING_SIZE = 5;
		int size = 0;
		bool isDead = false;

		Coordinate tailQueue[MAX_SIZE - 1];
		int tailQueuePointer = 0; // Points to the oldest segment on the snake.
	};

	Player snake;
	Coordinate foodLocation;

	long score = 0;
	double speed;

	char **board;
	const Coordinate BOARD_OFFSET = Screen::ORIGIN;
	char **gui;
	const Coordinate GUI_OFFSET = { BOARD_OFFSET.x + BOARD_SIZE, BOARD_OFFSET.y };
	char **grid;
	// Grid offset is ALWAYS the origin because it is the lowest visual layer by default.

	void drawScreen();
	void drawBoard();
	void drawGUI();
	void drawGrid();
	void move();
	void prepareSquare();

};

