#pragma once
#include "pch.h"

namespace TicTacToe {
	class Logic
	{
	public:
		static int gameStatus(const int* boardState);
	private:
		static int horizontalState(const int* board);
		static int verticalState(const int* board);
		static int rightDiagonalState(const int* board);
		static int leftDiagonalState(const int* board);

		static bool isBoardFull(const int* board);

		static int getPlayerAt(const int* board, int x, int y);
	};
}

