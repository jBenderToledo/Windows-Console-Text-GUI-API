#pragma once
#include "pch.h"

#include "TicTacToeLogic.h"

using namespace TicTacToe;

int Logic::gameStatus(const int* board) {
	int possibleState = 0;

	possibleState = horizontalState(board);
	if (possibleState != 0) return possibleState;

	possibleState = verticalState(board);
	if (possibleState != 0) return possibleState;

	possibleState = rightDiagonalState(board);
	if (possibleState != 0) return possibleState;

	possibleState = leftDiagonalState(board);
	
	if (isBoardFull(board)) {
		return 3;
	}

	return possibleState;
}

int Logic::horizontalState(const int* board) {
	int rowPlayer;

	for (int row = 0; row < 3; row++) {
		rowPlayer = getPlayerAt(board, 0, row);

		if (rowPlayer == getPlayerAt(board, 1, row)
			&& rowPlayer == getPlayerAt(board, 2, row)) {
			return rowPlayer;
		}
	}

	return 0;
}

int Logic::verticalState(const int* board) {
	int rowPlayer;

	for (int column = 0; column < 3; column++) {
		rowPlayer = getPlayerAt(board, column, 0);

		if (rowPlayer == getPlayerAt(board, column, 1)
			&& rowPlayer == getPlayerAt(board, column, 2)) {
			return rowPlayer;
		}
	}

	return 0;
}

int Logic::rightDiagonalState(const int* board) {
	bool isWinner;
	int rowPlayer;

	rowPlayer = getPlayerAt(board, 0, 0);

	if (rowPlayer == getPlayerAt(board, 1, 1) 
		&& rowPlayer == getPlayerAt(board, 2, 2)) {
		return rowPlayer;
	}

	return 0;
}

int Logic::leftDiagonalState(const int* board) {
	bool isWinner;
	int rowPlayer;

	rowPlayer = getPlayerAt(board, 0, 2);

	if (rowPlayer == getPlayerAt(board, 1, 1)
		&& rowPlayer == getPlayerAt(board, 2, 0)) {
		return rowPlayer;
	}

	return 0;
}

bool TicTacToe::Logic::isBoardFull(const int* board)
{
	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			if (getPlayerAt(board, column, row) == 0) {
				return false;
			}
		}
	}

	return true;
}

int Logic::getPlayerAt(const int* board, int x, int y)
{
	return board[3 * y + x];
}
