#pragma once
#include "pch.h"

#include "ConsoleIO.h"

using namespace Screen;

class ChessBoard
{
	static const char BLACK_SQUARE = ' ';
	static const char WHITE_SQUARE = 0xB2;

	char boardState[64] = { 0 };
	char outputBuffer[256] = { 0 };

public:
	ChessBoard();
	void PrintState();

private:

}