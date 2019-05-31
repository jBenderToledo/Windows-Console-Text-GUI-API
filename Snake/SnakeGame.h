#pragma once

#include "Screen.h"
using namespace Screen;

class SnakeGame
{
public:
	SnakeGame(double screenChangeFrequency = 1.0);
	~SnakeGame();

	long play(); // Returns the score from playing Snake.

private:
	const char FOOD = 'D';
	const char SNAKE_HEAD[4] = { 'V', '<', '^', '>' };
	const char SNAKE_SEGMENT = 'O';
	const char WALL_CHARACTER = 0xB2;
	const short BOARD_SIZE = 80; // Board is BOARD_SIZE x BOARD_SIZE in size excluding walls
	const short STATS_OFFSET = BOARD_SIZE + 4;

	const Coordinate STARTING_CORNER = { 0, 0 };
	const Coordinate ENDING_CORNER = { BOARD_SIZE, BOARD_SIZE };
	const Coordinate SCORE_POSITION = { STATS_OFFSET - 1, 2 };
	const Coordinate TIME_POSITION = { STATS_OFFSET, SCORE_POSITION.y + 2 };
	const Coordinate SIZE_POSITION = { STATS_OFFSET, TIME_POSITION.y + 1 };
	const Coordinate SCORE_RATE_POSITION = { STATS_OFFSET, SIZE_POSITION.y + 1 };


	struct Player
	{
		static enum Direction { DOWN, LEFT, UP, RIGHT };

		Coordinate location;
		Direction dir;

		Player();
		~Player();

		const static int MAX_SIZE = 255;
		const static int STARTING_SIZE = 5;
		int size = 0;
		bool isDead = false;

		Coordinate tailQueue[MAX_SIZE - 1];
		int tailQueuePointer = 0; // Points to the oldest segment on the snake.
	};

	Player snake;
	long score = 0;


	double speed;

	void move(Player &p);

	Coordinate foodLocation;

};

