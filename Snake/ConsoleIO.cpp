#include "pch.h"
#include "ConsoleIO.h"

using namespace Screen;

void ConsoleIO::TurnOffCursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;

	SetConsoleCursorInfo(h, &info);
}

void ConsoleIO::TurnOnCursor() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = TRUE;

	SetConsoleCursorInfo(h, &info);
}

void ConsoleIO::GotoXY(Coordinate position) {
	HANDLE h; _COORD c;
	fflush(stdout);

	c.X = position.x; c.Y = position.y;

	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}