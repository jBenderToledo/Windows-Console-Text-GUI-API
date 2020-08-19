#pragma once
#include "pch.h"

#include "MatrixPrinter.h"

using namespace Screen;

class ChessBoard
{
	static const unsigned char BLACK_SQUARE = ' ';
	static const unsigned char WHITE_SQUARE = 0xB2;


	const char INITIAL_STATE[8][9] = {
		"RNBQKBNR",
		"PPPPPPPP",
		"        ",
		"        ",
		"        ",
		"        ",
		"pppppppp",
		"rnbqkbnr" };

	const char MOVE_PROMPT[2][55] = {
		"White (capital) player, please make your move. ",
		"Black (lowercase) player, please make your move. "
	};

	char boardState[8][9];

	MatrixPrinter* boardPrinter;
	Coordinate boardStartPosition = { 1, 1 };
	Coordinate promptStartPosition = { 1, 4 * 8 + 1 + 2 };

public:
	ChessBoard();
	void PrintState();
	bool Move(int xCoordinate, int yCoordinate, int newCharacter);

private:
	void InitializeBoard();
	char** CreateCleanBoard();
	bool IsLegalMove(int xCoordinate, int yCoordinate, int newCharacter);
	bool isBlackPiece(int xCoordinate, int yCoordinate);
	bool isWhitePiece(int xCoordinate, int yCoordinate);
	bool isEmpty(int xCoordinate, int yCoordinate);
	bool isWhiteSquare(int xCoordinate, int yCoordinate);
};