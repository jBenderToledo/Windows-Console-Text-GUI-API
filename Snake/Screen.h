#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>

namespace Screen
{
	// Used mainly for console io. Makes function inputs much faster!
	struct Coordinate
	{
		short x = 0, y = 0;

		static bool operator==(Coordinate a, Coordinate b)
		{
			return (a.x == b.x && a.y == b.y);
		}

		Coordinate operator=(Coordinate b)
		{
			x += b.x;
			y += b.y;
			return { x,y };
		}
	};

	const Coordinate ORIGIN = { 0,0 };

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
	void gotoXY(Coordinate coord) // Sets screen coordinates to the coordinate passed.
	{
		HANDLE h; _COORD c;
		fflush(stdout);

		c.X = coord.x; c.Y = coord.y;

		h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
	}

	void resetScreen()
	{
		system("cls");
		gotoXY(ORIGIN);
	}

	// Force screen size in pixels
	void changeScreenSize(short x, short y)
	{
		HWND consoleWindow = GetConsoleWindow();
		RECT screenPosition;
		GetWindowRect(consoleWindow, &screenPosition);

		resetScreen();
		MoveWindow(consoleWindow, screenPosition.left, screenPosition.top, x, y, TRUE);
	}

	void writeAtXY(Coordinate coord, char c)
	{
		gotoXY(coord);
		putchar(c);
	}
	void writeSeries(Coordinate coordArr[], char chArr[], int numberOfBytes)
	{
		for (int i = 0; i < numberOfBytes; i++)
			writeAtXY(coordArr[i], chArr[i]);
	}
};