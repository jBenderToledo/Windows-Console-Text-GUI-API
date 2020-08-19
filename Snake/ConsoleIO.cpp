#include "pch.h"
#include "ConsoleIO.h"

using namespace Screen;

void ConsoleIO::TurnOffCursor() {
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;

	SetConsoleCursorInfo(stdHandle, &info);
}

void ConsoleIO::TurnOnCursor() {
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;

	SetConsoleCursorInfo(stdHandle, &info);
}

void ConsoleIO::GotoXY(Coordinate position) {
	HANDLE stdHandle; _COORD stdCoordinate;
	fflush(stdout);

	stdCoordinate.X = position.x; stdCoordinate.Y = position.y;

	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(stdHandle, stdCoordinate);
}

void ConsoleIO::writeToXY(Coordinate position, unsigned char c)
{
	ConsoleIO::GotoXY(position);
	putchar(c);
}