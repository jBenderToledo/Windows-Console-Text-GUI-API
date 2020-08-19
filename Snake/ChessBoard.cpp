#pragma once
#include "pch.h"

#include "ChessBoard.h"
#include "MatrixPrinter.h"

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
	boardPrinter->WriteAllToScreen(boardStartPosition);
}

char ChessBoard::GetPieceAt(int xCoordinate, int yCoordinate)
{
	return boardState[yCoordinate][xCoordinate];
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
			currentRow[x] = IsWhiteSquare(x, y) ? WHITE_SQUARE : BLACK_SQUARE;
		}
	}

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			buffer[4 * y + 2][4 * y + 2] = GetPieceAt(x,y);
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

bool ChessBoard::IsEmpty(int xCoordinate, int yCoordinate)
{
	return !IsBlackPiece(xCoordinate, yCoordinate)
		&& !IsWhitePiece(xCoordinate, yCoordinate);
}

bool ChessBoard::IsWhiteSquare(int xCoordinate, int yCoordinate) {
	return ((xCoordinate & 7) >= 4) ^ ((yCoordinate & 7) >= 4);
}
