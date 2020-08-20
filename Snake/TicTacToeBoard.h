#pragma once
#include "pch.h"

#include "MatrixPrinter.h"
#include <array>

namespace TicTacToe {
	class Board {
		std::array<char, 3> PLAYER_SYMBOLS = { ' ', 'X', 'O' };

		int boardState[9] = { 0 };
		Screen::MatrixPrinter boardPrinter;
		Coordinate initialPosition = { 2,2 };

	public:
		Board();

	private:
		bool isEmpty(int xCoordinate, int yCoordinate);
		bool isGameOver(int xCoordinate, int yCoordinate);
		int whichPlayerWins(int xCoordinate, int yCoordinate);
		int getPlayerIndexOf(int xCoordinate, int yCoordinate);
		char getPlayerSymbolOf(int xCoordinate, int yCoordinate);
		std::array<std::array<char, 3>, 3> getSymbolicBoardState();
	};
}