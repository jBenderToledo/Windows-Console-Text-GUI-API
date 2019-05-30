#pragma once
#include <Windows.h>
#include <conio.h>

namespace Screen
{
	// Turning cursor on/off
	void turnOffCursor()
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;

		SetConsoleCursorInfo(h, &info);
	}
	void turnOnCursor()
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = TRUE;

		SetConsoleCursorInfo(h, &info);
	}

	// Functions concerning coordinates on the screen
	void gotoXY(short x, short y) // Sets screen coordinates to (x,y) by classic c-style shenanigans
	{
		HANDLE h; COORD c;
		fflush(stdout);

		c.X = x; c.Y = y;

		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
	}
	void writeAtXY(short x, short y, char c)
	{
		gotoXY(x, y);
		putchar(c);
	}
	void writeSeries(short xArr[], short yArr[], char chArr[], int numberOfBytes)
	{
		for (int i = 0; i < numberOfBytes; i++)
			writeAtXY(xArr[i], yArr[i], chArr[i]);
	}
};