#pragma once
#include "pch.h"

#include "TicTacToeBoard.h"
#include "TicTacToeLogic.h"
#include <array>

#include <stdlib.h>
#include <time.h>


using namespace TicTacToe;

bool Board::isEmpty(int xCoordinate, int yCoordinate) {
	return (getGameState() != 0);
}

bool Board::isGameOver(int xCoordinate, int yCoordinate) {
	return (getGameState() != GameStatus::ongoing);
}

int Board::getGameState() {
	return Logic::gameStatus(boardState);
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

void Board::promptPlayer(){
	clearPromptOnScreen();

	char** prompt = determinePromptState();

	delete promptPrinter;
	promptPrinter = new Screen::MatrixPrinter(
		prompt,
		PROMPT_BUFFER_HEIGHT,
		PROMPT_BUFFER_WIDTH,
		PROMPT_START_POSITION
	);

	for (int y = 0; y < PROMPT_BUFFER_HEIGHT; y++) {
		delete[] prompt[y];
	}
	delete[] prompt;
}

void Board::determineTurnPlayer() {
	if (turnPlayer == 0) {
		srand(time(NULL));

		turnPlayer = 1 + (rand() % 2);
	}
	else {
		turnPlayer = (turnPlayer == 2) ? 1 : 2;
	}
}

void Board::clearPromptOnScreen() {
	promptClearer.WriteAllToScreen();
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

char** Board::determinePromptState()
{
	int gameState = getGameState();
	int playerPromptIndex = (gameState == 3) ? 3 : turnPlayer;

	char** promptBuffer = new char* [2]{
		(char*) PLAYER_PROMPTS[playerPromptIndex].c_str(),
		(char*) END_STATE_PROMPTS[gameState].c_str()
	};

	return promptBuffer;
}
