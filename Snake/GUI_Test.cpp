#include "pch.h"

#include "ChessBoard.h"

int main()
{
	ChessBoard PlayChess = ChessBoard();

	PlayChess.PrintState();

	std::cout << "Success!\n\n";

	char exitInput;
	exitInput = _getch();

	PlayChess.ILLEGAL_ForceMove({ 0,7 }, { 4,3 });

	std::cout << "Psych!! Get dunked on, NERD! Re5!\n\n";
	exitInput = _getch();
};
