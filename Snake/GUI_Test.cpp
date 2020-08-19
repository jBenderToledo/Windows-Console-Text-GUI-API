#include "pch.h"

#include "ChessBoard.h"
#include "GUI_Test.h"

int main()
{
	using namespace GUI_Test;

	TestChessBoard();

	system("cls");

	TestTicTacToe();
};

void GUI_Test::TestChessBoard()
{
	ChessBoard PlayChess = ChessBoard();

	PlayChess.PrintState();

	std::cout << "Success!\n\n";

	char exitInput;
	exitInput = _getch();

	PlayChess.ILLEGAL_ForceMove({ 0,7 }, { 4,3 });

	std::cout << "Psych!! Get dunked on, NERD! Re5!\n\n";
	exitInput = _getch();
}

void GUI_Test::TestTicTacToe()
{

}