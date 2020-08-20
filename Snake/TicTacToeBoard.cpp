#pragma once
#include "pch.h"

#include "TicTacToeBoard.h"
#include <array>

bool TicTacToeBoard::isEmpty(int xCoordinate, int yCoordinate) {
	int playerIndex = getPlayerIndexOf(xCoordinate, yCoordinate);

	return playerIndex == 1 || playerIndex == 2;
}

int TicTacToeBoard::getPlayerIndexOf(int xCoordinate, int yCoordinate) {
	int boardStateIndex = 3 * yCoordinate + xCoordinate;
	int playerIndex = boardState[boardStateIndex];

	return playerIndex;
}

char TicTacToeBoard::getPlayerSymbolOf(int xCoordinate, int yCoordinate) {
	int playerIndex = getPlayerIndexOf(xCoordinate, yCoordinate);

	return PLAYER_SYMBOLS[playerIndex];
}

std::array<std::array<char, 3>, 3> TicTacToeBoard::getSymbolicBoardState() {
	std::array<std::array<char, 3>, 3> symbolicBoardState;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			symbolicBoardState[y][x] = getPlayerSymbolOf(x, y);
		}
	}

	return symbolicBoardState;
}
