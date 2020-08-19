#include "pch.h"

#include "ChessBoard.h"

int main()
{
	ChessBoard PlayChess = ChessBoard();

	PlayChess.PrintState();

	std::cout << "\n\nSuccess!\n\n";

	char exitInput;
	std::cin >> exitInput;
};
