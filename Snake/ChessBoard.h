#pragma once
#include "pch.h"

#include "MatrixPrinter.h"

using namespace Screen;

class ChessBoard
{
	static const unsigned char BLACK_SQUARE = ' ';
	static const unsigned char WHITE_SQUARE = 0xB2;

	// white perspective
	const char INITIAL_STATE[8][9] = { 
		"rnbqkbnr",
		"pppppppp",
		"        ",
		"        ",
		"        ",
		"        ",
		"PPPPPPPP",
		"RNBQKBNR"
	};

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
	char GetPieceAt(int xCoordinate, int yCoordinate);

private:
	void InitializeBoard();
	char** CreateCleanBoard();
	bool IsLegalMove(int xCoordinate, int yCoordinate, int newCharacter);
	bool IsBlackPiece(int xCoordinate, int yCoordinate);
	bool IsWhitePiece(int xCoordinate, int yCoordinate);
	bool IsSquareEmpty(int xCoordinate, int yCoordinate);
	bool IsWhiteSquare(int xCoordinate, int yCoordinate);
};