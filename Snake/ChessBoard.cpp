#pragma once
#include "pch.h"

#include "ChessBoard.h"

ChessBoard::ChessBoard()
{
	InitializeBoard();

	boardPrinter = new Screen::MatrixPrinter(
		CreateCleanBoard(),
		4 * 8 + 1,
		4 * 8 + 1
	);
}

void ChessBoard::PrintState()
{
	boardPrinter->WriteToScreen(boardStartPosition);
}

void ChessBoard::InitializeBoard()
{
	for (int i = 0; i < 8; i++) {
		strcpy_s(boardState[i], 8, INITIAL_STATE[i]);
	}
}

char** ChessBoard::CreateCleanBoard()
{
	char** buffer = new char*[32];
	char* currentRow;

	for (int y = 0; y < 32; y++) {
		buffer[y] = new char[32];
		currentRow = buffer[y];

		for (int x = 0; x < 32; x++) {
			currentRow[x] = isWhitePiece(x, y) ? WHITE_SQUARE : BLACK_SQUARE;
		}
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			buffer[4 * y + 2][4 * y + 2] = boardState[y][x];
		}
	}


	return buffer;
}

bool ChessBoard::isWhitePiece(int xCoordinate, int yCoordinate) {
	char piece = boardState[yCoordinate][xCoordinate];

	return 'A' <= piece && piece <= 'Z';
}

bool ChessBoard::isEmpty(int xCoordinate, int yCoordinate)
{
	return !isBlackPiece(xCoordinate, yCoordinate)
		&& !isWhitePiece(xCoordinate, yCoordinate);
}

bool ChessBoard::isWhiteSquare(int xCoordinate, int yCoordinate) {
	return ((xCoordinate & 7) >= 4) ^ ((yCoordinate & 7) >= 4);
}
