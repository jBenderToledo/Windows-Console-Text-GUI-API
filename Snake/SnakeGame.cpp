#include "pch.h"
#include "SnakeGame.h"

#define _COORDINATE_EQUALS(a,b) (a).x == (b).x && (a).y == (b).y

using namespace Screen;

SnakeGame::SnakeGame(double screenChangeFrequency)
{
	changeScreenSize(800, 800);

	speed = screenChangeFrequency;
	foodLocation = { 30, 30 };
}


SnakeGame::~SnakeGame()
{
}

void SnakeGame::move(Player & player)
{
	Coordinate nextPosition = player.location;
	Coordinate *q = player.tailQueue;
	short &x = nextPosition.x, &y = nextPosition.y;
	int &ptr = player.tailQueuePointer;

	switch (player.dir)
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
		player.isDead = true;
		return;
	}

	if (_COORDINATE_EQUALS(foodLocation, nextPosition))
	{
		for (int i = player.size; i > ptr; i--)
			q[i] = q[i - 1];

		player.size++;

		bool foodOverlap = false;
		do
		{
			foodOverlap = false;
			foodLocation = { rand() % (BOARD_SIZE - 2) + 1, rand() % (BOARD_SIZE - 2) + 1 };

			for (int i = 0; i < player.size || foodOverlap; i++)
			{
				foodOverlap = _COORDINATE_EQUALS(foodLocation, q[i]);
				if (foodOverlap)
					break;
			}

			foodOverlap = (_COORDINATE_EQUALS(foodLocation, player.location) || _COORDINATE_EQUALS(foodLocation, nextPosition));
				
		} while (foodOverlap);
	}

	q[ptr] = player.location;
	player.location = nextPosition;
	ptr++;
}

SnakeGame::Player::Player()
{
	short x = 5, y = 5; int i = STARTING_SIZE;
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
