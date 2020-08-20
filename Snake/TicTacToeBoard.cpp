#pragma once
#include "pch.h"

#include "TicTacToeBoard.h"
#include "TicTacToeLogic.h"
#include <array>

using namespace TicTacToe;

bool Board::isEmpty(int xCoordinate, int yCoordinate) {
	int playerIndex = getPlayerIndexOf(xCoordinate, yCoordinate);

	return playerIndex == 1 || playerIndex == 2;
}

int Board::getPlayerIndexOf(int xCoordinate, int yCoordinate) {
	int boardStateIndex = 3 * yCoordinate + xCoordinate;
	int playerIndex = boardState[boardStateIndex];

	return playerIndex;
}

char Board::getPlayerSymbolOf(int xCoordinate, int yCoordinate) {
	int playerIndex = getPlayerIndexOf(xCoordinate, yCoordinate);

	return PLAYER_SYMBOLS[playerIndex];
}

std::array<std::array<char, 3>, 3> Board::getSymbolicBoardState() {
	std::array<std::array<char, 3>, 3> symbolicBoardState;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			symbolicBoardState[y][x] = getPlayerSymbolOf(x, y);
		}
	}

	return symbolicBoardState;
}
