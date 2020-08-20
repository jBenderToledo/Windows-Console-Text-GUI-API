#pragma once
#include "pch.h"

#include "MatrixPrinter.h"
#include <array>
#include <string>

namespace TicTacToe {

	enum GameStatus {
		ongoing = 0,
		player1Wins,
		player2Wins,
		tiedGame
	};

	class Board {
		static const int BOARD_SIZE_ON_SCREEN = 5 + 2;
		static const int BOARD_BUFFER_WIDTH = BOARD_SIZE_ON_SCREEN + 20;
		static const int BOARD_BUFFER_HEIGHT = BOARD_SIZE_ON_SCREEN;

		static const int PROMPT_BUFFER_WIDTH = 40;
		static const int PROMPT_BUFFER_HEIGHT = 2;

		const char PLAYER_SYMBOLS[3] = { ' ', 'X', 'O' };

		const Coordinate INITIAL_POSITION = { 1,1 };
		const Coordinate PROMPT_START_POSITION = {
			INITIAL_POSITION.x,
			INITIAL_POSITION.y + BOARD_BUFFER_HEIGHT + 2
		};

		const std::string CLEAR_PROMPT = "                                       ";
		const std::string PLAYER_PROMPTS[4] = {
			CLEAR_PROMPT,
			"Player X, please take your turn:",
			"Player O, please take your turn:",
			"Game over!"
		};

		const std::string END_STATE_PROMPTS[4] = {
			CLEAR_PROMPT,
			"Player X wins!",
			"Player O wins!",
			"A tie..."
		};

		int boardState[9] = { 0 };
		int turnPlayer = 0;

		Screen::MatrixPrinter boardPrinter;
		Screen::MatrixPrinter* promptPrinter = NULL;
		Screen::MatrixPrinter promptClearer = Screen::MatrixPrinter(
			new char*[2] {
				(char*) CLEAR_PROMPT.c_str(),
				(char*) CLEAR_PROMPT.c_str()
			},
			PROMPT_BUFFER_HEIGHT,
			PROMPT_BUFFER_WIDTH,
			PROMPT_START_POSITION
		);


	public:
		Board();
		void printBoardState();

	private:
		void initializeBoard();
		bool isEmpty(int xCoordinate, int yCoordinate);
		bool isGameOver(int xCoordinate, int yCoordinate);
		int getGameState();
		int getPlayerIndexOf(int xCoordinate, int yCoordinate);
		char getPlayerSymbolOf(int xCoordinate, int yCoordinate);

		void promptPlayer();
		void determineTurnPlayer();
		void clearPromptOnScreen();

		std::array<std::array<char, 3>, 3> getSymbolicBoardState();
		char** determinePromptState();
	};
}