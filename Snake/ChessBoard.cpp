#pragma once
#include "pch.h"

#include "ChessBoard.h"
#include "MatrixPrinter.h"

ChessBoard::ChessBoard()
{
	InitializeBoard();

	boardPrinter = new Screen::MatrixPrinter(
		CreateCleanBoard(),
		3 * 8,
		3 * 8,
		Coordinate(1, 1)
	);
}

void ChessBoard::PrintState()
{
	boardPrinter->WriteAllToScreen();

	ConsoleIO::GotoXY(promptStartPosition);
}

bool ChessBoard::ILLEGAL_ForceMove(Coordinate piecePosition, Coordinate newPiecePosition)
{
	int x0 = piecePosition.x, x1 = newPiecePosition.x, y0 = piecePosition.y, y1 = newPiecePosition.y;

	boardState[y1][x1] = boardState[y0][x0];
	boardPrinter->Edit(3*x1 + 1, 3*y1 + 1, boardState[y1][x1]);

	boardState[y0][x0] = IsWhiteSquare(3*x0+1, 3*y0+1) ? WHITE_SQUARE : BLACK_SQUARE;
	boardPrinter->Edit(3*x0 + 1, 3*y0 + 1, boardState[y0][x0]);

	ConsoleIO::GotoXY(promptStartPosition);

	return true;
}

char ChessBoard::GetPieceAt(int xCoordinate, int yCoordinate)
{
	return boardState[yCoordinate][xCoordinate];
}

void ChessBoard::InitializeBoard()
{
	for (int i = 0; i < 8; i++) {
		boardState[i][9] = 0;

		strcpy_s(boardState[i], sizeof(boardState[i]), (const char*) INITIAL_STATE[i]);
	}
}

char** ChessBoard::CreateCleanBoard()
{
	char** buffer = new char*[24];
	char* currentRow;

	for (int y = 0; y < 24; y++) {
		buffer[y] = new char[25]{ 0 };
		currentRow = buffer[y];

		for (int x = 0; x < 24; x++) {
			currentRow[x] = IsWhiteSquare(x, y) ? WHITE_SQUARE : BLACK_SQUARE;
		}
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			if (!IsSquareEmpty(x, y)) {
				buffer[3 * y + 1][3 * x + 1] = GetPieceAt(x, y);
			}
		}
	}


	return buffer;
}

bool ChessBoard::IsBlackPiece(int xCoordinate, int yCoordinate) {
	char piece = GetPieceAt(xCoordinate, yCoordinate);

	return 'a' <= piece && piece <= 'z';
}

bool ChessBoard::IsWhitePiece(int xCoordinate, int yCoordinate) {
	char piece = GetPieceAt(xCoordinate, yCoordinate);

	return 'A' <= piece && piece <= 'Z';
}

bool ChessBoard::IsSquareEmpty(int xCoordinate, int yCoordinate)
{
	return !IsBlackPiece(xCoordinate, yCoordinate)
		&& !IsWhitePiece(xCoordinate, yCoordinate);
}

bool ChessBoard::IsWhiteSquare(int xCoordinate, int yCoordinate) {
	return ((xCoordinate % 6) >= 3) ^ ((yCoordinate % 6) >= 3);
}
